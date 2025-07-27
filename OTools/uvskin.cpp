#include "uvskin.h"
#include "main.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\pbrmaterial.h>
#include "delaunator-cpp/include/delaunator.hpp"
#include <fstream>

void gen_uv_set(path const& out, path const& in) {
    if (out.empty())
        UVSkinning::Instance().GenerateSkinSet(in, in.has_parent_path() ? in.parent_path() : current_path());
	else
		UVSkinning::Instance().GenerateSkinSet(in, out);
}

float UVSkinning::UVSkinTexMap::GetWeight(float u, float v) const {
	float intpart = 0.0f;
	if (u < 0.0f || u > 1.0f)
		u = modf(u, &intpart);
	if (v < 0.0f || v > 1.0f)
		v = modf(v, &intpart);
	unsigned int x = (unsigned int)roundf((float)(width - 1) * u);
	unsigned int y = (unsigned int)roundf((float)(height - 1) * v);
	return (float)pixels[y * width + x] / 255.0f;
}

UVSkinning &UVSkinning::Instance() {
	static UVSkinning instance;
	return instance;
}

UVSkinning::UVSkinSet const &UVSkinning::GetSkinSet(path const &folder) {
	if (!uvSkinSets.contains(folder)) {
		UVSkinning::UVSkinSet &skinSet = uvSkinSets[folder];
		for (auto const &i : directory_iterator(folder)) {
			path p = i.path();
			string ext = ToLower(p.extension().string());
			if (ext == ".png" || ext == ".tga" || ext == ".bmp" || ext == ".dds" || ext == ".jpg") {
				IDirect3DTexture9 *texture = nullptr;
				if (FAILED(D3DXCreateTextureFromFileExW(globalVars().device->Interface(), p.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, 1,
					D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, D3DX_FILTER_TRIANGLE, D3DX_FILTER_BOX, 0, NULL, NULL, &texture)))
				{
					throw "UVSkinning::GetSkinSet: failed to read texture";
				}
				D3DSURFACE_DESC desc;
				if (FAILED(texture->GetLevelDesc(0, &desc))) {
					texture->Release();
					throw "UVSkinning::GetSkinSet: failed to retrieve texture data";
				}
				auto &texMap = skinSet[p.stem().string()];
				texMap.width = desc.Width;
				texMap.height = desc.Height;
				texMap.pixels.resize(texMap.width * texMap.height);
				D3DLOCKED_RECT rect;
				if (FAILED(texture->LockRect(0, &rect, NULL, D3DLOCK_READONLY))) {
					texture->Release();
					throw "UVSkinning::GetSkinSet: failed to lock texture";
				}
				struct clr_x8r8g8b8 { unsigned char b, g, r, x; };
				clr_x8r8g8b8 *xrgb = (clr_x8r8g8b8 *)rect.pBits;
				for (unsigned int ip = 0; ip < texMap.pixels.size(); ip++)
					texMap.pixels[ip] = xrgb[ip].r;
				if (FAILED(texture->UnlockRect(0))) {
					texture->Release();
					throw "UVSkinning::GetSkinSet: failed to unlock texture";
				}
				texture->Release();
			}
		}
	}
	return uvSkinSets[folder];
}

void UVSkinning::GenerateSkinSet(path const &modelPath, path const &folder) {
	map<string, vector<UVSkinMesh>> textureCollections;
	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT | aiPrimitiveType_LINE);
	importer.SetPropertyInteger(AI_CONFIG_IMPORT_REMOVE_EMPTY_BONES, 0);
	importer.SetPropertyInteger(AI_CONFIG_PP_SLM_VERTEX_LIMIT, 32'767);
	unsigned int sceneLoadingFlags = aiProcess_Triangulate | aiProcess_GenUVCoords |
		aiProcess_SortByPType | aiProcess_PopulateArmatureData | aiProcess_FlipWindingOrder;
	const aiScene *scene = importer.ReadFile(modelPath.string(), sceneLoadingFlags);
	if (!scene)
		throw runtime_error("UVSkinning: Unable to load scene");
	if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
		throw runtime_error("UVSkinning: Unable to load a complete scene");
	if (!scene->mRootNode)
		throw runtime_error("UVSkinning: Unable to find scene root node");
	for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
		aiMesh *mesh = scene->mMeshes[m];
		if (mesh->mNumVertices == 0 || mesh->mNumFaces == 0)
			continue;
		string texName;
		if (scene->mNumMaterials && mesh->HasTextureCoords(0)) {
			aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
			if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString texPath;
				path texFilePath;
				mat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath, nullptr, nullptr, nullptr, nullptr, nullptr);
				if (auto texture = scene->GetEmbeddedTexture(texPath.C_Str()))
					texFilePath = texture->mFilename.C_Str();
				else
					texFilePath = texPath.C_Str();
				texName = ToLower(texFilePath.stem().string());
			}
		}
		if (!texName.empty() && (options().uvSkinSetGenTextures.empty() || options().uvSkinSetGenTextures.contains(texName))) {
			auto &newMesh = textureCollections[texName].emplace_back();
			newMesh.faces.resize(mesh->mNumFaces);
			for (unsigned int t = 0; t < mesh->mNumFaces; t++) {
				newMesh.faces[t].a = mesh->mFaces[t].mIndices[0];
				newMesh.faces[t].b = mesh->mFaces[t].mIndices[1];
				newMesh.faces[t].c = mesh->mFaces[t].mIndices[2];
			}
			newMesh.verts.resize(mesh->mNumVertices);
			for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
				auto &vert = newMesh.verts[v];
				vert.x = mesh->mTextureCoords[0][v].x;
				vert.y = mesh->mTextureCoords[0][v].y;
				while (vert.x < 0.0f)
					vert.x += 1.0f;
				while (vert.x > 1.0f)
					vert.x -= 1.0f;
				while (vert.y < 0.0f)
					vert.y += 1.0f;
				while (vert.y > 1.0f)
					vert.y -= 1.0f;
				vert.y = vert.y * -1.0f + 1.0f;
			}
			for (unsigned int b = 0; b < mesh->mNumBones; b++) {
				aiBone *bone = mesh->mBones[b];
				string boneName = mesh->mBones[b]->mNode->mName.C_Str();
				auto idbp = boneName.find('[');
				if (idbp != string::npos) {
					boneName = boneName.substr(0, idbp);
					Trim(boneName);
				}
				for (unsigned int w = 0; w < bone->mNumWeights; w++) {
					if (bone->mWeights[w].mWeight > 0.0f)
						newMesh.verts[bone->mWeights[w].mVertexId].bones[boneName] = bone->mWeights[w].mWeight;
				}
			}
		}
	}
	for (auto &[texName, texMeshes] : textureCollections) {
		// for each texture
		set<string> usedBones;
		for (auto const &mesh : texMeshes) {
			for (auto const &vert : mesh.verts) {
				for (auto const &[b, w] : vert.bones)
					usedBones.insert(b);
			}
		}
		// for each used bone in this collection
		for (auto &boneName : usedBones) {
			globalVars().renderer->Begin();
			// for each mesh
			for (auto &mesh : texMeshes) {
				vector<Renderer::Vertex> verts(mesh.verts.size());
				vector<unsigned int> indices(mesh.faces.size() * 3);
				for (unsigned int f = 0; f < mesh.faces.size(); f++) {
					indices[f * 3 + 0] = mesh.faces[f].a;
					indices[f * 3 + 1] = mesh.faces[f].b;
					indices[f * 3 + 2] = mesh.faces[f].c;
				}
				for (unsigned int v = 0; v < mesh.verts.size(); v++) {
					verts[v].x = (float)options().uvSkinSetGenResolutionX * mesh.verts[v].x;
					verts[v].y = (float)options().uvSkinSetGenResolutionY * mesh.verts[v].y;
				}
				for (unsigned int v = 0; v < mesh.verts.size(); v++) {
					if (mesh.verts[v].bones.contains(boneName)) {
						unsigned char colorValue = clamp<unsigned int>((unsigned int)(mesh.verts[v].bones[boneName] * 255.0f), 0, 255);
						verts[v].color = D3DCOLOR_RGBA(colorValue, colorValue, colorValue, 255);
					}
					else
						verts[v].color = D3DCOLOR_RGBA(0, 0, 0, 255);
				} 
				globalVars().renderer->Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
				globalVars().renderer->RenderTriangles(indices.size(), indices.data(), verts.data(), verts.size());
			}
			// save final texture
			path folderPath = folder / texName;
			create_directories(folderPath);
			path savePath = folderPath / (boneName + ".png");
			globalVars().renderer->SaveRT(savePath.c_str());
			globalVars().renderer->End();
			// inpaint final texture
			STARTUPINFOW si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));
			path inpaintPath = GetOToolsDir() / "tools" / "inpaint.exe";
			wstring commandLine = inpaintPath.wstring() + L" -i \"" + savePath.c_str() + L"\" -radius 0";
			WCHAR wargs[2048];
			wcscpy(wargs, commandLine.c_str());
			if (CreateProcessW(inpaintPath.c_str(), wargs, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
		}
	}
}
