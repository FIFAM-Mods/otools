#pragma once
#include <string>
#include <array>
#include <vector>
#include <set>
#include <filesystem>

enum GltfVertexFormat {
	Gltf_Tex0 = 1,
    Gltf_Tex1 = 2,
    Gltf_Tex2 = 4,
	Gltf_Normal = 4,
	Gltf_Color0 = 8,
    Gltf_Color1 = 16,
	Gltf_Skin = 32
};

using GltfVec2 = aiVector2D;
using GltfVec3 = aiVector3D;

struct GltfColor {
    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 255;
    unsigned char a = 255;
};

class GltfVertex {
public:
	GltfVec3 xyz;
	GltfVec3 normal;
	GltfVec2 texCoords;
	GltfVec2 texCoords2;
    GltfVec2 texCoords3;
	GltfColor color;
    GltfColor color2;
	std::array<unsigned short, 8> bones = {};
	std::array<float, 8> weights = {};
};

class GltfMesh {
public:
	unsigned int material;
	unsigned int flags = 0;
	std::vector<GltfVertex> vertices;
	std::vector<unsigned int> indices;
    bool tristrips = false;
};

class GltfNode {
public:
	std::string name;
	std::vector<unsigned int> meshes;

	GltfNode();
	GltfNode(std::string const &_name, unsigned int _numMeshes = 0);
};

class GltfMaterial {
public:
	std::string name;
	bool textured = false;
    unsigned int texture = 0;

	GltfMaterial();
};

class GltfTexture {
public:
    std::string name;
    
};

class GltfBone {
public:
	std::string name;
	std::array<float, 4> rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	std::array<float, 3> translation = { 0.0f, 0.0f, 0.0f };
	std::array<float, 3> scale = { 1.0f, 1.0f, 1.0f };
	std::array<float, 16> inverseBindMatrix = {
	    1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
	    0.0f, 0.0f, 0.0f, 1.0f
	};
	std::string parentName;

	GltfBone();
	GltfBone(std::string const &_name, std::string const &_parentName = std::string());
};

class GltfModel {
public:
	std::vector<GltfNode *> nodes;
    std::vector<GltfMesh *> meshes;
    std::vector<GltfMaterial *> materials;
    std::vector<GltfTexture *> textures;
	std::vector<GltfBone *> bones;
	bool mergeMeshesWithSameMaterial = true;
	bool splitLargeMeshes = true;

	GltfModel();
    ~GltfModel();
	GltfModel(unsigned int _numNodes, unsigned int _numMaterials = 0, unsigned int _numBones = 0);
	GltfModel(std::vector<GltfNode> const &_vecNodes, std::vector<GltfMaterial> const &_vecMaterials, std::vector<GltfBone> const &_vecBones);
	GltfModel(std::vector<GltfNode> const &_vecNodes, std::vector<GltfMaterial> const &_vecMaterials);
	GltfModel(std::vector<GltfNode> const &_vecNodes);
	GltfNode *GetNode(std::string const &name);
	GltfBone *GetBone(std::string const &name);
	GltfMaterial *GetMaterial(std::string const &name);
	void Save(std::filesystem::path const &fileName);
};
