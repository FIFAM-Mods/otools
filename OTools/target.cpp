#include "target.h"
#include "outils.h"

unsigned int Target::GetMaxBoneWeightsPerVertex() {
    return 3;
}

unsigned int Target::GetMaxVertexWeightsPerMesh() {
    return 128;
}

unsigned short Target::AnimVersion() {
    return 0xC0DA;
}

Shader *Target::FindShader(std::string const &name) {
    auto nameLowered = ToLower(name);
    for (unsigned int i = 0; i < NumShaders(); i++) {
        if (nameLowered == Shaders()[i].nameLowered)
            return &Shaders()[i];
    }
    return nullptr;
}
