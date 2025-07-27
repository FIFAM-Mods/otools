#include "D3DInclude.h"
#include "main.h"
#include "commandline.h"
#include "message.h"
#include "Fsh/Fsh.h"
#include <fstream>
#include <sstream>
#include <iostream>

const char *OTOOLS_VERSION = "0.179";
const unsigned int OTOOLS_VERSION_INT = 179;

GlobalOptions &options() {
    static GlobalOptions go;
    return go;
}

enum ErrorType {
    NONE = 0,
    NOT_ENOUGHT_ARGUMENTS = 1,
    UNKNOWN_OPERATION_TYPE = 2,
    NO_INPUT_PATH = 3,
    INVALID_INPUT_PATH = 4,
    ERROR_OTHER = 5
};

int main(int argc, char *argv[]) {
    CommandLine cmd(argc, argv, { "i", "o", "game", "scale", "defaultVCol", "setVCol", "vColScale", "fshOutput", "fshLevels", "fshFormat", "fshTextures",
        "fshAddTextures", "fshIgnoreTextures", "startsWith", "pad", "instances", "computationIndex", "hwnd", "fshUnpackImageFormat",
        "forceShader", "fshHash", "fshId", "boneRemap", "skeletonData", "skeleton", "bonesFile", "maxBonesPerVertex", "vertexWeightPaletteSize",
        "translate", "minVCol", "maxVCol", "vColMergeConfig", "bboxScale", "layerFlags", "uid", "fshPalette", "hairSpec", "uvSkinning", "uvSkinSetGenResolution",
        "uvSkinSetGenTextures", "uvSkinningDefaultBone", "uvSkinningMode", "targetFormat", "platform", "material" },
        { "tristrip", "noTextures", "recursive", "createSubDir", "silent", "console", "onlyFirstTechnique", "dummyTextures", "jpegTextures", "embeddedTextures", 
        "swapYZ", "forceLighting", "noMetadata", "genTexNames", "writeFsh", "fshRescale", "fshDisableTextureIgnore", "preTransformVertices", "sortByName", 
        "sortByAlpha", "useMatColor", "noMeshJoin", "head", "hd", "ignoreEmbeddedTextures", "ord", "keepTex0InMatOptions", "fshWriteToParentDir",
        "conformant", "fshUniqueHashForEachTexture", "updateOldStadium", "stadium", "srgb", "fshForceAlphaCheck", "mergeVCols", "fshName",
        "stadium10to07", "stadium07to10", "flipNormals", "flipFaces", "sortHairFaces", "sortFaces", "useCompressonator", "tangents", "preferDxt3" });
    if (cmd.HasOption("silent"))
        SetMessageDisplayType(MessageDisplayType::MSG_NONE);
    else {
        if (cmd.HasOption("console"))
            SetMessageDisplayType(MessageDisplayType::MSG_CONSOLE);
        else
            SetMessageDisplayType(MessageDisplayType::MSG_MESSAGE_BOX);
    }
    if (cmd.HasArgument("platform")) {
        string platform = ToLower(cmd.GetArgumentString("platform"));
        if (platform == "psp")
            options().platform = ea::PLATFORM_PSP;
    }
    enum OperationType {
        UNKNOWN, VERSION, DUMP, EXPORT, IMPORT, INFO, DUMPSHADERS, EXPORTSHADERS, PACKFSH, UNPACKFSH, ALIGNFILES, GENUVSET, EXPORTPREVIEW
    } opType = OperationType::UNKNOWN;
    void (*callback)(path const &, path const &) = nullptr;
    bool isCustom = false;
    bool createDevice = false;
    bool createRenderer = false;
    string targetExt;
    set<string> inExt;
    if (argc >= 2) {
        string opTypeStr = argv[1];
        if (opTypeStr == "version") {
            opType = OperationType::VERSION;
        }
        else if (opTypeStr == "import") {
            opType = OperationType::IMPORT;
            callback = oimport;
            inExt = { ".gltf", ".glb", ".dae", ".fbx", ".obj", ".blend", ".3ds", ".x", ".x3d" };
            if (cmd.HasOption("ord"))
                targetExt = ".ord";
            else
                targetExt = ".o";
        }
        else if (opTypeStr == "export") {
            opType = OperationType::EXPORT;
            callback = oexport;
            inExt = { ".o", ".ord" };
            targetExt = ".gltf";
        }
        else if (opTypeStr == "dump") {
            opType = OperationType::DUMP;
            callback = odump;
            inExt = { ".o", ".ord" };
            targetExt = ".txt";
        }
        else if (opTypeStr == "info") {
            opType = OperationType::INFO;
            callback = oinfo;
            inExt = { ".o", ".ord" };
        }
        else if (opTypeStr == "dumpshaders") {
            opType = OperationType::DUMPSHADERS;
            callback = dumpshaders;
            isCustom = true;
        }
        else if (opTypeStr == "unpackfsh" || opTypeStr == "extractfsh") {
            opType = OperationType::UNPACKFSH;
            callback = unpackfsh;
            inExt = { ".fsh", ".msh" };
            createDevice = true;
        }
        else if (opTypeStr == "packfsh" || opTypeStr == "buildfsh" || opTypeStr == "makefsh") {
            opType = OperationType::PACKFSH;
            callback = packfsh_collect;
            inExt = { ".png", ".jpg", ".jpeg", ".bmp", ".tga", ".dds" };
            createDevice = true;
        }
        else if (opTypeStr == "align" || opTypeStr == "alignfile") {
            opType = OperationType::ALIGNFILES;
            callback = align_file;
            inExt = { ".o" };
        }
        else if (opTypeStr == "genuvset") {
            opType = OperationType::GENUVSET;
            callback = gen_uv_set;
            inExt = { ".gltf", ".glb", ".dae", ".fbx", ".blend", ".3ds", ".x", ".x3d" };
            createDevice = true;
            createRenderer = true;
            isCustom = true;
        }
        else if (opTypeStr == "exportshaders") {
            opType = OperationType::EXPORTSHADERS;
            callback = oexportshaders;
            inExt = { ".o" };
            targetExt = ".sh";
        }
        else if (opTypeStr == "exportpreview") {
            opType = OperationType::EXPORTPREVIEW;
            callback = oexport_x_preview;
            inExt = { ".o", ".ord" };
            targetExt = ".gltf";
        }
    }
    if (opType == OperationType::UNKNOWN) {
        ErrorMessage("Unknown operation type\nPlease use OTools_GUI if you don't understand how to work with command-line tool");
        return ErrorType::UNKNOWN_OPERATION_TYPE;
    }
    if (opType == OperationType::VERSION) {
        InfoMessage(string("OTools version: ") + OTOOLS_VERSION);
        return OTOOLS_VERSION_INT;
    }
    if (!cmd.HasArgument("i")) {
        ErrorMessage("Input path is not specified");
        return ErrorType::NO_INPUT_PATH;
    }
    path i = cmd.GetArgumentString("i");
    if (!exists(i)) {
        ErrorMessage("Input path does not exist");
        return ErrorType::INVALID_INPUT_PATH;
    }
    i = absolute(weakly_canonical(i));
    if (cmd.HasArgument("hwnd"))
        options().hwnd = cmd.GetArgumentInt("hwnd");
    if (cmd.HasOption("hd"))
        options().hd = true;
    string game = ToLower(cmd.GetArgumentString("game"));
    if (game == "fm") {
        static TargetFM13 defaultFMTarget;
        globalVars().target = &defaultFMTarget;
    }
    else if (game == "fifa") {
        static TargetFIFA10 defaultFIFATarget;
        globalVars().target = &defaultFIFATarget;
    }
    else if (game == "cricket") {
        static TargetCRICKET07 defaultCricketTarget;
        globalVars().target = &defaultCricketTarget;
    }
    else if (game == "nhl") {
        static TargetNHL04 defaultNHLTarget;
        globalVars().target = &defaultNHLTarget;
    }
    else if (game == "tcm") {
        static TargetTCM05 defaultTCMTarget;
        globalVars().target = &defaultTCMTarget;
    }
    else if (game == "rugby") {
        static TargetRUGBY08 defaultRugbyTarget;
        globalVars().target = &defaultRugbyTarget;
    }
    else if (game == "mvp") {
        static TargetMVP2005 defaultMVPTarget;
        globalVars().target = &defaultMVPTarget;
    }
    else if (game == "nba" || game == "nbalive") {
        static TargetNBA2004 defaultNBATarget;
        globalVars().target = &defaultNBATarget;
    }
    else if (game == "nfs" || game == "nfshp" || game == "nfshp2") {
        if (opType == OperationType::IMPORT) {
            ErrorMessage("Import is not implemented for Need for Speed Hot Pursuit 2 in this otools version");
            return ErrorType::ERROR_OTHER;
        }
        static TargetNFSHP2 targetNFSHP2;
        globalVars().target = &targetNFSHP2;
    }
    else if (game == "fm13") {
        static TargetFM13 targetFM13;
        globalVars().target = &targetFM13;
    }
    else if (game == "fm08") {
        static TargetFM08 targetFM08;
        globalVars().target = &targetFM08;
    }
    else if (game == "fm07") {
        static TargetFM07 targetFM07;
        globalVars().target = &targetFM07;
    }
    else if (game == "fm06") {
        static TargetFM06 targetFM06;
        globalVars().target = &targetFM06;
    }
    else if (game == "tcm05" || game == "tcm2005") {
        static TargetTCM05 targetTCM05;
        globalVars().target = &targetTCM05;
    }
    else if (game == "tcm04" || game == "tcm2004") {
        static TargetTCM04 targetTCM04;
        globalVars().target = &targetTCM04;
    }
    else if (game == "fifa10") {
        static TargetFIFA10 targetFIFA10;
        globalVars().target = &targetFIFA10;
    }
    else if (game == "fifa09") {
        static TargetFIFA09 targetFIFA09;
        globalVars().target = &targetFIFA09;
    }
    else if (game == "fifa08") {
        static TargetFIFA08 targetFIFA08;
        globalVars().target = &targetFIFA08;
    }
    else if (game == "fifa07") {
        static TargetFIFA07 targetFIFA07;
        globalVars().target = &targetFIFA07;
    }
    else if (game == "fifa06") {
        static TargetFIFA06 targetFIFA06;
        globalVars().target = &targetFIFA06;
    }
    else if (game == "fifa05" || game == "fifa2005") {
        static TargetFIFA05 targetFIFA05;
        globalVars().target = &targetFIFA05;
    }
    else if (game == "fifa04" || game == "fifa2004") {
        static TargetFIFA04 targetFIFA04;
        globalVars().target = &targetFIFA04;
    }
    else if (game == "fifa03" || game == "fifa2003") {
        static TargetFIFA03 targetFIFA03;
        globalVars().target = &targetFIFA03;
    }
    else if (game == "cl0607" || game == "cl07" || game == "uefacl0607" || game == "uefacl07") {
        static TargetCL0607 targetCL0607;
        globalVars().target = &targetCL0607;
    }
    else if (game == "cl0405" || game == "cl05" || game == "uefacl0405" || game == "uefacl05") {
        static TargetCL0405 targetCL0405;
        globalVars().target = &targetCL0405;
    }
    else if (game == "wc06" || game == "fifawc06" || game == "wc2006" || game == "fifawc2006") {
        static TargetWC06 targetWC06;
        globalVars().target = &targetWC06;
    }
    else if (game == "euro08" || game == "uefaeuro08" || game == "euro2008" || game == "uefaeuro2008") {
        static TargetEURO08 targetEURO08;
        globalVars().target = &targetEURO08;
    }
    else if (game == "euro04" || game == "uefaeuro04" || game == "euro2004" || game == "uefaeuro2004") {
        static TargetEURO04 targetEURO04;
        globalVars().target = &targetEURO04;
    }
    else if (game == "cricket07") {
        static TargetCRICKET07 targetCRICKET07;
        globalVars().target = &targetCRICKET07;
    }
    else if (game == "cricket2005" || game == "cricket05") {
        static TargetCRICKET2005 targetCRICKET2005;
        globalVars().target = &targetCRICKET2005;
    }
    else if (game == "nhl04" || game == "nhl2004") {
        static TargetNHL04 targetNHL04;
        globalVars().target = &targetNHL04;
    }
    else if (game == "rugby08") {
        static TargetRUGBY08 targetRUGBY08;
        globalVars().target = &targetRUGBY08;
    }
    else if (game == "rugby06") {
        static TargetRUGBY06 targetRUGBY06;
        globalVars().target = &targetRUGBY06;
    }
    else if (game == "rugby2005" || game == "rugby05") {
        static TargetRUGBY2005 targetRUGBY2005;
        globalVars().target = &targetRUGBY2005;
    }
    else if (game == "mvp2005" || game == "mvp05") {
        static TargetMVP2005 targetMVP2005;
        globalVars().target = &targetMVP2005;
    }
    else if (game == "mvp2004" || game == "mvp04") {
        static TargetMVP2004 targetMVP2004;
        globalVars().target = &targetMVP2004;
    }
    else if (game == "mvp2003" || game == "mvp03") {
        static TargetMVP2003 targetMVP2003;
        globalVars().target = &targetMVP2003;
    }
    else if (game == "nba2004" || game == "nbalive2004" || game == "nba04") {
        static TargetNBA2004 targetNBA2004;
        globalVars().target = &targetNBA2004;
    }
    else if (game == "nba2003" || game == "nbalive2003" || game == "nba03") {
        static TargetNBA2003 targetNBA2003;
        globalVars().target = &targetNBA2003;
    }
    else {
        static TargetFM13 defaultTarget;
        globalVars().target = &defaultTarget;
    }
    if (opType == OperationType::EXPORT) {
        if (cmd.HasOption("noTextures"))
            options().noTextures = true;
        if (cmd.HasOption("dummyTextures"))
            options().dummyTextures = true;
        if (cmd.HasOption("jpegTextures"))
            options().jpegTextures = true;
        if (cmd.HasOption("noMeshJoin"))
            options().noMeshJoin = true;
        if (cmd.HasOption("keepTex0InMatOptions"))
            options().keepTex0InMatOptions = true;
        if (cmd.HasArgument("skeleton"))
            options().skeleton = cmd.GetArgumentString("skeleton");
        if (cmd.HasOption("updateOldStadium"))
            options().updateOldStadium = true;
        if (cmd.HasOption("stadium10to07"))
            options().stadium10to07 = true;
        if (cmd.HasOption("stadium07to10"))
            options().stadium07to10 = true;
        if (cmd.HasArgument("targetFormat")) {
            options().targetFormat = ToLower(cmd.GetArgumentString("targetFormat"));
            if (options().targetFormat == "gltf" || options().targetFormat == "gltf2")
                targetExt = ".gltf";
            else if (options().targetFormat == "fbx" || options().targetFormat == "fbxa" || options().targetFormat == "asciifbx" || options().targetFormat == "fbxascii")
                targetExt = ".fbx";
            else if (options().targetFormat == "glb" || options().targetFormat == "glb2")
                targetExt = ".glb";
            else if (options().targetFormat == "collada" || options().targetFormat == "dae")
                targetExt = ".dae";
            else if (options().targetFormat == "obj" || options().targetFormat == "objnomtl")
                targetExt = ".obj";
            else if (options().targetFormat == "3ds")
                targetExt = ".3ds";
            else if (options().targetFormat == "x")
                targetExt = ".x";
            else if (options().targetFormat == "x3d")
                targetExt = ".x3d";
            else {
                targetExt = ".gltf";
                options().targetFormat = "gltf";
            }
        }
        else
            options().targetFormat = "gltf";
    }
    else if (opType == OperationType::IMPORT) {
        if (cmd.HasOption("conformant"))
            options().conformant = true;
        if (cmd.HasOption("noMetadata"))
            options().noMetadata = true;
        if (cmd.HasArgument("scale")) {
            auto scaleLine = cmd.GetArgumentString("scale");
            auto scaleParts = Split(scaleLine, ',');
            if (scaleParts.size() == 1) {
                options().scale.x = SafeConvertFloat(scaleParts[0]);
                options().scale.y = options().scale.x;
                options().scale.z = options().scale.x;
                options().scaleXYZ = false;
            }
            else if (scaleParts.size() == 3) {
                options().scale.x = SafeConvertFloat(scaleParts[0]);
                options().scale.y = SafeConvertFloat(scaleParts[1]);
                options().scale.z = SafeConvertFloat(scaleParts[2]);
                options().scaleXYZ = true;
            }
        }
        if (cmd.HasArgument("translate")) {
            auto translateLine = cmd.GetArgumentString("translate");
            auto translateParts = Split(translateLine, ',');
            if (translateParts.size() == 3) {
                options().translate.x = SafeConvertFloat(translateParts[0]);
                options().translate.y = SafeConvertFloat(translateParts[1]);
                options().translate.z = SafeConvertFloat(translateParts[2]);
            }
        }
        if (cmd.HasOption("tristrip"))
            options().tristrip = true;
        if (cmd.HasOption("embeddedTextures"))
            options().embeddedTextures = true;
        if (cmd.HasOption("swapYZ"))
            options().swapYZ = true;
        if (cmd.HasOption("forceLighting"))
            options().forceLighting = true;
        auto readVCol = [&](string const &argName, aiColor4D &outCol, bool &outHas) {
            if (cmd.HasArgument(argName)) {
                string vcol = cmd.GetArgumentString(argName);
                unsigned int r = 255, g = 255, b = 255, a = 255;
                if (vcol.length() == 6)
                    outHas = (sscanf(vcol.c_str(), "%2X%2X%2X", &r, &g, &b) == 3);
                else if (vcol.length() == 8)
                    outHas = (sscanf(vcol.c_str(), "%2X%2X%2X%2X", &r, &g, &b, &a) == 4);
                if (outHas) {
                    outCol.r = float(r) / 255.0f;
                    outCol.g = float(g) / 255.0f;
                    outCol.b = float(b) / 255.0f;
                    outCol.a = float(a) / 255.0f;
                }
            }
        };
        readVCol("setVCol", options().setVCol, options().hasSetVCol);
        if (!options().hasSetVCol) {
            readVCol("defaultVCol", options().defaultVCol, options().hasDefaultVCol);
            readVCol("minVCol", options().minVCol, options().hasMinVCol);
            readVCol("maxVCol", options().maxVCol, options().hasMaxVCol);
            if (cmd.HasArgument("vColScale"))
                options().vColScale = cmd.GetArgumentFloat("vColScale");
        }
        if (cmd.HasOption("mergeVCols")) {
            options().mergeVCols = true;
            if (cmd.HasArgument("vColMergeConfig")) {
                path vColMergeConfig = cmd.GetArgumentString("vColMergeConfig");
                if (exists(vColMergeConfig) && is_regular_file(vColMergeConfig)) {
                    ifstream f(vColMergeConfig);
                    for (string line; getline(f, line); ) {
                        auto info = Split(line, ',');
                        if (info.size() >= 3) {
                            unsigned int index = SafeConvertInt<unsigned int>(info[0]);
                            VColMergeLayerConfig config;
                            config.bottomRange = SafeConvertFloat(info[1]);
                            config.topRange = SafeConvertFloat(info[2]);
                            //Error("Index: %d %f %f", index, config.bottomRange, config.topRange);
                            options().vColMergeConfig[index] = config;
                        }
                    }
                }
            }
        }
        if (cmd.HasOption("genTexNames"))
            options().genTexNames = true;
        if (cmd.HasOption("preTransformVertices"))
            options().preTransformVertices = true;
        if (cmd.HasOption("sortByName"))
            options().sortByName = true;
        if (cmd.HasOption("sortByAlpha"))
            options().sortByAlpha = true;
        if (cmd.HasOption("useMatColor"))
            options().useMatColor = true;
        if (cmd.HasOption("head"))
            options().head = true;
        if (cmd.HasOption("ignoreEmbeddedTextures"))
            options().ignoreEmbeddedTextures = true;
        if (cmd.HasArgument("instances"))
            options().instances = cmd.GetArgumentInt("instances");
        if (cmd.HasArgument("computationIndex"))
            options().computationIndex = cmd.GetArgumentInt("computationIndex");
        if (cmd.HasArgument("forceShader"))
            options().forceShader = cmd.GetArgumentString("forceShader");
        if (cmd.HasArgument("material"))
            options().material = cmd.GetArgumentString("material");
        if (cmd.HasArgument("bonesFile")) {
            options().bonesFile = cmd.GetArgumentString("bonesFile");
            if (!options().bonesFile.empty()) {
                if (exists(options().bonesFile)) {
                    ifstream bf(options().bonesFile);
                    unsigned int boneIndex = 0;
                    for (string line; getline(bf, line); ) {
                        Trim(line);
                        if (!line.empty())
                            globalVars().customBones[line] = boneIndex++;
                    }
                    if (globalVars().customBones.size() > 255) {
                        ErrorMessage("Bones file: using more than 255 bones is not allowed");
                        return ErrorType::UNKNOWN_OPERATION_TYPE;
                    }
                }
                else
                    Error("File for bones doesn't exist");
            }
        }
        if (cmd.HasArgument("boneRemap")) {
            options().boneRemap = cmd.GetArgumentString("boneRemap");
            if (!options().boneRemap.empty()) {
                if (exists(options().boneRemap)) {
                    ifstream br(options().boneRemap);
                    for (string line; getline(br, line); ) {
                        auto info = Split(line, '\t', true, true);
                        // sourceBoneName,globalFactor,numTargetBones,[targetBoneName],[factor],[minX,minY,minZ,maxX,maxY,maxZ]
                        if (info.size() >= 3) {
                            unsigned int numTargetBones = SafeConvertInt<unsigned int>(info[2]);
                            if (numTargetBones > 0 && info.size() >= (3 + numTargetBones)) {
                                float globalFactor = SafeConvertFloat(info[1]);
                                if (globalFactor > 0.0f) {
                                    BoneTargets targets;
                                    string sourceBoneName = info[0];
                                    bool hasFactors = (info.size() >= (3 + numTargetBones * 2));
                                    targets.hasBounds = hasFactors && (info.size() >= (3 + numTargetBones * 8));
                                    targets.targetBones.resize(numTargetBones);
                                    bool failedToAdd = false;
                                    for (unsigned int tb = 0; tb < numTargetBones; tb++) {
                                        targets.targetBones[tb].boneName = info[3 + tb];
                                        if (globalVars().customBones.contains(targets.targetBones[tb].boneName))
                                            targets.targetBones[tb].boneIndex = globalVars().customBones[targets.targetBones[tb].boneName];
                                        else {
                                            Error("Target bone %s is not present in custom bones file", targets.targetBones[tb].boneName.c_str());
                                            failedToAdd = true;
                                            break;
                                        }
                                        if (hasFactors)
                                            targets.targetBones[tb].factor = SafeConvertFloat(info[3 + numTargetBones + tb]);
                                        else {
                                            if (numTargetBones == 1)
                                                targets.targetBones[tb].factor = 1.0f;
                                            else
                                                targets.targetBones[tb].factor = 1.0f / numTargetBones;
                                        }
                                        if (globalFactor != 1.0f)
                                            targets.targetBones[tb].factor *= globalFactor;
                                        if (targets.hasBounds) {
                                            targets.targetBones[tb].bound.mMin.x = SafeConvertFloat(info[3 + numTargetBones * 2 + tb * 6 + 0]);
                                            targets.targetBones[tb].bound.mMin.x = SafeConvertFloat(info[3 + numTargetBones * 2 + tb * 6 + 1]);
                                            targets.targetBones[tb].bound.mMin.x = SafeConvertFloat(info[3 + numTargetBones * 2 + tb * 6 + 2]);
                                            targets.targetBones[tb].bound.mMax.x = SafeConvertFloat(info[3 + numTargetBones * 2 + tb * 6 + 3]);
                                            targets.targetBones[tb].bound.mMax.x = SafeConvertFloat(info[3 + numTargetBones * 2 + tb * 6 + 4]);
                                            targets.targetBones[tb].bound.mMax.x = SafeConvertFloat(info[3 + numTargetBones * 2 + tb * 6 + 5]);
                                        }
                                        //Error("%s - %s %f", sourceBoneName.c_str(), targets.targetBones[tb].boneName.c_str(), targets.targetBones[tb].factor);
                                    }
                                    if (!failedToAdd)
                                        globalVars().boneRemap[sourceBoneName] = targets;
                                }
                            }
                        }
                    }
                }
                else
                    Error("File for bone remap doesn't exist");
            }
        }
        if (cmd.HasArgument("skeletonData"))
            options().skeletonData = cmd.GetArgumentString("skeletonData");
        if (cmd.HasArgument("boneRemap")) {
            if (!cmd.HasArgument("bonesFile") || !cmd.HasArgument("skeletonData")) {
                ErrorMessage("-boneRemap option must be used together with -bonesFile and -skeletonData options");
                return ErrorType::ERROR_OTHER;
            }
        }
        else if (cmd.HasArgument("bonesFile")) {
            if (!cmd.HasArgument("skeletonData")) {
                ErrorMessage("-bonesFile option must be used together with -skeletonData option");
                return ErrorType::ERROR_OTHER;
            }
        }
        if (cmd.HasArgument("maxBonesPerVertex"))
            options().maxBonesPerVertex = cmd.GetArgumentInt("maxBonesPerVertex");
        if (cmd.HasArgument("vertexWeightPaletteSize"))
            options().vertexWeightPaletteSize = cmd.GetArgumentInt("vertexWeightPaletteSize");
        if (cmd.HasArgument("bboxScale"))
            options().bboxScale = cmd.GetArgumentFloat("bboxScale");
        if (cmd.HasArgument("layerFlags"))
            options().layerFlags = cmd.GetArgumentInt("layerFlags");
        if (cmd.HasArgument("uid"))
            options().uid = cmd.GetArgumentInt("uid");
        if (cmd.HasArgument("hairSpec"))
            options().hairSpec = cmd.GetArgumentFloat("hairSpec");
        if (cmd.HasOption("sortHairFaces"))
            options().sortHairFaces = true;
        if (cmd.HasOption("sortFaces"))
            options().sortFaces = true;
        if (cmd.HasOption("tangents"))
            options().tangents = true;
        if (cmd.HasArgument("uvSkinning")) {
            createDevice = true;
            // -uvSkinning tp01=D:\tp01,tp02=D\tp02
            string uvSkinning = cmd.GetArgumentString("uvSkinning");
            auto vecUvSkinning = Split(uvSkinning, ',', true, true, true);
            for (auto parts : vecUvSkinning) {
                auto vec = Split(parts, '=', true, true, true);
                if (vec.size() == 1)
                    options().uvSkinning[""] = vec[0];
                else if (vec.size() == 2)
                    options().uvSkinning[vec[0]] = vec[1];
            }
            // -uvSkinningDefaultBone tp01=Bone1,tp02=Bone2
            string uvSkinningDefaultBone = cmd.GetArgumentString("uvSkinningDefaultBone");
            auto vecUvSkinningDefaultBone = Split(uvSkinningDefaultBone, ',', true, true, true);
            for (auto parts : vecUvSkinningDefaultBone) {
                auto vec = Split(parts, '=', true, true, true);
                if (vec.size() == 1)
                    options().uvSkinningDefaultBone[""] = vec[0];
                else if (vec.size() == 2)
                    options().uvSkinningDefaultBone[vec[0]] = vec[1];
            }
            // -uvSkinningMode tp01=0,tp02=1
            string uvSkinningMode = cmd.GetArgumentString("uvSkinningMode");
            auto vecUvSkinningMode = Split(uvSkinningMode, ',', true, true, true);
            for (auto parts : vecUvSkinningMode) {
                auto vec = Split(parts, '=', true, true, true);
                if (vec.size() == 1) {
                    options().uvSkinningMode[""] = SafeConvertInt<unsigned int>(vec[0]);
                    if (options().uvSkinningMode[""] > 1)
                        options().uvSkinningMode[""] = 0;
                }
                else if (vec.size() == 2) {
                    options().uvSkinningMode[vec[0]] = SafeConvertInt<unsigned int>(vec[1]);
                    if (options().uvSkinningMode[vec[0]] > 1)
                        options().uvSkinningMode[vec[0]] = 0;
                }
            }
        }
    }
    else if (opType == OperationType::DUMP) {
        if (cmd.HasOption("onlyFirstTechnique"))
            options().onlyFirstTechnique = true;
    }
    else if (opType == OperationType::PACKFSH) {
        if (cmd.HasOption("fshWriteToParentDir"))
            options().fshWriteToParentDir = true;
    }
    else if (opType == OperationType::UNPACKFSH) {
        if (cmd.HasArgument("fshUnpackImageFormat")) {
            auto imFormat = cmd.GetArgumentString("fshUnpackImageFormat");
            if (imFormat.starts_with('.'))
                imFormat = imFormat.substr(1);
            if (!imFormat.empty()) {
                imFormat = ToLower(imFormat);
                if (imFormat == "png") {
                    options().fshUnpackImageFormat = imFormat;
                    globalVars().fshUnpackImageFormat = ea::FshImage::PNG;
                }
                else if (imFormat == "bmp") {
                    options().fshUnpackImageFormat = imFormat;
                    globalVars().fshUnpackImageFormat = ea::FshImage::BMP;
                }
                else if (imFormat == "tga") {
                    options().fshUnpackImageFormat = imFormat;
                    globalVars().fshUnpackImageFormat = ea::FshImage::TGA;
                }
                else if (imFormat == "dds") {
                    options().fshUnpackImageFormat = imFormat;
                    globalVars().fshUnpackImageFormat = ea::FshImage::DDS;
                }
                else if (imFormat == "jpg") {
                    options().fshUnpackImageFormat = imFormat;
                    globalVars().fshUnpackImageFormat = ea::FshImage::JPG;
                }
            }
        }
    }
    else if (opType == OperationType::GENUVSET) {
        if (cmd.HasArgument("uvSkinSetGenResolution")) {
            string uvSkinSetGenResolution = cmd.GetArgumentString("uvSkinSetGenResolution");
            auto parts = Split(uvSkinSetGenResolution, 'x');
            if (parts.size() == 2) {
                unsigned int x = SafeConvertInt<unsigned int>(parts[0]);
                unsigned int y = SafeConvertInt<unsigned int>(parts[1]);
                if (x > 0 && x <= 16384 && y > 0 && y <= 16384) {
                    options().uvSkinSetGenResolutionX = x;
                    options().uvSkinSetGenResolutionY = y;
                }
            }
        }
        if (cmd.HasArgument("uvSkinSetGenTextures")) {
            string uvSkinSetGenTextures = cmd.GetArgumentString("uvSkinSetGenTextures");
            auto parts = Split(uvSkinSetGenTextures, ',');
            for (auto const &part : parts) {
                if (!part.empty())
                    options().uvSkinSetGenTextures.insert(ToLower(part));
            }
        }
    }
    else if (opType == OperationType::EXPORTPREVIEW) {
        if (cmd.HasArgument("translate")) {
            auto translateLine = cmd.GetArgumentString("translate");
            auto translateParts = Split(translateLine, ',');
            if (translateParts.size() == 3) {
                options().translate.x = SafeConvertFloat(translateParts[0]);
                options().translate.y = SafeConvertFloat(translateParts[1]);
                options().translate.z = SafeConvertFloat(translateParts[2]);
            }
        }
    }
    if (opType == PACKFSH || (opType == IMPORT && (cmd.HasOption("writeFsh") || cmd.HasOption("embeddedTextures")))) {
        options().writeFsh = true;
        if (cmd.HasArgument("fshOutput"))
            options().fshOutput = cmd.GetArgumentString("fshOutput");
        createDevice = true;
        options().fshLevels = D3DX_DEFAULT;
        if (cmd.HasArgument("fshLevels")) {
            options().fshLevels = cmd.GetArgumentInt("fshLevels");
            if (options().fshLevels == -1 || options().fshLevels == 0)
                options().fshLevels = D3DX_FROM_FILE;
            else if (options().fshLevels < -1 || options().fshLevels > 13)
                options().fshLevels = D3DX_DEFAULT;
        }
        if (cmd.HasArgument("fshPalette")) {
            options().fshPalette = cmd.GetArgumentInt("fshPalette");
            if (options().fshPalette != 24 && options().fshPalette != 32)
                options().fshPalette = -1;
        }
        options().fshFormat = unsigned int(-4);
        if (cmd.HasArgument("fshFormat")) {
            options().hasFshFormat = true;
            string format = ToLower(cmd.GetArgumentString("fshFormat"));
            if (!format.empty()) {
                if (format == "dxt")
                    options().fshFormat = unsigned int(-4);
                else if (format == "rgb" || format == "rgba" || format == "rgb32")
                    options().fshFormat = unsigned int(-5);
                else if (format == "rgb16" || format == "rgba16")
                    options().fshFormat = unsigned int(-6);
                else if (format == "auto")
                    options().fshFormat = unsigned int(-3);
                else if (format == "dxt1")
                    options().fshFormat = D3DFMT_DXT1;
                else if (format == "dxt3")
                    options().fshFormat = D3DFMT_DXT3;
                else if (format == "dxt5")
                    options().fshFormat = D3DFMT_DXT5;
                else if (format == "8888")
                    options().fshFormat = D3DFMT_A8R8G8B8;
                else if (format == "888")
                    options().fshFormat = D3DFMT_R8G8B8;
                else if (format == "4444")
                    options().fshFormat = D3DFMT_A4R4G4B4;
                else if (format == "5551")
                    options().fshFormat = D3DFMT_A1R5G5B5;
                else if (format == "565")
                    options().fshFormat = D3DFMT_R5G6B5;
                else if (format == "pal4")
                    options().fshFormat = unsigned int(-7);
                else if (format == "pal" || format == "pal8")
                    options().fshFormat = unsigned int(-8);
            }
        }
        if (cmd.HasOption("fshRescale"))
            options().fshRescale = true;
        if (cmd.HasArgument("fshTextures"))
            options().fshTextures = Split(cmd.GetArgumentString("fshTextures"), ',', true, true);
        if (cmd.HasArgument("fshAddTextures"))
            options().fshAddTextures = Split(cmd.GetArgumentString("fshAddTextures"), ',', true, true);
        if (cmd.HasOption("fshDisableTextureIgnore"))
            options().fshDisableTextureIgnore = true;
        else {
            if (cmd.HasArgument("fshIgnoreTextures")) {
                auto ignoredTexturesList = Split(cmd.GetArgumentString("fshIgnoreTextures"), ',', true, true);
                if (!ignoredTexturesList.empty()) {
                    for (auto const &it : ignoredTexturesList)
                        options().fshIgnoreTextures.insert(ToLower(it));
                }
            }
        }
        if (cmd.HasArgument("fshHash")) {
            options().fshHash = cmd.GetArgumentInt("fshHash");
            options().useFshHash = true;
        }
        if (cmd.HasArgument("fshId"))
            options().fshId = cmd.GetArgumentInt("fshId");
        if (cmd.HasOption("fshUniqueHashForEachTexture"))
            options().fshUniqueHashForEachTexture = true;
        if (cmd.HasOption("fshForceAlphaCheck"))
            options().fshForceAlphaCheck = true;
        ea::Fsh::PreferDxt3 = cmd.HasOption("preferDxt3");
        //ea::Fsh::UseCompressonator = cmd.HasOption("useCompressonator");
    }
    if (opType == EXPORT || opType == IMPORT) {
        if (cmd.HasOption("stadium")) {
            options().stadium = true;
            bool hasSkcd = false;
            for (auto const &t : options().fshAddTextures) {
                if (ToLower(t) == "skcd") {
                    hasSkcd = true;
                    break;
                }
            }
            if (!hasSkcd)
                options().fshAddTextures.push_back("skcd");
            options().fshForceAlphaCheck = true;
        }
        if (cmd.HasOption("srgb"))
            options().srgb = true;
        if (cmd.HasOption("flipNormals"))
            options().flipNormals = true;
        if (cmd.HasOption("flipFaces"))
            options().flipFaces = true;

    }
    if (opType == PACKFSH || opType == UNPACKFSH || (opType == IMPORT && cmd.HasOption("writeFsh"))) {
        options().fshName = cmd.HasOption("fshName");
    }
    if (opType == IMPORT || opType == ALIGNFILES) {
        if (cmd.HasArgument("pad"))
            options().pad = cmd.GetArgumentInt("pad");
    }
    path o;
    bool hasOutput = cmd.HasArgument("o");
    if (hasOutput) {
        o = cmd.GetArgumentString("o");
        o = absolute(weakly_canonical(o));
    }
    bool createSubDir = cmd.HasOption("createSubDir");
    string startsWith;
    if (cmd.HasArgument("startsWith"))
        startsWith = cmd.GetArgumentString("startsWith");
    if (createDevice) {
        D3DDevice *pDevice = nullptr;
        if (options().hwnd) {
            static D3DDevice deviceHWND((HWND)options().hwnd);
            pDevice = &deviceHWND;
        }
        else {
            static D3DDevice deviceNoHWND;
            pDevice = &deviceNoHWND;
        }
        ea::Fsh::SetDevice(pDevice);
        globalVars().device = pDevice;
        if (createRenderer)
            globalVars().renderer = new Renderer(pDevice, options().uvSkinSetGenResolutionX, options().uvSkinSetGenResolutionY);
    }

    auto errCode = ErrorType::NONE;
    
    if (!isCustom) {
        auto processFile = [&](path const &in, bool inDir) {
            try {
                if (!inDir || (is_regular_file(in) && inExt.contains(ToLower(in.extension().string())))) {
                    if (startsWith.empty() || in.filename().string().starts_with(startsWith)) {
                        path out;
                        if (hasOutput)
                            out = o;
                        else
                            out = in.parent_path();
                        if (!hasOutput || inDir || opType == OperationType::PACKFSH || opType == OperationType::UNPACKFSH) {
                            string targetFileName = in.stem().string();
                            string targetFileNameWithExt = targetFileName + targetExt;
                            if (createSubDir)
                                out = out / targetFileName / targetFileNameWithExt;
                            else
                                out = out / targetFileNameWithExt;
                        }
                        create_directories(out.parent_path());
                        globalVars().currentFilePath = in;
                        callback(out, in);
                    }
                }
            }
            catch (exception & e) {
                ErrorMessage(in.filename().string() + ": " + e.what());
                errCode = ErrorType::ERROR_OTHER;
            }
        };

        if (is_directory(i)) {
            options().processingFolders = true;
            if (cmd.HasOption("recursive")) {
                for (auto const &p : recursive_directory_iterator(i))
                    processFile(p.path(), true);
            }
            else {
                for (auto const &p : directory_iterator(i))
                    processFile(p.path(), true);
            }
        }
        else
            processFile(i, false);
    }
    else {
        globalVars().currentFilePath = i;
        callback(o, i);
    }

    if (opType == PACKFSH)
        packfsh_pack();

    if (createDevice)
        ea::Fsh::ClearDevice();
    delete globalVars().renderer;

    return errCode;
}

pair<unsigned char *, unsigned int> readofile(path const &inPath) {
    pair<unsigned char *, unsigned int> result = { nullptr, 0 };
    if (ToLower(inPath.extension().string()) != ".ord") {
        FILE *f = _wfopen(inPath.c_str(), L"rb");
        if (f) {
            fseek(f, 0, SEEK_END);
            unsigned int fileSize = ftell(f);
            fseek(f, 0, SEEK_SET);
            result.first = new unsigned char[fileSize];
            if (fread(result.first, 1, fileSize, f) != fileSize) {
                delete[] result.first;
                result.first = nullptr;
            }
            else
                result.second = fileSize;
            fclose(f);
        }
    }
    else {
        auto orlPath = inPath;
        orlPath.replace_extension(".orl");
        if (exists(orlPath) && is_regular_file(orlPath)) {
            FILE *ordFile = _wfopen(inPath.c_str(), L"rb");
            FILE *orlFile = _wfopen(orlPath.c_str(), L"rb");
            if (ordFile && orlFile) {
                fseek(ordFile, 0, SEEK_END);
                unsigned int ordFileSize = ftell(ordFile);
                fseek(ordFile, 0, SEEK_SET);
                fseek(orlFile, 0, SEEK_END);
                unsigned int orlFileSize = ftell(orlFile);
                fseek(orlFile, 0, SEEK_SET);
                result.first = new unsigned char[ordFileSize + orlFileSize];
                if (fread(result.first, 1, ordFileSize, ordFile) != ordFileSize || fread(result.first + ordFileSize, 1, orlFileSize, orlFile) != orlFileSize) {
                    delete[] result.first;
                    result.first = nullptr;
                }
                else
                    result.second = ordFileSize + orlFileSize;
            }
            if (ordFile)
                fclose(ordFile);
            if (orlFile)
                fclose(orlFile);
        }
    }
    return result;
}
