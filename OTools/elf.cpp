#include "elf.h"
#include "memory.h"

Elf32_Shdr::Elf32_Shdr() {}

Elf32_Shdr::Elf32_Shdr(Elf32_Word name, Elf32_Word type, Elf32_Word flags, Elf32_Addr addr, Elf32_Off offset, Elf32_Word size, Elf32_Word link, Elf32_Word info, Elf32_Word addralign, Elf32_Word entsize) {
    Memory_Zero(*this);
    sh_name = name;
    sh_type = type;
    sh_flags = flags;
    sh_addr = addr;
    sh_offset = offset;
    sh_size = size;
    sh_link = link;
    sh_info = info;
    sh_addralign = addralign;
    sh_entsize = entsize;
}

Elf32_Sym::Elf32_Sym() {}

Elf32_Sym::Elf32_Sym(Elf32_Word name, Elf32_Addr value, Elf32_Word size, unsigned char info, unsigned char other, Elf32_Half shndx) {
    Memory_Zero(*this);
    st_name = name;
    st_value = value;
    st_size = size;
    st_info = info;
    st_other = other;
    st_shndx = shndx;
}

Elf32_Rel::Elf32_Rel() {}

Elf32_Rel::Elf32_Rel(Elf32_Addr offset, unsigned int info_type, unsigned int info_sym) {
    Memory_Zero(*this);
    r_offset = offset;
    r_info_type = info_type;
    r_info_sym = info_sym;
}
