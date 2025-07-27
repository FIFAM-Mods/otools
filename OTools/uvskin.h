#pragma once
#include "D3DInclude.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

void gen_uv_set(path const& out, path const& in);

class UVSkinning {
public:
	struct UVSkinVertex {
		float x = 0.0f;
		float y = 0.0f;
		map<string, float> bones;
	};

	struct UVSkinFace {
		unsigned int a = 0;
		unsigned int b = 0;
		unsigned int c = 0;
		int component = -1;
	};

	struct UVSkinMesh {
		vector<UVSkinFace> faces;
		vector<UVSkinVertex> verts;
	};

	struct UVSkinTexMap {
		unsigned int width = 0;
		unsigned int height = 0;
		vector<unsigned char> pixels;

		float GetWeight(float u, float v) const;
	};

	using UVSkinSet = map<string, UVSkinTexMap>;
	map<path, UVSkinSet> uvSkinSets;

	static UVSkinning &Instance();

	UVSkinSet const &GetSkinSet(path const &folder);

	void GenerateSkinSet(path const &modelPath, path const &folder);
};
