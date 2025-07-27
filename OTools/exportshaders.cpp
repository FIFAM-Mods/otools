#include "main.h"
#include <fstream>

namespace shaderexport {
    struct FileSymbol : public Elf32_Sym {
        unsigned int id = 0;
        string name;
    };

    struct Pass {
        void *vs = nullptr;
        void *ps = nullptr;
    };

    struct Technique {
        vector<pair<unsigned int, Pass>> passes;
    };

    void writeshadercode(ofstream &f, void *code) {
        ID3DXBuffer *buf = nullptr;
        D3DXDisassembleShader((const DWORD *)code, FALSE, NULL, &buf);
        string codeStr = (char const *)buf->GetBufferPointer();
        string line;
        string comment;
        vector<string> lines;
        for (auto c : codeStr) {
            if (c == '\n') {
                if (!line.empty()) {
                    if (line.starts_with("// approximately"))
                        comment = line;
                    else {
                        if (line.starts_with("#line"))
                            line = "// " + line.substr(1);
                        lines.push_back(line);
                    }
                }
                line.clear();
            }
            else
                line.push_back(c);
        }
        if (!line.empty())
            lines.push_back(line);
        buf->Release();
        f << "        asm";
        if (!comment.empty())
            f << " " << comment;
        f << std::endl << "        {" << std::endl;
        for (auto const &l : lines)
            f << "        " << l << std::endl;
        f << "        };" << std::endl;
    }

    void exporteffect(unsigned char *data, path const &fileName) {
        vector<pair<unsigned int, Technique>> techniques;
        unsigned int numVShaderDeclarations = GetAt<unsigned int>(data, 8);
        unsigned int numTechniques = GetAt<unsigned int>(data, 12 + numVShaderDeclarations * 4);
        data += 16 + numVShaderDeclarations * 4;
        for (unsigned int t = 0; t < numTechniques; t++) {
            Technique technique;
            unsigned int numSamplers = GetAt<unsigned int>(data, 8);
            unsigned int numGeoPrims = GetAt<unsigned int>(data, 12);
            data += 16 + numSamplers * 12 + numGeoPrims * 12;
            unsigned int numPasses = GetAt<unsigned int>(data, 0);
            data += 4;
            for (unsigned int p = 0; p < numPasses; p++) {
                numSamplers = GetAt<unsigned int>(data, 4);
                numGeoPrims = GetAt<unsigned int>(data, 8);
                data += 16;
                unsigned int totalStates = numSamplers + numGeoPrims + 3;
                void *vs = nullptr;
                void *ps = nullptr;
                for (unsigned int s = 0; s < totalStates; s++) {
                    unsigned int type = GetAt<unsigned int>(data, 0);
                    data += 4;
                    if (type == 3 || type == 5 || type == 8)
                        data += 8;
                    else if (type == 4)
                        data += 548;
                    else if (type == 6 || type == 7) {
                        unsigned int codeSize = GetAt<unsigned int>(data, 0);
                        if (codeSize != 0) {
                            if (type == 6)
                                vs = At<void>(data, 4);
                            else
                                ps = At<void>(data, 4);
                        }
                        data += 4 + codeSize * 4;
                    }
                }
                if (vs || ps) {
                    Pass pass;
                    pass.vs = vs;
                    pass.ps = ps;
                    technique.passes.emplace_back(p, pass);
                }
            }
            if (!technique.passes.empty())
                techniques.emplace_back(t, technique);
        }
        ofstream f(fileName);
        for (unsigned int t = 0; t < techniques.size(); t++) {
            f << "technique " << techniques[t].first << std::endl << "{" << std::endl;
            for (unsigned int p = 0; p < techniques[t].second.passes.size(); p++) {
                f << "    pass " << techniques[t].second.passes[p].first << std::endl << "    {" << std::endl;
                if (techniques[t].second.passes[p].second.vs) {
                    f << "        VertexShader =" << std::endl;
                    writeshadercode(f, techniques[t].second.passes[p].second.vs);
                }
                if (techniques[t].second.passes[p].second.ps) {
                    f << "        PixelShader =" << std::endl;
                    writeshadercode(f, techniques[t].second.passes[p].second.ps);
                }
                f << "    }" << std::endl;
            }
            f << "}" << std::endl;
        }
    }

    void exportshaders(unsigned char *fileData, unsigned int fileDataSize, path const &outDir) {
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
        if (h->e_ident[0] != 0x7F || h->e_ident[1] != 'E' || h->e_ident[2] != 'L' || h->e_ident[3] != 'F')
            throw runtime_error("Not an ELF file");
        Elf32_Shdr *s = At<Elf32_Shdr>(h, h->e_shoff);
        for (unsigned int i = 0; i < h->e_shnum; i++) {
            if (s[i].sh_size > 0) {
                if (s[i].sh_type == 1 && !data) {
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
        map<unsigned int, FileSymbol> symbolRelocations;
        for (unsigned int i = 0; i < numRelocations; i++) {
            if (rel[i].r_info_sym < symbols.size())
                symbolRelocations[rel[i].r_offset] = symbols[rel[i].r_info_sym];
        }
        for (unsigned int i = 0; i < numRelocations; i++) {
            auto symbolId = rel[i].r_info_sym;
            if (symbolId < numSymbols && isSymbolDataPresent(symbols[symbolId]))
                SetAt(data, rel[i].r_offset, &data[GetAt<unsigned int>(data, rel[i].r_offset)]);
        }
        for (auto const &s : symbols) {
            if (isSymbolDataPresent(s)) {
                if (s.name.ends_with("__EAGLMicroCode"))
                    exporteffect(At<unsigned char>(data, s.st_value), outDir / (s.name.substr(0, s.name.size() - 15) + ".sh"));
            }
        }
    }

    void exportshaders(path const &inPath, path const &outDir) {
        auto fileData = readofile(inPath);
        if (fileData.first) {
            create_directories(outDir);
            exportshaders(fileData.first, fileData.second, outDir);
            delete[] fileData.first;
        }
    }
};

void oexportshaders(path const &out, path const &in) {
    shaderexport::exportshaders(in, in.parent_path() / ("shaders_" + in.stem().string()));
}
