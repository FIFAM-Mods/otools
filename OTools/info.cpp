#include "main.h"
#include <fstream>
#include <iostream>
#include "shaders.h"

map<string, set<string>> m;
map<string, set<int>> v;
set<string> ss;

class analyzer {
    string mResult;
    unsigned int mCurrentSpacing = 0;
    bool mJustOpened = true;
    bool mJustClosed = false;

    struct FileSymbol : public Elf32_Sym {
        unsigned int id = 0;
        string name;
    };

    bool compareCommands(unsigned int a, unsigned int b) {
        if ((a == 31 || a == 46) && (b == 31 || b == 46))
            return true;
        return a == b;
    }

    struct vector3 { float x, y, z; };
    struct vector4 { float x, y, z, w; };
    struct Matrix4x4 { vector4 vec1, vec2, vec3, posn; };
    struct BBOX { vector3 min, max; };

    struct ModifiableData {
        char *mName;
        unsigned short mEntrySize;
        unsigned short unknown;
        unsigned int mEntriesCount;
        void *mEntries;
    };

    struct Model {
        ModifiableData *mModifiableData;
        unsigned int mNumModifiableDatas;
        unsigned int mNumVariations;
        Matrix4x4 mTransform;
        vector4 field_4C;
        vector4 field_5C;
        vector4 mBoundMin;
        vector4 mBoundMax;
        vector4 mCenter;
        unsigned int mNumLayers;
        char const **mLayerNames;
        unsigned int field_A4;
        Model *field_A8;
        Model *field_AC;
        Model *mNext;
        char const *mName;
        void *mMorphVertexInfo;
        void *mTextures;
        unsigned int mVariationID;
        void *mLayersStates;
        unsigned int mIsRenderable;
        void *mLayers;
        unsigned int field_D0;
        unsigned int field_D4;
        unsigned int mSkeletonVersion;
        unsigned int mLastPresentCall;
    };

    struct RenderMethod {
        unsigned char *mCodeBlock;
        unsigned char **mCodeToUse;
        void *mMicroCode;
        void *mETTObject;
        RenderMethod *mParent;
        char const **mpParameterNames;
        unsigned int field_18;
        int field_1C;
        RenderMethod *field_20;
        void *mGeoPrimDataBuffer;
        int mComputationIndexCommand;
        char const *mShaderName;
        void *mEAGLModel;
    };

    struct GeometryInfo {
        unsigned int mNumIndices;
        unsigned int mNumVertices;
        unsigned int mNumPrimitives;
        unsigned int unknown;
    };

    struct Bone {
        unsigned int mIndex;
        unsigned int unknown1;
        unsigned int unknown2;
        unsigned int unknown3;
    };

    struct BoneState {
        vector3 unknown1;
        int mParentBoneId;
        vector4 unknown2;
        float unknown3;
        float unknown4;
        float unknown5;
        float unknown6;
        Matrix4x4 mInvBaseTransform;
    };

    struct Skeleton {
        unsigned short mSignature1;
        unsigned short unknown1;
        unsigned int mSignature2;
        unsigned int mNumBones;
        void *unknown2;
    };

    struct Buffer {
        enum Type {
            NotSet, Vertex, Index, VertexSkin, Matrix
        };
        Type type = NotSet;
        void *data = nullptr;
        unsigned int length = 0;
        unsigned int stride = 0;
    };

    struct Accessor {
        unsigned int componentType = 0;
        unsigned int count = 0;
        string type;
        unsigned int buffer = 0;
        unsigned int length = 0;
        unsigned int offset = 0;
        unsigned int stride = 0;
        Buffer::Type bufferType;
    };

    struct VertexSkinDataPacked {
        vector3 packedData;
        unsigned int padding;
    };

    struct VertexSkinData {
        unsigned char indices[4];
        vector4 weights;
    };

    struct Texture {
        unsigned int unknown1;
        char tag[4];
        unsigned int unknown2;
        float unknown3;
        float unknown4;
        unsigned int unknown5;
        unsigned int wrapU;
        unsigned int wrapV;
        unsigned int wrapW;
        unsigned int unknown6;
        unsigned int unknown7;
    };

    struct Material {
        unsigned int id = 0;
        string shader;
        int textures[3] = { -1, -1, -1 };
        bool doubleSided = false;
        string alphaMode;
        float alphaCutoff = 0.0f;
    };

    struct TexDesc {
        unsigned int symbolId;
        Texture *pTex;
        string name;
        string source;
        unsigned int wrapU = 33071;
        unsigned int wrapV = 33071;
        unsigned int minFilter = 9729;
        unsigned int magFilter = 9729;
    };

    struct GeoPrimState {
        unsigned int nPrimitiveType;
        unsigned int nShading;
        unsigned int bCullEnable;
        unsigned int nCullDirection;
        unsigned int nDepthTestMetod;
        unsigned int nAlphaBlendMode;
        unsigned int bAlphaTestEnable;
        unsigned int nAlphaCompareValue;
        unsigned int nAlphaTestMethod;
        unsigned int bTextureEnable;
        unsigned int nTransparencyMethod;
        unsigned int nFillMode;
        unsigned int nBlendOperation;
        unsigned int nSrcBlend;
        unsigned int nDstBlend;
        float fNumPatchSegments;
        int nZWritesEnable;
    };
public:
    void convert_o_to_gltf(unsigned char *fileData, unsigned int fileDataSize, path const &outPath) {
        Target *target = globalVars().target;
        if (!target)
            throw runtime_error("Unknown target");
        string filename = outPath.filename().string();
        unsigned char *data = nullptr;
        unsigned int dataSize = 0;
        Elf32_Sym *symbolsData = nullptr;
        unsigned int numSymbols = 0;
        Elf32_Rel *rel = nullptr;
        unsigned int numRelocations = 0;
        char *symbolNames = nullptr;
        unsigned int symbolNamesSize = 0;
        unsigned int dataIndex = 0;

        Elf32_Ehdr *h = (Elf32_Ehdr *)fileData;
        Elf32_Shdr *s = At<Elf32_Shdr>(h, h->e_shoff);
        for (unsigned int i = 0; i < h->e_shnum; i++) {
            if (s[i].sh_size > 0) {
                if (s[i].sh_type == 1) {
                    data = At<unsigned char>(h, s[i].sh_offset);
                    dataSize = s[i].sh_size;
                    dataIndex = i;
                }
                else if (s[i].sh_type == 2) {
                    symbolsData = At<Elf32_Sym>(h, s[i].sh_offset);
                    numSymbols = s[i].sh_size / 16;
                }
                else if (s[i].sh_type == 3) {
                    symbolNames = At<char>(h, s[i].sh_offset);
                    symbolNamesSize = s[i].sh_size;
                }
                else if (s[i].sh_type == 9) {
                    rel = At<Elf32_Rel>(h, s[i].sh_offset);
                    numRelocations = s[i].sh_size / 8;
                }
            }
        }

        // get symbols

        vector<FileSymbol> symbols;

        symbols.resize(numSymbols);

        for (unsigned int i = 0; i < numSymbols; i++) {
            symbols[i].st_info = symbolsData[i].st_info;
            symbols[i].st_name = symbolsData[i].st_name;
            symbols[i].st_other = symbolsData[i].st_other;
            symbols[i].st_shndx = symbolsData[i].st_shndx;
            symbols[i].st_size = symbolsData[i].st_size;
            symbols[i].st_value = symbolsData[i].st_value;
            symbols[i].name = &symbolNames[symbolsData[i].st_name];
            symbols[i].id = i;
        }

        auto isSymbolDataPresent = [&](FileSymbol const &s) {
            return (s.st_info & 0xF) != 0 && s.st_shndx == dataIndex;
        };

        // get relocation symbols

        map<unsigned int, FileSymbol> symbolRelocations;

        for (unsigned int i = 0; i < numRelocations; i++) {
            if (rel[i].r_info_sym < symbols.size())
                symbolRelocations[rel[i].r_offset] = symbols[rel[i].r_info_sym];
        }

        // do relocations

        for (unsigned int i = 0; i < numRelocations; i++) {
            auto symbolId = rel[i].r_info_sym;
            if (symbolId < numSymbols && isSymbolDataPresent(symbols[symbolId]))
                SetAt(data, rel[i].r_offset, &data[GetAt<unsigned int>(data, rel[i].r_offset)]);
        }

        // find model

        vector<Model *> models;
        vector<RenderMethod *> renderMethods;
        vector<void *> geoPrimDataBuffers;
        Skeleton *skeleton = nullptr;
        vector<Bone *> bones;
        vector<string> boneNames;
        vector<VertexSkinData *> vertexSkinBuffers;
        Matrix4x4 *skinMatrices = nullptr;
        vector<Material> materials;
        vector<TexDesc> textures;

        for (auto const &s : symbols) {
            if (isSymbolDataPresent(s)) {
                if (s.name.starts_with("__Model:::"))
                    models.push_back(At<Model>(data, s.st_value));
                else if (s.name.starts_with("__RenderMethod:::"))
                    renderMethods.push_back(At<RenderMethod>(data, s.st_value));
                else if (s.name.starts_with("__geoprimdatabuffer"))
                    geoPrimDataBuffers.push_back(At<void>(data, s.st_value));
                else if (s.name.starts_with("__Bone:::")) {
                    bones.push_back(At<Bone>(data, s.st_value));
                    string boneName = s.name.substr(9);
                    auto dotPos = boneName.find_last_of('.');
                    if (dotPos != string::npos)
                        boneName = boneName.substr(dotPos + 1);
                    boneNames.push_back(boneName);
                }
                else if (s.name.starts_with("__Skeleton:::")) {
                    if (!skeleton)
                        skeleton = At<Skeleton>(data, s.st_value);
                }
            }
        }

        // TODO: validate skeleton

        if (skeleton && skeleton->mNumBones != bones.size())
            skeleton = nullptr;

        // TODO: validate RMs and GPBs

        Model *model = nullptr;

        if (!models.empty()) {
            if (models.size() != 1)
                sort(models.begin(), models.end(), [](Model *a, Model *b) { return a->mVariationID <= b->mVariationID; });
            model = models[0];
        }

        if (model) {
            if (model->mNumLayers && model->mLayers) {
                unsigned int *modelLayers = (unsigned int *)(model->mLayers);
                modelLayers++;
                for (unsigned int i = 0; i < model->mNumLayers; i++) {
                    unsigned int numPrimitives = *modelLayers;
                    modelLayers++;
                    for (unsigned int p = 0; p < numPrimitives; p++) {
                        void *renderDescriptor = GetAt<void *>(modelLayers, p * 4);
                        RenderMethod *renderMethod = GetAt<RenderMethod *>(renderDescriptor, 0);
                        void *globalParameters = At<void *>(renderDescriptor, 4);
                        Shader *shader = nullptr;
                        unsigned int rmCodeOffset = At<unsigned char>(renderMethod, 8) - data;
                        auto it = symbolRelocations.find(rmCodeOffset);
                        if (it != symbolRelocations.end() && (*it).second.st_info == 0x10) {
                            string codeName = (*it).second.name;
                            if (codeName.ends_with("__EAGLMicroCode")) {
                                auto shaderName = codeName.substr(0, codeName.length() - 15);
                                // find texture reference and geoprimstate reference in the code (external only)
                                // todo check internal TAR
                                shader = target->FindShader(shaderName);
                                if (shader && shader->numTechniques) {
                                    //if (false && !v[shaderName].contains(renderMethod->mComputationIndexCommand)) {
                                    //    cout << shaderName << "," << renderMethod->mComputationIndexCommand << "," << filename << endl;
                                    //    v[shaderName].insert(renderMethod->mComputationIndexCommand);
                                    //}
                                    void *renderCode = GetAt<void *>(renderMethod, 0);
                                    unsigned int numCommands = 0;
                                    unsigned int commandOffset = 0;
                                    unsigned short id = GetAt<unsigned short>(renderCode, commandOffset + 2);
                                    unsigned short size = GetAt<unsigned short>(renderCode, commandOffset);
                                    unsigned char maxColorValue = 0;
                                    int colorOffset = -1;
                                    unsigned int currentOffset = 0;
                                    for (auto const &d : shader->declaration) {
                                        if (d.type == Shader::Color0) {
                                            colorOffset = currentOffset;
                                            break;
                                        }
                                        currentOffset += d.Size();
                                    }
                                    while (id != 0) {
                                        switch (id) {
                                        case 4:
                                        case 75:
                                        {
                                            auto vertexBuffer = GetAt<void *>(globalParameters, 4);
                                            auto numVertices = GetAt<unsigned int>(globalParameters, 0);
                                            auto vertexSize = GetAt<unsigned int>(renderCode, commandOffset + 8);
                                            if (colorOffset != 1) {
                                                unsigned char *clr = (unsigned char *)(unsigned int(vertexBuffer) + colorOffset);
                                                for (unsigned int vert = 0; vert < numVertices; vert++) {
                                                    unsigned char maxClr = clr[0];
                                                    if (maxClr < clr[1])
                                                        maxClr = clr[1];
                                                    if (maxClr < clr[2])
                                                        maxClr = clr[2];
                                                    if (globalVars().maxColorValue[shader->name].first < maxClr) {
                                                        globalVars().maxColorValue[shader->name].first = maxClr;
                                                        globalVars().maxColorValue[shader->name].second = filename;
                                                    }
                                                    clr = (unsigned char *)(unsigned int(clr) + vertexSize);
                                                }
                                            }
                                        }
                                        break;
                                        //case 33:
                                        //    if (!GetAt<GeoPrimState *>(globalParameters, 4)) {
                                        //        //it = symbolRelocations.find(unsigned int(At<GeoPrimState *>(globalParameters, 4)) - unsigned int(data));
                                        //        //if (it != symbolRelocations.end() && (*it).second.st_info == 0x10) {
                                        //        //    string format = (*it).second.name;
                                        //        //    string newFormat = format;
                                        //        //    auto idPos = newFormat.find("UID=");
                                        //        //    if (idPos != string::npos) {
                                        //        //        auto semiColonPos = newFormat.find(';', idPos + 4);
                                        //        //        if (semiColonPos != string::npos) {
                                        //        //            string idstr = newFormat.substr(idPos, semiColonPos - idPos);
                                        //        //            if (!m[idstr].contains(filename)) {
                                        //        //                cout << idstr << "," << filename << endl;
                                        //        //                m[idstr].insert(filename);
                                        //        //            }
                                        //        //        }  
                                        //        //    }
                                        //        //}
                                        //
                                        //    }
                                        //    else {
                                        //        if (!ss.contains(shaderName)) {
                                        //            cout << shaderName << " in " << filename << " at " << (unsigned int(At<GeoPrimState *>(globalParameters, 4)) - unsigned int(data)) << endl;
                                        //            ss.insert(shaderName);
                                        //        }
                                        //    }
                                        //    break;
                                        case 9:
                                        case 32:
                                            if (!GetAt<GeoPrimState *>(globalParameters, 4)) {
                                                //it = symbolRelocations.find(unsigned int(At<GeoPrimState *>(globalParameters, 4)) - unsigned int(data));
                                                //if (it != symbolRelocations.end() && (*it).second.st_info == 0x10) {
                                                //    string format = (*it).second.name;
                                                //    string newFormat = format;
                                                //    auto idPos = newFormat.find("UID=");
                                                //    if (idPos != string::npos) {
                                                //        auto semiColonPos = newFormat.find(';', idPos + 4);
                                                //        if (semiColonPos != string::npos)
                                                //            newFormat.erase(idPos, semiColonPos - idPos + 1);
                                                //    }
                                                //    string shapename;
                                                //    auto shapenamePos = newFormat.find("SHAPENAME=");
                                                //    if (shapenamePos != string::npos) {
                                                //        auto semiColonPos = newFormat.find(';', shapenamePos + 10);
                                                //        if (semiColonPos != string::npos) {
                                                //            shapename = newFormat.substr(shapenamePos, semiColonPos - shapenamePos);
                                                //            newFormat.erase(shapenamePos, semiColonPos - shapenamePos + 1);
                                                //        }
                                                //    }
                                                //    if (!m[shaderName].contains(newFormat)) {
                                                //        cout << shaderName << ": " << newFormat << " in " << outPath.filename().string() << " (" << shapename << ")" << endl;
                                                //        m[shaderName].insert(newFormat);
                                                //    }
                                                //}
                                            }
                                            else {
                                                if (!ss.contains(shaderName)) {
                                                    cout << shaderName << endl;
                                                    ss.insert(shaderName);
                                                }
                                            }
                                            break;
                                        }
                                        if (numCommands != 0)
                                            globalParameters = At<void *>(globalParameters, 8);
                                        numCommands++;
                                        commandOffset += size * 4;
                                        id = GetAt<unsigned short>(renderCode, commandOffset + 2);
                                        size = GetAt<unsigned short>(renderCode, commandOffset);
                                    }
                                }
                                else {
                                    if (!ss.contains(shaderName)) {
                                        cout << "Shader not found: " << shaderName << endl;
                                        ss.insert(shaderName);
                                    }
                                }
                            }
                        }
                    }
                    modelLayers += numPrimitives;
                }
            }
            if (false && model && model->mTextures) {
                void *texDesc = model->mTextures;
                char const *texName = GetAt<char const *>(texDesc, 0);
                while (texName) { // TODO: replace with IsValidOffset()
                    void **pTexTar = At<void *>(texDesc, 8);
                    Texture *tar = (Texture *)(*pTexTar);
                    if (tar) {

                        //Error(Utils::Format(L"%d %d %d", tar->wrapU, tar->wrapV, tar->wrapW));
                    }
                    else {
                        unsigned int tarOffset = unsigned int(pTexTar) - unsigned int(data);
                        auto it = symbolRelocations.find(tarOffset);
                        if (it != symbolRelocations.end()) {
                            auto const &s = (*it).second;
                            //Error(s.name);
                        }
                    }
                    unsigned int texCount = GetAt<unsigned int>(texDesc, 4);
                    if (texCount != 1)
                        cout << filename << " " << texCount << endl;
                    unsigned int texSize = texCount * 4;
                    unsigned short info = GetAt<unsigned int>(texDesc, 8 + texSize);
                    if (info == 1)
                        texDesc = At<void>(texDesc, 12 + texSize);
                    else
                        texDesc = At<void>(texDesc, 8 + texSize);
                    texName = GetAt<char const *>(texDesc, 0);
                }
            }
        }

        for (auto const &v : vertexSkinBuffers)
            delete[] v;
        delete[] skinMatrices;
    }

    void convert_o_to_gltf(path const &inPath, path const &outPath) {
        auto fileData = readofile(inPath);
        if (fileData.first) {
            convert_o_to_gltf(fileData.first, fileData.second, outPath);
            delete[] fileData.first;
        }
    }
};

void oinfo(path const &out, path const &in) {
    analyzer e;
    e.convert_o_to_gltf(in, out);
}
