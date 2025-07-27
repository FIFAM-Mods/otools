#include "D3DInclude.h"
#include "main.h"
#include "Fsh/Fsh.h"
#include "modelfsh_shared.h"

TextureToAdd::TextureToAdd() {};

TextureToAdd::TextureToAdd(string const &_name, string const &_filepath, unsigned int _format, int _levels, TexEmbedded const &_embedded) {
    name = _name; filepath = _filepath; format = _format; levels = _levels; embedded = _embedded;
}

string get_fsh_extension() {
    string fshExtension = ".fsh";
    if (options().platform == ea::PLATFORM_PSP)
        fshExtension = ".msh";
    return fshExtension;
}

void packfsh_collect(path const &out, path const &in) {
    auto filename = in.stem().string();
    auto texkey = ToLower(filename);
    auto atPos = filename.find('@');
    if (atPos != string::npos) {
        auto &fsh = globalVars().fshToBuild[out.parent_path() / filename.substr(atPos + 1)];
        if (!fsh.contains(texkey)) {
            auto &tex = fsh[texkey];
            tex.name = filename.substr(0, atPos);
            tex.filepath = in.string();
            tex.format = options().fshFormat;
            tex.levels = options().fshLevels;
        }
    }
    else {
        auto &fsh = globalVars().fshToBuild[out.parent_path() / in.parent_path().filename()];
        if (!fsh.contains(texkey)) {
            auto &tex = fsh[texkey];
            tex.name = filename;
            tex.filepath = in.string();
            tex.format = options().fshFormat;
            tex.levels = options().fshLevels;
        }
    }
}

void packfsh_pack() {
    string fshExtension = get_fsh_extension();
    for (auto const &[fshPath, fshImages] : globalVars().fshToBuild) {
        path fshFinalPath;
        if (options().fshWriteToParentDir && fshPath.has_parent_path() && fshPath.parent_path().has_parent_path())
            fshFinalPath = fshPath.parent_path().parent_path() / (fshPath.filename().string() + fshExtension);
        else if (fshPath.has_parent_path())
            fshFinalPath = fshPath.parent_path() / (fshPath.filename().string() + fshExtension);
        else
            fshFinalPath = fshPath / (fshPath.filename().string() + fshExtension);
        WriteFsh(fshFinalPath, fshPath, fshImages, nullptr, nullptr);
    }
}

void unpackfsh(path const &out, path const &in) {
    ea::Fsh fsh;
    fsh.Read(in);
    fsh.ForAllImages([&](ea::FshImage &image) {
        string fshName;
        if (options().fshName)
            fshName = image.GetTag() + "@" + in.stem().string();
        else
            fshName = image.GetTag();
        image.WriteToFile(out.parent_path() / (fshName + "." + options().fshUnpackImageFormat), globalVars().fshUnpackImageFormat);
    });
}

void WriteFsh(path const &fshFilePath, path const &searchDir, map<string, TextureToAdd> const &texturesToAdd, vector<Symbol> *symbols, BinaryBuffer *bufData) {
    static vector<string> imgExt = { ".png", ".jpg", ".jpeg", ".bmp", ".dds", ".tga" };
    path fshDir = fshFilePath.parent_path();
    string fshFileName = fshFilePath.filename().string();
    string targetName = globalVars().target->Name();
    ea::Fsh fsh;
    ea::Buffer metalBinData;
    metalBinData.Allocate(64);
    Memory_Zero(metalBinData.GetData(), metalBinData.GetSize());
    strcpy((char *)metalBinData.GetData(), "EAGL64 metal bin attachment for runtime texture management");
    if (!texturesToAdd.empty()) {
        for (auto const &[k, img] : texturesToAdd) {
            ea::FshImage::LoadingInfo loadingInfo;
            if (img.embedded.data && !options().ignoreEmbeddedTextures) {
                if (img.embedded.height == 0) { // compressed data
                    auto fileFormat = ea::FshImage::DIB;
                    if (img.embedded.format == "png")
                        fileFormat = ea::FshImage::PNG;
                    else if (img.embedded.format == "jpg")
                        fileFormat = ea::FshImage::JPG;
                    else if (img.embedded.format == "bmp")
                        fileFormat = ea::FshImage::BMP;
                    else if (img.embedded.format == "tga")
                        fileFormat = ea::FshImage::TGA;
                    else if (img.embedded.format == "dds")
                        fileFormat = ea::FshImage::DDS;
                    if (fileFormat != ea::FshImage::DIB) {
                        loadingInfo.fileData = img.embedded.data;
                        loadingInfo.fileDataSize = img.embedded.width;
                        loadingInfo.fileFormat = fileFormat;
                    }
                } else { // assimp uncompressed data
                    D3DFORMAT dataFormat = D3DFMT_UNKNOWN;
                    if (img.embedded.format == "rgba8888")
                        dataFormat = D3DFMT_A8R8G8B8;
                    else if (img.embedded.format == "argb8888")
                        dataFormat = D3DFMT_A8B8G8R8;
                    else if (img.embedded.format == "rgba5650")
                        dataFormat = D3DFMT_R5G6B5;
                    else if (img.embedded.format == "rgba0010")
                        dataFormat = D3DFMT_L8;
                    if (dataFormat != D3DFMT_UNKNOWN) {
                        loadingInfo.data = img.embedded.data;
                        loadingInfo.dataWidth = img.embedded.width;
                        loadingInfo.dataHeight = img.embedded.height;
                        loadingInfo.dataFormat = unsigned int(dataFormat);
                    }
                }
            }
            if (!loadingInfo.fileData && !loadingInfo.data) {
                path imgPath = img.filepath;
                auto imgParentDir = imgPath.parent_path();
                auto imgFileName = imgPath.filename().string();
                size_t atPos = string::npos;
                if (options().head)
                    atPos = imgFileName.find('@');
                unsigned int numSearchPasses = 1;
                if (atPos != string::npos && atPos != 0)
                    numSearchPasses = 2;

                for (unsigned int searchPass = 0; searchPass < numSearchPasses; searchPass++) {
                    if (searchPass == 1)
                        imgPath = imgParentDir / imgFileName.substr(0, atPos);
                    loadingInfo.filepath = imgPath;
                    bool hasExtension = false;
                    if (imgPath.has_extension()) {
                        string ext = ToLower(imgPath.extension().string());
                        for (auto const &ie : imgExt) {
                            if (ext == ie) {
                                hasExtension = true;
                                break;
                            }
                        }
                    }
                    if (hasExtension) {
                        loadingInfo.fileExists = exists(imgPath);
                        if (!loadingInfo.fileExists) {
                            loadingInfo.filepath = searchDir / imgPath;
                            loadingInfo.fileExists = exists(loadingInfo.filepath);
                            if (!loadingInfo.fileExists) {
                                imgPath.replace_extension();
                                hasExtension = false;
                            }
                        }
                    }
                    if (!loadingInfo.fileExists && !hasExtension) {
                        for (auto const &ie : imgExt) {
                            string filePathWithExt = imgPath.string() + ie;
                            loadingInfo.filepath = filePathWithExt;
                            loadingInfo.fileExists = exists(loadingInfo.filepath);
                            if (loadingInfo.fileExists)
                                break;
                            loadingInfo.filepath = searchDir / filePathWithExt;
                            loadingInfo.fileExists = exists(loadingInfo.filepath);
                            if (loadingInfo.fileExists)
                                break;
                        }
                    }
                    if (searchPass == 0 && loadingInfo.fileExists)
                        break;
                }
            }
            if (loadingInfo.fileData || loadingInfo.data || loadingInfo.fileExists) {
                auto &image = fsh.AddImage();
                image.Load(loadingInfo, options().platform, img.format, img.levels, options().fshRescale, options().fshForceAlphaCheck, options().fshPalette);
                ea::FshPixelData *pixelsData = image.FindFirstData(ea::FshData::PIXELDATA)->As<ea::FshPixelData>();
                image.AddData(new ea::FshMetalBin(metalBinData, 0x10));
                image.SetTag(img.name);
                auto hotSpot = image.AddData(new ea::FshHotSpot())->As<ea::FshHotSpot>();
                if (pixelsData) {
                    if (image.GetTag() == "glos") {
                        unsigned int hifa = (unsigned int)((float)pixelsData->GetWidth() * 0.3984375f);
                        if (options().hd || targetName == "FIFA09" || targetName == "FIFA10" || targetName == "FM13")
                            hifa = pixelsData->GetWidth() / 2;
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('sphi', hifa, 0, pixelsData->GetWidth() - hifa, pixelsData->GetHeight()));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('spsk', 0, 0, hifa, pixelsData->GetHeight()));
                    }
                    else if (image.GetTag() == "tp01" || image.GetTag() == "face") {
                        unsigned int hifa = (unsigned int)((float)pixelsData->GetWidth() * 0.3984375f);
                        if (options().hd || targetName == "FIFA09" || targetName == "FIFA10" || targetName == "FM13")
                            hifa = pixelsData->GetWidth() / 2;
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('hifa', hifa, 0, pixelsData->GetWidth() - hifa, pixelsData->GetHeight()));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('skin', 0, 0, hifa, pixelsData->GetHeight()));
                    }
                    else if (image.GetTag() == "tp02")
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('hair', 0, 0, pixelsData->GetWidth(), pixelsData->GetHeight()));
                    else if (image.GetTag() == "ball")
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('ball', 0, 0, pixelsData->GetWidth(), pixelsData->GetHeight()));
                    else if (image.GetTag() == "tp00") {
                        unsigned int shortsHeight = (unsigned int)(roundf(float(pixelsData->GetHeight()) * 0.333f));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('jrsy', 0, shortsHeight, pixelsData->GetWidth(), pixelsData->GetHeight() - shortsHeight));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('shrt', 0, 0, pixelsData->GetWidth(), shortsHeight));
                    }
                    else if (image.GetTag() == "clet")
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('clet', 0, 0, pixelsData->GetWidth(), pixelsData->GetHeight()));
                    else if (image.GetTag() == "mowp")
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('mowp', 0, 0, pixelsData->GetWidth(), pixelsData->GetHeight()));
                    else if (image.GetTag() == "JNum") {
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu9', 921, 0, 103, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu8', 409, 0, 103, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu7', 614, 0, 102, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu6', 102, 0, 102, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu5', 716, 0, 103, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu4', 204, 0, 103, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu3', 512, 0, 102, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu2', 0, 0, 102, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu1', 819, 0, 102, 128));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Jnu0', 307, 0, 102, 128));
                    }
                    else if (image.GetTag() == "SNum") {
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu9', 103, 0, 25, 32)); // 5
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu8', 51, 0, 26, 32)); // 3
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu7', 154, 0, 25, 32)); // 7
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu6', 179, 0, 25, 32)); // 8
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu5', 204, 0, 26, 32)); // 9
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu4', 128, 0, 26, 32)); // 6
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu3', 77, 0, 26, 32)); // 4
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu2', 25, 0, 26, 32)); // 2
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu1', 0, 0, 25, 32)); // 1
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('Snu0', 230, 0, 26, 32)); // 10
                    }
                    else if (image.GetTag() == "misc") {
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('glov', 0, 0, pixelsData->GetWidth() / 2, pixelsData->GetHeight()));
                        hotSpot->Regions().push_back(ea::FshHotSpot::Region('flag', pixelsData->GetWidth() / 2, 0, pixelsData->GetWidth() / 2, pixelsData->GetHeight()));
                    }
                }
                if (hotSpot->Regions().empty()) {
                    char fourcc[4] = { 0, 0, 0, 0 };
                    auto tag = image.GetTag();
                    for (unsigned int i = 0; i < 4; i++) {
                        if (tag.size() > i)
                            fourcc[i] = tag[i];
                    }
                    hotSpot->Regions().push_back(ea::FshHotSpot::Region(*((unsigned int *)fourcc), 0, 0, pixelsData->GetWidth(), pixelsData->GetHeight()));
                }
                image.AddData(new ea::FshName(img.name));
                if (pixelsData) {
                    char comment[256];
                    static char idStr[260];
                    if (options().fshId == 2)
                        strcpy(idStr, "0x0");
                    else {
                        unsigned int texNameHash = 0;
                        if (options().useFshHash)
                            texNameHash = options().fshHash;
                        else {
                            if (options().fshUniqueHashForEachTexture)
                                texNameHash = Hash(fshFilePath.stem().string() + "_" + img.name);
                            else
                                texNameHash = Hash(fshFilePath.stem().string());
                        }
                        sprintf_s(idStr, "0x%.8x", texNameHash);
                    }
                    sprintf_s(comment, "TXLY,%s,%d,%d,%d,%d,%s", image.GetTag().c_str(), options().fshId, pixelsData->GetNumMipLevels() > 0 ? 1 : 0,
                        pixelsData->GetWidth(), pixelsData->GetHeight(), idStr);
                    image.AddData(new ea::FshComment(comment));
                }
            }
        }
        if (fsh.GetImagesCount() > 0) {
            //fsh.ForAllImages([&](ea::FshImage &image) {
            //    auto hotSpot = image.FindFirstData(ea::FshData::HOTSPOT)->As<ea::FshHotSpot>();
            //    auto pixelsData = image.FindFirstData(ea::FshData::PIXELDATA)->As<ea::FshPixelData>();
            //    if (pixelsData && hotSpot && hotSpot->Regions().empty()) {
            //        fsh.ForAllImages([&](ea::FshImage &image2) {
            //            char fourcc[4] = { 0, 0, 0, 0 };
            //            auto tag = image2.GetTag();
            //            for (unsigned int i = 0; i < 4; i++) {
            //                if (tag.size() > i)
            //                    fourcc[i] = tag[i];
            //            }
            //            std::swap(fourcc[0], fourcc[3]);
            //            std::swap(fourcc[1], fourcc[2]);
            //            hotSpot->Regions().push_back(ea::FshHotSpot::Region(*((unsigned int *)fourcc), 0, 0,
            //                image2.FindFirstData(ea::FshData::PIXELDATA)->As<ea::FshPixelData>()->GetWidth(),
            //                image2.FindFirstData(ea::FshData::PIXELDATA)->As<ea::FshPixelData>()->GetHeight()));
            //        });
            //    }
            //});
            if (!fshDir.empty())
                create_directories(fshDir);
            fsh.SetAddBuyERTS(true);
            if (globalVars().target) {
                if (targetName == "CL0405")
                    fsh.SetAlignment(8);
            }
            if (symbols && bufData) {
                size_t im = 0;
                fsh.ForAllImages([&](ea::FshImage &fshIm) {
                    symbols->emplace_back("__SHAPE:::shape_" + fshIm.GetTag(), bufData->Position());
                    fsh.WriteImageToBuffer(*bufData, im++);
                    bufData->Align(16);
                });
            }
            else
                fsh.Write(fshFilePath);
        }
    }
}

void ProcessTextures(string const &modelName, string const &targetName, path const &out, path const &in, map<string, Tex> const &textures, StadiumExtra const &stadExtra, vector<Symbol> *symbols, BinaryBuffer *bufData) {
    auto modelNameLow = ToLower(modelName);
    if (options().head &&
        (
            modelNameLow.starts_with("m228__") ||
            modelNameLow.starts_with("player____model60__") ||
            modelNameLow.starts_with("player____m228__")
            )
        &&
        (
            targetName == "FIFA03" ||
            targetName == "FIFA04" ||
            targetName == "FIFA05" ||
            targetName == "FIFA06" ||
            targetName == "FIFA07" ||
            targetName == "FIFA08" ||
            targetName == "FIFA09" ||
            targetName == "FIFA10" ||
            targetName == "EURO04" ||
            targetName == "EURO08" ||
            targetName == "WC06" ||
            targetName == "CL0405" ||
            targetName == "CL0607" ||
            targetName == "FM13" ||
            targetName == "TCM04" ||
            targetName == "TCM05"
            )
        )
    {
        unsigned int playerId = 0;
        unsigned int numChars = 6;
        if (modelNameLow.starts_with("player____model60__"))
            numChars = 19;
        else if (modelNameLow.starts_with("player____m228__"))
            numChars = 16;
        if (sscanf(modelName.substr(numChars).c_str(), "%d", &playerId) == 1) {
            string playerIdStr = to_string(playerId);

            // writing head texture
            string headTexName;
            map<string, TextureToAdd> fshTextures1;

            unsigned int fshFormat32Bit = options().hasFshFormat ? options().fshFormat : D3DFMT_DXT1;
            unsigned int preferredDxtWithAlpha = ea::Fsh::PreferDxt3 ? D3DFMT_DXT3 : D3DFMT_DXT5;
            unsigned int fshFormat32BitAlpha = options().hasFshFormat ? options().fshFormat : preferredDxtWithAlpha;
            unsigned int fshFormat16Bit = options().hasFshFormat ? options().fshFormat : D3DFMT_R5G6B5;
            unsigned int fshFormat16BitAlpha = options().hasFshFormat ? options().fshFormat : D3DFMT_A4R4G4B4;
            bool isFIFA2003era = targetName == "FIFA03";
            bool isFIFA2004era = targetName == "FIFA04" || targetName == "FIFA05" || targetName == "EURO04" || targetName == "CL0405" || targetName == "TCM04" || targetName == "TCM05";
            bool isFIFA06era = targetName == "FIFA06" || targetName == "FIFA07" || targetName == "FIFA08" || targetName == "WC06" || targetName == "CL0607" || targetName == "EURO08";
            bool isFIFA09era = targetName == "FIFA09" || targetName == "FIFA10" || targetName == "FM13";
            if (isFIFA2003era)
                headTexName = "PlayerTexObj.texobj11__texture12__" + playerIdStr + "_0_0.fsh";
            else if (isFIFA2004era)
                headTexName = "playertexobj.texobj11__texture12__" + playerIdStr + "_0_0.fsh";
            else if (isFIFA06era)
                headTexName = "t21__" + playerIdStr + "_0_0.fsh";
            else
                headTexName = "t21__" + playerIdStr + "_0_0_0_0.fsh";
            if (targetName == "CL0405") {
                if (options().hd) {
                    fshTextures1["glos"] = { "glos", "glos@" + playerIdStr, fshFormat32Bit, 99 };
                    fshTextures1["face"] = { "face", "face@" + playerIdStr, fshFormat32Bit, 99 };
                }
                else {
                    fshTextures1["glos"] = { "glos", "glos@" + playerIdStr, fshFormat16Bit, 1 };
                    fshTextures1["face"] = { "face", "face@" + playerIdStr, fshFormat32Bit, 1 };
                }
            }
            else {
                if (options().hd) {
                    fshTextures1["tp01"] = { "tp01", "tp01@" + playerIdStr, fshFormat32Bit, 99 };
                    fshTextures1["eyes"] = { "eyes", "eyes@" + playerIdStr, fshFormat32Bit, 99 };
                    if (isFIFA06era) {
                        fshTextures1["glo1"] = { "glo1", "glo1@" + playerIdStr, fshFormat32Bit, 99 };
                        fshTextures1["glo2"] = { "glo2", "glo2@" + playerIdStr, fshFormat32Bit, 99 };
                    }
                }
                else {
                    if (targetName == "FIFA03")
                        fshTextures1["tp01"] = { "tp01", "tp01@" + playerIdStr, fshFormat32Bit, 7 };
                    else if (targetName == "FIFA10")
                        fshTextures1["tp01"] = { "tp01", "tp01@" + playerIdStr, fshFormat32Bit, 8 };
                    else
                        fshTextures1["tp01"] = { "tp01", "tp01@" + playerIdStr, fshFormat32Bit, 1 };
                }
            }
            WriteFsh(out.parent_path() / headTexName, in.parent_path(), fshTextures1, symbols, bufData);

            // writing hair texture
            if (!isFIFA09era) {
                string hairTexName;
                if (isFIFA2003era)
                    hairTexName = "PlayerTexObj.texobj11__texture14__0_" + playerIdStr + "_0.fsh";
                else if (isFIFA2004era)
                    hairTexName = "playertexobj.texobj11__texture14__0_" + playerIdStr + "_0.fsh";
                else if (isFIFA06era)
                    hairTexName = "t22__" + playerIdStr + "_0.fsh";

                map<string, TextureToAdd> fshTextures2;
                if (options().hd)
                    fshTextures2["tp02"] = { "tp02", "tp02@" + playerIdStr, fshFormat32BitAlpha, 99 };
                else {
                    int hairTexLevels = 99;
                    unsigned int hairTexFormat = fshFormat16BitAlpha;
                    if (targetName == "FIFA08" || targetName == "EURO08")
                        hairTexFormat = fshFormat32Bit;
                    fshTextures2["tp02"] = { "tp02", "tp02@" + playerIdStr, hairTexFormat, 7 };
                }
                WriteFsh(out.parent_path() / hairTexName, in.parent_path(), fshTextures2, symbols, bufData);
            }
        }
    }
    else {
        if (!options().stadium || stadExtra.used) {
            path fshPath;
            bool hasFshName = false;
            if (stadExtra.used) {
                if (stadExtra.stadType == StadiumExtra::STAD_CUSTOM) {
                    fshPath = out;
                    fshPath.replace_filename("texture_" + to_string(stadExtra.lightingId) + ".fsh");
                    hasFshName = true;
                }
                else if (stadExtra.stadType == StadiumExtra::STAD_DEFAULT) {
                    fshPath = out;
                    fshPath.replace_filename("t226__" + to_string(stadExtra.stadiumId) + "_" + to_string(stadExtra.lightingId) + ".fsh");
                    hasFshName = true;
                }
            }
            if (!hasFshName) {
                string fshExtension = get_fsh_extension();
                if (!options().fshOutput.empty()) {
                    if (options().processingFolders)
                        fshPath = path(options().fshOutput) / (out.stem().string() + fshExtension);
                    else
                        fshPath = options().fshOutput;
                }
                else {
                    fshPath = out;
                    fshPath.replace_extension(fshExtension);
                }
            }
            map<string, TextureToAdd> fshTextures;
            if (!options().fshTextures.empty()) {
                for (auto const &a : options().fshTextures) {
                    path ap = a;
                    string texFilenameLowered = ToLower(ap.stem().string());
                    string afilename = ap.stem().string();
                    if (!afilename.empty()) {
                        if (afilename.length() > 4)
                            afilename = afilename.substr(0, 4);
                        string akey = ToLower(afilename);
                        if (!fshTextures.contains(akey)) {
                            bool texFound = false;
                            for (auto const &[k, img] : textures) {
                                auto imgLoweredName = ToLower(img.name);
                                auto imgLoweredFilename = ToLower(path(img.filepath).stem().string());
                                if (imgLoweredFilename == texFilenameLowered) {
                                    fshTextures[imgLoweredName] = { img.name, img.filepath, options().fshFormat, options().fshLevels, img.embedded };
                                    texFound = true;
                                    break;
                                }
                            }
                            if (!texFound)
                                fshTextures[akey] = { afilename, a, options().fshFormat, options().fshLevels };
                        }
                    }
                }
            }
            else {
                static set<string> defaultTexturesToIgnore = { "eyeb", "rwa0", "rwa1", "rwa2", "rwa3", "rwh0", "rwh1", "rwh2", "rwh3", "rwn0", "rwn1", "rwn2", "rwn3", "abna", "abnb", "abnc", "afla", "aflb", "aflc", "hbna", "hbnb", "hbnc", "hfla", "hflb", "hflc", "adba", "adbb", "adbc", "chf0", "chf1", "chf2", "chf3","caf0", "caf1", "caf2", "caf3", "hcrs", "acrs", "hcla", "hclb", "acla", "aclb" };
                for (auto const &[k, img] : textures) {
                    auto imgLoweredName = ToLower(img.name);
                    auto imgLoweredFilename = ToLower(path(img.filepath).stem().string());
                    bool ignoreThisTexture = false;
                    if (!options().fshDisableTextureIgnore) {
                        if (defaultTexturesToIgnore.contains(imgLoweredName) || options().fshIgnoreTextures.contains(imgLoweredName)
                            || defaultTexturesToIgnore.contains(imgLoweredFilename) || options().fshIgnoreTextures.contains(imgLoweredFilename))
                        {
                            ignoreThisTexture = true;
                        }
                    }
                    if (!ignoreThisTexture) {
                        fshTextures[imgLoweredName] = { img.name, img.filepath, options().fshFormat, options().fshLevels, img.embedded };
                    }
                }
            }
            for (auto const &a : options().fshAddTextures) {
                path ap = a;
                string afilename = ap.stem().string();
                if (!afilename.empty()) {
                    if (afilename.length() > 4)
                        afilename = afilename.substr(0, 4);
                    string akey = ToLower(afilename);
                    if (!fshTextures.contains(akey))
                        fshTextures[akey] = { afilename, a, options().fshFormat, options().fshLevels };
                }
            }
            WriteFsh(fshPath, in.parent_path(), fshTextures, symbols, bufData);
        }
    }
}
