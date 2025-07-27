#include "main.h"
#include <stdio.h>
#include <fstream>

namespace dump {

struct Relocation : public Elf32_Rel {

};

struct Symbol : public Elf32_Sym {
    string name;
};

class Writer {
public:
    static unsigned int mSpacing;
    static string mResult;
    static void openScope(string const &title, unsigned int offset, string const &comment = string());
    static void closeScope();
    static string spacing();
    static void writeLine(string const &line, string const &comment = string());
    static void writeField(string const &name, string const &value, string const &comment = string());
};

string Writer::mResult;
unsigned int Writer::mSpacing = 0;
const unsigned int SPACING = 4;
map<unsigned int, Symbol> symbolRelocations;
void *currentData = nullptr;

void Writer::openScope(string const &title, unsigned int offset, string const &comment) {
    mResult += spacing() + title;
    if (mSpacing == 0)
        mResult += " @" + Format("%X", offset);
    mResult += " {";
    if (!comment.empty())
        mResult += " // " + comment;
    mResult += "\n";
    mSpacing += SPACING;
}

void Writer::closeScope() {
    mSpacing -= SPACING;
    mResult += spacing() + "}\n";
}

string Writer::spacing() {
    if (mSpacing > 0)
        return string(mSpacing, L' ');
    return string();
}

void Writer::writeLine(string const &line, string const &comment) {
    mResult += spacing() + line;
    if (!comment.empty())
        mResult += " // " + comment;
    mResult += "\n";
}

void Writer::writeField(string const &name, string const &value, string const &comment) {
    mResult += spacing() + name + ": " + value;
    if (!comment.empty())
        mResult += " // " + comment;
    mResult += "\n";
}

struct Struct {
    unsigned int(*mWriter)(void *, string const &, unsigned char *, unsigned int);
    unsigned int(*mArrayWriter)(void *, string const &, unsigned char *, unsigned int, unsigned int);

    Struct() {
        mWriter = nullptr;
        mArrayWriter = nullptr;
    }

    Struct(unsigned int(*writer)(void *, string const &, unsigned char *, unsigned int)) {
        mWriter = writer;
        mArrayWriter = nullptr;
    }

    Struct(unsigned int(*writer)(void *, string const &, unsigned char *, unsigned int), unsigned int(*arrayWriter)(void *, string const &, unsigned char *, unsigned int, unsigned int)) {
        mWriter = writer;
        mArrayWriter = arrayWriter;
    }
};

map<string, Struct> &GetStructs() {
    static map<string, Struct> structs;
    return structs;
}

unsigned int WriteInt8(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%d", GetAt<char>(data, offset)));
    return 1;
}

unsigned int WriteUInt8(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%u", GetAt<unsigned char>(data, offset)));
    return 1;
}

unsigned int WriteInt16(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%d", GetAt<short>(data, offset)));
    return 2;
}

unsigned int WriteUInt16(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%u", GetAt<unsigned short>(data, offset)));
    return 2;
}

unsigned int WriteInt32(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%d", GetAt<int>(data, offset)));
    return 4;
}

unsigned int WriteUInt32(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%u", GetAt<unsigned int>(data, offset)));
    return 4;
}

unsigned int WriteBool32(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%u", GetAt<unsigned int>(data, offset)));
    return 4;
}

unsigned int WriteFloat(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%.4f", GetAt<float>(data, offset)));
    return 4;
}

string VShaderDeclType(unsigned char type) {
    switch (type) {
    case 0:
        return "D3DCOLOR";
    case 1:
        return "FLOAT2";
    case 2:
        return "FLOAT3";
    case 3:
        return "FLOAT4";
    case 4:
        return "D3DCOLOR";
    case 5:
        return "";
    }
    return Format("%02X", type);
}

unsigned int WriteVShaderDecl(void *, string const &name, unsigned char *data, unsigned int offset) {
    unsigned char *decl = At<unsigned char>(data, offset);
    Writer::writeField(name, Format("%02X %02X %02X %02X", decl[0], decl[1], decl[2], decl[3]));
    return 4;
}

string CommandName(unsigned int id) {
    switch (id) {
    case 0:
        return "NO_COMMAND";
    case 1:
        return "NOP_1";
    case 2:
        return "SET_VERTEX_SHADER_CONSTANT_G";
    case 3:
        return "NOP_3";
    case 4:
        return "SET_STREAM_SOURCE";
    case 6:
        return "NOP_6";
    case 7:
        return "SET_INDEX_BUFFER";
    case 9:
        return "SET_SAMPLER_G";
    case 16:
        return "DRAW_PRIM";
    case 17:
        return "DRAW_INDEXED_PRIM_NO_Z_WRITE";
    case 18:
        return "DRAW_INDEXED_PRIM";
    case 28:
        return "SET_VERTEX_BONE_WEIGHTS";
    case 30:
        return "SET_VERTEX_SHADER_CONSTANT_L_30";
    case 31:
        return "SET_VERTEX_SHADER_CONSTANT_L_31";
    case 32:
        return "SET_SAMPLER";
    case 33:
        return "SET_GEO_PRIM_STATE";
    case 35:
        return "SET_VERTEX_SHADER_TRANSPOSED_MATRIX";
    case 40:
        return "SET_ANIMATION_BUFFER";
    case 46:
        return "SET_VERTEX_SHADER_CONSTANT_L_46";
    case 65:
        return "DRAW_INDEXED_PRIM_AND_END";
    case 69:
        return "SETUP_RENDER";
    case 72:
        return "SET_PIXEL_SHADER_CONTANT_G_72";
    case 73:
        return "SET_PIXEL_SHADER_CONTANT_G_73";
    case 75:
        return "SET_STREAM_SOURCE_SKINNED";
    }
    return Format("COMMAND_%02d", id);
}

unsigned int WriteCommand(void *, string const &name, unsigned char *data, unsigned int offset) {
    unsigned short id = GetAt<unsigned short>(data, offset + 2);
    unsigned short size = GetAt<unsigned short>(data, offset);
    string line;
    line += "{ " + CommandName(id) + ", { ";
    for (unsigned int i = 1; i < size; i++) {
        if (i != 1)
            line += ", ";
        unsigned int paramOffset = offset + i * 4;
        int paramValue = GetAt<unsigned int>(data, paramOffset);
        string paramLine;
        auto it = symbolRelocations.find(paramOffset);
        if (it != symbolRelocations.end()) {
            if ((*it).second.st_info == 0x10)
                paramLine = "(extern(" + (*it).second.name + ")";
            else
                paramLine = Format("@%X", paramValue);
        }
        else
            paramLine = Format(paramValue > 32'000 ? "0x%X" : "%d", paramValue);
        line += paramLine;
    }
    line += " } },";
    Writer::writeLine(line);
    return size * 4;
}

unsigned int WriteOffset(void *, string const &name, unsigned char *data, unsigned int offset) {
    string strValue;
    auto it = symbolRelocations.find(offset);
    if (it != symbolRelocations.end() && (*it).second.st_info == 0x10)
        strValue = (*it).second.name + " (extern)";
    else {
        auto value = GetAt<unsigned int>(data, offset);
        strValue = Format("0x%X", value);
        if (!value)
            strValue += " (null)";
    }
    Writer::writeField(name, strValue);
    return 4;
}

unsigned int WriteNameOffset(void *, string const &name, unsigned char *data, unsigned int offset) {
    auto value = GetAt<unsigned int>(data, offset);
    if (!value)
        Writer::writeField(name, "0x0 (null)");
    else {
        string strValue = string("\"") + (char *)(&data[value]) + "\"";
        strValue += Format(" @%X", value);
        Writer::writeField(name, strValue);
    }
    return 4;
}

unsigned int WriteName(void *, string const &name, unsigned char *data, unsigned int offset) {
    int len = strlen((char const *)data + offset) + 1;
    if (!Writer::mSpacing) {
        string line = string("\"") + ((char const *)(data)+offset) + "\", 00";
        Writer::writeLine(line + " @" + Format("%X", offset));
    }
    else
        Writer::writeField(name, string("\"") + ((char const *)data + offset) + "\"");
    return len;
}

unsigned int WriteNameAligned(void *, string const &name, unsigned char *data, unsigned int offset) {
    int len = strlen((char const *)data + offset) + 1;
    unsigned int padding = (-len) & 3;
    if (!Writer::mSpacing) {
        string line = string("\"") + ((char const *)data + offset) + "\", 00";
        for (unsigned int i = 0; i < padding; i++)
            line += " 00";
        Writer::writeLine(line + " @" + Format("%X", offset));
    }
    else
        Writer::writeField(name, string("\"") + ((char const *)data + offset) + "\"");
    return len + padding;
}

unsigned int WriteVector3(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%.4f %.4f %.4f", GetAt<float>(data, offset), GetAt<float>(data, offset + 4), GetAt<float>(data, offset + 8)));
    return 12;
}

unsigned int WriteVector4(void *, string const &name, unsigned char *data, unsigned int offset) {
    Writer::writeField(name, Format("%.4f %.4f %.4f %.4f", GetAt<float>(data, offset), GetAt<float>(data, offset + 4), GetAt<float>(data, offset + 8), GetAt<float>(data, offset + 12)));
    return 16;
}

unsigned int WriteObject(void *baseObj, string const &type, string const &name, unsigned char *data, unsigned int offset, unsigned int count = 0) {
    if (count > 0)
        Writer::openScope(Format("Array[%d] of ", count) + type, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    auto struc = GetStructs()[ToLower(type)];
    if (count > 0) {
        if (struc.mArrayWriter)
            bytesWritten = struc.mArrayWriter(baseObj, name, data, offset, count);
        else {
            if (struc.mWriter) {
                for (unsigned int i = 0; i < count; i++)
                    bytesWritten += struc.mWriter(baseObj, name + Format("[%d]", i), data, offset + bytesWritten);
            }
        }
    }
    else {
        if (struc.mWriter)
            bytesWritten = struc.mWriter(baseObj, name, data, offset);
    }
    if (count > 0)
        Writer::closeScope();
    return bytesWritten; // TODO: show error message
}

unsigned int WriteObjectWithFields(void *baseObj, string const &type, string const &name, unsigned char *data, unsigned int offset, vector<pair<string, string>> const &fields, unsigned int count = 0) {
    Writer::openScope(type + " " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    for (auto const &f : fields) {
        bytesWritten += WriteObject(baseObj, f.first, f.second, data, offset + bytesWritten, count);
    }
    Writer::closeScope();
    return bytesWritten;
}

string EnumValue(int value, std::initializer_list<std::pair<const int, string>> enumValues) {
    map<int, string> m(enumValues);
    string valueStr = Format("%d", value);
    string enumStr;
    if (m.contains(value))
        enumStr = m[value];
    else
        enumStr = "UNKNOWN";
    return valueStr + " (" + enumStr + ")";
}

unsigned int WriteEnum(string const &name, unsigned char *data, unsigned int offset, std::initializer_list<std::pair<const int, string>> enumValues) {
    Writer::writeField(name, EnumValue(GetAt<int>(data, offset), enumValues));
    return 4;
}

unsigned int WriteEnum16Bit(string const &name, unsigned char *data, unsigned int offset, std::initializer_list<std::pair<const int, string>> enumValues) {
    Writer::writeField(name, EnumValue(GetAt<short>(data, offset), enumValues));
    return 2;
}

unsigned int WriteMatrix4x4(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "Matrix4x4", name, data, offset,
        {
            { "VECTOR4", "vec1" },
        { "VECTOR4", "vec2" },
        { "VECTOR4", "vec3" },
        { "VECTOR4", "posn" }
        });
}

unsigned int WriteBBOX(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "BBOX", name, data, offset,
        {
         { "VECTOR3", "Min" },
        { "VECTOR3", "Max" }
        });
}

unsigned int WriteModel(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "Model", name, data, offset,
        {
            { "OFFSET", "ModifiableDataDescriptors" },
        { "UINT32", "NumModifiableDataDescriptors" },
        { "UINT32", "NumVariations" },
        { "MATRIX4X4", "TransformationMatrix" },
        { "VECTOR4", "unknown1" },
        { "VECTOR4", "unknown2" },
        { "VECTOR4", "BoundingMin" },
        { "VECTOR4", "BoundingMax" },
        { "VECTOR4", "Center" },
        { "UINT32", "NumModelLayers" },
        { "OFFSET", "ModelLayersNames" },
        { "UINT32", "unknown3" },
        { "OFFSET", "unknown4" },
        { "OFFSET", "unknown5" },
        { "OFFSET", "NextModel" },
        { "NAMEOFFSET", "ModelName" },
        { "OFFSET", "InterleavedVertices" },
        { "OFFSET", "Textures" },
        { "UINT32", "VariationID" },
        { "OFFSET", "ModelLayersStates" },
        { "BOOL32", "IsModelRenderable" },
        { "OFFSET", "ModelLayers" },
        { "UINT32", "unknown6" },
        { "UINT32", "unknown7" },
        { "UINT32", "SkeletonVersion" },
        { "UINT32", "LastFrame" }
        });
}

unsigned int WriteRenderMethod(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    if (globalVars().target->Version() <= 2) {
        return WriteObjectWithFields(baseObj, "RenderMethod", name, data, offset,
            {
                { "OFFSET", "CodeBlock" },
                { "OFFSET", "UsedCodeBlock" },
                { "OFFSET", "MicroCode" },
                { "OFFSET", "Effect" },
                { "OFFSET", "Parent" },
                { "OFFSET", "ParameterNames" },
                { "INT32", "unknown2" },
                { "INT32", "unknown3" },
                { "OFFSET", "unknown4" },
                { "OFFSET", "GeometryDataBuffer" },
                { "INT32", "ComputationIndexCommand" }
            });
    }
    else {
        return WriteObjectWithFields(baseObj, "RenderMethod", name, data, offset,
            {
                { "OFFSET", "CodeBlock" },
                { "OFFSET", "UsedCodeBlock" },
                { "OFFSET", "MicroCode" },
                { "OFFSET", "Effect" },
                { "OFFSET", "Parent" },
                { "OFFSET", "ParameterNames" },
                { "INT32", "unknown2" },
                { "INT32", "unknown3" },
                { "OFFSET", "unknown4" },
                { "OFFSET", "GeometryDataBuffer" },
                { "INT32", "ComputationIndexCommand" },
                { "NAMEOFFSET", "Name" },
                { "OFFSET", "EAGLModel" }
            });
    }
}

unsigned int WriteModelTexture(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("ModelTexture " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    char const *texName = GetAt<char const *>(data, offset + bytesWritten);
    bytesWritten += WriteObject(baseObj, "NAMEOFFSET", "Name", data, offset, 0);
    if (texName) {
        unsigned int tarCount = GetAt<unsigned int>(data, offset + bytesWritten);
        bytesWritten += WriteObject(baseObj, "UINT32", "TARCount", data, offset + bytesWritten, 0);
        if (tarCount > 0)
            bytesWritten += WriteObject(baseObj, "OFFSET", "Texture", data, offset + bytesWritten, tarCount);
        bytesWritten += WriteObject(baseObj, "UINT16", "unknown2", data, offset + bytesWritten, 0);
        bytesWritten += WriteObject(baseObj, "UINT16", "unknown3", data, offset + bytesWritten, 0);
    }
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteModelTexture_OldFormat(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("ModelTexture_OldFormat " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    char const *texName = GetAt<char const *>(data, offset + bytesWritten);
    bytesWritten += WriteObject(baseObj, "NAMEOFFSET", "Name", data, offset, 0);
    if (texName) {
        unsigned int tarCount = GetAt<unsigned int>(data, offset + bytesWritten);
        bytesWritten += WriteObject(baseObj, "UINT32", "TARCount", data, offset + bytesWritten, 0);
        if (tarCount > 0)
            bytesWritten += WriteObject(baseObj, "OFFSET", "Texture", data, offset + bytesWritten, tarCount);
    }
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteBone(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "Bone", name, data, offset,
        {
            { "UINT32", "Index" },
            { "UINT32", "unknown1" },
            { "UINT32", "unknown2" },
            { "UINT32", "unknown3" },
        });
}

unsigned int WriteModifiableData(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "ModifiableData", name, data, offset,
        {
            { "NAMEOFFSET", "Name" },
            { "UINT16", "EntrySize" },
            { "UINT16", "unknown1" },
            { "UINT32", "EntriesCount" },
            { "OFFSET", "Entries" }
        });
}

unsigned int WriteModelLayerBounding(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "ModelLayerBounding", name, data, offset,
        {
            { "VECTOR4", "Min" },
            { "VECTOR4", "Max" },
            { "VECTOR4", "Center" }
        });
}

unsigned int WriteGeoPrimState(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "GeoPrimState", name, data, offset,
        {
            { "UINT32", "PrimitiveType" },
            { "UINT32", "Shading" },
            { "BOOL32", "CullingEnabled" },
            { "UINT32", "CullDirection" },
            { "UINT32", "DepthTestMethod" },
            { "UINT32", "AlphaBlendMode" },
            { "BOOL32", "AlphaTestEnable" },
            { "UINT32", "AlphaCompareValue" },
            { "UINT32", "AlphaTestMethod" },
            { "BOOL32", "TextureEnabled" },
            { "UINT32", "TransparencyMethod" },
            { "UINT32", "FillMode" },
            { "UINT32", "BlendOperation" },
            { "UINT32", "SourceBlend" },
            { "UINT32", "DestinationBlend" },
            { "FLOAT", "NumberOfPatchSegments" },
            { "INT32", "ZWritingEnabled" }
        });
}

unsigned int WriteComputationIndex(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "ComputationIndex", name, data, offset,
        {
            { "UINT16", "ActiveTechnique" },
            { "UINT16", "unknown1" },
        });
}

unsigned int WriteIrradLight(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "IrradLight", name, data, offset,
        {
            { "VECTOR4", "unknown1" },
            { "VECTOR4", "unknown2" },
            { "VECTOR4", "unknown3" },
            { "VECTOR4", "unknown4" },
            { "VECTOR4", "unknown5" },
            { "VECTOR4", "unknown6" },
            { "VECTOR4", "unknown7" },
            { "VECTOR4", "unknown8" },
            { "VECTOR4", "unknown9" },
            { "VECTOR4", "unknown10" }
        });
}

unsigned int WriteLight(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "Light", name, data, offset,
        {
            { "MATRIX4X4", "unknown1" },
            { "VECTOR4", "unknown2" },
            { "VECTOR4", "unknown3" },
            { "VECTOR4", "unknown4" }
        });
}

unsigned int WriteModelLayerStates(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "ModelLayerStates", name, data, offset,
        {
            { "UINT16", "unknown1" },
            { "UINT16", "Visibility" }
        });
}

unsigned int WriteAnimationBank(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    unsigned short bankSize = GetAt<unsigned short>(data, offset);
    if (bankSize == 0x18) {
        return WriteObjectWithFields(baseObj, "AnimationBank", name, data, offset,
            {
                { "UINT32", "Size" },
                { "UINT32", "NumAnimations" },
                { "UINT32", "unknown1" },
                { "OFFSET", "Animations" },
                { "OFFSET", "AnimationNames" },
                { "UINT32", "Stat" },
            });
    }
    else {
        return WriteObjectWithFields(baseObj, "AnimationBank", name, data, offset,
            {
                { "UINT32", "Size" },
                { "UINT32", "NumAnimations" },
                { "UINT32", "unknown1" },
                { "UINT32", "unknown2" },
                { "OFFSET", "Animations" },
                { "OFFSET", "AnimationNames" },
                { "UINT32", "Stat" },
            });
    }
}

unsigned int WriteAnimation(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("Animation " + name, offset);
    unsigned int bytesWritten = 0;
    bytesWritten += WriteEnum16Bit("Type", data, offset + bytesWritten,
    { 
        { -1, "ANIM_INVALID" },
        {  0, "ANIM_RAWPOSE" },
        {  1, "ANIM_RAWEVENT" },
        {  2, "ANIM_RAWLINEAR" },
        {  3, "ANIM_CYCLE" },
        {  4, "ANIM_EVENTBLENDER" },
        {  5, "ANIM_GRAFT" },
        {  6, "ANIM_POSEBLENDER" },
        {  7, "ANIM_POSEMIRROR" },
        {  8, "ANIM_RUNBLENDER" },
        {  9, "ANIM_TURNBLENDER" },
        { 10, "ANIM_DELTALERP" },
        { 11, "ANIM_DELTAQUAT" },
        { 12, "ANIM_KEYLERP" },
        { 13, "ANIM_KEYQUAT" },
        { 14, "ANIM_PHASE" },
        { 15, "ANIM_COMPOUND" },
        { 16, "ANIM_RAWSTATE" },
        { 17, "ANIM_DELTAQ" },
        { 18, "ANIM_DELTAQFAST" },
        { 19, "ANIM_DELTASINGLEQ" },
        { 20, "ANIM_DELTAF3" },
        { 21, "ANIM_DELTAF1" },
        { 22, "ANIM_STATELESSQ" },
        { 23, "ANIM_STATELESSF3" },
        { 24, "ANIM_CSISEVENT" },
        { 25, "ANIM_POSEANIM" }
    });
    bytesWritten += WriteObject(baseObj, "UINT16", "CheckSum", data, offset + bytesWritten, 0);
    unsigned short animType = GetAt<unsigned short>(data, offset);
    if (animType == 15) { // ANIM_COMPOUND
        bytesWritten += WriteObject(baseObj, "OFFSET", "AttributeBlock", data, offset + bytesWritten, 0);
        bytesWritten += WriteObject(baseObj, "UINT16", "NumChannels", data, offset + bytesWritten, 0);
        bytesWritten += WriteObject(baseObj, "UINT16", "NumFrames", data, offset + bytesWritten, 0);
        unsigned short numChannels = GetAt<unsigned short>(data, offset + 0x8);
        if (numChannels)
            bytesWritten += WriteObject(baseObj, "OFFSET", "ChannelOffset", data, offset + bytesWritten, numChannels);
    }
    else if (animType == 10 || animType == 11) { // ANIM_DELTAQUAT, ANIM_DELTALERP
        bytesWritten += WriteObject(baseObj, "OFFSET", "DeltaCompressedData", data, offset + bytesWritten, 0);
        bytesWritten += WriteObject(baseObj, "UINT16", "NumFrames", data, offset + bytesWritten, 0);
        unsigned short deltaCompressedDataOffset = GetAt<unsigned short>(data, offset + 0x4);
        if (deltaCompressedDataOffset != 0) {
            unsigned short numDofs = GetAt<unsigned short>(data, deltaCompressedDataOffset);
            unsigned short numDofIndices = (animType == 11) ? (numDofs / 4) : numDofs;
            if (numDofIndices)
                bytesWritten += WriteObject(baseObj, "UINT16", "DofIndex", data, offset + bytesWritten, numDofIndices);
        }
    }
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteBoneState(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "BoneState", name, data, offset,
        {
            { "VECTOR3", "Scale" },
            { "INT32", "ParentBoneID" },
            { "VECTOR4", "RotationQuat" },
            { "VECTOR4", "Translation" },
            { "MATRIX4X4", "Transform" }
        });
}

unsigned int WriteBlendTarget(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("BlendTarget " + name, offset);
    unsigned int bytesWritten = 0;
    unsigned int numBlendShapes = GetAt<unsigned int>(data, offset + 0x4);
    bytesWritten += WriteObject(baseObj, "NAMEOFFSET", "InterleavedVerticesName", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumBlendShapes", data, offset + bytesWritten, 0);
    if (numBlendShapes)
        bytesWritten += WriteObject(baseObj, "BlendShape", Format("BlendShape.%X", offset + bytesWritten), data, offset + bytesWritten, numBlendShapes);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteBlendShape(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("BlendShape " + name, offset);
    unsigned int bytesWritten = 0;
    unsigned int numVertexTargets = GetAt<unsigned int>(data, offset + 0x4);
    bytesWritten += WriteObject(baseObj, "UINT32", "BlendWeightIndex", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumVertexAttributes", data, offset + bytesWritten, 0);
    if (numVertexTargets)
        bytesWritten += WriteObject(baseObj, "BlendShapeVertexAttribute", Format("BlendShapeVertexAttribute.%X", offset + bytesWritten), data, offset + bytesWritten, numVertexTargets);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteBlendShapeVertexAttribute(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("BlendShapeVertexAttribute " + name, offset);
    unsigned int bytesWritten = 0;
    unsigned int flags = GetAt<unsigned int>(data, offset);
    unsigned int blendDataSize = flags & 0xFFFFFFF;
    unsigned int componentType = (flags >> 28) & 0x3;
    unsigned int numComponents = (flags >> 30) & 0x3;
    string componentTypeName = "UNKNOWN";
    if (componentType == 1)
        componentTypeName = "BYTE";
    else if (componentType == 2)
        componentTypeName = "USHORT";
    else if (componentType == 4 || componentType == 0)
        componentTypeName = "FLOAT";
    Writer::writeField("BlendDataSize", Format("%u", blendDataSize));
    Writer::writeField("ComponentType", Format("%u (%s)", componentType, componentTypeName.c_str()));
    Writer::writeField("NumComponents", Format("%u", numComponents));
    bytesWritten += 4;
    bytesWritten += WriteObject(baseObj, "UINT32", "NumVertices", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "InterleavedVBOffset", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "InterleavedVBIndex", data, offset + bytesWritten, 0);
    Writer::openScope("BlendData [" + Format("%u", blendDataSize) + "]", offset + bytesWritten);
    string ary;
    for (unsigned int i = 0; i < min(blendDataSize, 100u); i++) {
        if (i != 0)
            ary += " ";
        ary += Format("%02X", ((unsigned char *)data)[offset + bytesWritten + i]);
    }
    if (blendDataSize > 100)
        ary += "...";
    Writer::writeLine(ary);
    Writer::closeScope();
    bytesWritten += blendDataSize;
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteCommandObjectParameter(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "CommandObjectParameter", name, data, offset,
        {
            { "UINT32", "Count" },
            { "OFFSET", "Data" }
        });
}

unsigned int WriteTexture(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "Texture", name, data, offset,
        {
             { "UINT32", "unknown1" },
             { "UINT32", "Tag" },
             { "UINT32", "unknown2" },
             { "FLOAT",  "unknown3" },
             { "UINT32", "unknown4" },
             { "FLOAT",  "unknown5" },
             { "UINT32", "unknown6" },
             { "UINT32", "WrapU" },
             { "UINT32", "WrapV" },
             { "UINT32", "WrapW" },
             { "UINT32", "unknown7" },
             { "UINT32", "unknown8" }
        });
}

unsigned int WriteGeometryInfo(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "GeometryInfo", name, data, offset,
        {
            { "UINT32", "NumIndices" },
            { "UINT32", "NumVertices" },
            { "UINT32", "NumPrimitives" },
            { "BOOL32", "unknown1" }
        });
}

unsigned int WriteSkeleton(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("Skeleton " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    unsigned int numBones = GetAt<unsigned int>(baseObj, 0x8);
    bytesWritten += WriteObject(baseObj, "UINT16", "Signature1", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT16", "unknown1", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "Signature2", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumBones", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "OFFSET", "unknown2", data, offset + bytesWritten, 0);
    if (numBones)
        bytesWritten += WriteObject(baseObj, "BoneState", Format("BoneState.%X", offset + bytesWritten), data, offset + bytesWritten, numBones);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteMorph(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("Morph " + name, offset);
    unsigned int bytesWritten = 0;
    unsigned int unknown3 = GetAt<unsigned int>(baseObj, 0x10);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumBlendWeights", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "OFFSET", "BlendWeightsNames", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "OFFSET", "BlendWeightsValues", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "unknown1", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumBlendTargets", data, offset + bytesWritten, 0);
    if (unknown3)
        bytesWritten += WriteObject(baseObj, "BlendTarget", Format("BlendTarget.%X", offset + bytesWritten), data, offset + bytesWritten, unknown3);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteModelLayersStates(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("ModelLayersStates " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    unsigned int numLayers = GetAt<unsigned int>(baseObj, 0x9C);
    bytesWritten += WriteObject(baseObj, "INT32", "unknown1", data, offset, 0);
    if (numLayers > 0)
        bytesWritten += WriteObject(baseObj, "ModelLayerStates", Format("ModelLayerStates.%X", offset + bytesWritten), data, offset + bytesWritten, numLayers);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteModelLayer(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("ModelLayer " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    bytesWritten += WriteObject(baseObj, "UINT32", "NumRenderDescriptors", data, offset, 0);
    unsigned int numRenderDescriptors = GetAt<unsigned int>(data, offset);
    bytesWritten += WriteObject(baseObj, "OFFSET", Format("RenderDescriptor.%X", offset + bytesWritten), data, offset + bytesWritten, numRenderDescriptors);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteRenderDescriptorListEntry(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("RenderDescriptorListEntry " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    unsigned int entryType = GetAt<unsigned int>(data, offset);
    string entryTypeName = "UNKNOWN";
    if (entryType == 0)
        entryTypeName = "NULL";
    else if (entryType == 0xA0000000)
        entryTypeName = "START";
    else if (entryType == 0xA0000001)
        entryTypeName = "GROUP";
    else if (entryType == 0xA000FFFF)
        entryTypeName = "MESH";
    Writer::writeField("EntryType", Format("%X (%s)", entryType, entryTypeName.c_str()));
    bytesWritten += 4;
    if (entryType == 0xA000FFFF)
        bytesWritten += WriteObject(baseObj, "OFFSET", "RenderDescriptor", data, offset + bytesWritten, 0);
    else if (entryType != 0) {
        bytesWritten += WriteObject(baseObj, "UINT32", "unknown1", data, offset + bytesWritten, 0);
        bytesWritten += WriteObject(baseObj, "UINT32", "Size", data, offset + bytesWritten, 0);
    }
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteModelLayers(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("ModelLayers " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    unsigned int modelLayersHeader = GetAt<unsigned int>(data, offset);
    bool isOldFormat = modelLayersHeader == 0xA0000000;
    if (isOldFormat) {
        void *modelLayers = &data[offset];
        do {
            modelLayersHeader = GetAt<unsigned int>(data, offset + bytesWritten);
            bytesWritten += WriteObject(baseObj, "RenderDescriptorListEntry", Format("RenderDescriptorListEntry.%X", offset + bytesWritten), data, offset + bytesWritten, 0);
            
        } while (modelLayersHeader != 0);
    }
    else {
        unsigned int numLayers = GetAt<unsigned int>(baseObj, 0x9C);
        bytesWritten += WriteObject(baseObj, "OFFSET", "unknown1", data, offset, 0);
        bytesWritten += WriteObject(baseObj, "ModelLayer", Format("ModelLayer.%X", offset + bytesWritten), data, offset + bytesWritten, numLayers);
    }
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteEAGLMicroCode(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("EAGLMicroCode " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    bytesWritten += WriteObject(baseObj, "UINT32", "MaxNumSelectedTechniques", data, offset + bytesWritten, 0);
    bytesWritten += WriteEnum("EffectType", data, offset + bytesWritten, { { 0, "EFFECT" }, { 1, "TECHNIQUE" }, { 2, "PASS" }});
    unsigned int numVSDeclarations = GetAt<unsigned int>(baseObj, bytesWritten);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumVertexShaderDeclarations", data, offset + bytesWritten, 0);
    if (numVSDeclarations)
        bytesWritten += WriteObject(baseObj, "VSDECL", "VertexShaderDeclaration", data, offset + bytesWritten, numVSDeclarations);
    unsigned int numTechniques = GetAt<unsigned int>(baseObj, bytesWritten);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumTechniques", data, offset + bytesWritten, 0);
    if (numTechniques)
        bytesWritten += WriteObject(baseObj, "EffectTechnique", Format("EffectTechnique.%X", offset + bytesWritten), data, offset + bytesWritten, numTechniques);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteEffectTechnique(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("EffectTechnique " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    bytesWritten += WriteEnum("TechniqueType", data, offset + bytesWritten, { { 0, "EFFECT" }, { 1, "TECHNIQUE" }, { 2, "PASS" } });
    bytesWritten += WriteObject(baseObj, "UINT32", "TecniqueId", data, offset + bytesWritten, 0);
    unsigned int numStateAssignments1 = GetAt<unsigned int>(data, offset + bytesWritten);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumTechniqueSamplerAssignments", data, offset + bytesWritten, 0);
    unsigned int numStateAssignments2 = GetAt<unsigned int>(data, offset + bytesWritten);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumTechniqueGeoPrimAssignments", data, offset + bytesWritten, 0);
    if (numStateAssignments1 + numStateAssignments2)
        bytesWritten += WriteObject(baseObj, "StateAssignment", Format("StateAssignment.%X", offset + bytesWritten), data, offset + bytesWritten, numStateAssignments1 + numStateAssignments2);
    unsigned int numPasses = GetAt<unsigned int>(data, offset + bytesWritten);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumPasses", data, offset + bytesWritten, 0);
    if (numPasses)
        bytesWritten += WriteObject(baseObj, "EffectPass", Format("EffectPass.%X", offset + bytesWritten), data, offset + bytesWritten, numPasses);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteEffectPass(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("EffectPass " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    bytesWritten += WriteEnum("PassType", data, offset + bytesWritten, { { 0, "EFFECT" }, { 1, "TECHNIQUE" }, { 2, "PASS" } });
    unsigned int numStateAssignments1 = GetAt<unsigned int>(data, offset + bytesWritten);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumPassSamplerAssignments", data, offset + bytesWritten, 0);
    unsigned int numStateAssignments2 = GetAt<unsigned int>(data, offset + bytesWritten);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumPassGeoPrimAssignments", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "UINT32", "pass_unknown1", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "StateAssignment", Format("StateAssignment.%X", offset + bytesWritten), data, offset + bytesWritten, numStateAssignments1 + numStateAssignments2 + 3);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteStateAssignment(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("StateAssignment " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    unsigned int type = GetAt<unsigned int>(data, offset + bytesWritten);
    bytesWritten += WriteEnum("Type", data, offset + bytesWritten, { { 3, "SAMPLER" }, { 4, "TEXTURE_STAGE" }, { 5, "GEO_PRIM" }, { 6, "VERTEX_SHADER" } , { 7, "PIXEL_SHADER" } , { 8, "VERTEX_SHADER_REFERENCE" } });
    if (type == 3) {
        bytesWritten += WriteObject(baseObj, "UINT32", "TextureStage", data, offset + bytesWritten, 0);
        bytesWritten += WriteObject(baseObj, "UINT32", "Sampler", data, offset + bytesWritten, 0);
    }
    else if (type == 4) {
        struct TextureStageState {
            unsigned int colorOp[8];
            unsigned int colorArg[8][3];
            unsigned int alphaOp[8];
            unsigned int alphaArg[8][3];
            unsigned int resultArg[8];
            unsigned int bumpEnvMat00[8];
            unsigned int bumpEnvMat01[8];
            unsigned int bumpEnvMat10[8];
            unsigned int bumpEnvMat11[8];
            unsigned int texCoordIndex[8];
            unsigned int bumpEnvScale[8];
            unsigned int bumpEnvLOffset[8];
            unsigned int textureTransformFlags[8];
            unsigned int maxTextureStage;
        };
        TextureStageState *ts = At<TextureStageState>(data, offset + bytesWritten);
        auto WriteLineTS = [](char const *tsName, unsigned int *values) {
            string tsLine = tsName;
            tsLine += ": ";
            for (size_t i = 0; i < 8; i++) {
                if (i != 0)
                    tsLine += " ";
                tsLine += Format("%u", values[i]);
            }
            Writer::writeLine(tsLine);
        };
        Writer::openScope("TextureStageState", offset + bytesWritten);
        WriteLineTS("state_D3DTSS_COLOROP", ts->colorOp);
        WriteLineTS("state_D3DTSS_COLORARG0", ts->colorArg[0]);
        WriteLineTS("state_D3DTSS_COLORARG1", ts->colorArg[1]);
        WriteLineTS("state_D3DTSS_COLORARG2", ts->colorArg[2]);
        WriteLineTS("state_D3DTSS_RESULTARG", ts->resultArg);
        WriteLineTS("state_D3DTSS_BUMPENVMAT00", ts->bumpEnvMat00);
        WriteLineTS("state_D3DTSS_BUMPENVMAT01", ts->bumpEnvMat01);
        WriteLineTS("state_D3DTSS_BUMPENVMAT10", ts->bumpEnvMat10);
        WriteLineTS("state_D3DTSS_BUMPENVMAT11", ts->bumpEnvMat11);
        WriteLineTS("state_D3DTSS_TEXCOORDINDEX", ts->texCoordIndex);
        WriteLineTS("state_D3DTSS_BUMPENVLSCALE", ts->bumpEnvScale);
        WriteLineTS("state_D3DTSS_BUMPENVLOFFSET", ts->bumpEnvLOffset);
        WriteLineTS("state_D3DTSS_TEXTURETRANSFORMFLAGS", ts->textureTransformFlags);
        Writer::writeLine("MaxTextureStage: " + Format("%u", ts->maxTextureStage));
        Writer::closeScope();
        bytesWritten += 548;
    }
    else if (type == 5) {
        bytesWritten += WriteEnum("GeoPrimStateOffset", data, offset + bytesWritten,
            {
                { 0X00, "PRIMITIVE_TYPE" },
                { 0X04, "SHADING" },
                { 0X08, "CULL_ENABLE" },
                { 0X0C, "CULL_DIRECTION" },
                { 0X10, "DEPTH_TEST_METHOD" },
                { 0X14, "ALPHA_BLEND_MODE" },
                { 0X18, "ALPHA_TEST_ENABLE" },
                { 0X1C, "ALPHA_COMPARE_VALUE" },
                { 0X20, "ALPHA_TEST_METHOD" },
                { 0X24, "TEXTURE_ENABLE" },
                { 0X28, "TRANSPARENCY_METHOD" },
                { 0X2C, "FILL_MODE" },
                { 0X30, "BLEND_OPERATION" },
                { 0X34, "SRC_BLEND" },
                { 0X38, "DST_BLEND" },
                { 0X3C, "NUM_PATCH_SEGMENTS" },
                { 0X40, "Z_WRITES_ENABLE" }
            });
        bytesWritten += WriteObject(baseObj, "UINT32", "GeoPrimStateValue", data, offset + bytesWritten, 0);
    }
    else if (type == 6) {
        unsigned int size = GetAt<unsigned int>(data, offset + bytesWritten) * 4;
        bytesWritten += WriteObject(baseObj, "UINT32", "VertexShaderSizeInInts", data, offset + bytesWritten, 0);
        if (size) {
            Writer::openScope("VertexShader [" + Format("%u", size) + "]", offset + bytesWritten);
            string ary;
            for (unsigned int i = 0; i < min(size, 16u); i++) {
                if (i != 0)
                    ary += " ";
                ary += Format("%02X", ((unsigned char *)data)[offset + bytesWritten + i]);
            }
            if (size > 16)
                ary += "...";
            Writer::writeLine(ary);
            Writer::closeScope();
            bytesWritten += size;
        }
    }
    else if (type == 7) {
        unsigned int size = GetAt<unsigned int>(data, offset + bytesWritten) * 4;
        bytesWritten += WriteObject(baseObj, "UINT32", "PixelShaderSizeInInts", data, offset + bytesWritten, 0);
        if (size) {
            Writer::openScope("PixelShader [" + Format("%u", size) + "]", offset + bytesWritten);
            string ary;
            for (unsigned int i = 0; i < min(size, 16u); i++) {
                if (i != 0)
                    ary += " ";
                ary += Format("%02X", ((unsigned char *)data)[offset + bytesWritten + i]);
            }
            if (size > 16)
                ary += "...";
            Writer::writeLine(ary);
            Writer::closeScope();
            bytesWritten += size;
        }
    }
    else if (type == 8) {
        unsigned int size = GetAt<unsigned int>(data, offset + bytesWritten) * 4;
        bytesWritten += WriteObject(baseObj, "UINT32", "VertexShaderReferenceSizeInInts", data, offset + bytesWritten, 0);
        if (size) {
            Writer::openScope("VertexShaderReference [" + Format("%u", size) + "]", offset + bytesWritten);
            string ary;
            for (unsigned int i = 0; i < min(size, 16u); i++) {
                if (i != 0)
                    ary += " ";
                ary += Format("%02X", ((unsigned char *)data)[offset + bytesWritten + i]);
            }
            if (size > 16)
                ary += "...";
            Writer::writeLine(ary);
            Writer::closeScope();
            bytesWritten += size;
        }
    }
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteRenderCode(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    unsigned int numCommands = 0;
    unsigned int commandOffset = 0;
    unsigned short id = GetAt<unsigned short>(data, offset + commandOffset + 2);
    unsigned short size = GetAt<unsigned short>(data, offset + commandOffset);
    while (id != 0) {
        //Message(Format("%d - %d", id, size));
        numCommands++;
        commandOffset += size * 4;
        id = GetAt<unsigned short>(data, offset + commandOffset + 2);
        size = GetAt<unsigned short>(data, offset + commandOffset);
    }
    unsigned int bytesWritten = 0;
    if (numCommands > 0)
        bytesWritten += WriteObject(baseObj, "COMMAND", "Command", data, offset + bytesWritten, numCommands);
    bytesWritten += WriteObject(baseObj, "UINT32", Format("RenderCodeFooter.%X", offset + bytesWritten), data, offset + bytesWritten, 0);
    return bytesWritten;
}

unsigned int WriteGeoPrimDataBuffer(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("geoprimdatabuffer " + name, offset); // TODO: write references
    unsigned int bytesWritten = 0;
    bytesWritten += WriteObject(baseObj, "UINT32", "unknown1", data, offset + bytesWritten, 0);
    unsigned int numTechniques = 1;
    string shaderName;
    unsigned int rmCodeOffset = (unsigned char *)baseObj - data + 8;
    auto it = symbolRelocations.find(rmCodeOffset);
    if (it != symbolRelocations.end() && (*it).second.st_info == 0x10) {
        string codeName = (*it).second.name;
        if (codeName.ends_with("__EAGLMicroCode"))
            shaderName = codeName.substr(0, codeName.length() - 15);
    }
    else
        shaderName = (char const *)data + GetAt<unsigned int>(baseObj, + 0x2C);
    auto codeShader = globalVars().target->FindShader(shaderName);
    if (codeShader)
        numTechniques = codeShader->numTechniques;
    bytesWritten += WriteObject(baseObj, "RenderCode", "RenderCode", data, offset + bytesWritten, options().onlyFirstTechnique ? 1 : numTechniques);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteRenderDescriptor(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("RenderDescriptor " + name, offset); // TODO: write references
    void *renderMethod = At<void *>(data, GetAt<unsigned int>(data, offset));
    void *renderCode = At<void *>(data, GetAt<unsigned int>(renderMethod, 0));
    unsigned int numCommands = 0;
    unsigned int commandOffset = 0;
    unsigned short id = GetAt<unsigned short>(renderCode, commandOffset + 2);
    unsigned short size = GetAt<unsigned short>(renderCode, commandOffset);
    while (id != 0) {
        //Message(Format("%d - %d", id, size));
        numCommands++;
        commandOffset += size * 4;
        id = GetAt<unsigned short>(renderCode, commandOffset + 2);
        size = GetAt<unsigned short>(renderCode, commandOffset);
    }
    unsigned int bytesWritten = 0;
    bytesWritten += WriteObject(baseObj, "OFFSET", "RenderMethod", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "CommandObjectParameter", "CommandObjectParameter", data, offset + bytesWritten, (numCommands > 2) ? (numCommands - 2) : 1);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteInterleavedVertices(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("InterleavedVertices " + name, offset);
    unsigned int bytesWritten = 0;
    bytesWritten += WriteObject(baseObj, "UINT32", "unknown1", data, offset + bytesWritten, 0);
    unsigned int numInterleavedVerticesDatas = 0;
    unsigned int nameOffset = 0;
    unsigned int curr = 4;
    while (true) {
        nameOffset = GetAt<unsigned int>(data, offset + curr);
        if (!nameOffset)
            break;
        unsigned int numVertexDatas = GetAt<unsigned int>(data, offset + curr + 4);
        curr += 8 + numVertexDatas * 16;
        numInterleavedVerticesDatas++;
    }
    //if (numInterleavedVerticesDatas > 1) {
    //    printf("MORE THAN ONE (%d) InterleavedVertices in %s\n", numInterleavedVerticesDatas, globalVars().currentFilePath.filename().string().c_str());
    //}
    //else if (numInterleavedVerticesDatas > 0) {
    //    printf("InterleavedVertices in %s\n", globalVars().currentFilePath.filename().string().c_str());
    //}
    if (numInterleavedVerticesDatas > 0)
        bytesWritten += WriteObject(baseObj, "InterleavedVerticesData", "InterleavedVerticesDatas", data, offset + bytesWritten, numInterleavedVerticesDatas);
    bytesWritten += WriteObject(baseObj, "UINT32", "Terminator", data, offset + bytesWritten, 0);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteInterleavedVerticesData(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("InterleavedVerticesData " + name, offset);
    unsigned int bytesWritten = 0;
    bytesWritten += WriteObject(baseObj, "NAMEOFFSET", "Name", data, offset + bytesWritten, 0);
    unsigned int numVertexDatas = GetAt<unsigned int>(data, offset + bytesWritten);
    bytesWritten += WriteObject(baseObj, "UINT32", "NumVertexDatas", data, offset + bytesWritten, 0);
    bytesWritten += WriteObject(baseObj, "InterleavedVerticesVertexData", "VertexDatas", data, offset + bytesWritten, numVertexDatas);
    Writer::closeScope();
    return bytesWritten;
}

unsigned int WriteInterleavedVerticesVertexData(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    return WriteObjectWithFields(baseObj, "InterleavedVerticesVertexData", name, data, offset,
    {
         { "UINT32", "Index" },
         { "UINT16", "VertexCount" },
         { "UINT16", "MorphVertexDataSize_MultipleVertexBuffers" },
         { "UINT32",  "VertexBufferSize" },
         { "OFFSET", "VertexBuffer" }
    });
    return 16;
}

unsigned int WriteVertexBuffer(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("VertexBuffer " + name, offset); // TODO: write references
    unsigned int numVertices = GetAt<unsigned int>(baseObj, 28);
    unsigned int vertexSize = GetAt<unsigned int>(baseObj, 8);
    Writer::writeLine(to_string(numVertices) + " vertices (vertex stride " + to_string(vertexSize) + " bytes) [...]");
    // TODO: remove this
    //unsigned char *vb = At<unsigned char>(currentData, GetAt<unsigned int>(baseObj, 24));
    //for (unsigned int i = 0; i < numVertices; i++) {
    //    aiVector3D *pos = (aiVector3D *)vb;
    //    unsigned char *clr1 = vb + 12;
    //    aiVector3D *nrm = (aiVector3D *)(vb + 16);
    //    unsigned char *clr0 = vb + 28;
    //    float *txc = (float *)(vb + 32);
    //    //{ Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 }
    //    Writer::writeLine(Format("%.4f %.4f %.4f n %.4f %.4f %.4f t %.4f %.4f c0 %d %d %d %d c1 %d %d %d %d", pos->x, pos->y, pos->z, nrm->x, nrm->y, nrm->z, txc[0], txc[1], 
    //        clr0[0], clr0[1], clr0[2], clr0[3], clr1[0], clr1[1], clr1[2], clr1[3]));
    //    vb += vertexSize;
    //}
    //
    Writer::closeScope();
    return numVertices * vertexSize;
}

unsigned int WriteIndexBuffer(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("IndexBuffer " + name, offset); // TODO: write references
    unsigned int numIndices = GetAt<unsigned int>(baseObj, 20);
    Writer::writeLine(to_string(numIndices) + " indices [...]");
    Writer::closeScope();
    return numIndices * 2;
}

unsigned int WriteBoneWeightsBuffer(void *baseObj, string const &name, unsigned char *data, unsigned int offset) {
    Writer::openScope("BoneWeightsBuffer " + name, offset); // TODO: write references
    unsigned int numBoneWeights = GetAt<unsigned int>(baseObj, 0);
    struct boneweight { union boneref { float weight; unsigned char boneIndex; }; boneref bones[4]; };
    boneweight *weights = At<boneweight>(currentData, GetAt<unsigned int>(baseObj, 4));
    Writer::writeLine(to_string(numBoneWeights) + " bone weights [...]");
    //for (unsigned int i = 0; i < numBoneWeights; i++) {
    //    string line;
    //    for (unsigned int b = 0; b < 4; b++) {
    //        float weight = weights[i].bones[b].weight;
    //        *(unsigned char *)(&weight) = 0;
    //        line += Format("bone %2d %.4f", weights[i].bones[b].boneIndex, weight);
    //        if (b != 3)
    //            line += "   ";
    //    }
    //    Writer::writeLine(line);
    //}
    Writer::closeScope();
    return numBoneWeights * 16;
}

void InitAnalyzer() {
    GetStructs()["int8"] = WriteInt8;
    GetStructs()["uint8"] = WriteUInt8;
    GetStructs()["int16"] = WriteInt16;
    GetStructs()["uint16"] = WriteUInt16;
    GetStructs()["int32"] = WriteInt32;
    GetStructs()["uint32"] = WriteUInt32;
    GetStructs()["bool32"] = WriteBool32;
    GetStructs()["float"] = WriteFloat;
    GetStructs()["offset"] = WriteOffset;
    GetStructs()["nameoffset"] = WriteNameOffset;
    GetStructs()["name"] = WriteName;
    GetStructs()["namealigned"] = WriteNameAligned;
    GetStructs()["vector3"] = WriteVector3;
    GetStructs()["vector4"] = WriteVector4;
    GetStructs()["coordinate4"] = WriteVector4;
    GetStructs()["matrix4x4"] = WriteMatrix4x4;
    GetStructs()["bbox"] = WriteBBOX;
    GetStructs()["bone"] = WriteBone;
    GetStructs()["model"] = WriteModel;
    GetStructs()["rendermethod"] = WriteRenderMethod;
    GetStructs()["modeltexture"] = WriteModelTexture;
    GetStructs()["modeltexture_oldformat"] = WriteModelTexture_OldFormat;
    GetStructs()["modifiabledata"] = WriteModifiableData;
    GetStructs()["geoprimstate"] = WriteGeoPrimState;
    GetStructs()["computationindex"] = WriteComputationIndex;
    GetStructs()["irradlight"] = WriteIrradLight;
    GetStructs()["light"] = WriteLight;
    GetStructs()["modellayer"] = WriteModelLayer;
    GetStructs()["modellayers"] = WriteModelLayers;
    GetStructs()["modellayerstates"] = WriteModelLayerStates;
    GetStructs()["modellayersstates"] = WriteModelLayersStates;
    GetStructs()["modellayerbounding"] = WriteModelLayerBounding;
    GetStructs()["renderdescriptorlistentry"] = WriteRenderDescriptorListEntry;
    GetStructs()["animationbank"] = WriteAnimationBank;
    GetStructs()["animation"] = WriteAnimation;
    GetStructs()["skeleton"] = WriteSkeleton;
    GetStructs()["morph"] = WriteMorph;
    GetStructs()["bonestate"] = WriteBoneState;
    GetStructs()["blendtarget"] = WriteBlendTarget;
    GetStructs()["blendshape"] = WriteBlendShape;
    GetStructs()["blendshapevertexattribute"] = WriteBlendShapeVertexAttribute;
    GetStructs()["eaglmicrocode"] = WriteEAGLMicroCode;
    GetStructs()["vsdecl"] = WriteVShaderDecl;
    GetStructs()["geoprimdatabuffer"] = WriteGeoPrimDataBuffer;
    GetStructs()["rendercode"] = WriteRenderCode;
    GetStructs()["command"] = WriteCommand;
    GetStructs()["renderdescriptor"] = WriteRenderDescriptor;
    GetStructs()["commandobjectparameter"] = WriteCommandObjectParameter;
    GetStructs()["geometryinfo"] = WriteGeometryInfo;
    GetStructs()["vertexbuffer"] = WriteVertexBuffer;
    GetStructs()["indexbuffer"] = WriteIndexBuffer;
    GetStructs()["texture"] = WriteTexture;
    GetStructs()["boneweightsbuffer"] = WriteBoneWeightsBuffer;
    GetStructs()["interleavedvertices"] = WriteInterleavedVertices;
    GetStructs()["interleavedverticesdata"] = WriteInterleavedVerticesData;
    GetStructs()["interleavedverticesvertexdata"] = WriteInterleavedVerticesVertexData;
    GetStructs()["effecttechnique"] = WriteEffectTechnique;
    GetStructs()["effectpass"] = WriteEffectPass;
    GetStructs()["stateassignment"] = WriteStateAssignment;
}

void AnalyzeFile(string const &filename, unsigned char *fileData, unsigned int fileDataSize, vector<Symbol> const &symbols, vector<Relocation> const &references) {
    Writer::mResult.clear();
    currentData = fileData;
    class Object {
    public:
        string mType;
        string mName;
        int mOffset = 0;
        unsigned int mCount = 0;
        void *mBaseObj = nullptr;

        Object() {}
        Object(string const &type, string const &name, int offset, unsigned int count, void *baseObj) {
            mType = type;
            mName = name;
            mOffset = offset;
            mCount = count;
            mBaseObj = baseObj;
        }
    };

    class Reference {

    };

    map<unsigned int, Object> objects;

    auto AddObjectInfo = [&](string const &type, string const &name, unsigned int offset, unsigned int count, void *baseObj) {
        if (objects.find(offset) == objects.end())
            objects[offset] = Object(type, name, offset, count, baseObj);
    };

    symbolRelocations.clear();

    for (auto const &r : references) {
        if (r.r_info_sym < symbols.size())
            symbolRelocations[r.r_offset] = symbols[r.r_info_sym];
    }

    for (auto const &s : symbols) {
        if (s.name.starts_with("__Model:::")) {
            void *model = At<void *>(fileData, s.st_value);
            AddObjectInfo("Model", s.name.substr(10), s.st_value, 0, model);
            // TODO: add symbol validation
            unsigned int texturesOffset = GetAt<unsigned int>(model, 0xBC);
            if (texturesOffset) { // TODO: replace with IsValidOffset()
                unsigned int numTextures = 0;
                unsigned int tmpTexOffset = texturesOffset;
                void *texDesc = At<void *>(fileData, tmpTexOffset);
                unsigned int texNameOffset = GetAt<unsigned int>(texDesc, 0);
                bool oldModelTextureFormat = false;
                while (texNameOffset) { // TODO: replace with IsValidOffset()
                    numTextures++;
                    unsigned int texCount = GetAt<unsigned int>(texDesc, 4);
                    unsigned int texSize = texCount * 4;
                    for (unsigned int tx = 0; tx < texCount; tx++) {
                        unsigned int texOffset = GetAt<unsigned int>(texDesc, 8 + tx * 4);
                        if (texOffset != 0) // TODO: replace with IsValidOffset()
                            AddObjectInfo("Texture", Format("Texture.%X", texOffset), texOffset, 0, model);
                    }
                    unsigned short info = GetAt<unsigned int>(texDesc, 8 + texSize);
                    AddObjectInfo("NAME", Format("Name.%X", texNameOffset), texNameOffset, 0, model);
                    if (info == 1)
                        tmpTexOffset += 12 + texSize;
                    else {
                        tmpTexOffset += 8 + texSize;
                        oldModelTextureFormat = true;
                    }
                    texDesc = At<void *>(fileData, tmpTexOffset);
                    texNameOffset = GetAt<unsigned int>(texDesc, 0);
                }
                AddObjectInfo("UINT32", Format("ModelTexturesFooter.%X", tmpTexOffset), tmpTexOffset, 0, model);
                if (numTextures > 0) {
                    if (oldModelTextureFormat)
                        AddObjectInfo("ModelTexture_OldFormat", Format("ModelTexture_OldFormat.%X", texturesOffset), texturesOffset, numTextures, model);
                    else
                        AddObjectInfo("ModelTexture", Format("ModelTexture.%X", texturesOffset), texturesOffset, numTextures, model);
                }
            }
            unsigned int numLayers = GetAt<unsigned int>(model, 0x9C);
            if (numLayers) {
                unsigned int layerNamesOffset = GetAt<unsigned int>(model, 0xA0);
                AddObjectInfo("NAMEOFFSET", Format("ModelLayerName.%X", layerNamesOffset), layerNamesOffset, numLayers, model);
                for (unsigned int i = 0; i < numLayers; i++)
                    AddObjectInfo("NAME", Format("Name.%X", GetAt<unsigned int>(fileData, layerNamesOffset + 4 * i)), GetAt<unsigned int>(fileData, layerNamesOffset + 4 * i), 0, model);
                unsigned int modelLayersOffset = GetAt<unsigned int>(model, 0xCC);
                AddObjectInfo("ModelLayers", Format("ModelLayers.%X", modelLayersOffset), modelLayersOffset, 0, model);
                void *modelLayers = At<void *>(fileData, modelLayersOffset);
                unsigned int modelLayersHeader = GetAt<unsigned int>(modelLayers, 0);
                bool isOldFormat = modelLayersHeader == 0xA0000000;
                unsigned int *rd = At<unsigned int>(modelLayers, isOldFormat ? 12 : 4);
                for (unsigned int i = 0; i < numLayers; i++) {
                    if (isOldFormat)
                        rd += 2;
                    unsigned int numRenderDescriptors = *rd;
                    if (isOldFormat)
                        numRenderDescriptors /= 2;
                    rd++;
                    for (unsigned int d = 0; d < numRenderDescriptors; d++) {
                        if (isOldFormat)
                            rd++;
                        unsigned int renderDescriptorOffset = *rd;
                        rd++;
                        void *renderDescriptor = At<void *>(fileData, renderDescriptorOffset);
                        AddObjectInfo("RenderDescriptor", Format("RenderDescriptor.%X", renderDescriptorOffset), renderDescriptorOffset, 0, model);
                        void *renderMethod = At<void *>(fileData, GetAt<unsigned int>(renderDescriptor, 0));
                        void *globalParameters = At<void *>(renderDescriptor, 4);
                        AddObjectInfo("GeometryInfo", Format("GeometryInfo.%X", GetAt<unsigned int>(globalParameters, 4)), GetAt<unsigned int>(globalParameters, 4), GetAt<unsigned int>(globalParameters, 0), model);
                        unsigned int rmCodeOffset = GetAt<unsigned int>(renderDescriptor, 0) + 8;
                        auto it = symbolRelocations.find(rmCodeOffset);
                        if (it != symbolRelocations.end() && (*it).second.st_info == 0x10) {
                            string codeName = (*it).second.name;
                            if (codeName.ends_with("__EAGLMicroCode")) {
                                auto codeShader = globalVars().target->FindShader(codeName.substr(0, codeName.length() - 15));
                                unsigned int numTechniques = codeShader ? codeShader->numTechniques : 1;
                                if (numTechniques) {
                                    void *renderCode = At<void *>(fileData, GetAt<unsigned int>(renderMethod, 0));
                                    unsigned int numCommands = 0;
                                    unsigned int commandOffset = 0;
                                    unsigned short id = GetAt<unsigned short>(renderCode, commandOffset + 2);
                                    unsigned short size = GetAt<unsigned short>(renderCode, commandOffset);
                                    while (id != 0) {
                                        switch (id) {
                                        case 4:
                                        case 75:
                                            AddObjectInfo("VertexBuffer", Format("VertexBuffer.%X", GetAt<unsigned int>(renderCode, commandOffset + 24)), GetAt<unsigned int>(renderCode, commandOffset + 24), 0, At<void *>(renderCode, commandOffset));
                                            break;
                                        case 7:
                                            AddObjectInfo("IndexBuffer", Format("IndexBuffer.%X", GetAt<unsigned int>(renderCode, commandOffset + 16)), GetAt<unsigned int>(renderCode, commandOffset + 16), 0, At<void *>(renderCode, commandOffset));
                                            break;
                                        case 28:
                                            AddObjectInfo("BoneWeightsBuffer", Format("BoneWeightsBuffer.%X", GetAt<unsigned int>(globalParameters, 4)), GetAt<unsigned int>(globalParameters, 4), 0, globalParameters);
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
                            }
                        }
                    }
                }
                AddObjectInfo("ModelLayerBounding", Format("ModelLayerBounding.%X", s.st_value - numLayers * 48), s.st_value - numLayers * 48, numLayers, model);
            }
            AddObjectInfo("ModelLayersStates", Format("ModelLayersStates.%X", GetAt<unsigned int>(model, 0xC4)), GetAt<unsigned int>(model, 0xC4), 0, model);
            AddObjectInfo("InterleavedVertices", Format("InterleavedVertices.%X", GetAt<unsigned int>(model, 0xB8)), GetAt<unsigned int>(model, 0xB8), 0, model);
            unsigned int nameOffset = GetAt<unsigned int>(model, 0xB4);
            if (nameOffset) // TODO: replace with IsValidOffset()
                AddObjectInfo("NAME", Format("Name.%X", nameOffset), nameOffset, 0, model);
            unsigned int numModifiableDatas = GetAt<unsigned int>(model, 0x04);
            if (numModifiableDatas) {
                AddObjectInfo("ModifiableData", Format("ModifiableData.%X", GetAt<unsigned int>(model, 0x0)), GetAt<unsigned int>(model, 0x0), numModifiableDatas, model);
                for (unsigned int i = 0; i < numModifiableDatas; i++) {
                    void *modData = At<void *>(fileData, GetAt<unsigned int>(model, 0x0) + 16 * i);
                    unsigned int numEntries = GetAt<unsigned int>(modData, 0x8);
                    if (numEntries) {
                        unsigned short entrySize = GetAt<unsigned short>(modData, 0x4);
                        char *name = At<char>(fileData, GetAt<unsigned int>(modData, 0x0));
                        AddObjectInfo("NAMEALIGNED", Format("Name.%X", GetAt<unsigned int>(modData, 0x0)), GetAt<unsigned int>(modData, 0x0), 0, model);
                        auto it = symbolRelocations.find(GetAt<unsigned int>(model, 0x0) + 16 * i + 0xC);
                        if (it == symbolRelocations.end() || (*it).second.st_info != 0x10) {
                            if (entrySize == 68)
                                AddObjectInfo("GeoPrimState", name + Format(".%X", GetAt<unsigned int>(modData, 0xC)), GetAt<unsigned int>(modData, 0xC), numEntries, model);
                            else if (entrySize == 4)
                                AddObjectInfo("ComputationIndex", name + Format(".%X", GetAt<unsigned int>(modData, 0xC)), GetAt<unsigned int>(modData, 0xC), numEntries, model);
                            else if (entrySize == 160)
                                AddObjectInfo("IrradLight", name + Format(".%X", GetAt<unsigned int>(modData, 0xC)), GetAt<unsigned int>(modData, 0xC), numEntries, model);
                            else if (entrySize == 112)
                                AddObjectInfo("Light", name + Format(".%X", GetAt<unsigned int>(modData, 0xC)), GetAt<unsigned int>(modData, 0xC), numEntries, model);
                            else if (entrySize == 16)
                                AddObjectInfo("Coordinate4", name + Format(".%X", GetAt<unsigned int>(modData, 0xC)), GetAt<unsigned int>(modData, 0xC), numEntries, model);
                            else if (entrySize == 64)
                                AddObjectInfo("Matrix4x4", name + Format(".%X", GetAt<unsigned int>(modData, 0xC)), GetAt<unsigned int>(modData, 0xC), numEntries, model);
                        }
                    }
                }
            }
        }
        if (s.name.starts_with("__RenderMethod:::")) {
            void *renderMethod = At<void *>(fileData, s.st_value);
            AddObjectInfo("RenderMethod", s.name.substr(17), s.st_value, 0, renderMethod);
            if (globalVars().target->Version() >= 3) {
                unsigned int nameOffset = GetAt<unsigned int>(renderMethod, 0x2C);
                if (nameOffset) // TODO: replace with IsValidOffset()
                    AddObjectInfo("NAMEALIGNED", Format("Name.%X", nameOffset), nameOffset, 0, renderMethod);
            }
            unsigned int geoBuf = GetAt<unsigned int>(renderMethod, 0x24);
            if (geoBuf && geoBuf != GetAt<unsigned int>(renderMethod, 8)) // TODO: replace with IsValidOffset()
                AddObjectInfo("geoprimdatabuffer", Format("geoprimdatabuffer.%X", geoBuf), geoBuf, 0, renderMethod);
            else {
                unsigned int codeBlock = GetAt<unsigned int>(renderMethod, 0);
                if (codeBlock >= 4) // TODO: replace with IsValidOffset()
                    AddObjectInfo("geoprimdatabuffer", Format("geoprimdatabuffer.%X", codeBlock - 4), codeBlock - 4, 0, renderMethod);
            }
        }
        else if (s.name.starts_with("__BBOX:::"))
            AddObjectInfo("BBOX", s.name.substr(9), s.st_value, 0, nullptr);
        else if (s.name.starts_with("__Bone:::"))
            AddObjectInfo("Bone", s.name.substr(9), s.st_value, 0, nullptr);
        else if (s.name.starts_with("__AnimationBank:::")) {
            AddObjectInfo("AnimationBank", s.name.substr(18), s.st_value, 0, nullptr);
            void *bank = At<void *>(fileData, s.st_value);
            unsigned int numAnimations = GetAt<unsigned int>(bank, 0x4);
            if (numAnimations > 0) {
                unsigned short animBankSize = GetAt<unsigned short>(bank, 0x0);
                bool oldBankVersion = animBankSize == 0x18;
                unsigned int animNamesOffset = GetAt<unsigned int>(bank, oldBankVersion ? 0x10 : 0x14);
                unsigned int animsOffset = GetAt<unsigned int>(bank, oldBankVersion ? 0xC : 0x10);
                AddObjectInfo("NAMEOFFSET", Format("AnimationName.%X", animNamesOffset), animNamesOffset, numAnimations, bank);
                AddObjectInfo("OFFSET", Format("AnimationOffset.%X", animsOffset), animsOffset, numAnimations, bank);
                for (unsigned int i = 0; i < numAnimations; i++) {
                    unsigned int animationOffset = GetAt<unsigned int>(fileData, animsOffset + 4 * i);
                    AddObjectInfo("Animation", Format("Animation.%X", animationOffset), animationOffset, 0, bank);
                    AddObjectInfo((i == (numAnimations - 1)) ? "NAMEALIGNED" : "NAME", Format("Name.%X", GetAt<unsigned int>(fileData, animNamesOffset + 4 * i)), GetAt<unsigned int>(fileData, animNamesOffset + 4 * i), 0, bank);
                    void *animation = At<void *>(fileData, animationOffset);
                    if (GetAt<unsigned short>(animation, 0) == 15) {
                        unsigned short numChannels = GetAt<unsigned short>(animation, 0x8);
                        for (unsigned int a = 0; a < numChannels; a++) {
                            unsigned int channelOffset = GetAt<unsigned int>(animation, 0xC + a * 4);
                            AddObjectInfo("Animation", Format("Animation.%X", channelOffset), channelOffset, 0, bank);
                        }
                    }
                }
            }
        }
        else if (s.name.starts_with("__Skeleton:::")) {
            void *skeleton = At<void *>(fileData, s.st_value);
            AddObjectInfo("Skeleton", s.name.substr(13), s.st_value, 0, skeleton);
        }
        else if (s.name.starts_with("__Morph:::")) {
            void *morph = At<void *>(fileData, s.st_value);
            AddObjectInfo("Morph", s.name.substr(10), s.st_value, 0, morph);
            unsigned int numWeights = GetAt<unsigned int>(morph, 0x0);
            unsigned int weightNamesOffset = GetAt<unsigned int>(morph, 0x4);
            unsigned int weightValuesOffset = GetAt<unsigned int>(morph, 0x8);
            unsigned int numBlendTargets = GetAt<unsigned int>(morph, 0x10);
            AddObjectInfo("NAMEOFFSET", Format("BlendWeightName.%X", weightNamesOffset), weightNamesOffset, numWeights, morph);
            AddObjectInfo("FLOAT", Format("BlendWeightValue.%X", weightValuesOffset), weightValuesOffset, numWeights, morph);
            for (unsigned int i = 0; i < numWeights; i++) {
                unsigned int nameOffset = GetAt<unsigned int>(fileData, weightNamesOffset + 4 * i);
                AddObjectInfo("NAME", Format("Name.%X", nameOffset), nameOffset, 0, morph);
            }
            unsigned int morphOffset = s.st_value + 20;
            for (unsigned int t = 0; t < numBlendTargets; t++) {
                unsigned int nameOffset = GetAt<unsigned int>(fileData, morphOffset);
                unsigned int numBlendShapes = GetAt<unsigned int>(fileData, morphOffset + 4);
                morphOffset += 8;
                AddObjectInfo("NAME", Format("Name.%X", nameOffset), nameOffset, 0, morph);
                for (unsigned int b = 0; b < numBlendShapes; b++) {
                    unsigned int numAttributes = GetAt<unsigned int>(fileData, morphOffset + 4);
                    morphOffset += 8;
                    for (unsigned int a = 0; a < numAttributes; a++) {
                        unsigned int flags = GetAt<unsigned int>(fileData, morphOffset);
                        morphOffset += 16 + (flags & 0xFFFFFFF);
                    }
                }
            }
        }
        else if (s.name.ends_with("__EAGLMicroCode") && s.st_info == 0x11) {
            void *microCode = At<void *>(fileData, s.st_value);
            AddObjectInfo("EAGLMicroCode", s.name.substr(0, s.name.length() - 15), s.st_value, 0, microCode);
        }
        //else if (s.name.starts_with("__geoprimdatabuffer")) {
        //    void *geoprimdatabuffer = At<void *>(fileData, s.st_value);
        //    AddObjectInfo("geoprimdatabuffer", s.name, s.st_value, 0, geoprimdatabuffer);
        //}
    }
    Writer::writeLine("// " + filename);

    int previousStructEnd = -1;

    auto WriteUnknown = [&](unsigned int endOffset) {
        if (previousStructEnd == -1)
            previousStructEnd = 0;
        if (previousStructEnd > endOffset) {
            return;
            Error("previousStructEnd (%X) > endOffset (%X)", previousStructEnd, endOffset);
        }
        unsigned int size = endOffset - previousStructEnd;
        Writer::openScope("Unknown [" + Format("%u", size) + "]", previousStructEnd); // TODO: write references
        string ary;
        for (unsigned int i = 0; i < min(size, 100u); i++) {
            if (i != 0)
                ary += " ";
            ary += Format("%02X", ((unsigned char *)fileData)[previousStructEnd + i]);
        }
        if (size > 100)
            ary += "...";
        Writer::writeLine(ary);
        Writer::closeScope();
        previousStructEnd += size;
    };
    for (auto const &[i, o] : objects) {
        if (previousStructEnd == -1)
            previousStructEnd = 0;
        //::Warning("writing %s - %s", o.mType.c_str(), o.mName.c_str());
        if (o.mOffset != previousStructEnd)
            WriteUnknown(o.mOffset);
        previousStructEnd += WriteObject(o.mBaseObj, o.mType, o.mName, fileData, o.mOffset, o.mCount);
    }
    if (previousStructEnd != fileDataSize)
        WriteUnknown(fileDataSize);
}

}

GlobalVars &globalVars() {
    static GlobalVars gv;
    return gv;
}

void odump(path const &out, path const &in) {
    dump::InitAnalyzer();
    auto fileData = readofile(in);
    if (fileData.first) {
        unsigned char *data = nullptr;
        unsigned int dataSize = 0;
        Elf32_Sym *symbols = nullptr;
        unsigned int numSymbols = 0;
        Elf32_Rel *rel = nullptr;
        unsigned int numRelocations = 0;
        char *symbolNames = nullptr;
        unsigned int symbolNamesSize = 0;

        Elf32_Ehdr *h = (Elf32_Ehdr *)fileData.first;
        Elf32_Shdr *s = At<Elf32_Shdr>(h, h->e_shoff);
        for (unsigned int i = 1; i < 6; i++) {
            if (s[i].sh_size > 0) {
                if (s[i].sh_type == 1) {
                    data = At<unsigned char>(h, s[i].sh_offset);
                    dataSize = s[i].sh_size;
                }
                else if (s[i].sh_type == 2) {
                    symbols = At<Elf32_Sym>(h, s[i].sh_offset);
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

        vector<dump::Symbol> vecSymbols;
        vector<dump::Relocation> vecReferences;

        vecSymbols.resize(numSymbols);
        vecReferences.resize(numRelocations);

        for (unsigned int i = 0; i < numSymbols; i++) {
            vecSymbols[i].st_info = symbols[i].st_info;
            vecSymbols[i].st_name = symbols[i].st_name;
            vecSymbols[i].st_other = symbols[i].st_other;
            vecSymbols[i].st_shndx = symbols[i].st_shndx;
            vecSymbols[i].st_size = symbols[i].st_size;
            vecSymbols[i].st_value = symbols[i].st_value;
            vecSymbols[i].name = &symbolNames[symbols[i].st_name];
        }

        for (unsigned int i = 0; i < numRelocations; i++) {
            vecReferences[i].r_info_sym = rel[i].r_info_sym;
            vecReferences[i].r_info_type = rel[i].r_info_type;
            vecReferences[i].r_offset = rel[i].r_offset;
        }
        AnalyzeFile(in.filename().string(), data, dataSize, vecSymbols, vecReferences);
        delete[] fileData.first;
    }
    ofstream w(out, ios::out);
    if (w.is_open())
        w << dump::Writer::mResult;
}
