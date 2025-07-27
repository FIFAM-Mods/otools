#pragma once
#include <string>
#include <vector>

enum ShaderCommand {
    NOP_1 = 1,
    SET_VERTEX_SHADER_CONSTANT_G = 2,
    NOP_3 = 3,
    SET_STREAM_SOURCE = 4,
    NOP_6 = 6,
    SET_INDEX_BUFFER = 7,
    SET_SAMPLER_G = 9,
    SET_VERTEX_SHADER_CONSTANT_MATRIX = 12,
    DRAW_PRIM = 16,
    DRAW_INDEXED_PRIM_NO_Z_WRITE = 17,
    DRAW_INDEXED_PRIM = 18,
    SET_VERTEX_BONE_WEIGHTS = 28,
    SET_VERTEX_SHADER_CONSTANT_L_30 = 30,
    SET_VERTEX_SHADER_CONSTANT_L_31 = 31,
    SET_SAMPLER = 32,
    SET_GEO_PRIM_STATE = 33,
    SET_VERTEX_SHADER_TRANSPOSED_MATRIX = 35,
    SET_ANIMATION_BUFFER = 40,
    SET_VERTEX_SHADER_CONSTANT_L_46 = 46,
    DRAW_INDEXED_PRIM_57 = 57,
    DRAW_INDEXED_PRIM_AND_END = 65,
    SETUP_RENDER = 69,
    SET_PIXEL_SHADER_CONTANT_G_72 = 72,
    SET_PIXEL_SHADER_CONTANT_G_73 = 73,
    SET_STREAM_SOURCE_SKINNED = 75
};

struct Shader {
    enum DataType {
        NoType, Float2, Float3, Float4, D3DColor, UByte4
    };
    enum DataUsage {
        NoUsage, Position, Normal, Color0, Color1, Texcoord0, Texcoord1, Texcoord2, Texcoord3, BlendIndices, BlendWeight
    };
    struct VertexDeclElement {
        DataType type = NoType;
        DataUsage usage = NoUsage;

        unsigned int Size() const;
    };

    enum Argument {
        UnknownArgument = 0x70000001,
        VertexData,
        VertexCount,
        VertexBufferIndex,
        IndexData,
        IndexCount,
        VertexSkinData,
        GeometryInfo,
        ModelMatrix,
        ViewMatrix,
        ProjectionMatrix,
        ModelViewProjectionMatrix,
        ModelViewMatrix,
        FogParameters0,
        FogParameters1,
        FogParameters2,
        FogParameters3,
        Sampler0,
        Sampler1,
        Sampler2,
        Sampler3,
        Sampler0Local,
        Sampler1Local,
        Sampler2Local,
        Sampler3Local,
        Sampler0Size,
        Sampler1Size,
        Sampler2Size,
        Sampler3Size,
        GeoPrimState,
        RuntimeGeoPrimState,
        RuntimeGeoPrimState2,
        ComputationIndex,
        Light,
        IrradLight,
        ZeroOneTwoThree,
        ZeroOneTwoThreeLocal,
        EnvMapConstants,
        EnvMapConstantsLocal,
        EnvmapColour,
        FogParameters,
        UVOffset0,
        UVOffset1,
        XFade,
        BaseColour,
        ShadowColour,
        ShadowColour2,
        RMGrass_PSConstants,
        RMGrass_VSConstants,
        RMGrass_CameraPosition,
        EAGLAnimationBuffer,
        ViewVector,
        RimLightCol,
        VertexWeights3Bones,
        VertexWeights2Bones,
        VertexWeights1Bone,
        SubSurfFactor,
        SpecLightVec,
        SpecLightCol,
        HalfVector,
        HighlightAlpha,
        VariationsCount,
        VecZeroLocal,
        VecOneLocal,
        Vec0505051Local,
        ColourModulator,
        ColourTranslate,
        CrowdTintH,
        CrowdTintA,
        RMStadium_CameraPos,
        StarBall_MatrixMVP,
        StarBall_MatrixMV,
        StarBall_MatrixMVR,
        StarBall_Params0,
        StarBall_Params1,
        SubSurfFactor2,
        SpecFactor,
        PlaneEquation,
        FresnelColour,
        Fresnel,
        LightMultipliers,
        Irradiance,
        FaceIrradiance,
        Vec3E30B0B1Local,
        Vec3DA0A0A1Local,
        UVOffset,
        UVMatrix,
        ColourScale,
        ColourScaleFactor,
        EyeVector,
        Contrast,
        Vec40200000Local,
        UVOffset_Layer,
        UVMatrix_Layer,
        CrowdState,
        LineNoDepthWriteState,
        GlowerState,
        InstanceColour,
        FlagLightBlock,
        GlobalDiffuse,
        TextureProjectionMatrix,
        LocalLightDirection,
        ProjectiveShadow2State,
        NbaLightBlock,
        NbaEnvMapMatrix,
        NbaCourtComputation,
        CourtConst,
        CourtConstMatrix,
        NbaDimComputation,
        NbaDornaUVOffset,
        StadiumDimmer,
        NbaDornaUVMatrix,
        NbaGeomPrimStateT_Reflect,
        NbaGeomPrimStateT,
        NbaIrradCompIdx,
        NbaIrradBlock,
        NbaEyeUVOffset,
        NbaEyeUVMatrix,
        NbaReflectCompIdx,
        ViewProjectionMatrix,
        NbaReflectLightblock,
        ReflectionParams,
        NbaReflectionAttenMatrix,
        SpecmapColour,
        NbaShotclockUVs,
        NbaShotclockMatrix0,
        NbaShotclockMatrix1,
        NbaShotclockMatrix2,
        NbaShotclockMatrix3,
        NbaShotclockMatrix4,
        NbaShotclockMatrix5,
        NbaShotClock0Local,
        NbaShotClock1Local,
        NbaShotClock2Local,
        NbaShotClock3Local,
        NbaShotClock4Local,
        NbaShotClock5Local,
        NbaUniformComputation,
        NbaUniformFrontUVScaleOffset,
        NbaUniformFrontUVScaleOffset_Matrix,
        NbaUniformBackUVScaleOffset,
        NbaUniformBackUVScaleOffset_Matrix,
        NbaUnlitUniformComputation,
        NbaZBias,
        NbaJumbotron0Local,
        NbaJumbotron1Local,
        NbaJumbotron2Local,
        NbaJumbotron3Local,
        NbaJumbotron4Local,
        NbaJumbotron5Local,
        NbaJumbotron6Local,
        NbaJumbotron7Local,
        NbaJumbotron8Local,
        NbaJumbotron9Local,
        NbaJumbotronUVOffsets,
        NbaJumbotronMatrix0,
        NbaJumbotronMatrix1,
        NbaJumbotronMatrix2,
        NbaJumbotronMatrix3,
        NbaJumbotronMatrix4,
        NbaJumbotronMatrix5,
        NbaJumbotronMatrix6,
        NbaJumbotronMatrix7,
        NbaJumbotronMatrix8,
        NbaJumbotronMatrix9
    };

    struct Command {
        unsigned short id;
        std::vector<int> arguments;

        Command(unsigned char _id, std::vector<int> const &_arguments);
    };

    struct GlobalArgument {
        unsigned int type;
        std::string format;

        GlobalArgument();
        GlobalArgument(unsigned int _type, std::string const &_format = std::string());
    };

    std::string name;
    std::string nameLowered;
    unsigned int numTechniques;
    int computationCommandIndex;
    std::vector<VertexDeclElement> declaration;
    unsigned int vertexSize;
    std::vector<Command> commands;
    std::vector<GlobalArgument> globalArguments;

    Shader();
    Shader(std::string const &_name, unsigned int _numTechniques, std::vector<VertexDeclElement> const &_declaration, std::vector<Command> const&_commands, std::vector<GlobalArgument> const&_globalArguments);
    unsigned int VertexSize() const;
    int ComputationCommandIndex() const;
    bool HasAttribute(DataUsage attribute) const;
    void Update(bool validate = true);
};

bool operator==(Shader::Command const &a, Shader::Command const &b);
bool operator==(Shader::GlobalArgument const &a, Shader::GlobalArgument const &b);

extern Shader DummyShader;
extern Shader DummyShader_Skin;
