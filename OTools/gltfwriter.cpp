#include "gltfwriter.h"
#include "jsonwriter.h"
#include <map>

GltfVertex::GltfVertex() {}

GltfVertex::GltfVertex(float _x, float _y, float _z) {
	xyz = { _x, _y, _z };
}

GltfVertex::GltfVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u0, float _v0) {
	xyz = { _x, _y, _z };
	normal = { _nx, _ny, _nz };
	texCoords = { _u0, _v0 };
}

GltfVertex::GltfVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u0, float _v0, float _u1, float _v1) {
	xyz = { _x, _y, _z };
	normal = { _nx, _ny, _nz };
	texCoords = { _u0, _v0 };
	texCoords2 = { _u1, _v1 };
}

GltfVertex::GltfVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u0, float _v0, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) {
	xyz = { _x, _y, _z };
	normal = { _nx, _ny, _nz };
	texCoords = { _u0, _v0 };
	rgba = { _r, _g, _b, _a };
}

GltfVertex::GltfVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u0, float _v0, float _u1, float _v1, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) {
	xyz = { _x, _y, _z };
	normal = { _nx, _ny, _nz };
	texCoords = { _u0, _v0 };
	texCoords2 = { _u1, _v1 };
	rgba = { _r, _g, _b, _a };
}

GltfMesh::GltfMesh() {}

GltfMesh::GltfMesh(std::string _materialName, unsigned int _flags, unsigned int _numVertices, unsigned int _numIndices) {
	materialName = _materialName;
	flags = _flags;
	if (_numVertices != 0)
		vertices.resize(_numVertices);
	if (_numIndices != 0)
		indices.resize(_numIndices);
}

GltfNode::GltfNode() {}

GltfNode::GltfNode(std::string const &_name, unsigned int _numMeshes) {
	name = _name;
	if (_numMeshes != 0)
		meshes.resize(_numMeshes);
}

GltfMaterial::GltfMaterial() {}

GltfMaterial::GltfMaterial(std::string _name, std::string _textureName) {
	name = _name;
	textureName = _textureName;
}

GltfBone::GltfBone() {}

GltfBone::GltfBone(std::string const &_name, std::string const &_parentName) {
	name = _name;
	parentName = _parentName;
}

GltfModel::GltfModel() {}

GltfModel::GltfModel(unsigned int _numNodes, unsigned int _numMaterials, unsigned int _numBones) {
	if (_numNodes != 0)
		nodes.resize(_numNodes);
	if (_numMaterials != 0)
		materials.resize(_numMaterials);
	if (_numBones != 0)
		bones.resize(_numBones);
}

GltfModel::GltfModel(std::vector<GltfNode> const &_vecNodes, std::vector<GltfMaterial> const &_vecMaterials, std::vector<GltfBone> const &_vecBones) {
	nodes = _vecNodes;
	materials = _vecMaterials;
	bones = _vecBones;
}

GltfModel::GltfModel(std::vector<GltfNode> const &_vecNodes, std::vector<GltfMaterial> const &_vecMaterials) {
	nodes = _vecNodes;
	materials = _vecMaterials;
}

GltfModel::GltfModel(std::vector<GltfNode> const &_vecNodes) {
	nodes = _vecNodes;
}

GltfNode *GltfModel::GetNode(std::string const &name) {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		if (nodes[i].name == name)
			return &nodes[i];
	}
	return nullptr;
}

GltfBone *GltfModel::GetBone(std::string const &name) {
	for (unsigned int i = 0; i < bones.size(); i++) {
		if (bones[i].name == name)
			return &bones[i];
	}
	return nullptr;
}

GltfMaterial *GltfModel::GetMaterial(std::string const &name) {
	for (unsigned int i = 0; i < materials.size(); i++) {
		if (materials[i].name == name)
			return &materials[i];
	}
	return nullptr;
}

void GltfModel::Save(std::filesystem::path const &fileName) {
	std::map<std::string, unsigned int> boneNameToId;
	unsigned int totalNodes = nodes.size();
	bool hasSkeleton = bones.size() > 0;
	if (hasSkeleton)
		totalNodes += 1;
	JsonWriter j(fileName);
	j.startScope();
	j.openScope("asset");
	j.writeFieldString("generator", string("FM-FIFA GLTF Writer"));
	j.writeFieldString("version", "2.0");
	j.closeScope();
	j.writeFieldInt("scene", 0);
	j.openArray("scenes");
	j.openScope();
	if (totalNodes > 0) {
		j.openArray("nodes");
		for (unsigned int i = 0; i < totalNodes; i++)
			j.writeValueInt(i);
		j.closeArray();
	}
	j.closeScope();
	j.closeArray();
	unsigned int meshCounter = 0;
	unsigned int accessorIndex = 0;
	// Disabled because Assimp doesn't work when IBM are not defined
	//bool hasIBM = true;
	if (totalNodes > 0) {
		j.openArray("nodes");
		for (unsigned int i = 0; i < nodes.size(); i++) {
			j.openScope();
			if (!nodes[i].name.empty())
				j.writeFieldString("name", nodes[i].name);
			unsigned int numMeshes = 0;
			for (unsigned int m = 0; m < nodes[i].meshes.size(); m++) {
				if (nodes[i].meshes[m].vertices.size() > 0 && nodes[i].meshes[m].indices.size() > 0)
					numMeshes++;
			}
			if (numMeshes > 0) {
				j.writeFieldInt("mesh", meshCounter++);
				if (hasSkeleton)
					j.writeFieldInt("skin", 0);
			}
			j.closeScope();
		}
        if (hasSkeleton) {
            struct SkeletonNode {
                SkeletonNode *parent = nullptr;
                vector<SkeletonNode *> children;
                string name;
            };
            j.openScope();
            j.writeFieldString("name", "Skeleton");
            vector<unsigned int> skelRootNodes;
            for (unsigned int i = 0; i < bones.size(); i++) {
                boneNameToId[bones[i].name] = i;
                if (bones[i].parentName.empty())
                    skelRootNodes.push_back(totalNodes + i);
            }
            if (skelRootNodes.size() > 0) {
                j.openArray("children");
                for (unsigned int i = 0; i < skelRootNodes.size(); i++)
                    j.writeValueInt(skelRootNodes[i]);
                j.closeArray();
            }
            j.closeScope();
            for (unsigned int i = 0; i < bones.size(); i++) {
                j.openScope();
                if (!bones[i].name.empty())
                    j.writeFieldString("name", bones[i].name);
                if (bones[i].rotation[0] != 0.0f && bones[i].rotation[1] != 0.0f && bones[i].rotation[2] != 0.0f && bones[i].rotation[3] != 1.0f) {
                    j.openArray("rotation");
                    j.writeValueFloat(bones[i].rotation[0]);
                    j.writeValueFloat(bones[i].rotation[1]);
                    j.writeValueFloat(bones[i].rotation[2]);
                    j.writeValueFloat(bones[i].rotation[3]);
                    j.closeArray();
                }
                if (bones[i].scale[0] != 1.0f && bones[i].scale[1] != 1.0f && bones[i].scale[2] != 1.0f) {
                    j.openArray("scale");
                    j.writeValueFloat(bones[i].scale[0]);
                    j.writeValueFloat(bones[i].scale[1]);
                    j.writeValueFloat(bones[i].scale[2]);
                    j.closeArray();
                }
                if (bones[i].translation[0] != 0.0f && bones[i].translation[1] != 0.0f && bones[i].translation[2] != 0.0f) {
                    j.openArray("translation");
                    j.writeValueFloat(bones[i].translation[0]);
                    j.writeValueFloat(bones[i].translation[1]);
                    j.writeValueFloat(bones[i].translation[2]);
                    j.closeArray();
                }
                vector<unsigned int> childNodes;
                for (unsigned int b = 0; b < bones.size(); b++) {
                    if (b != i && !bones[b].parentName.empty() && bones[b].parentName == bones[i].name)
                        childNodes.push_back(totalNodes + boneNameToId[bones[b].name]);
                }
                if (childNodes.size() > 0) {
                    j.openArray("children");
                    for (unsigned int c = 0; c < childNodes.size(); c++)
                        j.writeValueInt(childNodes[c]);
                    j.closeArray();
                }
                j.closeScope();
            }
            j.closeArray();
            if (meshCounter > 0) {
                j.openArray("skins");
                j.openScope();
                //for (auto const &b : bones) {
                //	if (b.inverseBindMatrix[0] != 1.0f || b.inverseBindMatrix[1] != 0.0f || b.inverseBindMatrix[2] != 0.0f || b.inverseBindMatrix[3] != 0.0f ||
                //		b.inverseBindMatrix[4] != 0.0f || b.inverseBindMatrix[5] != 1.0f || b.inverseBindMatrix[6] != 0.0f || b.inverseBindMatrix[7] != 0.0f ||
                //		b.inverseBindMatrix[8] != 0.0f || b.inverseBindMatrix[9] != 0.0f || b.inverseBindMatrix[10] != 1.0f || b.inverseBindMatrix[11] != 0.0f ||
                //		b.inverseBindMatrix[12] != 0.0f || b.inverseBindMatrix[13] != 0.0f || b.inverseBindMatrix[14] != 0.0f || b.inverseBindMatrix[15] != 1.0f)
                //	{
                //		hasIBM = true;
                //		break;
                //	}
                //}
                //if (hasIBM) {
                j.writeFieldInt("inverseBindMatrices", 0);
                accessorIndex = 1;
                //}
                j.writeFieldInt("skeleton", nodes.size());
                j.openArray("joints");
                for (unsigned int i = 0; i < bones.size(); i++)
                    j.writeValueInt(totalNodes + i);
                j.closeArray();
                j.closeScope();
                j.closeArray();
            }
        }
        else
            j.closeArray();
	}
	struct MeshInfo {
		GltfMesh *originalMesh = nullptr;
		GltfMesh newMesh;
		unsigned int maxBonesPerVertex = 0;
	};
	vector<vector<MeshInfo>> allNodeMeshes(nodes.size());
	if (meshCounter > 0) {
		j.openArray("meshes");
		for (unsigned int i = 0; i < nodes.size(); i++) {
			auto &nodeMeshes = allNodeMeshes[i];
			for (unsigned int m = 0; m < nodes[i].meshes.size(); m++) {
				auto &mesh = nodes[i].meshes[m];
				if (mesh.vertices.size() > 0 && mesh.indices.size() > 0) {
					bool merged = false;
					if (mergeMeshesWithSameMaterial) {
						for (auto &mi : nodeMeshes) {
							auto checkMesh = mi.originalMesh ? mi.originalMesh : &mi.newMesh;
							if (mesh.materialName == checkMesh->materialName && mesh.flags == checkMesh->flags) {
								if (mi.originalMesh) {
									mi.newMesh = *mi.originalMesh;
									mi.originalMesh = nullptr;
								}
								auto startVertex = mi.newMesh.vertices.size();
								mi.newMesh.vertices.resize(mi.newMesh.vertices.size() + mesh.vertices.size());
								for (unsigned int v = 0; v < mesh.vertices.size(); v++)
									mi.newMesh.vertices[startVertex + v] = mesh.vertices[v];
								auto startIndex = mi.newMesh.indices.size();
								mi.newMesh.indices.resize(mi.newMesh.indices.size() + mesh.indices.size());
								for (unsigned int t = 0; t < mesh.indices.size(); t++)
									mi.newMesh.indices[startIndex + t] = startVertex + mesh.indices[t];
							    merged = true;
							}
						}
					}
					if (!merged) {
						auto &mi = nodeMeshes.emplace_back();
						mi.originalMesh = &mesh;
					}
				}
			}
			if (nodeMeshes.size() > 0) {
				//for (unsigned int m = 0; m < nodeMeshes.size(); m++) {
				//	auto &nodeMesh = nodeMeshes[m];
				//	auto mesh = nodeMeshes[m].originalMesh ? nodeMeshes[m].originalMesh : &nodeMeshes[m].newMesh;
				//	const unsigned int MAX_VERTS_PER_MESH = 32'000;
				//	if (mesh->vertices.size() > MAX_VERTS_PER_MESH) {
				//		unsigned int numMeshSplitParts = mesh->vertices.size() / MAX_VERTS_PER_MESH + 1;
				//		nodeMeshes.insert(nodeMeshes.begin() + m + 1, numMeshSplitParts - 1, MeshInfo());
				//
				//		m += (numMeshSplitParts - 1);
				//	}
				//}
				j.openScope();
				j.openArray("primitives");
				for (unsigned int m = 0; m < nodeMeshes.size(); m++) {
					auto mesh = nodeMeshes[m].originalMesh ? nodeMeshes[m].originalMesh : &nodeMeshes[m].newMesh;
					j.openScope();
					j.openScope("attributes");
					j.writeFieldInt("POSITION", accessorIndex++);
					if (mesh->flags & Gltf_HasNormals)
					    j.writeFieldInt("NORMAL", accessorIndex++);
					if (mesh->flags & Gltf_HasColors)
					    j.writeFieldInt("COLOR_0", accessorIndex++);
					if (mesh->flags & Gltf_Textured)
					    j.writeFieldInt("TEXCOORD_0", accessorIndex++);
					if (mesh->flags & Gltf_SecondTexture)
					    j.writeFieldInt("TEXCOORD_1", accessorIndex++);
					if (hasSkeleton && mesh->flags & Gltf_Skinned) {
						for (unsigned int v = 0; v < mesh->vertices.size(); v++) {
							unsigned int numWeights = 0;
							for (unsigned int w = 0; w < 8; w++) {
								if (mesh->vertices[v].weights[w] == 0.0f)
									break;
								numWeights++;
							}
							if (numWeights > nodeMeshes[m].maxBonesPerVertex)
								nodeMeshes[m].maxBonesPerVertex = numWeights;
						}
						j.writeFieldInt("JOINTS_0", accessorIndex++);
						if (nodeMeshes[m].maxBonesPerVertex > 4)
							j.writeFieldInt("JOINTS_1", accessorIndex++);
						j.writeFieldInt("WEIGHTS_0", accessorIndex++);
						if (nodeMeshes[m].maxBonesPerVertex > 4)
							j.writeFieldInt("WEIGHTS_1", accessorIndex++);
					}
					j.closeScope();
					j.writeFieldInt("indices", accessorIndex++);
					if (!mesh->materialName.empty()) {
						for (unsigned int mtl = 0; mtl < materials.size(); mtl++) {
							if (materials[mtl].name == mesh->materialName) {
								j.writeFieldInt("material", mtl);
								break;
							}
						}
					}
					j.writeFieldInt("mode", 4);
					j.closeScope();
				}
				j.closeArray();
				j.closeScope();
			}
		}
		j.closeArray();
	}
	vector<string> textures;
	if (!materials.empty()) {
		j.openArray("materials");
		for (unsigned int i = 0; i < materials.size(); i++) {
			j.openScope();
			j.writeFieldString("name", materials[i].name);
			j.openScope("pbrMetallicRoughness");
			j.writeFieldFloat("metallicFactor", 0.0f);
			j.writeFieldFloat("roughnessFactor", 1.0f);
			if (!materials[i].textureName.empty()) {
				j.openScope("baseColorTexture");
				j.writeFieldInt("index", textures.size());
				textures.push_back(materials[i].textureName);
				j.closeScope();
			}
			j.closeScope();
			j.closeScope();
		}
		j.closeArray();
	}
	if (!textures.empty()) {
		j.openArray("textures");
		for (unsigned int i = 0; i < textures.size(); i++) {
			j.openScope();
			j.writeFieldString("name", textures[i]);
			j.writeFieldInt("source", i);
			j.closeScope();
		}
		j.closeArray();
		j.openArray("images");
		for (unsigned int i = 0; i < textures.size(); i++) {
			j.openScope();
			j.writeFieldString("name", textures[i]);
			j.writeFieldString("mimeType", "image/png");
			j.writeFieldString("uri", textures[i] + ".png");
			j.closeScope();
		}
		j.closeArray();
	}
	if (meshCounter > 0) {
		j.openArray("accessors");
		accessorIndex = 0;
		auto WriteAccessor = [&](int componentType, int count, string const &type, bool normalized = false, bool usesMinMax = false,
			std::array<float, 3> vecMin = { 0, 0, 0 }, std::array<float, 3> vecMax = { 0, 0, 0 })
		{
			j.openScope();
			j.writeFieldInt("bufferView", accessorIndex++);
			j.writeFieldInt("componentType", componentType);
			j.writeFieldInt("count", count);
			j.writeFieldString("type", type);
			if (normalized)
				j.writeFieldBool("normalized", true);
			if (usesMinMax) {
				j.openArray("min");
				j.writeValueFloat(vecMin[0]);
				j.writeValueFloat(vecMin[1]);
				j.writeValueFloat(vecMin[2]);
				j.closeArray();
				j.openArray("max");
				j.writeValueFloat(vecMax[0]);
				j.writeValueFloat(vecMax[1]);
				j.writeValueFloat(vecMax[2]);
				j.closeArray();
			}
			j.closeScope();
		};
		struct Buffer {
			vector<unsigned char> data;
			bool indexBuffer = false;
		};
		vector<Buffer> buffers;
        if (!bones.empty()) {
		    //if (hasIBM) {
            WriteAccessor(5126, bones.size(), "MAT4");
            auto &b = buffers.emplace_back();
            b.data.resize(bones.size() * 64);
            for (unsigned int i = 0; i < bones.size(); i++)
                memcpy(b.data.data() + i * 64, bones[i].inverseBindMatrix.data(), 64);
            //}
        }
		for (unsigned int i = 0; i < allNodeMeshes.size(); i++) {
			auto &nodeMeshes = allNodeMeshes[i];
			for (unsigned int m = 0; m < nodeMeshes.size(); m++) {
				auto mesh = nodeMeshes[m].originalMesh ? nodeMeshes[m].originalMesh : &nodeMeshes[m].newMesh;
				std::array<float, 3> minPos = { 0.0f, 0.0f, 0.0f };
				std::array<float, 3> maxPos = { 0.0f, 0.0f, 0.0f };
				for (unsigned int v = 0; v < mesh->vertices.size(); v++) {
					if (v == 0) {
						minPos = mesh->vertices[v].xyz;
						maxPos = mesh->vertices[v].xyz;
					}
					else {
						for (unsigned int ip = 0; ip < 3; ip++) {
							if (mesh->vertices[v].xyz[ip] < minPos[ip])
								minPos[ip] = mesh->vertices[v].xyz[ip];
							if (mesh->vertices[v].xyz[ip] > maxPos[ip])
								maxPos[ip] = mesh->vertices[v].xyz[ip];
						}
					}
				}
				WriteAccessor(5126, mesh->vertices.size(), "VEC3", false, true, minPos, maxPos);
				{
					auto &b = buffers.emplace_back();
					b.data.resize(mesh->vertices.size() * 12);
					for (unsigned int v = 0; v < mesh->vertices.size(); v++)
						memcpy(b.data.data() + v * 12, mesh->vertices[v].xyz.data(), 12);
				}
				if (mesh->flags & Gltf_HasNormals) {
					WriteAccessor(5126, mesh->vertices.size(), "VEC3");
					auto &b = buffers.emplace_back();
					b.data.resize(mesh->vertices.size() * 12);
					for (unsigned int v = 0; v < mesh->vertices.size(); v++)
						memcpy(b.data.data() + v * 12, mesh->vertices[v].normal.data(), 12);
				}
				if (mesh->flags & Gltf_HasColors) {
					WriteAccessor(5121, mesh->vertices.size(), "VEC4", true);
					auto &b = buffers.emplace_back();
					b.data.resize(mesh->vertices.size() * 4);
					for (unsigned int v = 0; v < mesh->vertices.size(); v++)
						memcpy(b.data.data() + v * 4, mesh->vertices[v].rgba.data(), 4);
				}
				if (mesh->flags & Gltf_Textured) {
					WriteAccessor(5126, mesh->vertices.size(), "VEC2");
					auto &b = buffers.emplace_back();
					b.data.resize(mesh->vertices.size() * 8);
					for (unsigned int v = 0; v < mesh->vertices.size(); v++)
						memcpy(b.data.data() + v * 8, mesh->vertices[v].texCoords.data(), 8);
				}
				if (mesh->flags & Gltf_SecondTexture) {
					WriteAccessor(5126, mesh->vertices.size(), "VEC2");
					auto &b = buffers.emplace_back();
					b.data.resize(mesh->vertices.size() * 8);
					for (unsigned int v = 0; v < mesh->vertices.size(); v++)
						memcpy(b.data.data() + v * 8, mesh->vertices[v].texCoords2.data(), 8);
				}
				if (hasSkeleton && mesh->flags & Gltf_Skinned) {
					unsigned int boneIndexDataSize = bones.size() > 255 ? 8 : 4;
					WriteAccessor(bones.size() > 255 ? 5123 : 5121, mesh->vertices.size(), "VEC4");
					{
						auto &b = buffers.emplace_back();
						b.data.resize(mesh->vertices.size() * boneIndexDataSize);
						for (unsigned int v = 0; v < mesh->vertices.size(); v++) {
							if (boneIndexDataSize == 8)
							    memcpy(b.data.data() + v * boneIndexDataSize, mesh->vertices[v].bones.data(), boneIndexDataSize);
							else {
								unsigned char bonesData[4];
								for (unsigned int bi = 0; bi < 4; bi++)
									bonesData[bi] = (unsigned char)mesh->vertices[v].bones[bi];
								memcpy(b.data.data() + v * boneIndexDataSize, bonesData, boneIndexDataSize);
							}
						}
					}
					if (nodeMeshes[m].maxBonesPerVertex > 4) {
						WriteAccessor(bones.size() > 255 ? 5123 : 5121, mesh->vertices.size(), "VEC4");
						auto &b = buffers.emplace_back();
						b.data.resize(mesh->vertices.size() * boneIndexDataSize);
						for (unsigned int v = 0; v < mesh->vertices.size(); v++) {
							if (boneIndexDataSize == 8)
								memcpy(b.data.data() + v * boneIndexDataSize, mesh->vertices[v].bones.data() + 4, boneIndexDataSize);
							else {
								unsigned char bonesData[4];
								for (unsigned int bi = 0; bi < 4; bi++)
									bonesData[bi] = (unsigned char)mesh->vertices[v].bones[bi + 4];
								memcpy(b.data.data() + v * boneIndexDataSize, bonesData, boneIndexDataSize);
							}
						}
					}
					WriteAccessor(5126, mesh->vertices.size(), "VEC4");
					{
						auto &b = buffers.emplace_back();
						b.data.resize(mesh->vertices.size() * 16);
						for (unsigned int v = 0; v < mesh->vertices.size(); v++)
							memcpy(b.data.data() + v * 16, mesh->vertices[v].weights.data(), 16);
					}
					if (nodeMeshes[m].maxBonesPerVertex > 4) {
						WriteAccessor(5126, mesh->vertices.size(), "VEC4");
						auto &b = buffers.emplace_back();
						b.data.resize(mesh->vertices.size() * 16);
						for (unsigned int v = 0; v < mesh->vertices.size(); v++)
							memcpy(b.data.data() + v * 16, mesh->vertices[v].weights.data() + 4, 16);
					}
				}
				WriteAccessor(mesh->vertices.size() > 32767 ? 5125 : 5123, mesh->indices.size(), "SCALAR");
				{
					unsigned int indexSize = mesh->vertices.size() > 32767 ? 4 : 2;
					auto &b = buffers.emplace_back();
					b.data.resize(mesh->indices.size() * indexSize);
					if (indexSize == 4)
						memcpy(b.data.data(), mesh->indices.data(), b.data.size());
					else {
						for (unsigned int t = 0; t < mesh->indices.size(); t++) {
							unsigned short indexValue = (unsigned short)mesh->indices[t];
							memcpy(b.data.data() + t * indexSize, &indexValue, indexSize);
						}
					}
					b.indexBuffer = true;
				}
			}
		}
		j.closeArray();
		j.openArray("bufferViews");
		for (unsigned int i = 0; i < buffers.size(); i++) {
			auto const &b = buffers[i];
			j.openScope();
			j.writeFieldInt("buffer", i);
			j.writeFieldInt("byteLength", b.data.size());
			if (b.indexBuffer)
				j.writeFieldInt("target", 34963);
			j.closeScope();
		}
		j.closeArray();
		j.openArray("buffers");
		for (auto const &b : buffers) {
			j.openScope();
			j.writeFieldInt("byteLength", b.data.size());
			j.writeFieldString("uri", "data:application/octet-stream;base64," + j.base64_encode(b.data.data(), b.data.size()));
			j.closeScope();
		}
		j.closeArray();
	}
	j.endScope();
	j.close();
}
