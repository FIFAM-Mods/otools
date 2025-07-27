#include "shaders.h"
#include "outils.h"

Shader DummyShader = { "DUMMY", 0, { { Shader::Float3, Shader::Position } }, {}, {} };
Shader DummyShader_Skin = { "DUMMY_SKIN", 0, { { Shader::Float3, Shader::Position }, { Shader::D3DColor, Shader::Color1 }, { Shader::UByte4, Shader::BlendIndices }, { Shader::Float3, Shader::BlendWeight } }, {}, {} };

Shader::Shader() {}

Shader::Shader(std::string const &_name, unsigned int _numTechniques, std::vector<VertexDeclElement> const &_declaration, std::vector<Command> const&_commands, std::vector<GlobalArgument> const&_globalArguments) {
    name = _name;
    numTechniques = _numTechniques;
    declaration = _declaration;
    commands = _commands;
    globalArguments = _globalArguments;
    Update();
}

unsigned int Shader::VertexDeclElement::Size() const {
    if (usage != BlendWeight && usage != BlendIndices) {
        switch (type) {
        case Float2:
            return 8;
        case Float3:
            return 12;
        case Float4:
            return 16;
        case D3DColor:
        case UByte4:
            return 4;
        }
    }
    return 0;
}

unsigned int Shader::VertexSize() const {
    return vertexSize;
}

int Shader::ComputationCommandIndex() const {
    return computationCommandIndex;
}

bool Shader::HasAttribute(DataUsage attribute) const {
    for (auto const &d : declaration) {
        if (d.usage == attribute)
            return true;
    }
    return false;
}

void Shader::Update(bool validate) {
    nameLowered = ToLower(name);
    vertexSize = 0;
    for (auto const &d : declaration)
        vertexSize += d.Size();
    computationCommandIndex = -1;
    for (unsigned int i = 0; i < globalArguments.size(); i++) {
        if (globalArguments[i].type == Shader::ComputationIndex) {
            computationCommandIndex = int(i);
            break;
        }
    }
    if (validate) {
        if (numTechniques > 0) {
            if ((commands.size() % numTechniques) != 0)
                Error("Invalid command buffer in shader " + name);
            else if ((commands.size() / numTechniques) != (globalArguments.size() + 2))
                Error("Invalid argument buffer in shader " + name);
        }
    }
}

Shader::GlobalArgument::GlobalArgument() {}

Shader::GlobalArgument::GlobalArgument(unsigned int _type, std::string const &_format) {
    type = _type;
    format = _format;
}

Shader::Command::Command(unsigned char _id, std::vector<int> const &_arguments) {
    id = _id;
    arguments = _arguments;
}

bool operator==(Shader::Command const &a, Shader::Command const &b) {
    return a.id == b.id && a.arguments == b.arguments;
}

bool operator==(Shader::GlobalArgument const &a, Shader::GlobalArgument const &b) {
    return a.type == b.type && a.format == b.format;
}
