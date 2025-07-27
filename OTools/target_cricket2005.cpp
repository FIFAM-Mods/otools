#include "target.h"

Shader shaders_CRICKET2005[10] = {
    // Gouraud, hash 3037938960
    // in files (134): 04272f7672b68a2a0b935dd683d6a492.o, 08d89df82858b64a8e605c96f8e289b6.o, 0aa7625fe46ab033098c92efa5037c2d.o, 0bad575f84a1ae52add919854280a36f.o, 0e0e536741c7e92aa815305846cc6f0e.o, 1020a3a8a19fd21f79f0c3c300150ff4.o, 108026fd4465697c0df4b500302bd6f2.o, 20dc9d22d54cbc68f2338dd74aff427d.o, 275a2815a1b0ee058738c39f5c901fb0.o, 2fb4c19ac75d25ebe630818d6be044b4.o, 32d243dd4a2af466c7ebac2d68c802df.o, 3900f595526bff443f30de11b482e4c4.o, 3978e198943373dee46d234f0006d089.o, 40c3d7fbaf0045602fb40e3f93b65dc8.o, 4a381877dfb05e1dbe9f65ac23791967.o, 4e521d2dd1f713f984b55a55c6fb28d2.o, 4f83ea6abfba06ecd065db10e46d6fab.o, 5ae3a9fb66c3b63a7c6f2ec2411928da.o, 5beb64c2c6af56f475bc61cad19a72bb.o, 61ba5626a37269f7e3947df3d917b516.o, 64cfc25fe971cb66fa65dede732d17c9.o, 65f543457a72920c9fdad2cb057b662f.o, 69680536d9231acb4422f96687e12bcc.o, 6b7ba35f87c91253351a5b97f6ce18c2.o, 7c30348183ada24562030df4d14e035a.o, 7c7ea009f760516af64c2e2bcbbda972.o, 926a8150608942d812fc584dccfd3e09.o, 9681e0cc950378b7beb39b0cfea19af0.o, a5aa36e9abbeaf0397249dbd9b134d1b.o, a9ad77811640f2d0ad27183850819c57.o, aca20752aa62e630719facde508c160b.o, adc0637506b96dd2ad0a17ca7925e2c3.o, af6089e34ace00ef3aa2940f952cb47f.o, b3b93af030a7629df2ac0aa84ecc3c46.o, ba8aeb7caaaa832ab9d4e96b8ec9dc71.o, c3cfa5d1c12aaa0c8a7b52733d04c19e.o, c516d7bc5ec57b64658763646b49f87d.o, ca49106b8d950b42650c39c38bc2389a.o, cd9367447cb9a822ce6a2f3de8579103.o, dcf793a4fea7f820c0da34d9423d7e95.o, de14e546fab81224bd8dbe46a59430c5.o, df4f8258176bec0d3003b7dbbbdb73d3.o, e2b6976250911b6a4d0e4e2aefd49cbc.o, e62d006a2d36ec5fe8e3456c8b74871f.o, e63976b010c87786f78417f5b206b1ee.o, e8ea5732885803bcb91fcc866baf8dec.o, ea696fd300b51b2bf566fde5f3e61ce0.o, ed3ca2aed0c1ff1944bc380fda92bc7d.o, f4f7724c59721757e67267fc7e7ede18.o, f90d349b1096e2775a6e0ce398c958a7.o
    { "Gouraud", 2, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_STREAM_SOURCE, { 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 2 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { NOP_1, { 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 6, 0x330002, 1, 0x340002, 2, 0x3D0002, 3, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::ModelViewProjectionMatrix,
    { Shader::RuntimeGeoPrimState, ";SetTextureEnable=false" },
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // Gouraud_Skin, hash 359323073
    // in files (46): 18504bbc6b5b5f33089b826fe7be01f4.o, 35f9a288440b6e34b4f73864b207fa32.o, 3e5d6a3045137d1a919925fd6b4fb6ee.o, 6350be6da0133421cec17f77f2be60b2.o, 9960a52dfa9e1ff0589f86fff78dc9d6.o, a0da54a7f196eab044ec2bf85be44d24.o, b49e6a867e770ed74a3dfb25fe23238a.o, b820df4cdd32ba005d43cbb327d1ec70.o, d40140ecfdcd8a2dc0a3dcd282cd0ad7.o, df13d53b8d20e3fb26b8443897b39af8.o
    { "Gouraud_Skin", 2, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::D3DColor, Shader::Color0 }, { Shader::UByte4, Shader::BlendIndices }, { Shader::Float3, Shader::BlendWeight } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 12, 512 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_STREAM_SOURCE_SKINNED, { 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 12, 512 } },
    { NOP_1, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { NOP_1, { 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 1, 0x340002, 2, 0x3D0002, 3, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexSkinData,
    Shader::EAGLAnimationBuffer,
    Shader::ModelViewProjectionMatrix,
    { Shader::RuntimeGeoPrimState, ";SetTextureEnable=false" },
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // IrradLitTexture2Alpha2x_Skin, hash 3319798473
    // in files (20): 16a5c4cd5956623367249a641df9f331.o, 20510f39de37c88abaf7c7b4bb2da7af.o, 340e0167b39b8e62df5e5007501a99b0.o, 6f3216dd1f4c20110ec1e85041dcde7a.o, 75cebdd5fcf14fbe524a9af59fefddb3.o, 932e7651b1585728a5b14e1272d3aecc.o, ac449bf1f713c8396fca94278414bcdd.o, c68d555752dff2956d6765f2b2284e82.o, c8389d93e994f895be15a0ca5d7c31e5.o, fc49c502bae507cdaf628227c37f9b93.o
    { "IrradLitTexture2Alpha2x_Skin", 7, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 }, { Shader::Float2, Shader::Texcoord1 }, { Shader::UByte4, Shader::BlendIndices }, { Shader::Float3, Shader::BlendWeight } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_SAMPLER, { 1, Shader::Sampler1Size } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 16, 40 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 26, 28 } },
    { SET_VERTEX_SHADER_CONSTANT_L_30, { 33, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 34, 4 } },
    { SET_STREAM_SOURCE_SKINNED, { 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 6 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_SAMPLER, { 1, Shader::Sampler1Size } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 40 } },
    { NOP_1, { 26, 28 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 34, 4 } },
    { NOP_1, { 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 12, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_SAMPLER, { 1, Shader::Sampler1Size } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 40 } },
    { NOP_1, { 26, 28 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 34, 4 } },
    { NOP_1, { 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x440001, 0x4000B, 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 15, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 12, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_SAMPLER, { 1, Shader::Sampler1Size } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 40 } },
    { NOP_1, { 26, 28 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 34, 4 } },
    { NOP_1, { 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x440001, 0x440001, 0x4000B, 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 15, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 12, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_SAMPLER, { 1, Shader::Sampler1Size } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 40 } },
    { NOP_1, { 26, 28 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 34, 4 } },
    { NOP_1, { 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 12, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_SAMPLER, { 1, Shader::Sampler1Size } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 40 } },
    { NOP_1, { 26, 28 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 34, 4 } },
    { NOP_1, { 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 12, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_SAMPLER, { 1, Shader::Sampler1Size } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 40 } },
    { NOP_1, { 26, 28 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 34, 4 } },
    { NOP_1, { 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 48, 598, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 12, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    Shader::GeoPrimState,
    Shader::Sampler0, // global
    Shader::Sampler1, // global
    Shader::ComputationIndex,
    Shader::VertexSkinData,
    Shader::EAGLAnimationBuffer,
    Shader::ModelViewProjectionMatrix,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::IrradLight,
    Shader::Light,
    Shader::ZeroOneTwoThreeLocal,
    Shader::FogParameters,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // IrradLitTexture2x, hash 1841355404
    // in files (89): 1b74a8439ab109bd456929214b8e877c.o, 1e81730284efcb850eb34cd91d45ed11.o, 20976039bb27f256b40cefb7b84aa217.o, 2e571717354e4c85b3a23c4b97cb64a4.o, 31b273ee2372fa9d7326acbdcb6f606b.o, 370b61435819b03432938afcc60804c0.o, 3a319494dc696a073dfc61a495783d97.o, 3b452accc4169636d9b2aee6d3f2d187.o, 3f7f7b16d027fdef0f6c7b56e2e88862.o, 4a7121a9eea54d566f4bda21077df2ba.o, 5224a7fec7d0cad5e3d0c05af19cbde8.o, 55d3f55258f74253e46d6eb3fff58e0f.o, 650b306a7f37ec925ea6561b659957b5.o, 67901b65549c139ff881467fc6332d28.o, 71fe5eadc0072837d7d3b86b05b11265.o, 72a02caea4ea74417ded4e1ec5fc77e0.o, 7e0869d08d6cea954aebb48ca82b5329.o, 80c328a13e21fa32462cd0877d8e4337.o, 88888157dcddeea555c85ea1438e1947.o, 89ceadce6b6a53317b1189d326bb2272.o, 8b57de93f39d71f2d0aa73e533c4d753.o, a009be0d5ec2052b1541b32f2ea9d4c5.o, a063b61b24f7ddfb5a028b0d0b47bfa8.o, a115b1ddebd80a0043c35412626511ab.o, c6f2b6db5d29b17ca7337017d5cdbfb4.o, cb208016ff705391b48c5064bb4f7fac.o, efb5b3a48b716b9a8131f737ddbb6402.o, f102e0710a9feb98dc8c05c42c8c1baa.o, f8cb26dd31624527052945b735725e0c.o
    { "IrradLitTexture2x", 3, { { Shader::Float3, Shader::Position }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 16, 40 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 26, 28 } },
    { SET_VERTEX_SHADER_CONSTANT_L_30, { 33, 4 } },
    { SET_STREAM_SOURCE, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 4 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 40 } },
    { NOP_1, { 26, 28 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 10, 0x330002, 4, 0x340002, 5, 0x3D0002, 6, 0x320003, 8, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 40 } },
    { NOP_1, { 26, 28 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 10, 0x330002, 4, 0x340002, 5, 0x3D0002, 6, 0x320003, 8, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::RuntimeGeoPrimState,
    Shader::Sampler0, // global
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::IrradLight,
    Shader::Light,
    Shader::ZeroOneTwoThreeLocal,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // IrradLitTexture2x_Skin, hash 2251647568
    // in files (1511): 0de21fc3d60ff55f1f9aeac2f18b9ad1.o, 1098d96f42739778e4848a3cdf7c6237.o, 16a5c4cd5956623367249a641df9f331.o, 196542472f39946a01c0b2371bfc1d6e.o, 1a82af68a5f77cda61f1d9fccfc6d13d.o, 1c405d960585065f4afdc6f067834b2e.o, 1e579f36589c25882d403ff4707cc46e.o, 20510f39de37c88abaf7c7b4bb2da7af.o, 2ab4ab34d06f76c02090ce78e69e65cd.o, 2f488970b885f8a0ecbcdda3f042e158.o, 325d7e1a3b84c0c7ee3d8695d5484cdd.o, 340e0167b39b8e62df5e5007501a99b0.o, 37063a6c45de3853592ae1d4942c7644.o, 3d36803f9151572292370d123f5d85cd.o, 3e4acac300d199b0cc0a1cd0d996b000.o, 4669bf20312c366bd7cf672c378b4511.o, 472c9633fcba127a17658a94bc406ddf.o, 473f13bd660b9d1bd1bf2954a9da3ace.o, 4a388ff1c5e0bfb5a6933423949befd9.o, 4b7d7addabd5af3e4a2610e7b4371bac.o, 4ed1e02e707db9336d784276f3894eb3.o, 5872f6f36dcfa4de6d5073a0dd22b871.o, 59a3aed119f2146e7a2b64d589ca7068.o, 59af6741af642a935b37cfab57164712.o, 6215ffa0d052e59b0f8f26c7c3228cbb.o, 6f3216dd1f4c20110ec1e85041dcde7a.o, 75cebdd5fcf14fbe524a9af59fefddb3.o, 84b6c3d943c703ab2de439853b1b9839.o, 932e7651b1585728a5b14e1272d3aecc.o, 9373541fcf1f13e325e559409eff066e.o, a1e3221c5b5c1fcc27b5e4a9f2c238c9.o, a3c663d290af5889efda88134efaf790.o, ac449bf1f713c8396fca94278414bcdd.o, b640792aea463c39819162eef402edba.o, b8eced6654d73f5582af8740a8e7380e.o, bee61b5353aeca84837d5d5f97b2a2cc.o, bf9f914dbed358a979657553ad785e5b.o, c5c2f42624531fe79c6dbf244f2f12ef.o, c68d555752dff2956d6765f2b2284e82.o, c8389d93e994f895be15a0ca5d7c31e5.o, ccbe9d28b016ce2084cdd9b945634fcb.o, cf2c9c2048db05b07acbc9ef72ce2bcf.o, dd0174f8746ec7248ff591ed72a18e47.o, e6668dd5a45ebbc1f286ed04fe45e14a.o, f0f8a6f38197f294f8dd8aa03461b0e3.o, f86493d3189b2fc632d1431e62421e23.o, fc49c502bae507cdaf628227c37f9b93.o, fece0969877e57d947c0ff775e9d2e74.o, hhead.o, lhead.o, mhead.o
    { "IrradLitTexture2x_Skin", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 }, { Shader::UByte4, Shader::BlendIndices }, { Shader::Float3, Shader::BlendWeight } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER_G, { 0, Shader::Sampler0Size } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 4, 40 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 14, 28 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 21 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 25 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 29 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 33, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 34, 4 } },
    { SET_STREAM_SOURCE_SKINNED, { 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 5 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER_G, { 0, Shader::Sampler0Size } },
    { NOP_1, {  } },
    { NOP_1, { 4, 40 } },
    { NOP_1, { 14, 28 } },
    { NOP_1, { 21 } },
    { NOP_1, { 25 } },
    { NOP_1, { 29 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 34, 4 } },
    { NOP_1, { 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 9, 0x340002, 10, 0x3D0002, 11, 0x320003, 8, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER_G, { 0, Shader::Sampler0Size } },
    { NOP_1, {  } },
    { NOP_1, { 4, 40 } },
    { NOP_1, { 14, 28 } },
    { NOP_1, { 21 } },
    { NOP_1, { 25 } },
    { NOP_1, { 29 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 34, 4 } },
    { NOP_1, { 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 9, 0x340002, 10, 0x3D0002, 11, 0x320003, 8, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    Shader::VertexSkinData,
    Shader::EAGLAnimationBuffer,
    Shader::ModelViewProjectionMatrix,
    Shader::GeoPrimState,
    Shader::Sampler0, // global
    Shader::ComputationIndex,
    Shader::IrradLight,
    Shader::Light,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::ZeroOneTwoThree,
    Shader::FogParameters,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // IrradLitTexture_Skin, hash 793066988
    // in files (2): 3af3bb6f7eefef1c28d630e885e7f284.o
    { "IrradLitTexture_Skin", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 }, { Shader::UByte4, Shader::BlendIndices }, { Shader::Float3, Shader::BlendWeight } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 4, 40 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 14, 28 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 21 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 25 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 29 } },
    { SET_VERTEX_SHADER_CONSTANT_L_30, { 33, 4 } },
    { SET_STREAM_SOURCE_SKINNED, { 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 5 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4, 40 } },
    { NOP_1, { 14, 28 } },
    { NOP_1, { 21 } },
    { NOP_1, { 25 } },
    { NOP_1, { 29 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 7, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4, 40 } },
    { NOP_1, { 14, 28 } },
    { NOP_1, { 21 } },
    { NOP_1, { 25 } },
    { NOP_1, { 29 } },
    { NOP_1, { 33, 4 } },
    { NOP_1, { 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 7, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    Shader::VertexSkinData,
    Shader::EAGLAnimationBuffer,
    Shader::ModelViewProjectionMatrix,
    Shader::RuntimeGeoPrimState,
    Shader::Sampler0, // global
    Shader::IrradLight,
    Shader::Light,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::ZeroOneTwoThreeLocal,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // LitGouraud, hash 3300873351
    // in files (9): 1b74a8439ab109bd456929214b8e877c.o, 23a19dc9d2a0b2ff189546e8366aa1c6.o, 6386443e375a67baf92fd0e62ea2d9bb.o, 650b306a7f37ec925ea6561b659957b5.o, 705425a575c4c47c3d82b4a90d460711.o, 8b43c468388ceff228ec61fc8b96fa51.o, c6f2b6db5d29b17ca7337017d5cdbfb4.o
    { "LitGouraud", 2, { { Shader::Float3, Shader::Position }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 16, 28 } },
    { SET_VERTEX_SHADER_CONSTANT_L_30, { 23, 4 } },
    { SET_STREAM_SOURCE, { 0, 28, 82, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 28 } },
    { NOP_1, { 23, 4 } },
    { NOP_1, { 0, 28, 82, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 28, 82, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 3, 0x340002, 4, 0x3D0002, 5, 0x320003, 6, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    { Shader::RuntimeGeoPrimState, ";SetTextureEnable=false" },
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::Light,
    Shader::ZeroOneTwoThreeLocal,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // LitGouraud_Skin, hash 2034225020
    // in files (19): 16a5c4cd5956623367249a641df9f331.o, 3d36803f9151572292370d123f5d85cd.o, 4669bf20312c366bd7cf672c378b4511.o, 4a388ff1c5e0bfb5a6933423949befd9.o, 6215ffa0d052e59b0f8f26c7c3228cbb.o, 75cebdd5fcf14fbe524a9af59fefddb3.o, 932e7651b1585728a5b14e1272d3aecc.o, ac449bf1f713c8396fca94278414bcdd.o, c68d555752dff2956d6765f2b2284e82.o
    { "LitGouraud_Skin", 2, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::UByte4, Shader::BlendIndices }, { Shader::Float3, Shader::BlendWeight } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 16, 28 } },
    { SET_VERTEX_SHADER_CONSTANT_L_30, { 23, 4 } },
    { SET_STREAM_SOURCE_SKINNED, { 0, 32, 86, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 4 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 16, 28 } },
    { NOP_1, { 23, 4 } },
    { NOP_1, { 0, 32, 86, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 32, 86, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x320003, 8, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    { Shader::RuntimeGeoPrimState, ";SetTextureEnable=false" },
    Shader::VertexSkinData,
    Shader::EAGLAnimationBuffer,
    Shader::ModelViewProjectionMatrix,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::Light,
    Shader::ZeroOneTwoThreeLocal,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // LitTexture, hash 742550785
    // in files (2): 44b859645e27003c6c8d622903fbcd98.o, 65f1fa0687f2bd5d5ac9740af8720359.o
    { "LitTexture", 6, { { Shader::Float3, Shader::Position }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 16, 28 } },
    { SET_VERTEX_SHADER_CONSTANT_L_30, { 23, 4 } },
    { SET_STREAM_SOURCE, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 4 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 16, 28 } },
    { NOP_1, { 23, 4 } },
    { NOP_1, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 9, 0x330002, 2, 0x340002, 3, 0x3D0002, 4, 0x320003, 7, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 16, 28 } },
    { NOP_1, { 23, 4 } },
    { NOP_1, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 9, 0x330002, 2, 0x340002, 3, 0x3D0002, 4, 0x320003, 7, 1, 0x440001 } },

    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 16, 28 } },
    { SET_VERTEX_SHADER_CONSTANT_L_30, { 23, 4 } },
    { SET_STREAM_SOURCE, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 4 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 16, 28 } },
    { NOP_1, { 23, 4 } },
    { NOP_1, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 9, 0x330002, 2, 0x340002, 3, 0x3D0002, 4, 0x320003, 7, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 16, 28 } },
    { NOP_1, { 23, 4 } },
    { NOP_1, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 9, 0x330002, 2, 0x340002, 3, 0x3D0002, 4, 0x320003, 7, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::RuntimeGeoPrimState,
    Shader::Sampler0, // global
    Shader::Light,
    Shader::ZeroOneTwoThreeLocal,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // Texture, hash 2902309007
    // in files (15524): 0050f7a2d082a2aab30ef2af43335d97.o, 01c092a62903fbccab8b12b289dbaa77.o, 04272f7672b68a2a0b935dd683d6a492.o, 05a2b9326ce02dcaf0f91c6f40e05189.o, 08cd2f3c96533a02fee50ed8a0fbfba8.o, 08d89df82858b64a8e605c96f8e289b6.o, 091c9de8ceddbef72c90ff0f9c58bfb4.o, 0a9744aca65f8c6aeb611101fd0288e0.o, 0a98ab0ba6033e53b95b16c0d033c11b.o, 0aa7625fe46ab033098c92efa5037c2d.o, 0bad575f84a1ae52add919854280a36f.o, 0e0e536741c7e92aa815305846cc6f0e.o, 0e1b5c6716d7b6ebda1c4e425715aa21.o, 0e816634c4cbd532b2bac1f9b3865bea.o, 0e9ded192175d96d62b6ce8402371c68.o, 0ec7e87624072e836d393f6d8ab060ed.o, 0ed0776739b5ade4ba5c3e49b029fee4.o, 0ef3917aa5c83b554a559b533d163721.o, 103b591d4ea04c0a8e4b837a6887eae5.o, 108026fd4465697c0df4b500302bd6f2.o, 1117ddaf70ce3d63526d2e8f26c204f4.o, 130d2c27f32be65997102bed086b6d01.o, 15bebfd7572ee6f7ebb9c175d94fd785.o, 16957fe27d829888c8ccf6c63f40b781.o, 16f3dc0f28da4981af2244ae38526417.o, 17222b3ccf80675e9456f19d3508b70b.o, 1a30a1913ecab9d6faca52e04cf099ea.o, 1ab3836594b141ce3dc5ae09f9367e62.o, 1b1f014b34ba080afe44e861a4a870d9.o, 1c7feaefa6e98938c2649ea3b1002fdd.o, 1db28a757b1ce77d9d4c401fb7c87f95.o, 20dc9d22d54cbc68f2338dd74aff427d.o, 2120919292c0dbeced2980387d82144a.o, 215ce03b964770625695f9be8e777c6e.o, 2282f2b580512142f992182ba9d47b83.o, 262c9981843682a80c8c8ce952691d10.o, 2843fb22fdfeae8770ecc882d1aae163.o, 2b8c8c67f7f3f6725c481b516bbfe59e.o, 2ea6bd99317b3b3256f809ff85a2789c.o, 2f246663e61d9a82f73b5f41d2df02e5.o, 2fef5d418ce2ac5a9d52621196f7cfd3.o, 31a766fb434e213c9d9711e801475008.o, 32d243dd4a2af466c7ebac2d68c802df.o, 3388a3270b79d729788d3665962a241d.o, 354024324a4356a446bb453975a742f0.o, 354b8841ca0d0ed9eff8fba3a4229dbd.o, 356e92034e5b6515bb448f413a192291.o, 3628a74b1a9403c67b4bfad2dd9799d2.o, 36496f06d4fbdcd2dbb85c3e1755d388.o, 37bd77836fbb05fd8cf356f0e8390e4e.o, 38d4922e012b02279d5611932fbec2f8.o, 3927aa6c700ec139b30fc3e8b05dfcab.o, 3a3a547765ae4a06c66bd5071f9f8932.o, 3c763a9d43c0a5db662671a6f8c8fa91.o, 3d9da7adb90e461a2ea778b524faadc2.o, 3e92ce6d556d2c2948133e3167e7dc36.o, 3f94ea4c52e59657d7276fea72b5240f.o, 4048508db9972b102b915431bc66c126.o, 40c3d7fbaf0045602fb40e3f93b65dc8.o, 41cc1bcfd00e59f39081a556dcfaae77.o, 44cf9c918cfdc5fc532bdb30e8406e62.o, 457f6148656a58ff513a75bd3664360b.o, 479f0249e8eacca319a135d8827f3ec5.o, 47d34007ec0dd74d7e2df07f9ca9bbbb.o, 4896c4feb90313e4b103cf13a9fb1c2d.o, 49d52ed1ddc9ad8fa762f76ea9aaa7ce.o, 4a056e3582de2ce050c6d95b9366c846.o, 4a381877dfb05e1dbe9f65ac23791967.o, 4be8e8d9a83b5609460bec25090b02e1.o, 4d22ee48c53bf16017368bb51a432b20.o, 4df052106ccc1ec6844bd8b0f16b0554.o, 4e521d2dd1f713f984b55a55c6fb28d2.o, 4facd78a0a3e64779415693436fb3fd1.o, 504a6bcb0f40164f02a791445fd4f6c5.o, 50e0d5f227097d87dd670695bdc7f944.o, 52bc0755888a351fee231ea5db8726fc.o, 551b6c6642311d3109ae2c9f5816d4a7.o, 55c4cf0923a51aa22724e634284d9bd3.o, 57cebcdcf1e59da7977c42da20e33dd6.o, 5ae3a9fb66c3b63a7c6f2ec2411928da.o, 5b6ced468e9697cfdaa402be95dc1dc0.o, 5bb924bda512f7cdd8cbfc9ea4cfdf30.o, 5beb64c2c6af56f475bc61cad19a72bb.o, 5c6d19c639ef995b4f62df118456cac1.o, 5c861ae7ff64800b28e9f35915463e90.o, 5dd394bd0bca05a17b4ae896c755f768.o, 615a7a3575413d72d786ca4ae7e29dc6.o, 61ba5626a37269f7e3947df3d917b516.o, 61c725e9b412ffc528898593c21d9c7f.o, 61f652a9b42c757570dec8fef10b5be6.o, 6467cc439e3836350602ed707159bf41.o, 64cfc25fe971cb66fa65dede732d17c9.o, 64f988243ff25cd79a1db3f53dfc3c34.o, 651a904195e3ab3303599b02b32f756e.o, 65f543457a72920c9fdad2cb057b662f.o, 663572c72f3dd3e1c46e24afd75aabc0.o, 66402c4bf05b0963646d5f8b5689387f.o, 6874b5f774e5273333c7acfd138300f9.o, 68783e9de58d07a11c43fa24cd761ba7.o, 69680536d9231acb4422f96687e12bcc.o, 69f21674a31762ad5ce45e7e7fcaaa18.o, 6a370c10b698244a2cb2162cdfe8f061.o, 6a78e6611b2c194cd00e21f3ca0f9fdd.o, 6b7ba35f87c91253351a5b97f6ce18c2.o, 6cdbd37983debfeadbb1113888f409b8.o, 6d1471ebcfc1bbd6f46dbd23a14c50b0.o, 6e1934001a1b7238a9075dfda486bfcd.o, 705f631360ef140e051925544d19c435.o, 71114df1f78b60cf09c66d2eaf6689d3.o, 722e0c95fe2418de4402613c1eb21aab.o, 72dae0a30b4cf8c84189697df27dd08b.o, 74f15e9ad3ec75878fbb4690ad83cdf8.o, 75fc3b30d434410b178c0f6a7aeaf7a9.o, 7684da8aaa11454a6c52fd1c156a2c5f.o, 76a9fba49d5cc60003d40c6d651331b4.o, 76ba6c49e2b778967bbc3cebf190f627.o, 78130968d6c01f95bc703f7f72ee9085.o, 798aaed7c5ed306b2dcaf9f369a1cd88.o, 7c7ea009f760516af64c2e2bcbbda972.o, 7d438d77d3a2385c4f47cd17d3623d75.o, 7f0d7ff60ec2bd2f9f222b641da16170.o, 7facb3dd0baed6fed45e1834133c0c92.o, 7fb8bf4e7cded27f6864fcce6e3ff40a.o, 8032cd2b273200348adbc4fc40f95725.o, 848fe00f9b64f62be418785d85c29451.o, 85ec444563b53511888979334220be9f.o, 8777057abe7a213a45969eda36fb2fc6.o, 8814ef63622eec76472a5fb5c80f0295.o, 885fcb0ba7b981b70b42352877ef0964.o, 8962ffb19f6241776d8a2000bf648e41.o, 9084e6450cb0cefe2741ff4abf595578.o, 91a7b09b734a0abfc6973cdca6b71317.o, 92218cf862a4de9ec5fe7dfd7f28f70a.o, 926a8150608942d812fc584dccfd3e09.o, 95af228001e8d634c8490965b0636ff7.o, 9681e0cc950378b7beb39b0cfea19af0.o, 97562081b15151f2870660c8b132ab6d.o, 981cbe96f212851ecaf3fe713c13089d.o, 9d8415987df1b81100c8a8429f474b2f.o, 9e029f24a6cfc3348a113b9a954b76f5.o, 9e385f107b0edf846f3d4dfa3c50c1b3.o, 9f4daf4a3aecf2d7a20a14628568c02e.o, a0609e702c060e91409e9bba62ee85a4.o, a179876d12e063846dc89a745247dbd6.o, a36f6e0e93da17b88cfe7e7dc09be48a.o, a5aa36e9abbeaf0397249dbd9b134d1b.o, a7c3f27a89e91dddfe6cac69f5066b21.o, a97559359e2491030299ddb5ecf77bd2.o, a9ad77811640f2d0ad27183850819c57.o, aca20752aa62e630719facde508c160b.o, ace4a7eee301aa7f200260c53ddcdeed.o, ad921f986059f6fbc6e1f7164087024d.o, adc0637506b96dd2ad0a17ca7925e2c3.o, aec2c602d87093a0cb9805de52ad5fe4.o, af6089e34ace00ef3aa2940f952cb47f.o, b00acdc353d8ba1e6c3df7150487163c.o, b11b49e37af4f21e0b759849175f44db.o, b25a745b3978d3cda1355d25a078cd59.o, b30b7fe6ff085336a9d7235fd7481655.o, b3b93af030a7629df2ac0aa84ecc3c46.o, b4c1690c2e39b3a8d3f3a12aa29dca02.o, b567d2961349494932b46d5749c066ea.o, ba8aeb7caaaa832ab9d4e96b8ec9dc71.o, bc47d6ac81e1e8f7279f3d823da219b0.o, bed66e6bda03bde6ebf9f500a87efc1a.o, c39086f82d4028a9d9922d84f06fb26d.o, c3cfa5d1c12aaa0c8a7b52733d04c19e.o, c4bfa7c98cfc7f44ddfc1b052d2a55cb.o, c50744028d7e36f4063b9d3340420317.o, c516d7bc5ec57b64658763646b49f87d.o, c5908d1f2e1d66a2d76b0e9c54cd8ab1.o, c64e916b9486bd1417e9195d8057ea3d.o, c6ea00150f94c53e1659a75938d85a6a.o, c76a1f455c452b9507fc1a5c3fbf0e13.o, c7c48a55a8d8f0cd39267bd15dbe14ab.o, c93a5ad3aca63f2b567ab417e1da7e4b.o, ca49106b8d950b42650c39c38bc2389a.o, cbca624c0ad762bb515b23be3e78c522.o, cd9367447cb9a822ce6a2f3de8579103.o, ce136bf112b7c4e5dd4b7eee015d7079.o, d104a9cf0d22d700fcf7b93c78931b5e.o, d38994b1618ef1e514ebd039538a8b42.o, d5d9d631a21eea6795f32f69a3c258eb.o, d6f101396bc2ede4a5b49639a2cda555.o, d8ff28e94821a006852a58655f2eed74.o, d9ce55754ec897a2d233b5a01eaa40f4.o, dab3cba7ff94c425c65d2f8da2ee008f.o, dbfa9e0e9638c69ff9044db692159547.o, dcf793a4fea7f820c0da34d9423d7e95.o, dd64055a9cdcbaa4dcf2dd741d46efe3.o, ddf5a64731661d63aa58f48d6bc2525d.o, de14e546fab81224bd8dbe46a59430c5.o, de22862babb11689ec143c1590c77152.o, de796cc2da978f0bfcbc591034768d51.o, df4f8258176bec0d3003b7dbbbdb73d3.o, e07f55adc4b302c6fd1ae8fd4b8a1e48.o, e101025639bdf5c5e0dfa4c19523b1f7.o, e2b6976250911b6a4d0e4e2aefd49cbc.o, e380feff0a6e6354f8cf384427070909.o, e47fcd896877132f8aa5fafaa657407d.o, e5f664ca8070e10b0e0ec5ebbefb39b4.o, e62d006a2d36ec5fe8e3456c8b74871f.o, e63976b010c87786f78417f5b206b1ee.o, e779ab09bd4ad804502d03e30bb9aef5.o, e8d1befe7e91ec87ff84fee41b28d186.o, ea696fd300b51b2bf566fde5f3e61ce0.o, eb36383bb803dc70e7d4f14c07288a1b.o, ec391732d8a8d385a248c8328ad16665.o, ec44ef1cd57ad75eb4f9ecb3e3f02c58.o, ed0436cb28032ff78c9f4450303d84fb.o, ed3ca2aed0c1ff1944bc380fda92bc7d.o, ed54c1d1792271215e14031b4b31569d.o, eecc593609522e6f85af833b35e3eebd.o, f29b3dc052b65bb90b5527886b3ec8bb.o, f4762582c5c9b70e4767398514e0a6e9.o, f5f631aa46c4b9abef1b3460035705e8.o, f75473684869544fa1caada607365388.o, f80cc8907a67989fcae14aa9f1599c35.o, f87c28d749de6a90bbc3e3d693b2a5b3.o, f90d349b1096e2775a6e0ce398c958a7.o, f96213ebaf8bdf8e920679b4da2392b4.o, fab2163dce33ced0c9b269023108b605.o, fc0d6c1a265ce590af5104c98c84e823.o, fc144610a5552e6398ecbb4dc3625d08.o, fccc16d5158e82214532c08747a1299c.o, fe3b4fbca79dc4be6faf837ad2beb673.o, fe4fbbaf7473b12a95d63d9daa69ad65.o
    { "Texture", 6, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 7, 0x330002, 4, 0x340002, 5, 0x3D0002, 6, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 7, 0x330002, 4, 0x340002, 5, 0x3D0002, 6, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 8 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 12 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 7, 0x330002, 4, 0x340002, 5, 0x3D0002, 6, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4 } },
    { NOP_1, { 8 } },
    { NOP_1, { 12 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 7, 0x330002, 4, 0x340002, 5, 0x3D0002, 6, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::RuntimeGeoPrimState,
    Shader::Sampler0, // global
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    }
};

char const *TargetCRICKET2005::Name() {
    return "CRICKET2005";
}

int TargetCRICKET2005::Version() {
    return 4;
}

unsigned short TargetCRICKET2005::AnimVersion() {
    return 0x0181;
}

Shader *TargetCRICKET2005::Shaders() {
    return shaders_CRICKET2005;
}

unsigned int TargetCRICKET2005::NumShaders() {
    return std::size(shaders_CRICKET2005);
}

Shader *TargetCRICKET2005::DecideShader(MaterialProperties const &properties) {
    if (!properties.isSkinned) {
        if (properties.isTextured) {
            if (properties.isLit && !properties.isUnlit)
                return FindShader("IrradLitTexture2x");
            else
                return FindShader("Texture");
        }
        else {
            if (properties.isLit && !properties.isUnlit)
                return FindShader("LitGouraud");
            else
                return FindShader("Gouraud");
        }
    }
    else {
        if (properties.isTextured) {
            if (properties.numUVs > 1)
                return FindShader("IrradLitTexture2Alpha2x_Skin");
            else
                return FindShader("IrradLitTexture2x_Skin");
        }
        else {
            if (properties.isLit && !properties.isUnlit)
                return FindShader("LitGouraud_Skin");
            else
                return FindShader("Gouraud_Skin");
        }
    }
}
