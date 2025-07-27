#include "main.h"
#include <fstream>
#include <iostream>
#include "shaders.h"

enum SamplerArgumentType {
    SamplerUndefined = 0,
    SamplerGlobal = 1,
    SamplerLocalPublic = 2,
    SamplerLocalPrivate = 4
};

struct ShaderInfo : public Shader {
    set<string> files;
    unsigned int numFiles = 0;
    unsigned int debugVertexSize = 0;
    unsigned int samplerArguments[4] = { SamplerUndefined, SamplerUndefined, SamplerUndefined, SamplerUndefined };
};

bool operator==(ShaderInfo const &a, ShaderInfo const &b) {
    return a.name == b.name /*&& a.commands == b.commands && a.globalArguments == b.globalArguments*/;
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
    case 12:
        return "SET_VERTEX_SHADER_CONSTANT_MATRIX";
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
    case 57:
        return "DRAW_INDEXED_PRIM_57";
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

string GetShaderAttributeName(int attr) {
    switch (attr) {
    case Shader::VertexData:                return "Shader::VertexData";
    case Shader::VertexCount:               return "Shader::VertexCount";
    case Shader::VertexBufferIndex:         return "Shader::VertexBufferIndex";
    case Shader::IndexData:                 return "Shader::IndexData";
    case Shader::IndexCount:                return "Shader::IndexCount";
    case Shader::VertexSkinData:            return "Shader::VertexSkinData";
    case Shader::GeometryInfo:              return "Shader::GeometryInfo";
    case Shader::ModelMatrix:               return "Shader::ModelMatrix";
    case Shader::ViewMatrix:                return "Shader::ViewMatrix";
    case Shader::ProjectionMatrix:          return "Shader::ProjectionMatrix";
    case Shader::ModelViewProjectionMatrix: return "Shader::ModelViewProjectionMatrix";
    case Shader::ModelViewMatrix:           return "Shader::ModelViewMatrix";
    case Shader::FogParameters0:            return "Shader::FogParameters0";
    case Shader::FogParameters1:            return "Shader::FogParameters1";
    case Shader::FogParameters2:            return "Shader::FogParameters2";
    case Shader::FogParameters3:            return "Shader::FogParameters3";
    case Shader::Sampler0:                  return "Shader::Sampler0";
    case Shader::Sampler1:                  return "Shader::Sampler1";
    case Shader::Sampler2:                  return "Shader::Sampler2";
    case Shader::Sampler3:                  return "Shader::Sampler3";
    case Shader::Sampler0Local:             return "Shader::Sampler0Local";
    case Shader::Sampler1Local:             return "Shader::Sampler1Local";
    case Shader::Sampler2Local:             return "Shader::Sampler2Local";
    case Shader::Sampler3Local:             return "Shader::Sampler3Local";
    case Shader::Sampler0Size:              return "Shader::Sampler0Size";
    case Shader::Sampler1Size:              return "Shader::Sampler1Size";
    case Shader::Sampler2Size:              return "Shader::Sampler2Size";
    case Shader::Sampler3Size:              return "Shader::Sampler3Size";
    case Shader::GeoPrimState:              return "Shader::GeoPrimState";
    case Shader::RuntimeGeoPrimState:       return "Shader::RuntimeGeoPrimState";
    case Shader::RuntimeGeoPrimState2:      return "Shader::RuntimeGeoPrimState2";
    case Shader::ComputationIndex:          return "Shader::ComputationIndex";
    case Shader::Light:                     return "Shader::Light";
    case Shader::IrradLight:                return "Shader::IrradLight";
    case Shader::ZeroOneTwoThree:           return "Shader::ZeroOneTwoThree";
    case Shader::ZeroOneTwoThreeLocal:      return "Shader::ZeroOneTwoThreeLocal";
    case Shader::EnvMapConstants:           return "Shader::EnvMapConstants";
    case Shader::EnvMapConstantsLocal:      return "Shader::EnvMapConstantsLocal";
    case Shader::EnvmapColour:              return "Shader::EnvmapColour";
    case Shader::FogParameters:             return "Shader::FogParameters";
    case Shader::UVOffset0:                 return "Shader::UVOffset0";
    case Shader::UVOffset1:                 return "Shader::UVOffset1";
    case Shader::XFade:                     return "Shader::XFade";
    case Shader::BaseColour:                return "Shader::BaseColour";
    case Shader::ShadowColour:              return "Shader::ShadowColour";
    case Shader::ShadowColour2:             return "Shader::ShadowColour2";
    case Shader::RMGrass_PSConstants:       return "Shader::RMGrass_PSConstants";
    case Shader::RMGrass_VSConstants:       return "Shader::RMGrass_VSConstants";
    case Shader::RMGrass_CameraPosition:    return "Shader::RMGrass_CameraPosition";
    case Shader::EAGLAnimationBuffer:       return "Shader::EAGLAnimationBuffer";
    case Shader::ViewVector:                return "Shader::ViewVector";
    case Shader::RimLightCol:               return "Shader::RimLightCol";
    case Shader::VertexWeights3Bones:       return "Shader::VertexWeights3Bones";
    case Shader::VertexWeights2Bones:       return "Shader::VertexWeights2Bones";
    case Shader::VertexWeights1Bone:        return "Shader::VertexWeights1Bone";
    case Shader::SubSurfFactor:             return "Shader::SubSurfFactor";
    case Shader::SpecLightVec:              return "Shader::SpecLightVec";
    case Shader::SpecLightCol:              return "Shader::SpecLightCol";
    case Shader::HalfVector:                return "Shader::HalfVector";
    case Shader::HighlightAlpha:            return "Shader::HighlightAlpha";
    case Shader::CrowdTintH:                return "Shader::CrowdTintH";
    case Shader::CrowdTintA:                return "Shader::CrowdTintA";
    case Shader::RMStadium_CameraPos:       return "Shader::RMStadium_CameraPos";
    case Shader::ColourModulator:           return "Shader::ColourModulator";
    case Shader::ColourTranslate:           return "Shader::ColourTranslate";
    case Shader::VariationsCount:           return "Shader::VariationsCount";
    case Shader::VecOneLocal:               return "Shader::VecOneLocal";
    case Shader::VecZeroLocal:              return "Shader::VecZeroLocal";
    case Shader::Vec0505051Local:           return "Shader::Vec0505051Local";
    case Shader::SubSurfFactor2:            return "Shader::SubSurfFactor2";
    case Shader::SpecFactor:                return "Shader::SpecFactor";
    case Shader::StarBall_MatrixMVP:        return "Shader::StarBall_MatrixMVP";
    case Shader::StarBall_MatrixMV:         return "Shader::StarBall_MatrixMV";
    case Shader::StarBall_MatrixMVR:        return "Shader::StarBall_MatrixMVR";
    case Shader::StarBall_Params0:          return "Shader::StarBall_Params0";
    case Shader::StarBall_Params1:          return "Shader::StarBall_Params1";
    case Shader::PlaneEquation:             return "Shader::PlaneEquation";
    case Shader::FresnelColour:             return "Shader::FresnelColour";
    case Shader::Fresnel:                   return "Shader::Fresnel";
    case Shader::LightMultipliers:          return "Shader::LightMultipliers";
    case Shader::Irradiance:                return "Shader::Irradiance";
    case Shader::FaceIrradiance:            return "Shader::FaceIrradiance";
    case Shader::Vec3E30B0B1Local:          return "Shader::Vec3E30B0B1Local";
    case Shader::Vec3DA0A0A1Local:          return "Shader::Vec3DA0A0A1Local";
    case Shader::UVOffset:                  return "Shader::UVOffset";
    case Shader::UVMatrix:                  return "Shader::UVMatrix";
    case Shader::ColourScale:               return "Shader::ColourScale";
    case Shader::ColourScaleFactor:         return "Shader::ColourScaleFactor";
    case Shader::EyeVector:                 return "Shader::EyeVector";
    case Shader::Contrast:                  return "Shader::Contrast";
    case Shader::Vec40200000Local:          return "Shader::Vec40200000Local";
    case Shader::UVOffset_Layer:            return "Shader::UVOffset_Layer";
    case Shader::UVMatrix_Layer:            return "Shader::UVMatrix_Layer";
    case Shader::CrowdState:                return "Shader::CrowdState";
    case Shader::LineNoDepthWriteState:     return "Shader::LineNoDepthWriteState";
    case Shader::GlowerState:               return "Shader::GlowerState";
    case Shader::InstanceColour:            return "Shader::InstanceColour";
    case Shader::FlagLightBlock:            return "Shader::FlagLightBlock";
    case Shader::GlobalDiffuse:             return "Shader::GlobalDiffuse";
    case Shader::TextureProjectionMatrix:   return "Shader::TextureProjectionMatrix";
    case Shader::LocalLightDirection:       return "Shader::LocalLightDirection";
    case Shader::ProjectiveShadow2State:    return "Shader::ProjectiveShadow2State";
    case Shader::NbaLightBlock:             return "Shader::NbaLightBlock";
    case Shader::NbaEnvMapMatrix:           return "Shader::NbaEnvMapMatrix";
    case Shader::NbaCourtComputation:       return "Shader::NbaCourtComputation";
    case Shader::CourtConst:                return "Shader::CourtConst";
    case Shader::CourtConstMatrix:          return "Shader::CourtConstMatrix";
    case Shader::NbaDimComputation:         return "Shader::NbaDimComputation";
    case Shader::NbaDornaUVOffset:          return "Shader::NbaDornaUVOffset";
    case Shader::StadiumDimmer:             return "Shader::StadiumDimmer";
    case Shader::NbaDornaUVMatrix:          return "Shader::NbaDornaUVMatrix";
    case Shader::NbaGeomPrimStateT_Reflect: return "Shader::NbaGeomPrimStateT_Reflect";
    case Shader::NbaGeomPrimStateT:         return "Shader::NbaGeomPrimStateT";
    case Shader::NbaIrradCompIdx:           return "Shader::NbaIrradCompIdx";
    case Shader::NbaIrradBlock:             return "Shader::NbaIrradBlock";
    case Shader::NbaEyeUVOffset:            return "Shader::NbaEyeUVOffset";
    case Shader::NbaEyeUVMatrix:            return "Shader::NbaEyeUVMatrix";
    case Shader::NbaReflectCompIdx:         return "Shader::NbaReflectCompIdx";
    case Shader::ViewProjectionMatrix:      return "Shader::ViewProjectionMatrix";
    case Shader::NbaReflectLightblock:      return "Shader::NbaReflectLightblock";
    case Shader::ReflectionParams:          return "Shader::ReflectionParams";
    case Shader::NbaReflectionAttenMatrix:  return "Shader::NbaReflectionAttenMatrix";
    case Shader::SpecmapColour:             return "Shader::SpecmapColour";
    case Shader::NbaShotclockUVs:           return "Shader::NbaShotclockUVs";
    case Shader::NbaShotclockMatrix0:       return "Shader::NbaShotclockMatrix0";
    case Shader::NbaShotclockMatrix1:       return "Shader::NbaShotclockMatrix1";
    case Shader::NbaShotclockMatrix2:       return "Shader::NbaShotclockMatrix2";
    case Shader::NbaShotclockMatrix3:       return "Shader::NbaShotclockMatrix3";
    case Shader::NbaShotclockMatrix4:       return "Shader::NbaShotclockMatrix4";
    case Shader::NbaShotclockMatrix5:       return "Shader::NbaShotclockMatrix5";
    case Shader::NbaShotClock0Local:        return "Shader::NbaShotClock0Local";
    case Shader::NbaShotClock1Local:        return "Shader::NbaShotClock1Local";
    case Shader::NbaShotClock2Local:        return "Shader::NbaShotClock2Local";
    case Shader::NbaShotClock3Local:        return "Shader::NbaShotClock3Local";
    case Shader::NbaShotClock4Local:        return "Shader::NbaShotClock4Local";
    case Shader::NbaShotClock5Local:        return "Shader::NbaShotClock5Local";
    case Shader::NbaUniformComputation:     return "Shader::NbaUniformComputation";
    case Shader::NbaUniformFrontUVScaleOffset: return "Shader::NbaUniformFrontUVScaleOffset";
    case Shader::NbaUniformFrontUVScaleOffset_Matrix: return "Shader::NbaUniformFrontUVScaleOffset_Matrix";
    case Shader::NbaUniformBackUVScaleOffset: return "Shader::NbaUniformBackUVScaleOffset";
    case Shader::NbaUniformBackUVScaleOffset_Matrix: return "Shader::NbaUniformBackUVScaleOffset_Matrix";
    case Shader::NbaUnlitUniformComputation: return "Shader::NbaUnlitUniformComputation";
    case Shader::NbaZBias:                  return "Shader::NbaZBias";
    case Shader::NbaJumbotron0Local:        return "Shader::NbaJumbotron0Local";
    case Shader::NbaJumbotron1Local:        return "Shader::NbaJumbotron1Local";
    case Shader::NbaJumbotron2Local:        return "Shader::NbaJumbotron2Local";
    case Shader::NbaJumbotron3Local:        return "Shader::NbaJumbotron3Local";
    case Shader::NbaJumbotron4Local:        return "Shader::NbaJumbotron4Local";
    case Shader::NbaJumbotron5Local:        return "Shader::NbaJumbotron5Local";
    case Shader::NbaJumbotron6Local:        return "Shader::NbaJumbotron6Local";
    case Shader::NbaJumbotron7Local:        return "Shader::NbaJumbotron7Local";
    case Shader::NbaJumbotron8Local:        return "Shader::NbaJumbotron8Local";
    case Shader::NbaJumbotron9Local:        return "Shader::NbaJumbotron9Local";
    case Shader::NbaJumbotronUVOffsets:     return "Shader::NbaJumbotronUVOffsets";
    case Shader::NbaJumbotronMatrix0:       return "Shader::NbaJumbotronMatrix0";
    case Shader::NbaJumbotronMatrix1:       return "Shader::NbaJumbotronMatrix1";
    case Shader::NbaJumbotronMatrix2:       return "Shader::NbaJumbotronMatrix2";
    case Shader::NbaJumbotronMatrix3:       return "Shader::NbaJumbotronMatrix3";
    case Shader::NbaJumbotronMatrix4:       return "Shader::NbaJumbotronMatrix4";
    case Shader::NbaJumbotronMatrix5:       return "Shader::NbaJumbotronMatrix5";
    case Shader::NbaJumbotronMatrix6:       return "Shader::NbaJumbotronMatrix6";
    case Shader::NbaJumbotronMatrix7:       return "Shader::NbaJumbotronMatrix7";
    case Shader::NbaJumbotronMatrix8:       return "Shader::NbaJumbotronMatrix8";
    case Shader::NbaJumbotronMatrix9:       return "Shader::NbaJumbotronMatrix9";
    }
    return string();
}

int GetShaderAttributeFromSymbolName(string const &symbolName) {
    static map<string, unsigned int> attrMap = {
        { "__const MATRIX4:::EAGL::ViewPort::gpModelViewProjectionMatrix", Shader::ModelViewProjectionMatrix },
        { "__const MATRIX4:::EAGL::ViewPort::gpModelMatrix", Shader::ModelMatrix },
        { "__COORD4:::&EAGL::RenderMethodConstants::gZeroOneTwoThree", Shader::ZeroOneTwoThree },
        { "__const MATRIX4:::EAGL::ViewPort::gpViewMatrix", Shader::ViewMatrix },
        { "__const MATRIX4:::EAGL::ViewPort::gpProjectionMatrix", Shader::ProjectionMatrix },
        { "__const MATRIX4:::EAGL::ViewPort::gpModelViewMatrix", Shader::ModelViewMatrix },
        { "__COORD4:::&EAGL::RenderMethodConstants::gEnvMapConstants", Shader::EnvMapConstants },
        { "__COORD4:::EnvmapColour", Shader::EnvmapColour },
        { "__COORD4:::&EAGL::RenderMethodConstants::gFogParameters", Shader::FogParameters },
        { "__COORD4:::SGR::Fog::Parameters0", Shader::FogParameters0 },
        { "__COORD4:::SGR::Fog::Parameters1", Shader::FogParameters1 },
        { "__COORD4:::SGR::Fog::Parameters2", Shader::FogParameters2 },
        { "__COORD4:::SGR::Fog::Parameters3", Shader::FogParameters3 },
        { "__COORD4:::gShadowColour", Shader::ShadowColour },
        { "__COORD4:::gShadowColour2", Shader::ShadowColour2 },
        { "__COORD4:::RMGrass::PSConstants", Shader::RMGrass_PSConstants },
        { "__COORD4:::RMGrass::VSConstants", Shader::RMGrass_VSConstants },
        { "__COORD4:::RMGrass::CameraPosition", Shader::RMGrass_CameraPosition },
        { "__const MATRIX4:::EAGLAnimationBuffer", Shader::EAGLAnimationBuffer },
        { "__COORD4:::ViewVector", Shader::ViewVector },
        { "__COORD4:::SGR::Rim::RimLightCol", Shader::RimLightCol },
        { "__COORD4:::SGR::SubSurf::SubSurfFactor", Shader::SubSurfFactor },
        { "__COORD4:::SGR::Specular::SpecLightVec", Shader::SpecLightVec },
        { "__COORD4:::SGR::Specular::SpecLightCol", Shader::SpecLightCol },
        { "__COORD4:::SGR::Specular::HalfVector", Shader::HalfVector },
        { "__COORD4:::SGR::GameFace::HighlightAlpha", Shader::HighlightAlpha },
        { "__COORD4:::RMStadium::CameraPos", Shader::RMStadium_CameraPos },
        { "__COORD4:::ColourModulator", Shader::ColourModulator },
        { "__COORD4:::SGR:SubSurf:SubSurfFactor", Shader::SubSurfFactor2 },
        { "__COORD4:::SGR:SubSurf:SpecFactor", Shader::SpecFactor },
        { "__const MATRIX4:::RM::StarBall::MatrixMVP", Shader::StarBall_MatrixMVP },
        { "__const MATRIX4:::RM::StarBall::MatrixMV", Shader::StarBall_MatrixMV },
        { "__const MATRIX4:::RM::StarBall::MatrixMVR", Shader::StarBall_MatrixMVR },
        { "__COORD4:::RM::StarBall::Params0", Shader::StarBall_Params0 },
        { "__COORD4:::RM::StarBall::Params1", Shader::StarBall_Params1 },
        { "__COORD4:::RM::Globe::PlaneEquation", Shader::PlaneEquation },
        { "__COORD4:::RM::Globe::FresnelColour", Shader::FresnelColour },
        { "__COORD4:::ColourTranslate", Shader::ColourTranslate },
        { "__COORD4:::Hbs::Render::Fresnel", Shader::Fresnel },
        { "__COORD4:::gpIrradiance", Shader::Irradiance },
        { "__COORD4:::gpFaceIrradiance", Shader::FaceIrradiance },
        { "__COORD4:::ColourScaleFactor", Shader::ColourScaleFactor },
        { "__COORD4:::Hbs::Render::EyeVector", Shader::EyeVector },
        { "__COORD4:::Hbs::Render::MowPattern::Contrast", Shader::Contrast },
        { "__EAGL::GeoPrimState:::crowd_state", Shader::CrowdState },
        { "__EAGL::GeoPrimState:::line_no_depth_write_state", Shader::LineNoDepthWriteState },
        { "__EAGL::GeoPrimState:::glower_state", Shader::GlowerState },
        { "__EAGL::LightBlock:::FlagLightBlock", Shader::FlagLightBlock },
        { "__COORD4:::GlobalDiffuse", Shader::GlobalDiffuse },
        { "__const MATRIX4:::TextureProjectionMatrix", Shader::TextureProjectionMatrix },
        { "__COORD3:::LocalLightDirection", Shader::LocalLightDirection },
        { "__EAGL::GeoPrimState:::projective_shadow2_state", Shader::ProjectiveShadow2State },
        { "__EAGL::LightBlock:::nba_lightblock", Shader::NbaLightBlock },
        { "__const MATRIX4:::nba_envmapmatrix", Shader::NbaEnvMapMatrix },
        { "__EAGL::ComputationIndex:::nba_court_computation", Shader::NbaCourtComputation },
        { "__COORD4:::CourtConst", Shader::CourtConst },
        { "__const MATRIX4:::CourtConstMatrix", Shader::CourtConstMatrix },
        { "__EAGL::ComputationIndex:::nba_dimcomputation", Shader::NbaDimComputation },
        { "__COORD4:::nba_dornaUVOffset", Shader::NbaDornaUVOffset },
        { "__COORD4:::StadiumDimmer", Shader::StadiumDimmer },
        { "__const MATRIX4:::nba_dornaUVMatrix", Shader::NbaDornaUVMatrix },
        { "__EAGL::GeoPrimState:::nba_geomprimstatet_reflect", Shader::NbaGeomPrimStateT_Reflect },
        { "__EAGL::GeoPrimState:::nba_geomprimstatet", Shader::NbaGeomPrimStateT },
        { "__EAGL::ComputationIndex:::nba_irradcompidx", Shader::NbaIrradCompIdx },
        { "__COORD4:::nba_irradblock", Shader::NbaIrradBlock },
        { "__COORD4:::nba_eyeuvoffset", Shader::NbaEyeUVOffset },
        { "__const MATRIX4:::nba_eyeuvmatrix", Shader::NbaEyeUVMatrix },
        { "__EAGL::ComputationIndex:::nba_reflectcompidx", Shader::NbaReflectCompIdx },
        { "__const MATRIX4:::EAGL::ViewPort::gpViewProjectionMatrix", Shader::ViewProjectionMatrix },
        { "__EAGL::LightBlock:::nba_reflect_lightblock", Shader::NbaReflectLightblock },
        { "__COORD4:::ReflectionParams", Shader::ReflectionParams },
        { "__const MATRIX4:::nba_reflection_atten_matrix", Shader::NbaReflectionAttenMatrix },
        { "__COORD4:::SpecmapColour", Shader::SpecmapColour },
        { "__COORD4:::nba_shotclockUVs", Shader::NbaShotclockUVs },
        { "__const MATRIX4:::nba_shotclock_matrix0", Shader::NbaShotclockMatrix0 },
        { "__const MATRIX4:::nba_shotclock_matrix1", Shader::NbaShotclockMatrix1 },
        { "__const MATRIX4:::nba_shotclock_matrix2", Shader::NbaShotclockMatrix2 },
        { "__const MATRIX4:::nba_shotclock_matrix3", Shader::NbaShotclockMatrix3 },
        { "__const MATRIX4:::nba_shotclock_matrix4", Shader::NbaShotclockMatrix4 },
        { "__const MATRIX4:::nba_shotclock_matrix5", Shader::NbaShotclockMatrix5 },
        { "__EAGL::ComputationIndex:::nba_uniform_computation", Shader::NbaUniformComputation },
        { "__COORD4:::nba_uniform_front_uvscaleoffset", Shader::NbaUniformFrontUVScaleOffset },
        { "__const MATRIX4:::nba_uniform_front_uvscaleoffset_matrix", Shader::NbaUniformFrontUVScaleOffset_Matrix },
        { "__COORD4:::nba_uniform_back_uvscaleoffset", Shader::NbaUniformBackUVScaleOffset },
        { "__const MATRIX4:::nba_uniform_back_uvscaleoffset_matrix", Shader::NbaUniformBackUVScaleOffset_Matrix },
        { "__EAGL::ComputationIndex:::nba_unlituniform_computation", Shader::NbaUnlitUniformComputation },
        { "__COORD4:::nba_zbias", Shader::NbaZBias },
        { "__COORD4:::nba_jumbotron_uvoffsets", Shader::NbaJumbotronUVOffsets },
        { "__const MATRIX4:::nba_jumbotron_matrix0", Shader::NbaJumbotronMatrix0 },
        { "__const MATRIX4:::nba_jumbotron_matrix1", Shader::NbaJumbotronMatrix1 },
        { "__const MATRIX4:::nba_jumbotron_matrix2", Shader::NbaJumbotronMatrix2 },
        { "__const MATRIX4:::nba_jumbotron_matrix3", Shader::NbaJumbotronMatrix3 },
        { "__const MATRIX4:::nba_jumbotron_matrix4", Shader::NbaJumbotronMatrix4 },
        { "__const MATRIX4:::nba_jumbotron_matrix5", Shader::NbaJumbotronMatrix5 },
        { "__const MATRIX4:::nba_jumbotron_matrix6", Shader::NbaJumbotronMatrix6 },
        { "__const MATRIX4:::nba_jumbotron_matrix7", Shader::NbaJumbotronMatrix7 },
        { "__const MATRIX4:::nba_jumbotron_matrix8", Shader::NbaJumbotronMatrix8 },
        { "__const MATRIX4:::nba_jumbotron_matrix9", Shader::NbaJumbotronMatrix9 }
    };
    auto it = attrMap.find(symbolName);
    if (it != attrMap.end())
        return (*it).second;
    return 0;
}

class ShaderDumper {
    map<string, pair<unsigned int, vector<Shader::VertexDeclElement>>> shadersDef;
    vector<ShaderInfo> shaders;
    set<string> notFoundShaders;
    map<string, unsigned int> shaderTextures;

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
    void get_o_info(path const &inPath, bool isEAGLRM = false) {
        auto fileData = readofile(inPath);
        if (!fileData.first)
            return;
        string filename = inPath.filename().string();
        unsigned char *data = nullptr;
        unsigned int dataSize = 0;
        Elf32_Sym *symbolsData = nullptr;
        unsigned int numSymbols = 0;
        Elf32_Rel *rel = nullptr;
        unsigned int numRelocations = 0;
        char *symbolNames = nullptr;
        unsigned int symbolNamesSize = 0;
        unsigned int dataIndex = 0;

        Elf32_Ehdr *h = (Elf32_Ehdr *)fileData.first;
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

        if (isEAGLRM) {
            for (auto const &s : symbols) {
                if (isSymbolDataPresent(s)) {
                    if (s.name.ends_with("__EAGLMicroCode")) {
                        string shaderName = s.name.substr(0, s.name.length() - 15);
                        if (!shaderName.empty()) {
                            void *m = At<void *>(data, s.st_value);
                            auto &def = shadersDef[shaderName];
                            unsigned int maxSelected = GetAt<unsigned int>(m, 0);
                            unsigned int baseOffset = 4;
                            if (maxSelected == 0)
                                baseOffset = 0;
                            unsigned int numVD = GetAt<unsigned int>(m, baseOffset + 4);
                            unsigned int texCoordIndex = 0;
                            bool isSkinned = false;
                            bool hasPositions = false;
                            for (unsigned int i = 0; i < numVD; i++) {
                                unsigned char *pDecl = At<unsigned char>(m, baseOffset + 8 + i * 4);
                                if (pDecl[3] == 0x40) {
                                    Shader::VertexDeclElement decl;
                                    switch (pDecl[2]) {
                                    case 0:
                                        decl.type = Shader::D3DColor;
                                        decl.usage = Shader::Color1;
                                        isSkinned = true;
                                        break;
                                    case 1:
                                        decl.type = Shader::Float2;
                                        if (texCoordIndex == 0)
                                            decl.usage = Shader::Texcoord0;
                                        else if (texCoordIndex == 1)
                                            decl.usage = Shader::Texcoord1;
                                        else if (texCoordIndex == 2)
                                            decl.usage = Shader::Texcoord2;
                                        else if (texCoordIndex == 3)
                                            decl.usage = Shader::Texcoord3;
                                        texCoordIndex++;
                                        break;
                                    case 2:
                                        decl.type = Shader::Float3;
                                        if (!hasPositions) {
                                            decl.usage = Shader::Position;
                                            hasPositions = true;
                                        }
                                        else
                                            decl.usage = Shader::Normal;
                                        break;
                                    case 3:
                                        decl.type = Shader::Float4;
                                        decl.usage = Shader::Position;
                                        hasPositions = true;
                                        break;
                                    case 4:
                                        decl.type = Shader::D3DColor;
                                        decl.usage = Shader::Color0;
                                        break;
                                    default:
                                        Error("Unknown vertex decl type: %d in %s", pDecl[2], filename.c_str());
                                        break;
                                    }
                                    def.second.push_back(decl);
                                }
                            }
                            if (isSkinned) {
                                Shader::VertexDeclElement bi;
                                bi.type = Shader::UByte4;
                                bi.usage = Shader::BlendIndices;
                                def.second.push_back(bi);
                                Shader::VertexDeclElement bw;
                                bw.type = Shader::Float3;
                                bw.usage = Shader::BlendWeight;
                                def.second.push_back(bw);
                            }
                            def.first = GetAt<unsigned int>(m, baseOffset + 8 + numVD * 4);
                        }
                    }
                }
            }
        }
        else {
            vector<Model *> models;
            for (auto const &s : symbols) {
                if (isSymbolDataPresent(s)) {
                    if (s.name.starts_with("__Model:::"))
                        models.push_back(At<Model>(data, s.st_value));
                }
            }
            Model *model = nullptr;
            if (!models.empty()) {
                if (models.size() != 1)
                    sort(models.begin(), models.end(), [](Model *a, Model *b) { return a->mVariationID <= b->mVariationID; });
                model = models[0];
            }
            if (model) {
                static float vecOne[4] = { 1, 1, 1, 1 };
                static float vecZero[4] = { 0, 0, 0, 0 };
                static float vec0123[4] = { 0, 1, 2, 3 };
                static float vecNbaShotClock0[4] = { 0, 0, 0, 0 };
                static float vecNbaShotClock1[4] = { 1, 0, 0, 0 };
                static float vecNbaShotClock2[4] = { 2, 0, 0, 0 };
                static float vecNbaShotClock3[4] = { 3, 0, 0, 0 };
                static float vecNbaShotClock4[4] = { 4, 0, 0, 0 };
                static float vecNbaShotClock5[4] = { 5, 0, 0, 0 };
                static float vecNbaJumbotron0[4] = { 0, 0, 0, 0 };
                static float vecNbaJumbotron1[4] = { 1, 0, 0, 0 };
                static float vecNbaJumbotron2[4] = { 2, 0, 0, 0 };
                static float vecNbaJumbotron3[4] = { 3, 0, 0, 0 };
                static float vecNbaJumbotron4[4] = { 4, 0, 0, 0 };
                static float vecNbaJumbotron5[4] = { 5, 0, 0, 0 };
                static float vecNbaJumbotron6[4] = { 6, 0, 0, 0 };
                static float vecNbaJumbotron7[4] = { 7, 0, 0, 0 };
                static float vecNbaJumbotron8[4] = { 8, 0, 0, 0 };
                static float vecNbaJumbotron9[4] = { 9, 0, 0, 0 };
                static float vecEnvMapCoeff[4] = { 1.0f, 0.25f, 0.5f, 0.75f };
                static unsigned int vec0505051[4] = { 0x3EFEFF00, 0x3EFEFF00, 0x3EFEFF00, 0x3F800000 };
                static unsigned int vec3E30B0B1[4] = { 0x3E30B0B1, 0x3E30B0B1, 0x3E30B0B1, 0x3E30B0B1};
                static unsigned int vec3DA0A0A1[4] = { 0x3DA0A0A1, 0x3DA0A0A1, 0x3DA0A0A1, 0x3DA0A0A1 };
                static unsigned int vec40200000[4] = { 0x40200000, 0x40A00000, 0x3F000000, 0x3F800000 };
                map<void const *, ModifiableData const *> modifiables;
                for (unsigned int m = 0; m < model->mNumModifiableDatas; m++)
                    modifiables[model->mModifiableData[m].mEntries] = &model->mModifiableData[m];
                if (model->mNumLayers && model->mLayers) {
                    unsigned int *modelLayers = (unsigned int *)(model->mLayers);
                    unsigned int modelLayersHeader = *modelLayers;
                    bool isOldFormat = modelLayersHeader == 0xA0000000;
                    modelLayers++;
                    if (isOldFormat)
                        modelLayers += 2;
                    for (unsigned int i = 0; i < model->mNumLayers; i++) {
                        if (isOldFormat)
                            modelLayers += 2;
                        unsigned int numPrimitives = *modelLayers;
                        if (isOldFormat)
                            numPrimitives /= 2;
                        modelLayers++;
                        for (unsigned int p = 0; p < numPrimitives; p++) {
                            void *renderDescriptor = GetAt<void *>(modelLayers, isOldFormat ? (p * 8 + 4) : (p * 4));
                            RenderMethod *renderMethod = GetAt<RenderMethod *>(renderDescriptor, 0);
                            void *globalParameters = At<void *>(renderDescriptor, 4);
                            unsigned int rmCodeOffset = At<unsigned char>(renderMethod, 8) - data;
                            auto it = symbolRelocations.find(rmCodeOffset);
                            if (it != symbolRelocations.end() && (*it).second.st_info == 0x10) {
                                string codeName = (*it).second.name;
                                if (codeName.ends_with("__EAGLMicroCode")) {
                                    auto shaderName = codeName.substr(0, codeName.length() - 15);
                                    auto it = shadersDef.find(shaderName);
                                    if (it != shadersDef.end()) {
                                        auto const &shader = (*it).second;
                                        ShaderInfo info;
                                        info.name = shaderName;
                                        void *renderCode = GetAt<void *>(renderMethod, 0);
                                        unsigned int numCommands = 0;
                                        unsigned int commandOffset = 0;
                                        vector<unsigned short> firstTechniqueCommands;
                                        for (unsigned int t = 0; t < shader.first; t++) {
                                            unsigned short id = GetAt<unsigned short>(renderCode, commandOffset + 2);
                                            unsigned short size = GetAt<unsigned short>(renderCode, commandOffset);
                                            unsigned int commandIndex = 0;
                                            while (id != 0) {
                                                if (t == 0)
                                                    numCommands++;
                                                if (size == 0) {
                                                    Error("Incorrect instruction size (0) in %s", filename.c_str());
                                                    break;
                                                }
                                                if (id == 31)
                                                    id = 46;
                                                auto firstTechniqueCommandId = id;
                                                if (t == 0)
                                                    firstTechniqueCommands.push_back(id);
                                                else if (firstTechniqueCommandId == 1)
                                                    firstTechniqueCommandId = firstTechniqueCommands[commandIndex];
                                                unsigned int numArguments = size - 1;
                                                vector<int> args(numArguments);
                                                vector<int> originalArgs(numArguments);
                                                for (unsigned int a = 0; a < numArguments; a++)
                                                    originalArgs[a] = GetAt<unsigned int>(renderCode, commandOffset + 4 + a * 4);
                                                for (unsigned int a = 0; a < numArguments; a++) {
                                                    args[a] = GetAt<unsigned int>(renderCode, commandOffset + 4 + a * 4);
                                                    if (firstTechniqueCommandId == 4 || firstTechniqueCommandId == 75) {
                                                        if (a == 5)
                                                            args[a] = Shader::VertexData;
                                                        else if (a == 6)
                                                            args[a] = Shader::VertexCount;
                                                        else if (a == 7)
                                                            args[a] = Shader::VariationsCount;
                                                        else if (a == 8)
                                                            args[a] = Shader::VertexBufferIndex;
                                                        if (t == 0 && a == 1)
                                                            info.debugVertexSize = args[a];
                                                    }
                                                    else if (firstTechniqueCommandId == 65 || firstTechniqueCommandId == 57) {
                                                        if (a == 6)
                                                            args[a] = Shader::VertexData;
                                                        else if (a == 7)
                                                            args[a] = Shader::VertexCount;
                                                        else if (a == 8)
                                                            args[a] = Shader::VariationsCount;
                                                        else if (a == 9)
                                                            args[a] = Shader::VertexBufferIndex;
                                                        else if (a >= 22) {
                                                            if (numArguments == 43) {
                                                                if (originalArgs[6] == originalArgs[28] && originalArgs[7] == originalArgs[29] && originalArgs[8] == originalArgs[30] && originalArgs[9] == originalArgs[31]) {
                                                                    if (a == 28)
                                                                        args[a] = Shader::VertexData;
                                                                    else if (a == 29)
                                                                        args[a] = Shader::VertexCount;
                                                                    else if (a == 30)
                                                                        args[a] = Shader::VariationsCount;
                                                                    else if (a == 31)
                                                                        args[a] = Shader::VertexBufferIndex;
                                                                }
                                                                else if (originalArgs[6] == originalArgs[26] && originalArgs[7] == originalArgs[27] && originalArgs[8] == originalArgs[28] && originalArgs[9] == originalArgs[29]) {
                                                                    if (a == 26)
                                                                        args[a] = Shader::VertexData;
                                                                    else if (a == 27)
                                                                        args[a] = Shader::VertexCount;
                                                                    else if (a == 28)
                                                                        args[a] = Shader::VariationsCount;
                                                                    else if (a == 29)
                                                                        args[a] = Shader::VertexBufferIndex;
                                                                }
                                                            }
                                                            else if (numArguments == 35 && originalArgs[6] == originalArgs[22] && originalArgs[7] == originalArgs[23] && originalArgs[8] == originalArgs[24] && originalArgs[9] == originalArgs[25]) {
                                                                if (a == 22)
                                                                    args[a] = Shader::VertexData;
                                                                else if (a == 23)
                                                                    args[a] = Shader::VertexCount;
                                                                else if (a == 24)
                                                                    args[a] = Shader::VariationsCount;
                                                                else if (a == 25)
                                                                    args[a] = Shader::VertexBufferIndex;
                                                            }
                                                            else {
                                                                if (args[18] == args[19]) {
                                                                    if (a == 26)
                                                                        args[a] = Shader::VertexData;
                                                                    else if (a == 27)
                                                                        args[a] = Shader::VertexCount;
                                                                    else if (a == 28)
                                                                        args[a] = Shader::VariationsCount;
                                                                    else if (a == 29)
                                                                        args[a] = Shader::VertexBufferIndex;
                                                                }
                                                                else {
                                                                    if (a == 25)
                                                                        args[a] = Shader::VertexData;
                                                                    else if (a == 26)
                                                                        args[a] = Shader::VertexCount;
                                                                    else if (a == 27)
                                                                        args[a] = Shader::VariationsCount;
                                                                    else if (a == 28)
                                                                        args[a] = Shader::VertexBufferIndex;
                                                                }
                                                            }
                                                        }
                                                    }
                                                    else if (firstTechniqueCommandId == 7) {
                                                        if (a == 3)
                                                            args[a] = Shader::IndexData;
                                                        else if (a == 4)
                                                            args[a] = Shader::IndexCount;
                                                    }
                                                    else if (firstTechniqueCommandId == 28) {
                                                        if (a == 0)
                                                            args[a] = Shader::VertexWeights3Bones;
                                                        else if (a == 1)
                                                            args[a] = Shader::VertexWeights2Bones;
                                                        else if (a == 2)
                                                            args[a] = Shader::VertexWeights1Bone;
                                                    }
                                                    else if (firstTechniqueCommandId == 9 || firstTechniqueCommandId == 32) {
                                                        if (a == 1) {
                                                            if (args[0] == 0)
                                                                args[a] = Shader::Sampler0Size;
                                                            else if (args[0] == 1)
                                                                args[a] = Shader::Sampler1Size;
                                                            else if (args[0] == 2)
                                                                args[a] = Shader::Sampler2Size;
                                                            else if (args[0] == 3)
                                                                args[a] = Shader::Sampler3Size;
                                                        }
                                                    }
                                                }
                                                info.commands.emplace_back(unsigned char(id), args);
                                                commandIndex++;
                                                commandOffset += size * 4;
                                                id = GetAt<unsigned short>(renderCode, commandOffset + 2);
                                                size = GetAt<unsigned short>(renderCode, commandOffset);
                                            }
                                            commandOffset += 4;
                                        }
                                        if (numCommands > 2) {
                                            info.globalArguments.resize(numCommands - 2);
                                            for (unsigned int g = 0; g < info.globalArguments.size(); g++) {
                                                info.globalArguments[g].type = 0;
                                                if (g == 0)
                                                    info.globalArguments[g].type = Shader::GeometryInfo;
                                                else {
                                                    auto argDataPtr = At<void *>(globalParameters, 4);
                                                    auto argData = *argDataPtr;
                                                    auto argCount = GetAt<unsigned int>(globalParameters, 0);
                                                    switch (firstTechniqueCommands[g + 1]) {
                                                    case 4:
                                                    case 75:
                                                        info.globalArguments[g].type = Shader::VertexData;
                                                        break;
                                                    case 7:
                                                        info.globalArguments[g].type = Shader::IndexData;
                                                        break;
                                                    case 28:
                                                        info.globalArguments[g].type = Shader::VertexSkinData;
                                                        break;
                                                    case 9:
                                                    case 32:
                                                    {
                                                        if (info.commands[g + 1].arguments.size() > 0) {
                                                            switch (info.commands[g + 1].arguments[0]) {
                                                            case 0:
                                                                info.globalArguments[g].type = Shader::Sampler0;
                                                                break;
                                                            case 1:
                                                                info.globalArguments[g].type = Shader::Sampler1;
                                                                break;
                                                            case 2:
                                                                info.globalArguments[g].type = Shader::Sampler2;
                                                                break;
                                                            case 3:
                                                                info.globalArguments[g].type = Shader::Sampler3;
                                                                break;
                                                            default:
                                                                info.globalArguments[g].type = 0;
                                                                break;
                                                            }
                                                        }
                                                        Texture const *tar = GetAt<Texture *>(globalParameters, 4);
                                                        string tarAttributes;
                                                        if (tar) { // local texture
                                                            char texTag[5];
                                                            Memory_Copy(texTag, tar->tag, 4);
                                                            texTag[4] = '\0';
                                                            string texName = texTag;
                                                            string texSymbolName = "__EAGL::TAR:::tar_" + texName + "_";
                                                            unsigned int samplerArgType = SamplerArgumentType::SamplerLocalPrivate;
                                                            for (auto const &ts : symbols) {
                                                                if (ts.name.starts_with(texSymbolName)) {
                                                                    samplerArgType = SamplerArgumentType::SamplerLocalPublic;
                                                                    break;
                                                                }
                                                            }
                                                            shaderTextures[texTag] |= samplerArgType;
                                                            if (info.commands[g + 1].arguments.size() > 0 && info.commands[g + 1].arguments[0] < 4)
                                                                info.samplerArguments[info.commands[g + 1].arguments[0]] |= samplerArgType;
                                                        }
                                                        else { // global or runtime-constructed texture
                                                            unsigned int tarOffset = unsigned int(At<Texture *>(globalParameters, 4)) - unsigned int(data);
                                                            auto it2 = symbolRelocations.find(tarOffset);
                                                            if (it2 != symbolRelocations.end()) {
                                                                auto const &s = (*it2).second;
                                                                if (s.name.length() > 14 && s.name.starts_with("__EAGL::TAR:::")) {
                                                                    tarAttributes = s.name.substr(14);
                                                                    string texName;
                                                                    if (!tarAttributes.starts_with("RUNTIME_ALLOC"))
                                                                        texName = tarAttributes;
                                                                    else {
                                                                        auto shapenamePos = tarAttributes.find("SHAPENAME=");
                                                                        if (shapenamePos != string::npos) {
                                                                            auto semiColonPos = tarAttributes.find_first_of(",;", shapenamePos + 10);
                                                                            if (semiColonPos != string::npos)
                                                                                texName = tarAttributes.substr(shapenamePos + 10, semiColonPos - shapenamePos - 10);
                                                                            else
                                                                                texName = tarAttributes.substr(shapenamePos + 10);
                                                                        }
                                                                    }
                                                                    if (!texName.empty()) {
                                                                        shaderTextures[texName] |= SamplerArgumentType::SamplerGlobal;
                                                                        if (info.commands[g + 1].arguments.size() > 0 && info.commands[g + 1].arguments[0] < 4)
                                                                            info.samplerArguments[info.commands[g + 1].arguments[0]] |= SamplerArgumentType::SamplerGlobal;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    break;
                                                    default:
                                                        {
                                                            auto rit = symbolRelocations.find(unsigned int(argDataPtr) - unsigned int(data));
                                                            if (rit != symbolRelocations.end()) {
                                                                string symbolName = (*rit).second.name;
                                                                auto attr = GetShaderAttributeFromSymbolName(symbolName);
                                                                if (attr != 0)
                                                                    info.globalArguments[g].type = attr;
                                                                else {
                                                                    if (symbolName.starts_with("__EAGL::GeoPrimState:::RUNTIME_ALLOC")) {
                                                                        auto gb = symbolName.find(';');
                                                                        if (gb != string::npos) {
                                                                            auto ge = symbolName.find("SetPrimitiveType=");
                                                                            if (ge != string::npos) {
                                                                                info.globalArguments[g].type = Shader::RuntimeGeoPrimState;
                                                                                if (argData) {
                                                                                    auto mit = modifiables.find(argData);
                                                                                    if (mit != modifiables.end()) {
                                                                                        if ((*mit).second->mName == "State::GeoPrimState")
                                                                                            info.globalArguments[g].type = Shader::RuntimeGeoPrimState2;
                                                                                    }
                                                                                } 
                                                                                info.globalArguments[g].format = symbolName.substr(gb + 1, ge - gb - 2);
                                                                            }
                                                                        }
                                                                    }
                                                                    if (!info.globalArguments[g].type && argData) {
                                                                        auto mit = modifiables.find(argData);
                                                                        if (mit != modifiables.end()) {
                                                                            ModifiableData const *m = (*mit).second;
                                                                            string mname = m->mName;
                                                                            if (mname == "ComputationIndex::CompIdx")
                                                                                info.globalArguments[g].type = Shader::ComputationIndex;
                                                                            else if(mname == "Coordinate4::BaseColour")
                                                                                info.globalArguments[g].type = Shader::BaseColour;
                                                                            else if(mname == "Light::LightBlock")
                                                                                info.globalArguments[g].type = Shader::Light;
                                                                            else if(mname == "IrradLight::IrradBlock")
                                                                                info.globalArguments[g].type = Shader::IrradLight;
                                                                            else if(mname == "State::State")
                                                                                info.globalArguments[g].type = Shader::GeoPrimState;
                                                                            else if (mname.ends_with("::UVOffset0"))
                                                                                info.globalArguments[g].type = Shader::UVOffset0;
                                                                            else if (mname.ends_with("::UVOffset1"))
                                                                                info.globalArguments[g].type = Shader::UVOffset1;
                                                                            else if (mname.ends_with("::XFade"))
                                                                                info.globalArguments[g].type = Shader::XFade;
                                                                            else if (mname == "Coordinate4::GeomName::CrowdTintH")
                                                                                info.globalArguments[g].type = Shader::CrowdTintH;
                                                                            else if (mname == "Coordinate4::GeomName::CrowdTintA")
                                                                                info.globalArguments[g].type = Shader::CrowdTintA;
                                                                            else if (mname == "Coordinate4::LightMultipliers")
                                                                                info.globalArguments[g].type = Shader::LightMultipliers;
                                                                            else if (mname == "Coordinate4::UVOffset")
                                                                                info.globalArguments[g].type = Shader::UVOffset;
                                                                            else if (mname == "Coordinate4::UVMatrix")
                                                                                info.globalArguments[g].type = Shader::UVMatrix;
                                                                            else if (mname.ends_with("::UVOffset"))
                                                                                info.globalArguments[g].type = Shader::UVOffset_Layer;
                                                                            else if (mname.ends_with("::UVMatrix"))
                                                                                info.globalArguments[g].type = Shader::UVMatrix_Layer;
                                                                            else if (mname == "Coordinate4::ColourScale")
                                                                                info.globalArguments[g].type = Shader::ColourScale;
                                                                            else if (mname.length() >= 29 && mname.starts_with("Coordinate4::") && mname.ends_with("::InstanceColour"))
                                                                                info.globalArguments[g].type = Shader::InstanceColour;
                                                                        }
                                                                        else {
                                                                            if (!memcmp(argData, vec0123, 16))
                                                                                info.globalArguments[g].type = Shader::ZeroOneTwoThreeLocal;
                                                                            else if (!memcmp(argData, vecEnvMapCoeff, 16))
                                                                                info.globalArguments[g].type = Shader::EnvMapConstantsLocal;
                                                                            else if (shaderName == "ClipTextureModulateNodepthwrite") {
                                                                                if (!memcmp(argData, vecOne, 16))
                                                                                    info.globalArguments[g].type = Shader::VecOneLocal;
                                                                                else if (!memcmp(argData, vecZero, 16))
                                                                                    info.globalArguments[g].type = Shader::VecZeroLocal;
                                                                            }
                                                                            else if (shaderName == "GouraudApt") {
                                                                                if (!memcmp(argData, vec0505051, 16))
                                                                                    info.globalArguments[g].type = Shader::Vec0505051Local;
                                                                            }
                                                                            else if (shaderName == "IrradTextureEnvmapLS_Skin") {
                                                                                if (!memcmp(argData, vec3E30B0B1, 16))
                                                                                    info.globalArguments[g].type = Shader::Vec3E30B0B1Local;
                                                                                else if (!memcmp(argData, vec3DA0A0A1, 16))
                                                                                    info.globalArguments[g].type = Shader::Vec3DA0A0A1Local;
                                                                            }
                                                                            else if (shaderName == "MowPattern") {
                                                                                if (!memcmp(argData, vec40200000, 16))
                                                                                    info.globalArguments[g].type = Shader::Vec40200000Local;
                                                                            }
                                                                            else if (shaderName == "NBAShotClock_FastSkin") {
                                                                                if (!memcmp(argData, vecNbaShotClock0, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaShotClock0Local;
                                                                                else if (!memcmp(argData, vecNbaShotClock1, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaShotClock1Local;
                                                                                else if (!memcmp(argData, vecNbaShotClock2, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaShotClock2Local;
                                                                                else if (!memcmp(argData, vecNbaShotClock3, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaShotClock3Local;
                                                                                else if (!memcmp(argData, vecNbaShotClock4, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaShotClock4Local;
                                                                                else if (!memcmp(argData, vecNbaShotClock5, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaShotClock5Local;
                                                                            }
                                                                            else if (shaderName == "NBAJumbotron") {
                                                                                if (!memcmp(argData, vecNbaJumbotron0, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron0Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron1, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron1Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron2, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron2Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron3, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron3Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron4, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron4Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron5, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron5Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron6, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron6Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron7, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron7Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron8, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron8Local;
                                                                                else if (!memcmp(argData, vecNbaJumbotron9, 16))
                                                                                    info.globalArguments[g].type = Shader::NbaJumbotron9Local;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        break;
                                                    }
                                                }
                                                globalParameters = At<void>(globalParameters, 8);
                                            }
                                        }
                                        bool found = false;
                                        for (auto &si : shaders) {
                                            if (si == info) {
                                                si.files.insert(filename);
                                                si.numFiles += 1;
                                                found = true;
                                                break;
                                            }
                                        }
                                        if (!found) {
                                            info.numTechniques = shader.first;
                                            info.declaration = shader.second;
                                            info.files.insert(filename);
                                            info.numFiles = 1;
                                            info.Update(false);
                                            shaders.push_back(info);
                                        }
                                    }
                                    else {
                                        if (!notFoundShaders.contains(shaderName)) {
                                            Error("Shader not found: " + shaderName);
                                            notFoundShaders.insert(shaderName);
                                        }
                                    }
                                }
                            }
                        }
                        modelLayers += numPrimitives * (isOldFormat ? 2 : 1);
                    }
                }
            }
        }
        delete[] fileData.first;
    }

    void dump(path const &inPath) {
        cout << "Scanning folders for eaglrm.o" << endl;
        bool eaglrmFound = false;
        for (auto const &i : recursive_directory_iterator(inPath)) {
            auto const &p = i.path();
            if (is_regular_file(p) && p.filename() == "eaglrm.o") {
                cout << "Found eaglrm.o" << endl;
                get_o_info(p, true);
                eaglrmFound = true;
                break;
            }
        }
        if (eaglrmFound) {
            cout << "Scanning folders for .o files" << endl;
            for (auto const &i : recursive_directory_iterator(inPath)) {
                auto const &p = i.path();
                if (is_regular_file(p) && (ToLower(p.extension().string()) == ".o" || ToLower(p.extension().string()) == ".ord") && p.filename() != "eaglrm.o") {
                    try {
                        get_o_info(p, false);
                    }
                    catch (exception e) {
                        Error("Unable to get info from model %s", p.string().c_str());
                    }
                }
            }
            string targetName = "shaders_" + inPath.filename().string();
            string targetFileName = targetName + ".txt";
            cout << "Writing to " << targetFileName << endl;
            FILE *out = fopen(targetFileName.c_str(), "wt");
            if (out) {
                sort(shaders.begin(), shaders.end(), [](ShaderInfo const &a, ShaderInfo const &b) {
                    if (a.name < b.name)
                        return true;
                    if (b.name < a.name)
                        return false;
                    if (a.commands.size() > b.commands.size())
                        return true;
                    if (b.commands.size() > a.commands.size())
                        return false;
                    return a.files.size() > b.files.size();
                });
                vector<string> samplersLocalPublic;
                vector<string> samplersLocalPrivate;
                vector<string> samplersLocalPublicAndPrivate;
                vector<string> samplersLocalPublicAndGlobal;
                vector<string> samplersLocalPrivateAndGlobal;
                vector<string> samplersLocalPublicAndPrivateAndGlobal;
                for (auto const &[texName, type] : shaderTextures) {
                    if (type == (SamplerArgumentType::SamplerLocalPublic))
                        samplersLocalPublic.push_back(texName);
                    else if (type == (SamplerArgumentType::SamplerLocalPrivate))
                        samplersLocalPrivate.push_back(texName);
                    else if (type == (SamplerArgumentType::SamplerLocalPublic | SamplerArgumentType::SamplerLocalPrivate))
                        samplersLocalPublicAndPrivate.push_back(texName);
                    else if (type == (SamplerArgumentType::SamplerLocalPublic | SamplerArgumentType::SamplerGlobal))
                        samplersLocalPublicAndGlobal.push_back(texName);
                    else if (type == (SamplerArgumentType::SamplerLocalPrivate | SamplerArgumentType::SamplerGlobal))
                        samplersLocalPrivateAndGlobal.push_back(texName);
                    else if (type == (SamplerArgumentType::SamplerLocalPublic | SamplerArgumentType::SamplerLocalPrivate | SamplerArgumentType::SamplerGlobal))
                        samplersLocalPublicAndPrivateAndGlobal.push_back(texName);
                }
                if (!samplersLocalPublic.empty()) {
                    fputs("// local public samplers: ", out);
                    for (unsigned int n = 0; n < samplersLocalPublic.size(); n++) {
                        if (n != 0)
                            fputs(", ", out);
                        fputs(("\"" + samplersLocalPublic[n] + "\"").c_str(), out);
                    }
                    fputs("\n", out);
                }
                if (!samplersLocalPrivate.empty()) {
                    fputs("// local private samplers: ", out);
                    for (unsigned int n = 0; n < samplersLocalPrivate.size(); n++) {
                        if (n != 0)
                            fputs(", ", out);
                        fputs(("\"" + samplersLocalPrivate[n] + "\"").c_str(), out);
                    }
                    fputs("\n", out);
                }
                if (!samplersLocalPublicAndPrivate.empty()) {
                    fputs("// local public/private samplers: ", out);
                    for (unsigned int n = 0; n < samplersLocalPublicAndPrivate.size(); n++) {
                        if (n != 0)
                            fputs(", ", out);
                        fputs(("\"" + samplersLocalPublicAndPrivate[n] + "\"").c_str(), out);
                    }
                    fputs("\n", out);
                }
                if (!samplersLocalPublicAndGlobal.empty()) {
                    fputs("// local public/global samplers: ", out);
                    for (unsigned int n = 0; n < samplersLocalPublicAndGlobal.size(); n++) {
                        if (n != 0)
                            fputs(", ", out);
                        fputs(("\"" + samplersLocalPublicAndGlobal[n] + "\"").c_str(), out);
                    }
                    fputs("\n", out);
                }
                if (!samplersLocalPrivateAndGlobal.empty()) {
                    fputs("// local private/global samplers: ", out);
                    for (unsigned int n = 0; n < samplersLocalPrivateAndGlobal.size(); n++) {
                        if (n != 0)
                            fputs(", ", out);
                        fputs(("\"" + samplersLocalPrivateAndGlobal[n] + "\"").c_str(), out);
                    }
                    fputs("\n", out);
                }
                if (!samplersLocalPublicAndPrivateAndGlobal.empty()) {
                    fputs("// local public/private/global samplers: ", out);
                    for (unsigned int n = 0; n < samplersLocalPublicAndPrivateAndGlobal.size(); n++) {
                        if (n != 0)
                            fputs(", ", out);
                        fputs(("\"" + samplersLocalPublicAndPrivateAndGlobal[n] + "\"").c_str(), out);
                    }
                    fputs("\n", out);
                }
                fprintf(out, "Shader %s[%d] = {\n", targetName.c_str(), shaders.size());
                string lastShaderName;
                unsigned int nameCounter = 1;
                for (unsigned int i = 0; i < shaders.size(); i++) {
                    auto const &s = shaders[i];
                    string name = s.name;
                    if (name == lastShaderName)
                        name += "." + to_string(++nameCounter);
                    else {
                        lastShaderName = name;
                        nameCounter = 1;
                    }
                    if (i != 0)
                        fputs(",\n", out);
                    fputs("    // ", out);
                    string shaderFullId = "t" + to_string(s.numTechniques);
                    if (!s.declaration.empty()) {
                        shaderFullId += "d";
                        for (auto const &d : s.declaration)
                            shaderFullId += to_string(d.type) + to_string(d.usage);
                    }
                    for (auto const &ic : s.commands) {
                        shaderFullId += "c" + to_string(ic.id);
                        for (auto const &ica : ic.arguments)
                            shaderFullId += "a" + to_string(unsigned int(ica));
                    }
                    for (auto const &ig : s.globalArguments) {
                        shaderFullId += "g" + to_string(unsigned int(ig.type));
                        if (!ig.format.empty())
                            shaderFullId += "f" + to_string(Hash(ig.format));
                    }
                    string shaderIdLine = name + ", hash " + to_string(Hash(shaderFullId));
                    fputs(shaderIdLine.c_str(), out);
                    fputs("\n", out);
                    if (s.debugVertexSize != s.VertexSize())
                        fprintf(out, "    // NOTE: vertex size mismatch (%d calculated, %d in code)", s.VertexSize(), s.debugVertexSize);
                    fprintf(out, "    // in files (%d): ", s.numFiles);
                    bool first = true;
                    for (auto const &f : s.files) {
                        if (first)
                            first = false;
                        else
                            fputs(", ", out);
                        fputs(f.c_str(), out);
                    }
                    fprintf(out, "\n    { \"%s\", %d, { ", name.c_str(), s.numTechniques);
                    first = true;
                    for (auto const &d : s.declaration) {
                        if (first)
                            first = false;
                        else
                            fputs(", ", out);
                        fputs("{ Shader::", out);
                        switch (d.type) {
                        case Shader::D3DColor:
                            fputs("D3DColor", out);
                            break;
                        case Shader::UByte4:
                            fputs("UByte4", out);
                            break;
                        case Shader::Float2:
                            fputs("Float2", out);
                            break;
                        case Shader::Float3:
                            fputs("Float3", out);
                            break;
                        case Shader::Float4:
                            fputs("Float4", out);
                            break;
                        }
                        fputs(", Shader::", out);
                        switch (d.usage) {
                        case Shader::Color0:
                            fputs("Color0", out);
                            break;
                        case Shader::Color1:
                            fputs("Color1", out);
                            break;
                        case Shader::Position:
                            fputs("Position", out);
                            break;
                        case Shader::Normal:
                            fputs("Normal", out);
                            break;
                        case Shader::Texcoord0:
                            fputs("Texcoord0", out);
                            break;
                        case Shader::Texcoord1:
                            fputs("Texcoord1", out);
                            break;
                        case Shader::Texcoord2:
                            fputs("Texcoord2", out);
                            break;
                        case Shader::Texcoord3:
                            fputs("Texcoord3", out);
                            break;
                        case Shader::BlendIndices:
                            fputs("BlendIndices", out);
                            break;
                        case Shader::BlendWeight:
                            fputs("BlendWeight", out);
                            break;
                        }
                        fputs(" }", out);
                    }
                    fputs(" },\n", out);
                    fputs("    {\n", out);
                    if (!s.commands.empty() && s.numTechniques > 0) {
                        unsigned int commandsPerTechnique = s.commands.size() / s.numTechniques;
                        unsigned int currentCommand = 0;
                        for (unsigned int ci = 0; ci < s.commands.size(); ci++) {
                            auto const &c = s.commands[ci];
                            if (ci != 0) {
                                if (currentCommand == 0)
                                    fputs(",\n\n", out);
                                else
                                    fputs(",\n", out);
                            }
                            fputs("    { ", out);
                            fputs(CommandName(c.id).c_str(), out);
                            fputs(", { ", out);
                            for (unsigned int ai = 0; ai < c.arguments.size(); ai++) {
                                auto const &a = c.arguments[ai];
                                if (ai != 0)
                                    fputs(", ", out);
                                string astr = GetShaderAttributeName(a);
                                if (!astr.empty())
                                    fputs(astr.c_str(), out);
                                else
                                    fputs(Format(a > 32'000 ? "0x%X" : "%d", a).c_str(), out);
                            }
                            fputs(" } }", out);
                            currentCommand++;
                            if (currentCommand == commandsPerTechnique)
                                currentCommand = 0;
                        }
                    }
                    fputs("\n    },\n", out);
                    fputs("    {\n", out);
                    if (!s.globalArguments.empty() && s.numTechniques > 0) {
                        for (unsigned int gi = 0; gi < s.globalArguments.size(); gi++) {
                            auto const &g = s.globalArguments[gi];
                            fputs("    ", out);
                            if (!g.format.empty())
                                fputs("{ ", out);
                            string astr = GetShaderAttributeName(g.type);
                            if (!astr.empty())
                                fputs(astr.c_str(), out);
                            else
                                fputs("UNKNOWN_ARGUMENT", out);
                            if (!g.format.empty()) {
                                fputs(", \"", out);
                                fputs(g.format.c_str(), out);
                                fputs("\" }", out);
                            }
                            int samplerIndex = -1;
                            if (astr.starts_with("Shader::Sampler")) {
                                if (astr.ends_with("0"))
                                    samplerIndex = 0;
                                else if (astr.ends_with("1"))
                                    samplerIndex = 1;
                                else if (astr.ends_with("2"))
                                    samplerIndex = 2;
                                else if (astr.ends_with("3"))
                                    samplerIndex = 3;
                            }
                            if (samplerIndex >= 0 && samplerIndex <= 3) {
                                unsigned int type = s.samplerArguments[samplerIndex];
                                if (type == SamplerArgumentType::SamplerLocalPublic || type == SamplerArgumentType::SamplerLocalPrivate || type == (SamplerArgumentType::SamplerLocalPublic | SamplerArgumentType::SamplerLocalPrivate))
                                    fputs("Local", out);
                            }
                            if (gi != (s.globalArguments.size() - 1))
                                fputs(",", out);
                            if (samplerIndex >= 0 && samplerIndex <= 3) {
                                unsigned int type = s.samplerArguments[samplerIndex];
                                if (type == (SamplerArgumentType::SamplerGlobal))
                                    fputs(" // global", out);
                                else if (type == (SamplerArgumentType::SamplerLocalPublic))
                                    fputs(" // local public", out);
                                else if (type == (SamplerArgumentType::SamplerLocalPrivate))
                                    fputs(" // local private", out);
                                else if (type == (SamplerArgumentType::SamplerLocalPublic | SamplerArgumentType::SamplerLocalPrivate))
                                    fputs(" // local public/private", out);
                                else if (type == (SamplerArgumentType::SamplerLocalPublic | SamplerArgumentType::SamplerGlobal))
                                    fputs(" // local public/global", out);
                                else if (type == (SamplerArgumentType::SamplerLocalPrivate | SamplerArgumentType::SamplerGlobal))
                                    fputs(" // local private/global", out);
                                else if (type == (SamplerArgumentType::SamplerLocalPublic | SamplerArgumentType::SamplerLocalPrivate | SamplerArgumentType::SamplerGlobal))
                                    fputs(" // local public/private/global", out);
                            }
                            if (gi != (s.globalArguments.size() - 1))
                                fputs("\n", out);
                        }
                    }
                    fputs("\n    }\n", out);
                    fputs("    }", out);
                }
                fputs("\n};\n", out);
                fclose(out);
            }
        }
        else
            cout << "Can't find eaglrm.o" << endl;
    }
};

void dumpshaders(path const &out, path const &in) {
    ShaderDumper s;
    s.dump(in);
}
