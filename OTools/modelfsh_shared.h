#pragma once
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include "binbuf.h"
#include <assimp/scene.h>

struct Symbol {
    std::string name;
    int offset;

    Symbol(std::string const &_name, int _offset = -1);
};

struct TexEmbedded {
    unsigned int width = 0;
    unsigned int height = 0;
    std::string format;
    void *data = nullptr;
};

struct TextureToAdd {
    std::string name;
    std::string filepath;
    unsigned int format = 0;
    int levels = 0;
    TexEmbedded embedded;

    TextureToAdd();
    TextureToAdd(std::string const &_name, std::string const &_filepath, unsigned int _format, int _levels, TexEmbedded const &_embedded = TexEmbedded());
};

struct StadiumExtra {
    bool used = false;
    unsigned int stadiumId = 0;
    unsigned int lightingId = 0;
    aiNode *flags = nullptr;
    aiNode *effects = nullptr;
    aiNode *collision = nullptr;
    enum FIFA_STAD_TYPE { STAD_DEFAULT, STAD_CUSTOM } stadType = STAD_DEFAULT;
};

struct Tex {
    enum Mode {
        Wrap = 1,
        Mirror = 2,
        Clamp = 3,
        Border = 4,
        ClampToEdge = 5
    };
    enum Filter {
        Point = 1,
        Bilinear = 2,
        Anisotropic = 3,
        GaussianCubic = 5
    };
    enum MipMapMode {
        Off = 0,
        Nearest = 1,
        Linear = 2
    };
    std::string name;
    Mode uAddressing = Wrap;
    Mode vAddressing = Mirror;
    unsigned char anisotropy = 1;
    Filter filtering = Bilinear;
    float mipMapLodBias = 0.0f;
    MipMapMode mipMapMode = Linear;
    unsigned int offset = 0;
    bool isGlobal = false;
    bool runtimeConstructed = true;
    std::string filepath;
    TexEmbedded embedded;

    Tex();
    Tex(std::string const &_name, Mode _u, Mode _v, Filter _filtering, MipMapMode _mipMapMode, float _mipMapLodBias = 0.0f, unsigned char _anisotropy = 1, unsigned int _offset = 0, TexEmbedded const &_embedded = TexEmbedded());
    bool IsRuntimeConstructed() const;
    bool IsFIFAAdboardsTexture() const;
    bool IsFIFACrowdHomeTexture() const;
    bool IsFIFACrowdAwayTexture() const;
    void SetUVAddressingMode(aiTextureMapMode _mode);
    static std::string GetModeName(Mode m);
    static std::string GetFilteringName(Filter f);
    static std::string GetMipMapModeName(MipMapMode m);
    std::string GetRuntimeConstructorLine(unsigned int uid, unsigned int numVariations = 1) const;
};

void WriteFsh(std::filesystem::path const &fshFilePath, std::filesystem::path const &searchDir, std::map<std::string, TextureToAdd> const &texturesToAdd, std::vector<Symbol> *symbols, BinaryBuffer *bufData);
void ProcessTextures(std::string const &modelName, std::string const &targetName, std::filesystem::path const &out, std::filesystem::path const &in, std::map<std::string, Tex> const &textures, StadiumExtra const &stadExtra, std::vector<Symbol> *symbols, BinaryBuffer *bufData);
