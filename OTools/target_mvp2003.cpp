#include "target.h"

// local public samplers: "0001", "0309", "0326", "0330", "0335", "0339", "0345", "0353", "0355", "0361", "0365", "0368", "0370", "0380", "0382", "0385", "0390", "0399", "0400", "0401", "0404", "0405", "0421", "0434", "0tr1", "1boa", "1fra", "1pot", "1tre", "2fra", "2pot", "2sdu", "2sea", "2tre", "2wbo", "302n", "310n", "327a", "330a", "3380", "343a", "372a", "379n", "380n", "3960", "3bar", "3gre", "3pot", "3tre", "402a", "408a", "4100", "420n", "4dug", "4gre", "4pot", "9out", "9tre", "a780", "abg1", "ad00", "ad01", "ad03", "ad08", "ad09", "ad10", "ad11", "ad17", "add4", "add8", "adpc", "adpe", "ads1", "ads2", "ads3", "ads6", "ads8", "adtr", "adug", "adz4", "adzu", "alkh", "amlo", "an01", "an03", "anhm", "aple", "arb1", "arb2", "arbs", "arce", "arch", "astr", "asun", "at01", "badm", "bafz", "bak1", "bak2", "bak3", "bak4", "bakm", "bakn", "ball", "balt", "ban2", "ban4", "bar2", "bark", "barl", "barm", "barr", "bas5", "batl", "batt", "bbag", "bd01", "bd02", "bd03", "bd04", "bd05", "bd06", "bd07", "bd08", "bd09", "bd11", "bd12", "bd13", "bd14", "bd15", "bd16", "bd17", "bd32", "bd97", "bd98", "bd99", "bd9a", "bdg2", "bdn2", "bdpp", "beam", "bell", "benc", "benn", "ber3", "berg", "bern", "bg00", "bg01", "bg02", "bg03", "bg04", "bg05", "bg08", "bg09", "bg10", "bg13", "bg15", "bg16", "bg17", "bg18", "bg19", "bg22", "bga6", "bgb7", "bghk", "bgsk", "bgsm", "bi2n", "bi3n", "bi4n", "bil5", "bkb2", "bkg3", "bkgn", "bkgr", "bkn8", "bkw3", "bkw4", "bkw8", "blak", "blda", "blni", "blnk", "blue", "bn03", "bn05", "bn06", "bn07", "bn08", "bn09", "bn10", "bn13", "bord", "boto", "bots", "bpan", "bpbl", "brav", "brds", "brid", "brk2", "brka", "brli", "btod", "btop", "bui1", "bui2", "bul2", "bush", "buve", "bwl1", "bx01", "bx02", "bx05", "c001", "c002", "cab2", "cab4", "cab5", "cab7", "cab8", "cabi", "cama", "can2", "can4", "casp", "cavn", "cavt", "cc02", "cc03", "cc04", "cc05", "cc10", "ce01", "ce02", "ce03", "ce13", "ce4m", "cebx", "ceff", "cel1", "cel2", "cel4", "cel5", "cela", "celb", "celc", "celd", "celg", "cell", "cem0", "cem1", "cem2", "cem3", "cem4", "cem5", "cem6", "cem7", "cem8", "cem9", "cema", "cemb", "cemc", "cemd", "ceme", "cemf", "cemh", "cemi", "cemm", "cemn", "cemp", "cemv", "cemw", "cemx", "cemy", "cemz", "cen2", "cenn", "chad", "chev", "chk2", "chkb", "chlk", "cie4", "cime", "cl01", "cl02", "cl03", "cl04", "cl05", "cl06", "clb1", "clb2", "clb3", "clev", "cn01", "cnc1", "co01", "cobs", "coin", "cok2", "colo", "con1", "con2", "con3", "con4", "con7", "conc", "conk", "conq", "corn", "crbd", "crbn", "crl1", "dayd", "dbak", "dess", "dg01", "dg02", "dg03", "dg04", "dg05", "dg08", "dg10", "dg12", "dg13", "dg17", "dg19", "dir1", "dir2", "dirs", "dirt", "dist", "dits", "dlig", "dout", "dr02", "drlr", "drpq", "drzw", "dstr", "dtop", "duff", "dug0", "dug1", "dug2", "dug3", "dug4", "dug5", "dug6", "dug7", "dug8", "dug9", "duga", "dugb", "dugc", "dugd", "duge", "dugf", "dugg", "dugh", "dugi", "dugl", "dugn", "dugo", "dugp", "dugw", "dugx", "dun1", "dun2", "dun3", "dunb", "dune", "duni", "ea01", "exit", "expp", "ext2", "face", "fand", "fd01", "fd02", "fd11", "fd14", "fd27", "fd28", "fd29", "fd30", "fda1", "fda2", "fda3", "fda4", "fea1", "feet", "fena", "fenb", "fenc", "fila", "flag", "flgp", "flod", "floh", "flor", "flos", "flp2", "flp3", "flr1", "fmb1", "fnc0", "fole", "fond", "fotb", "foul", "fral", "fram", "frem", "fres", "frg2", "frg3", "frgr", "frim", "from", "fron", "frum", "ful1", "fus1", "g111", "gab2", "gab4", "gab7", "genw", "gepp", "gexi", "gl01", "glas", "glo1", "glo2", "glo3", "glo4", "glo7", "glof", "gloo", "glow", "gloy", "glpg", "gls1", "gls2", "glwb", "gotr", "gr01", "gr04", "gr05", "gra0", "gra1", "gra2", "gra3", "gra4", "gra5", "gra6", "gra7", "gra8", "gra9", "gras", "gray", "grd4", "gree", "gril", "grin", "grnd", "grs1", "grs2", "grwl", "grww", "haut", "hbak", "hdug", "heli", "hflo", "hiro", "hom0", "home", "hots", "hplt", "hr01", "hr02", "hr03", "hr04", "hrw1", "inda", "jaco", "jmbo", "jmfr", "jum2", "kans", "kanz", "kwbl", "kwl0", "kwl1", "kwl2", "kwl3", "kwl4", "kwl5", "kwl6", "kwl7", "kwl8", "kwl9", "kwlc", "kwlh", "kwll", "kwlm", "lamp", "larc", "lbbu", "lcon", "leaf", "left", "lemo", "lflo", "lgre", "ligp", "lin1", "line", "lip1", "lip3", "lit0", "lit1", "lit2", "lit4", "lita", "litb", "lmse", "lmsn", "lod1", "lod2", "lodd", "lodn", "lone", "long", "lrof", "lroo", "lt01", "ly38", "m_04", "m_06", "m_07", "mark", "mb01", "mccc", "mcvv", "mini", "mlb1", "mlbx", "mmpk", "mo4a", "mout", "mrk1", "mrk2", "msc1", "msc2", "msc3", "msc4", "msc5", "msc7", "msc8", "msca", "mscb", "mscc", "mscd", "msce", "mscf", "mscg", "msci", "msck", "mscm", "msct", "mscv", "mscz", "msea", "msnt", "mssv", "muet", "mur2", "murl", "n326", "n362", "n373", "n435", "nera", "nete", "newg", "nflg", "nibd", "nigh", "nigt", "niid", "nitd", "nite", "nm99", "nnci", "nobo", "num1", "num2", "nyyk", "orio", "pad1", "pad2", "pad3", "pad4", "pad5", "pada", "padd", "padr", "pan1", "pan2", "pan3", "park", "pasa", "pass", "pdw2", "pdw3", "peps", "pgs4", "pgs5", "phil", "phot", "pil1", "pil2", "pil3", "pil4", "pile", "pilo", "pipe", "pira", "pirr", "pl01", "pod1", "pole", "porc", "port", "post", "poto", "pou1", "pou2", "pout", "pqws", "pres", "prn1", "prs1", "prs2", "psoo", "q1b1", "q1b3", "q2b1", "q2ba", "q3b2", "q3b3", "raaf", "rail", "rcn1", "rcsn", "rdtm", "red1", "red2", "reds", "reed", "rema", "rf01", "rf02", "rf03", "rf11", "rf22", "rf33", "rftp", "rim1", "rim2", "rim3", "rim4", "rll0", "road", "robi", "roc5", "rock", "rof1", "rofa", "rofd", "roll", "roof", "rouf", "royy", "rshk", "ru01", "rubs", "rufi", "ruuf", "saac", "sb00", "sb01", "sb02", "sb03", "sb04", "sb09", "sb10", "sb17", "sb7b", "sc01", "scar", "sco2", "scor", "scr1", "scr3", "scr5", "scri", "scrz", "sea1", "sea3", "seat", "set1", "set2", "set3", "set4", "set6", "sett", "sfra", "sglo", "sha2", "sha3", "shad", "shae", "sher", "side", "sign", "sit2", "skcd", "sko2", "sky0", "sky1", "sky2", "sky3", "sky8", "skyd", "skye", "skyl", "skyn", "skyt", "skyx", "skyy", "sn00", "sn02", "sold", "soxl", "spea", "speb", "spek", "spik", "ssin", "ssit", "st01", "st03", "stai", "star", "stcs", "std2", "stor", "str1", "str2", "str7", "str9", "strm", "strs", "stuf", "stvb", "t35d", "tamm", "tbl1", "tcab", "tcan", "team", "teet", "terr", "texa", "tigr", "tiig", "tirr", "tn99", "tnn1", "top1", "topf", "tops", "tplo", "tr01", "tr02", "tr03", "tr04", "tr05", "tr06", "tr07", "tr08", "tr09", "tr0b", "tr10", "tr11", "tr12", "tr13", "tr14", "tr15", "tr16", "tr17", "tr18", "tr19", "tr20", "tr21", "tr22", "tr23", "tr24", "tr25", "tr27", "tr29", "tr2x", "tr30", "tr32", "tr33", "tr84", "tr85", "tr99", "tra1", "tran", "trb1", "trbl", "trd0", "trd1", "trd5", "tre1", "tre2", "tre3", "tree", "trf0", "trf1", "trff", "trfg", "trfn", "trfp", "trg0", "trg1", "trg2", "trg3", "trg4", "trg5", "trg6", "trg8", "trg9", "trga", "trgb", "trgg", "trgr", "trh1", "trhw", "trj1", "trjx", "trkk", "trl2", "trla", "trlb", "trlg", "trlt", "trlx", "trm0", "trmx", "trn1", "trn2", "tro0", "troj", "trow", "trpf", "trr1", "trr2", "trrt", "trs2", "trs4", "trs5", "trtr", "trw1", "trw3", "trw4", "trw6", "trw7", "trwl", "trwn", "tryy", "trzz", "tube", "twii", "twin", "txt1", "udh1", "udh2", "unde", "undr", "uni2", "uni3", "unni", "unti", "us01", "us1t", "v000", "verl", "vert", "vis0", "visi", "vito", "vitr", "vwal", "wa01", "wa02", "wa03", "wa04", "wa11", "wabl", "wagg", "wakk", "wal0", "wal1", "wal2", "wal3", "wal4", "wal5", "wal6", "wal7", "wal8", "wal9", "wala", "walb", "walc", "wald", "wale", "walf", "walg", "walh", "wali", "walj", "walk", "wall", "walm", "waln", "walo", "walp", "walq", "walr", "wals", "walx", "waly", "walz", "wan0", "wan2", "wan6", "wana", "wanr", "wans", "war1", "war3", "warm", "warn", "watp", "watr", "wavb", "wbar", "wbbw", "wbor", "wdw1", "wdw3", "wdws", "wea1", "wel1", "welc", "wgl7", "whi1", "whi2", "whit", "win1", "win3", "wlbr", "wlog", "wlpl", "wn01", "wnn1", "wntk", "wol1", "wol9", "wrn1", "wt01", "wt02", "wtr2", "wwgd", "wwin", "yelp", "yves"
Shader shaders_MVP2003[12] = {
    // ArbitraryShadowFog, hash 1504470770
    // in files (2): batshadw.o
    { "ArbitraryShadowFog", 4, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 4, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 5, 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 6 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 10 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 14 } },
    { SET_STREAM_SOURCE, { 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 2 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5, 4 } },
    { NOP_1, { 6 } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x4D0002, 3, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5, 4 } },
    { NOP_1, { 6 } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5, 4 } },
    { NOP_1, { 6 } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 16, 66, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::GeoPrimState,
    Shader::ModelViewProjectionMatrix,
    Shader::ShadowColour,
    Shader::FogParameters,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // ArbitraryShadowFog_Skin, hash 735607561
    // in files (5): hishadow.o, loshadow.o
    { "ArbitraryShadowFog_Skin", 4, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::D3DColor, Shader::Color0 }, { Shader::UByte4, Shader::BlendIndices }, { Shader::Float3, Shader::BlendWeight } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 4, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 5, 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 6 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 10 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 14 } },
    { SET_STREAM_SOURCE_SKINNED, { 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5, 4 } },
    { NOP_1, { 6 } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 7, 0x340002, 8, 0x3D0002, 9, 0x4D0002, 5, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5, 4 } },
    { NOP_1, { 6 } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 7, 0x340002, 8, 0x3D0002, 9, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5, 4 } },
    { NOP_1, { 6 } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 20, 70, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 7, 0x340002, 8, 0x3D0002, 9, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::GeoPrimState,
    Shader::VertexSkinData,
    Shader::EAGLAnimationBuffer,
    Shader::ModelViewProjectionMatrix,
    Shader::ShadowColour,
    Shader::FogParameters,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // LitTextureIrradFog, hash 2407847630
    // in files (4): ball.o, bat.o, brknbat.o
    { "LitTextureIrradFog", 3, { { Shader::Float3, Shader::Position }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 4, 40 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 14, 28 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 21, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 22, 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 23 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 27 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 31 } },
    { SET_STREAM_SOURCE, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 4 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4, 40 } },
    { NOP_1, { 14, 28 } },
    { NOP_1, { 21, 4 } },
    { NOP_1, { 22, 4 } },
    { NOP_1, { 23 } },
    { NOP_1, { 27 } },
    { NOP_1, { 31 } },
    { NOP_1, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 11, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 5, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4, 40 } },
    { NOP_1, { 14, 28 } },
    { NOP_1, { 21, 4 } },
    { NOP_1, { 22, 4 } },
    { NOP_1, { 23 } },
    { NOP_1, { 27 } },
    { NOP_1, { 31 } },
    { NOP_1, { 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 36, 338, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 11, 0x330002, 8, 0x340002, 9, 0x3D0002, 10, 0x320003, 5, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::GeoPrimState,
    Shader::Sampler0Local, // local public
    Shader::IrradLight,
    Shader::Light,
    Shader::ZeroOneTwoThree,
    Shader::FogParameters,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // LitTextureIrradFog_Skin, hash 1177539002
    // in files (1476): c001.ord, c002.ord, c003.ord, c004.ord, c005.ord, c006.ord, c007.ord, c008.ord, c009.ord, c010.ord, c011.ord, c012.ord, c013.ord, c014.ord, c015.ord, c016.ord, c017.ord, c018.ord, c019.ord, c020.ord, c021.ord, c022.ord, c023.ord, c024.ord, c025.ord, c026.ord, c027.ord, c028.ord, c029.ord, c030.ord, c031.ord, c032.ord, c033.ord, c034.ord, c035.ord, c036.ord, c037.ord, c038.ord, c039.ord, c040.ord, c041.ord, c042.ord, c043.ord, c044.ord, c045.ord, c046.ord, c047.ord, c048.ord, c049.ord, c050.ord, c051.ord, c052.ord, c053.ord, c054.ord, c055.ord, c056.ord, c057.ord, c058.ord, c059.ord, c060.ord, c061.ord, c062.ord, c063.ord, c064.ord, c065.ord, c066.ord, c067.ord, c068.ord, c069.ord, c070.ord, c071.ord, c072.ord, c073.ord, c074.ord, c075.ord, c076.ord, c077.ord, c078.ord, c079.ord, c080.ord, c081.ord, c082.ord, c083.ord, c084.ord, c085.ord, c086.ord, c087.ord, c088.ord, c089.ord, c090.ord, c091.ord, c092.ord, c093.ord, c094.ord, c095.ord, c096.ord, c097.ord, c098.ord, c099.ord, c100.ord, c101.ord, c102.ord, c103.ord, c104.ord, c105.ord, c106.ord, c107.ord, c108.ord, c109.ord, c110.ord, c111.ord, c112.ord, c113.ord, c114.ord, c115.ord, c116.ord, c117.ord, c118.ord, c119.ord, c120.ord, c121.ord, c122.ord, c123.ord, c124.ord, c125.ord, c126.ord, c127.ord, c128.ord, c129.ord, c130.ord, c131.ord, c132.ord, c133.ord, c134.ord, c135.ord, c136.ord, c137.ord, c138.ord, c139.ord, c140.ord, c141.ord, c142.ord, c143.ord, c144.ord, c145.ord, c146.ord, c147.ord, c148.ord, c149.ord, c150.ord, c151.ord, c152.ord, c153.ord, c154.ord, c155.ord, c156.ord, c157.ord, c158.ord, c159.ord, c160.ord, c161.ord, c162.ord, c163.ord, c164.ord, c165.ord, c166.ord, c167.ord, c168.ord, c169.ord, c170.ord, c171.ord, c172.ord, c173.ord, c174.ord, c175.ord, c176.ord, c177.ord, c178.ord, c179.ord, c180.ord, c181.ord, c182.ord, c183.ord, c184.ord, c185.ord, c186.ord, c187.ord, c188.ord, c189.ord, c190.ord, c191.ord, c192.ord, c193.ord, c194.ord, c195.ord, c196.ord, c197.ord, c198.ord, c199.ord, c200.ord, c201.ord, c202.ord, c203.ord, c204.ord, c205.ord, c206.ord, c207.ord, c208.ord, c209.ord, c210.ord, c211.ord, c212.ord, c213.ord, c214.ord, c215.ord, c216.ord, c217.ord, c218.ord, c219.ord, c220.ord, c221.ord, c222.ord, c223.ord, c224.ord, c225.ord, c226.ord, c227.ord, c228.ord, c229.ord, c230.ord, c231.ord, g001.ord, g002.ord, g003.ord, g004.ord, g005.ord, g006.ord, g007.ord, g008.ord, g009.ord, g010.ord, g011.ord, g012.ord, g013.ord, g014.ord, g015.ord
    { "LitTextureIrradFog_Skin", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 }, { Shader::UByte4, Shader::BlendIndices }, { Shader::Float3, Shader::BlendWeight } },
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
    { SET_VERTEX_SHADER_CONSTANT_G, { 21, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 22, 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 23 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 27 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 31 } },
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
    { NOP_1, { 21, 4 } },
    { NOP_1, { 22, 4 } },
    { NOP_1, { 23 } },
    { NOP_1, { 27 } },
    { NOP_1, { 31 } },
    { NOP_1, { 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 10, 0x340002, 11, 0x3D0002, 12, 0x320003, 7, 1, 0x440001 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_BONE_WEIGHTS, { Shader::VertexWeights3Bones, Shader::VertexWeights2Bones, Shader::VertexWeights1Bone } },
    { SET_ANIMATION_BUFFER, { 0, 512 } },
    { NOP_1, { 0 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 4, 40 } },
    { NOP_1, { 14, 28 } },
    { NOP_1, { 21, 4 } },
    { NOP_1, { 22, 4 } },
    { NOP_1, { 23 } },
    { NOP_1, { 27 } },
    { NOP_1, { 31 } },
    { NOP_1, { 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4B000C, 0, 40, 342, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1, 0x330002, 10, 0x340002, 11, 0x3D0002, 12, 0x320003, 7, 1, 0x440001 } }
    },
    {
    Shader::GeometryInfo,
    Shader::VertexSkinData,
    Shader::EAGLAnimationBuffer,
    Shader::ModelViewProjectionMatrix,
    Shader::GeoPrimState,
    Shader::Sampler0Local, // local public
    Shader::IrradLight,
    Shader::Light,
    Shader::ZeroOneTwoThree,
    Shader::FogParameters,
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // MatCrowdScrollTexture, hash 498645562
    // in files (458): crowd.ord
    { "MatCrowdScrollTexture", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 4, 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 5 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 9, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 10 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 14 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 18 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5 } },
    { NOP_1, { 9, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 18 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 10, 0x330002, 7, 0x340002, 8, 0x3D0002, 9, 0x350002, 3, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5 } },
    { NOP_1, { 9, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 18 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 10, 0x330002, 7, 0x340002, 8, 0x3D0002, 9, 0x350002, 3, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::UVOffset_Layer,
    Shader::UVMatrix_Layer,
    Shader::FogParameters,
    Shader::CrowdState,
    Shader::Sampler0Local, // local public
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // MatField, hash 593252708
    // in files (640): mfield.ord
    { "MatField", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 5 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 9 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 13 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::FogParameters,
    { Shader::RuntimeGeoPrimState, "SetTextureEnable=true;SetAlphaBlendMode=EAGL::ABM_BLEND;SetAlphaTestEnable=true;SetAlphaTestMethod=EAGL::ATM_GREATER;SetDepthTestMethod=EAGL::DTM_ALWAYS" },
    Shader::Sampler0Local, // local public
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // MatGlower, hash 2529310735
    // in files (216): mstadium.ord, net.ord
    { "MatGlower", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 5 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 9 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 13 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::FogParameters,
    Shader::GlowerState,
    Shader::Sampler0Local, // local public
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // MatJumbo, hash 1339504296
    // in files (57): jumbo.ord
    { "MatJumbo", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 5 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 9 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 13 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::FogParameters,
    Shader::GeoPrimState,
    Shader::Sampler0, // global
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // MatLoResField, hash 1339504296
    // in files (58): mfield.ord
    { "MatLoResField", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 5 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 9 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 13 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::FogParameters,
    Shader::GeoPrimState,
    Shader::Sampler0Local, // local public
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // MatProjectiveShadow, hash 3354855957
    // in files (57): mshadow.ord
    { "MatProjectiveShadow", 3, { { Shader::Float3, Shader::Position }, { Shader::Float3, Shader::Normal }, { Shader::D3DColor, Shader::Color0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 8, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 9, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 10, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_STREAM_SOURCE, { 0, 28, 82, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 8, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 9, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 10, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_STREAM_SOURCE, { 0, 28, 82, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 4 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 8, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 9, 4 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 10, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_STREAM_SOURCE, { 0, 28, 82, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::TextureProjectionMatrix,
    Shader::LocalLightDirection,
    Shader::ZeroOneTwoThree,
    Shader::FogParameters,
    { Shader::RuntimeGeoPrimState, "SetTextureEnable=true;SetAlphaBlendMode=EAGL::ABM_SUBTRACT;SetAlphaTestEnable=true;SetAlphaTestMethod=EAGL::ATM_ALWAYS;SetDepthTestMethod=EAGL::DTM_LEQUAL" },
    Shader::Sampler0, // global
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // MatScrollTexture, hash 1885164110
    // in files (564): mstadium.ord, net.ord
    { "MatScrollTexture", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_L_46, { 4, 4 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 5 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 9, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 10 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 14 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 18 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5 } },
    { NOP_1, { 9, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 18 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 10, 0x330002, 7, 0x340002, 8, 0x3D0002, 9, 0x350002, 3, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { NOP_1, { 5 } },
    { NOP_1, { 9, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 10 } },
    { NOP_1, { 14 } },
    { NOP_1, { 18 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 10, 0x330002, 7, 0x340002, 8, 0x3D0002, 9, 0x350002, 3, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::UVOffset_Layer,
    Shader::UVMatrix_Layer,
    Shader::FogParameters,
    Shader::GeoPrimState,
    Shader::Sampler0Local, // local public
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    },
    // TextureFog, hash 1339504296
    // in files (9540): apple.o, bern.o, mstadium.ord, net.ord, sky.ord, train.o
    { "TextureFog", 3, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color0 }, { Shader::Float2, Shader::Texcoord0 } },
    {
    { SETUP_RENDER, { 0, -1 } },
    { NOP_1, {  } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 0 } },
    { SET_VERTEX_SHADER_CONSTANT_G, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 5 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 9 } },
    { SET_VERTEX_SHADER_TRANSPOSED_MATRIX, { 13 } },
    { SET_STREAM_SOURCE, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_NO_Z_WRITE, { 3 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } },

    { SETUP_RENDER, { 1, -1 } },
    { NOP_1, {  } },
    { NOP_1, { 0 } },
    { NOP_1, { 4, 4 } },
    { SET_GEO_PRIM_STATE, {  } },
    { SET_SAMPLER, { 0, Shader::Sampler0Size } },
    { NOP_1, { 5 } },
    { NOP_1, { 9 } },
    { NOP_1, { 13 } },
    { NOP_1, { 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, -1, -1 } },
    { SET_INDEX_BUFFER, { 2, -1, -1, Shader::IndexData, Shader::IndexCount } },
    { DRAW_INDEXED_PRIM_AND_END, { 0x4000B, 0, 24, 322, -1, -1, Shader::VertexData, Shader::VertexCount, Shader::VariationsCount, Shader::VertexBufferIndex, 8, 0x330002, 5, 0x340002, 6, 0x3D0002, 7, 0x440001, 0x320003, 0, 0 } }
    },
    {
    Shader::GeometryInfo,
    Shader::ModelViewProjectionMatrix,
    Shader::FogParameters,
    Shader::GeoPrimState,
    Shader::Sampler0Local, // local public
    Shader::ModelMatrix,
    Shader::ViewMatrix,
    Shader::ProjectionMatrix,
    Shader::VertexData,
    Shader::IndexData
    }
    }
};

char const *TargetMVP2003::Name() {
    return "MVP2003";
}

int TargetMVP2003::Version() {
    return 2;
}

unsigned short TargetMVP2003::AnimVersion() {
    return 0xDB15;
}

Shader *TargetMVP2003::Shaders() {
    return shaders_MVP2003;
}

unsigned int TargetMVP2003::NumShaders() {
    return std::size(shaders_MVP2003);
}

Shader *TargetMVP2003::DecideShader(MaterialProperties const &properties) {
    if (!properties.isSkinned) {
        if (properties.isUnlit)
            return FindShader("TextureFog");
        else {
            if (properties.isLit)
                return FindShader("LitTextureIrradFog");
            else
                return FindShader("TextureFog");
        }
    }
    else
        return FindShader("LitTextureIrradFog_Skin");
}
