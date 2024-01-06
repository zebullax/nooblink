// File: elf_constants.h
// Project: nooblink
//

#ifndef NOOBLINK_ELF_CONSTANTS_H
#define NOOBLINK_ELF_CONSTANTS_H

// std
#include <cstdint>
#include <ostream>

namespace NoobLink {

enum class AddressClass : uint8_t { e_Invalid, e_32, e_64 };
std::ostream &operator<<(std::ostream &os, const AddressClass &addressClass);

enum class Endianness : uint8_t { e_Invalid, e_LittleEndian, e_BigEndian };
std::ostream &operator<<(std::ostream &os, const Endianness &endianness);

enum class ObjectFileType : uint16_t { e_Unknown, e_Relocatable, e_Executable, e_Shared, e_Core };
std::ostream &operator<<(std::ostream &os, const ObjectFileType &objectFileType);

enum class Abi : uint8_t {
  e_None = 0,
  e_Hpux = 1,
  e_Netbsd = 2,
  e_Linux = 3,
  e_Solaris = 6,
  e_Aix = 7,
  e_Irix = 8,
  e_Freebsd = 9,
  e_Tru64 = 10,
  e_Modesto = 11,
  e_Openbsd = 12,
  e_Openvms = 13,
  e_Nsk = 14,
  e_Aros = 15,
  e_Fenixos = 16,
  e_C6000Elfabi = 64,
  e_C6000Linux = 65,
  e_Arm = 97,
};
std::ostream &operator<<(std::ostream &os, const Abi &abi);

enum class Architecture : uint16_t {
  e_None = 0,            /* No machine */
  e_M32 = 1,             /* AT&T WE 32100 */
  e_Sparc = 2,           /* SUN SPARC */
  e_386 = 3,             /* Intel 80386 */
  e_68k = 4,             /* Motorola m68k family */
  e_88k = 5,             /* Motorola m88k family */
  e_486 = 6,             /* Intel 80486 */
  e_860 = 7,             /* Intel 80860 */
  e_Mips = 8,            /* MIPS R3000 (officially, big-endian only) */
  e_S370 = 9,            /* IBM System/370 */
  e_Mips_rs3_le = 10,    /* MIPS R3000 little-endian (Oct 4 1999 Draft) Deprecated */
  e_res011 = 11,         /* Reserved */
  e_res012 = 12,         /* Reserved */
  e_res013 = 13,         /* Reserved */
  e_res014 = 14,         /* Reserved */
  e_Parisc = 15,         /* HPPA */
  e_res016 = 16,         /* Reserved */
  e_Vpp550 = 17,         /* Fujitsu VPP500 */
  e_Sparc32plus = 18,    /* Sun's "v8plus" */
  e_960 = 19,            /* Intel 80960 */
  e_Ppc = 20,            /* PowerPC */
  e_Ppc64 = 21,          /* 64-bit PowerPC */
  e_S390 = 22,           /* IBM S/390 */
  e_Spu = 23,            /* Sony/Toshiba/IBM SPU */
  e_res024 = 24,         /* Reserved */
  e_res025 = 25,         /* Reserved */
  e_res026 = 26,         /* Reserved */
  e_res027 = 27,         /* Reserved */
  e_res028 = 28,         /* Reserved */
  e_res029 = 29,         /* Reserved */
  e_res030 = 30,         /* Reserved */
  e_res031 = 31,         /* Reserved */
  e_res032 = 32,         /* Reserved */
  e_res033 = 33,         /* Reserved */
  e_res034 = 34,         /* Reserved */
  e_res035 = 35,         /* Reserved */
  e_V800 = 36,           /* NEC V800 series */
  e_Fr20 = 37,           /* Fujitsu FR20 */
  e_Rh32 = 38,           /* TRW RH32 */
  e_Mcore = 39,          /* MCore */
  e_Arm = 40,            /* ARM */
  e_Old_alpha = 41,      /* Digital Alpha */
  e_Sh = 42,             /* Renesas (formerly Hitachi) / SuperH SH */
  e_Sparcv9 = 43,        /* SPARC v9 64-bit */
  e_Tricore = 44,        /* Siemens Tricore embedded processor */
  e_Arc = 45,            /* ARC Cores */
  e_H8_300 = 46,         /* Renesas (formerly Hitachi) H8/300 */
  e_H8_300h = 47,        /* Renesas (formerly Hitachi) H8/300H */
  e_H8s = 48,            /* Renesas (formerly Hitachi) H8S */
  e_H8_500 = 49,         /* Renesas (formerly Hitachi) H8/500 */
  e_Ia_64 = 50,          /* Intel IA-64 Processor */
  e_Mips_x = 51,         /* Stanford MIPS-X */
  e_Coldfire = 52,       /* Motorola Coldfire */
  e_68hc12 = 53,         /* Motorola M68HC12 */
  e_Mma = 54,            /* Fujitsu Multimedia Accelerator */
  e_Pcp = 55,            /* Siemens PCP */
  e_Ncpu = 56,           /* Sony nCPU embedded RISC processor */
  e_Ndr1 = 57,           /* Denso NDR1 microprocessor */
  e_Starcore = 58,       /* Motorola Star*Core processor */
  e_Me16 = 59,           /* Toyota ME16 processor */
  e_St100 = 60,          /* STMicroelectronics ST100 processor */
  e_Tinyj = 61,          /* Advanced Logic Corp. TinyJ embedded processor */
  e_X86_64 = 62,         /* Advanced Micro Devices X86-64 processor */
  e_Pdsp = 63,           /* Sony DSP Processor */
  e_Pdp10 = 64,          /* Digital Equipment Corp. PDP-10 */
  e_Pdp11 = 65,          /* Digital Equipment Corp. PDP-11 */
  e_Fx66 = 66,           /* Siemens FX66 microcontroller */
  e_St9plus = 67,        /* STMicroelectronics ST9+ 8/16 bit microcontroller */
  e_St7 = 68,            /* STMicroelectronics ST7 8-bit microcontroller */
  e_68hc16 = 69,         /* Motorola MC68HC16 Microcontroller */
  e_68hc11 = 70,         /* Motorola MC68HC11 Microcontroller */
  e_68hc08 = 71,         /* Motorola MC68HC08 Microcontroller */
  e_68hc05 = 72,         /* Motorola MC68HC05 Microcontroller */
  e_Svx = 73,            /* Silicon Graphics SVx */
  e_St19 = 74,           /* STMicroelectronics ST19 8-bit cpu */
  e_Vax = 75,            /* Digital VAX */
  e_Cris = 76,           /* Axis Communications 32-bit embedded processor */
  e_Javelin = 77,        /* Infineon Technologies 32-bit embedded cpu */
  e_Firepath = 78,       /* Element 14 64-bit DSP processor */
  e_Zsp = 79,            /* LSI Logic's 16-bit DSP processor */
  e_Mmix = 80,           /* Donald Knuth's educational 64-bit processor */
  e_Huany = 81,          /* Harvard's machine-independent format */
  e_Prism = 82,          /* SiTera Prism */
  e_Avr = 83,            /* Atmel AVR 8-bit microcontroller */
  e_Fr30 = 84,           /* Fujitsu FR30 */
  e_D10v = 85,           /* Mitsubishi D10V */
  e_D30v = 86,           /* Mitsubishi D30V */
  e_V850 = 87,           /* Renesas V850 (formerly NEC V850) */
  e_M32r = 88,           /* Renesas M32R (formerly Mitsubishi M32R) */
  e_Mn10300 = 89,        /* Matsushita MN10300 */
  e_Mn10200 = 90,        /* Matsushita MN10200 */
  e_Pj = 91,             /* picoJava */
  e_Or1k = 92,           /* OpenRISC 1000 32-bit embedded processor */
  e_Arc_a5 = 93,         /* ARC Cores Tangent-A5 */
  e_Xtensa = 94,         /* Tensilica Xtensa Architecture */
  e_Videocore = 95,      /* Alphamosaic VideoCore processor */
  e_Tmm_gpp = 96,        /* Thompson Multimedia General Purpose Processor */
  e_Ns32k = 97,          /* National Semiconductor 32000 series */
  e_Tpc = 98,            /* Tenor Network TPC processor */
  e_Snp1k = 99,          /* Trebia SNP 1000 processor */
  e_St200 = 100,         /* STMicroelectronics ST200 microcontroller */
  e_Ip2k = 101,          /* Ubicom IP2022 micro controller */
  e_Max = 102,           /* MAX Processor */
  e_Cr = 103,            /* National Semiconductor CompactRISC */
  e_F2mc16 = 104,        /* Fujitsu F2MC16 */
  e_Msp430 = 105,        /* TI msp430 micro controller */
  e_Blackfin = 106,      /* ADI Blackfin */
  e_Se_c33 = 107,        /* S1C33 Family of Seiko Epson processors */
  e_Sep = 108,           /* Sharp embedded microprocessor */
  e_Arca = 109,          /* Arca RISC Microprocessor */
  e_Unicore = 110,       /* Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University */
  e_Excess = 111,        /* eXcess: 16/32/64-bit configurable embedded CPU */
  e_Dxp = 112,           /* Icera Semiconductor Inc. Deep Execution Processor */
  e_Altera_nios2 = 113,  /* Altera Nios II soft-core processor */
  e_Crx = 114,           /* National Semiconductor CRX */
  e_Xgate = 115,         /* Motorola XGATE embedded processor */
  e_C166 = 116,          /* Infineon C16x/XC16x processor */
  e_M16c = 117,          /* Renesas M16C series microprocessors */
  e_Dspic30f = 118,      /* Microchip Technology dsPIC30F Digital Signal Controller */
  e_Ce = 119,            /* Freescale Communication Engine RISC core */
  e_M32c = 120,          /* Renesas M32C series microprocessors */
  e_res121 = 121,        /* Reserved */
  e_res122 = 122,        /* Reserved */
  e_res123 = 123,        /* Reserved */
  e_res124 = 124,        /* Reserved */
  e_res125 = 125,        /* Reserved */
  e_res126 = 126,        /* Reserved */
  e_res127 = 127,        /* Reserved */
  e_res128 = 128,        /* Reserved */
  e_res129 = 129,        /* Reserved */
  e_res130 = 130,        /* Reserved */
  e_Tsk3000 = 131,       /* Altium TSK3000 core */
  e_Rs08 = 132,          /* Freescale RS08 embedded processor */
  e_res133 = 133,        /* Reserved */
  e_Ecog2 = 134,         /* Cyan Technology eCOG2 microprocessor */
  e_Score7 = 135,        /* Sunplus S+core7 RISC processor */
  e_Dsp24 = 136,         /* New Japan Radio (NJR) 24-bit DSP Processor */
  e_Videocore3 = 137,    /* Broadcom VideoCore III processor */
  e_Latticemico32 = 138, /* RISC processor for Lattice FPGA architecture */
  e_Se_c17 = 139,        /* Seiko Epson C17 family */
  e_Ti_c6000 = 140,      /* Texas Instruments TMS320C6000 DSP family */
  e_Ti_c2000 = 141,      /* Texas Instruments TMS320C2000 DSP family */
  e_Ti_c5500 = 142,      /* Texas Instruments TMS320C55x DSP family */
  e_res143 = 143,        /* Reserved */
  e_res144 = 144,        /* Reserved */
  e_res145 = 145,        /* Reserved */
  e_res146 = 146,        /* Reserved */
  e_res147 = 147,        /* Reserved */
  e_res148 = 148,        /* Reserved */
  e_res149 = 149,        /* Reserved */
  e_res150 = 150,        /* Reserved */
  e_res151 = 151,        /* Reserved */
  e_res152 = 152,        /* Reserved */
  e_res153 = 153,        /* Reserved */
  e_res154 = 154,        /* Reserved */
  e_res155 = 155,        /* Reserved */
  e_res156 = 156,        /* Reserved */
  e_res157 = 157,        /* Reserved */
  e_res158 = 158,        /* Reserved */
  e_res159 = 159,        /* Reserved */
  e_Mmdsp_plus = 160,    /* STMicroelectronics 64bit VLIW Data Signal Processor */
  e_Cypress_m8c = 161,   /* Cypress M8C microprocessor */
  e_R32c = 162,          /* Renesas R32C series microprocessors */
  e_Trimedia = 163,      /* NXP Semiconductors TriMedia architecture family */
  e_Qdsp6 = 164,         /* QUALCOMM DSP6 Processor */
  e_8051 = 165,          /* Intel 8051 and variants */
  e_Stxp7x = 166,        /* STMicroelectronics STxP7x family */
  e_Nds32 = 167,         /* Andes Technology compact code size embedded RISC processor family */
  e_Ecog1x = 168,        /* Cyan Technology eCOG1X family */
  e_Maxq30 = 169,        /* Dallas Semiconductor MAXQ30 Core Micro-controllers */
  e_Ximo16 = 170,        /* New Japan Radio (NJR) 16-bit DSP Processor */
  e_Manik = 171,         /* M2000 Reconfigurable RISC Microprocessor */
  e_Craynv2 = 172,       /* Cray Inc. NV2 vector architecture */
  e_Rx = 173,            /* Renesas RX family */
  e_Metag = 174,         /* Imagination Technologies Meta processor architecture */
  e_Mcst_elbrus = 175,   /* MCST Elbrus general purpose hardware architecture */
  e_Ecog16 = 176,        /* Cyan Technology eCOG16 family */
  e_Cr16 = 177,          /* National Semiconductor CompactRISC 16-bit processor */
  e_Etpu = 178,          /* Freescale Extended Time Processing Unit */
  e_Sle9x = 179,         /* Infineon Technologies SLE9X core */
  e_L1om = 180,          /* Intel L1OM */
  e_K1om = 181,          /* Intel K1OM */
  e_Intel182 = 182,      /* Reserved by Intel */
  e_Aarch64 = 183,       /* ARM 64-bit architecture */
  e_Arm184 = 184,        /* Reserved by ARM */
  e_Avr32 = 185,         /* Atmel Corporation 32-bit microprocessor family */
  e_Stm8 = 186,          /* STMicroeletronics STM8 8-bit microcontroller */
  e_Tile64 = 187,        /* Tilera TILE64 multicore architecture family */
  e_Tilepro = 188,       /* Tilera TILEPro multicore architecture family */
  e_Microblaze = 189,    /* Xilinx MicroBlaze 32-bit RISC soft processor core */
  e_Cuda = 190,          /* NVIDIA CUDA architecture */
  e_Tilegx = 191,        /* Tilera TILE-Gx multicore architecture family */
  e_Rl78 = 197,          /* Renesas RL78 family.  */
  e_78k0r = 199,         /* Renesas 78K0R.  */
  e_Intel205 = 205,      /* Reserved by Intel */
  e_Intel206 = 206,      /* Reserved by Intel */
  e_Intel207 = 207,      /* Reserved by Intel */
  e_Intel208 = 208,      /* Reserved by Intel */
  e_Intel209 = 209,      /* Reserved by Intel */
  e_Visium = 221,        /* Controls and Data Services VISIUM core processor */
  e_Moxie = 223,         /* Moxie processor family */
};
std::ostream &operator<<(std::ostream &os, const Architecture &architecture);

enum class SectionType : uint32_t {
  e_Null = 0,
  e_Progbits = 1,
  e_Symtab = 2,
  e_Strtab = 3,
  e_Rela = 4,
  e_Hash = 5,
  e_Dynamic = 6,
  e_Note = 7,
  e_Nobits = 8,
  e_Rel = 9,
  e_Shlib = 10,
  e_Dynsym = 11,
  e_Init_array = 14,
  e_Fini_array = 15,
  e_Preinit_array = 16,
  e_Group = 17,
  e_Symtab_shndx = 18,
  e_Loos = 0x60000000,
  e_Hios = 0x6fffffff,
  e_Loproc = 0x70000000,
  e_Hiproc = 0x7fffffff,
  e_Louser = 0x80000000,
  e_Hiuser = 0xffffffff,
};
std::ostream &operator<<(std::ostream &os, const SectionType &sectionType);

enum class SectionFlag : uint64_t {
  e_Write = 0x1,     // Writable
  e_Alloc = 0x2,     // Occupies memory at runtime
  e_Execinstr = 0x4, // Executable
  e_Merge = 0x10,    // Might be merged
  e_Strings = 0x20,  // Contains C-style string
  e_Info_link = 0x40,
  e_Link_order = 0x80, // Preserve order after combining
  e_Os_nonconforming = 0x100,
  e_Group = 0x200,
  e_Tls = 0x400, // Section hold thread local data
  e_Maskos = 0x0ff00000,
  e_Maskproc = 0xf0000000,
};
std::ostream &operator<<(std::ostream &os, const SectionFlag &sectionFlag);

} // namespace NoobLink

inline std::ostream &NoobLink::operator<<(std::ostream &os, const AddressClass &addressClass) {
  switch (addressClass) {

  case AddressClass::e_32:
    return os << "32bits";
  case AddressClass::e_64:
    return os << "64bits";
  case AddressClass::e_Invalid:
  default:
    return os << "Invalid";
  }
}

inline std::ostream &NoobLink::operator<<(std::ostream &os, const Endianness &endianness) {
  switch (endianness) {

  case Endianness::e_LittleEndian:
    return os << "LowEndian";
  case Endianness::e_BigEndian:
    return os << "HighEndian";
  case Endianness::e_Invalid:
  default:
    return os << "Invalid";
  }
}

inline std::ostream &NoobLink::operator<<(std::ostream &os, const ObjectFileType &objectFileType) {
  switch (objectFileType) {

  case ObjectFileType::e_Relocatable:
    return os << "Relocatable";
  case ObjectFileType::e_Executable:
    return os << "Executable";
  case ObjectFileType::e_Shared:
    return os << "Shared";
  case ObjectFileType::e_Core:
    return os << "Core";
  default:
    return os << "Unknown";
  }
}

inline std::ostream &NoobLink::operator<<(std::ostream &os, const Abi &abi) {
  switch (abi) {
  case Abi::e_None:
    return os << "None";
  case Abi::e_Hpux:
    return os << "Hpux";
  case Abi::e_Netbsd:
    return os << "Netbsd";
  case Abi::e_Linux:
    return os << "Linux";
  case Abi::e_Solaris:
    return os << "Solaris";
  case Abi::e_Aix:
    return os << "Aix";
  case Abi::e_Irix:
    return os << "Irix";
  case Abi::e_Freebsd:
    return os << "Freebsd";
  case Abi::e_Tru64:
    return os << "Tru64";
  case Abi::e_Modesto:
    return os << "Modesto";
  case Abi::e_Openbsd:
    return os << "Openbsd";
  case Abi::e_Openvms:
    return os << "Openvms";
  case Abi::e_Nsk:
    return os << "Nsk";
  case Abi::e_Aros:
    return os << "Aros";
  case Abi::e_Fenixos:
    return os << "Fenixos";
  case Abi::e_C6000Elfabi:
    return os << "C6000Elfabi";
  case Abi::e_C6000Linux:
    return os << "C6000Linux";
  case Abi::e_Arm:
    return os << "Arm";
  default:
    return os << "Unknown";
  }
}

inline std::ostream &NoobLink::operator<<(std::ostream &os, const Architecture &architecture) {
  switch (architecture) {
  case Architecture::e_None:
    return os << "No machine";
  case Architecture::e_M32:
    return os << "AT&T WE 32100";
  case Architecture::e_Sparc:
    return os << "SUN SPARC";
  case Architecture::e_386:
    return os << "Intel 80386";
  case Architecture::e_68k:
    return os << "Motorola m68k family";
  case Architecture::e_88k:
    return os << "Motorola m88k family";
  case Architecture::e_486:
    return os << "Intel 80486";
  case Architecture::e_860:
    return os << "Intel 80860";
  case Architecture::e_Mips:
    return os << "MIPS R3000 (officially, big-endian only)";
  case Architecture::e_S370:
    return os << "IBM System/370";
  case Architecture::e_Mips_rs3_le:
    return os << "MIPS R3000 little-endian (Oct 4 1999 Draft) Deprecated";
  case Architecture::e_res011:
  case Architecture::e_res012:
  case Architecture::e_res013:
  case Architecture::e_res014:
    return os << "Reserved";
  case Architecture::e_Parisc:
    return os << "HPPA";
  case Architecture::e_res016:
    return os << "Reserved";
  case Architecture::e_Vpp550:
    return os << "Fujitsu VPP500";
  case Architecture::e_Sparc32plus:
    return os << "Sun's \"v8plus\"";
  case Architecture::e_960:
    return os << "Intel 80960";
  case Architecture::e_Ppc:
    return os << "PowerPC";
  case Architecture::e_Ppc64:
    return os << "64-bit PowerPC";
  case Architecture::e_S390:
    return os << "IBM S/390";
  case Architecture::e_Spu:
    return os << "Sony/Toshiba/IBM SPU";
  case Architecture::e_res024:
  case Architecture::e_res025:
  case Architecture::e_res026:
  case Architecture::e_res027:
  case Architecture::e_res028:
  case Architecture::e_res029:
  case Architecture::e_res030:
  case Architecture::e_res031:
  case Architecture::e_res032:
  case Architecture::e_res033:
  case Architecture::e_res034:
  case Architecture::e_res035:
    return os << "Reserved";
  case Architecture::e_V800:
    return os << "NEC V800 series";
  case Architecture::e_Fr20:
    return os << "Fujitsu FR20";
  case Architecture::e_Rh32:
    return os << "TRW RH32";
  case Architecture::e_Mcore:
    return os << "MCore";
  case Architecture::e_Arm:
    return os << "ARM";
  case Architecture::e_Old_alpha:
    return os << "Digital Alpha";
  case Architecture::e_Sh:
    return os << "Renesas (formerly Hitachi) / SuperH SH";
  case Architecture::e_Sparcv9:
    return os << "SPARC v9 64-bit";
  case Architecture::e_Tricore:
    return os << "Siemens Tricore embedded processor";
  case Architecture::e_Arc:
    return os << "ARC Cores";
  case Architecture::e_H8_300:
    return os << "Renesas (formerly Hitachi) H8/300";
  case Architecture::e_H8_300h:
    return os << "Renesas (formerly Hitachi) H8/300H";
  case Architecture::e_H8s:
    return os << "Renesas (formerly Hitachi) H8S";
  case Architecture::e_H8_500:
    return os << "Renesas (formerly Hitachi) H8/500";
  case Architecture::e_Ia_64:
    return os << "Intel IA-64 Processor";
  case Architecture::e_Mips_x:
    return os << "Stanford MIPS-X";
  case Architecture::e_Coldfire:
    return os << "Motorola Coldfire";
  case Architecture::e_68hc12:
    return os << "Motorola M68HC12";
  case Architecture::e_Mma:
    return os << "Fujitsu Multimedia Accelerator";
  case Architecture::e_Pcp:
    return os << "Siemens PCP";
  case Architecture::e_Ncpu:
    return os << "Sony nCPU embedded RISC processor";
  case Architecture::e_Ndr1:
    return os << "Denso NDR1 microprocessor";
  case Architecture::e_Starcore:
    return os << "Motorola Star*Core processor";
  case Architecture::e_Me16:
    return os << "Toyota ME16 processor";
  case Architecture::e_St100:
    return os << "STMicroelectronics ST100 processor";
  case Architecture::e_Tinyj:
    return os << "Advanced Logic Corp. TinyJ embedded processor";
  case Architecture::e_X86_64:
    return os << "Advanced Micro Devices X86-64 processor";
  case Architecture::e_Pdsp:
    return os << "Sony DSP Processor";
  case Architecture::e_Pdp10:
    return os << "Digital Equipment Corp. PDP-10";
  case Architecture::e_Pdp11:
    return os << "Digital Equipment Corp. PDP-11";
  case Architecture::e_Fx66:
    return os << "Siemens FX66 microcontroller";
  case Architecture::e_St9plus:
    return os << "STMicroelectronics ST9+ 8/16 bit microcontroller";
  case Architecture::e_St7:
    return os << "STMicroelectronics ST7 8-bit microcontroller";
  case Architecture::e_68hc16:
    return os << "Motorola MC68HC16 Microcontroller";
  case Architecture::e_68hc11:
    return os << "Motorola MC68HC11 Microcontroller";
  case Architecture::e_68hc08:
    return os << "Motorola MC68HC08 Microcontroller";
  case Architecture::e_68hc05:
    return os << "Motorola MC68HC05 Microcontroller";
  case Architecture::e_Svx:
    return os << "Silicon Graphics SVx";
  case Architecture::e_St19:
    return os << "STMicroelectronics ST19 8-bit cpu";
  case Architecture::e_Vax:
    return os << "Digital VAX";
  case Architecture::e_Cris:
    return os << "Axis Communications 32-bit embedded processor";
  case Architecture::e_Javelin:
    return os << "Infineon Technologies 32-bit embedded cpu";
  case Architecture::e_Firepath:
    return os << "Element 14 64-bit DSP processor";
  case Architecture::e_Zsp:
    return os << "LSI Logic's 16-bit DSP processor";
  case Architecture::e_Mmix:
    return os << "Donald Knuth's educational 64-bit processor";
  case Architecture::e_Huany:
    return os << "Harvard's machine-independent format";
  case Architecture::e_Prism:
    return os << "SiTera Prism";
  case Architecture::e_Avr:
    return os << "Atmel AVR 8-bit microcontroller";
  case Architecture::e_Fr30:
    return os << "Fujitsu FR30";
  case Architecture::e_D10v:
    return os << "Mitsubishi D10V";
  case Architecture::e_D30v:
    return os << "Mitsubishi D30V";
  case Architecture::e_V850:
    return os << "Renesas V850 (formerly NEC V850)";
  case Architecture::e_M32r:
    return os << "Renesas M32R (formerly Mitsubishi M32R)";
  case Architecture::e_Mn10300:
    return os << "Matsushita MN10300";
  case Architecture::e_Mn10200:
    return os << "Matsushita MN10200";
  case Architecture::e_Pj:
    return os << "picoJava";
  case Architecture::e_Or1k:
    return os << "OpenRISC 1000 32-bit embedded processor";
  case Architecture::e_Arc_a5:
    return os << "ARC Cores Tangent-A5";
  case Architecture::e_Xtensa:
    return os << "Tensilica Xtensa Architecture";
  case Architecture::e_Videocore:
    return os << "Alphamosaic VideoCore processor";
  case Architecture::e_Tmm_gpp:
    return os << "Thompson Multimedia General Purpose Processor";
  case Architecture::e_Ns32k:
    return os << "National Semiconductor 32000 series";
  case Architecture::e_Tpc:
    return os << "Tenor Network TPC processor";
  case Architecture::e_Snp1k:
    return os << "Trebia SNP 1000 processor";
  case Architecture::e_St200:
    return os << "STMicroelectronics ST200 microcontroller";
  case Architecture::e_Ip2k:
    return os << "Ubicom IP2022 micro controller";
  case Architecture::e_Max:
    return os << "MAX Processor";
  case Architecture::e_Cr:
    return os << "National Semiconductor CompactRISC";
  case Architecture::e_F2mc16:
    return os << "Fujitsu F2MC16";
  case Architecture::e_Msp430:
    return os << "TI msp430 micro controller";
  case Architecture::e_Blackfin:
    return os << "ADI Blackfin";
  case Architecture::e_Se_c33:
    return os << "S1C33 Family of Seiko Epson processors";
  case Architecture::e_Sep:
    return os << "Sharp embedded microprocessor";
  case Architecture::e_Arca:
    return os << "Arca RISC Microprocessor";
  case Architecture::e_Unicore:
    return os << "Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University";
  case Architecture::e_Excess:
    return os << "eXcess: 16/32/64-bit configurable embedded CPU";
  case Architecture::e_Dxp:
    return os << "Icera Semiconductor Inc. Deep Execution Processor";
  case Architecture::e_Altera_nios2:
    return os << "Altera Nios II soft-core processor";
  case Architecture::e_Crx:
    return os << "National Semiconductor CRX";
  case Architecture::e_Xgate:
    return os << "Motorola XGATE embedded processor";
  case Architecture::e_C166:
    return os << "Infineon C16x/XC16x processor";
  case Architecture::e_M16c:
    return os << "Renesas M16C series microprocessors";
  case Architecture::e_Dspic30f:
    return os << "Microchip Technology dsPIC30F Digital Signal Controller";
  case Architecture::e_Ce:
    return os << "Freescale Communication Engine RISC core";
  case Architecture::e_M32c:
    return os << "Renesas M32C series microprocessors";
  case Architecture::e_res121:
  case Architecture::e_res122:
  case Architecture::e_res123:
  case Architecture::e_res124:
  case Architecture::e_res125:
  case Architecture::e_res126:
  case Architecture::e_res127:
  case Architecture::e_res128:
  case Architecture::e_res129:
  case Architecture::e_res130:
    return os << "Reserved";
  case Architecture::e_Tsk3000:
    return os << "Altium TSK3000 core";
  case Architecture::e_Rs08:
    return os << "Freescale RS08 embedded processor";
  case Architecture::e_res133:
    return os << "Reserved";
  case Architecture::e_Ecog2:
    return os << "Cyan Technology eCOG2 microprocessor";
  case Architecture::e_Score7:
    return os << "Sunplus S+core7 RISC processor";
  case Architecture::e_Dsp24:
    return os << "New Japan Radio (NJR) 24-bit DSP Processor";
  case Architecture::e_Videocore3:
    return os << "Broadcom VideoCore III processor";
  case Architecture::e_Latticemico32:
    return os << "RISC processor for Lattice FPGA architecture";
  case Architecture::e_Se_c17:
    return os << "Seiko Epson C17 family";
  case Architecture::e_Ti_c6000:
    return os << "Texas Instruments TMS320C6000 DSP family";
  case Architecture::e_Ti_c2000:
    return os << "Texas Instruments TMS320C2000 DSP family";
  case Architecture::e_Ti_c5500:
    return os << "Texas Instruments TMS320C55x DSP family";
  case Architecture::e_res143:
  case Architecture::e_res144:
  case Architecture::e_res145:
  case Architecture::e_res146:
  case Architecture::e_res147:
  case Architecture::e_res148:
  case Architecture::e_res149:
  case Architecture::e_res150:
  case Architecture::e_res151:
  case Architecture::e_res152:
  case Architecture::e_res153:
  case Architecture::e_res154:
  case Architecture::e_res155:
  case Architecture::e_res156:
  case Architecture::e_res157:
  case Architecture::e_res158:
  case Architecture::e_res159:
    return os << "Reserved";
  case Architecture::e_Mmdsp_plus:
    return os << "STMicroelectronics 64bit VLIW Data Signal Processor";
  case Architecture::e_Cypress_m8c:
    return os << "Cypress M8C microprocessor";
  case Architecture::e_R32c:
    return os << "Renesas R32C series microprocessors";
  case Architecture::e_Trimedia:
    return os << "NXP Semiconductors TriMedia architecture family";
  case Architecture::e_Qdsp6:
    return os << "QUALCOMM DSP6 Processor";
  case Architecture::e_8051:
    return os << "Intel 8051 and variants";
  case Architecture::e_Stxp7x:
    return os << "STMicroelectronics STxP7x family";
  case Architecture::e_Nds32:
    return os << "Andes Technology compact code size embedded RISC processor family";
  case Architecture::e_Ecog1x:
    return os << "Cyan Technology eCOG1X family";
  case Architecture::e_Maxq30:
    return os << "Dallas Semiconductor MAXQ30 Core Micro-controllers";
  case Architecture::e_Ximo16:
    return os << "New Japan Radio (NJR) 16-bit DSP Processor";
  case Architecture::e_Manik:
    return os << "M2000 Reconfigurable RISC Microprocessor";
  case Architecture::e_Craynv2:
    return os << "Cray Inc. NV2 vector architecture";
  case Architecture::e_Rx:
    return os << "Renesas RX family";
  case Architecture::e_Metag:
    return os << "Imagination Technologies Meta processor architecture";
  case Architecture::e_Mcst_elbrus:
    return os << "MCST Elbrus general purpose hardware architecture";
  case Architecture::e_Ecog16:
    return os << "Cyan Technology eCOG16 family";
  case Architecture::e_Cr16:
    return os << "National Semiconductor CompactRISC 16-bit processor";
  case Architecture::e_Etpu:
    return os << "Freescale Extended Time Processing Unit";
  case Architecture::e_Sle9x:
    return os << "Infineon Technologies SLE9X core";
  case Architecture::e_L1om:
    return os << "Intel L1OM";
  case Architecture::e_K1om:
    return os << "Intel K1OM";
  case Architecture::e_Intel182:
    return os << "Reserved by Intel";
  case Architecture::e_Aarch64:
    return os << "ARM 64-bit architecture";
  case Architecture::e_Arm184:
    return os << "Reserved by ARM";
  case Architecture::e_Avr32:
    return os << "Atmel Corporation 32-bit microprocessor family";
  case Architecture::e_Stm8:
    return os << "STMicroeletronics STM8 8-bit microcontroller";
  case Architecture::e_Tile64:
    return os << "Tilera TILE64 multicore architecture family";
  case Architecture::e_Tilepro:
    return os << "Tilera TILEPro multicore architecture family";
  case Architecture::e_Microblaze:
    return os << "Xilinx MicroBlaze 32-bit RISC soft processor core";
  case Architecture::e_Cuda:
    return os << "NVIDIA CUDA architecture";
  case Architecture::e_Tilegx:
    return os << "Tilera TILE-Gx multicore architecture family";
  case Architecture::e_Rl78:
    return os << "Renesas RL78 family. ";
  case Architecture::e_78k0r:
    return os << "Renesas 78K0R. ";
  case Architecture::e_Intel205:
  case Architecture::e_Intel206:
  case Architecture::e_Intel207:
  case Architecture::e_Intel208:
  case Architecture::e_Intel209:
    return os << "Reserved by Intel";
  case Architecture::e_Visium:
    return os << "Controls and Data Services VISIUM core processor";
  case Architecture::e_Moxie:
    return os << "Moxie processor family";
  default:
    return os << "Unknown";
  }
}

inline std::ostream &NoobLink::operator<<(std::ostream &os, const SectionType &sectionType) {
  switch (sectionType) {
  case SectionType::e_Null:
    return os << "Null";
  case SectionType::e_Progbits:
    return os << "Progbits";
  case SectionType::e_Symtab:
    return os << "Symtab"; // Symbol table
  case SectionType::e_Strtab:
    return os << "Strtab"; // String table
  case SectionType::e_Rela:
    return os << "Elf64_Rela"; // Relocation with addend
  case SectionType::e_Hash:
    return os << "Hash"; // Symbol hash table
  case SectionType::e_Dynamic:
    return os << "Dynamic"; // Dynmimc linking info
  case SectionType::e_Note:
    return os << "Note";
  case SectionType::e_Nobits:
    return os << "Nobits";
  case SectionType::e_Rel:
    return os << "Elf64_Rel";
  case SectionType::e_Shlib:
    return os << "Shlib";
  case SectionType::e_Dynsym:
    return os << "Dynsym";
  case SectionType::e_Init_array:
    return os << "Init_array";
  case SectionType::e_Fini_array:
    return os << "Fini_array";
  case SectionType::e_Preinit_array:
    return os << "Preinit_array";
  case SectionType::e_Group:
    return os << "Group";
  case SectionType::e_Symtab_shndx:
    return os << "Symtab_shndx";
  case SectionType::e_Loos:
    return os << "Loos";
  case SectionType::e_Hios:
    return os << "Hios";
  case SectionType::e_Loproc:
    return os << "Loproc";
  case SectionType::e_Hiproc:
    return os << "Hiproc";
  case SectionType::e_Louser:
    return os << "Louser";
  case SectionType::e_Hiuser:
    return os << "Hiuser";
  }
}

inline std::ostream &NoobLink::operator<<(std::ostream &os, const SectionFlag &sectionFlag) {
  switch (sectionFlag) {
  case SectionFlag::e_Write:
    return os << "Write";
  case SectionFlag::e_Alloc:
    return os << "Alloc";
  case SectionFlag::e_Execinstr:
    return os << "Execinstr";
  case SectionFlag::e_Merge:
    return os << "Merge";
  case SectionFlag::e_Strings:
    return os << "Strings";
  case SectionFlag::e_Info_link:
    return os << "Info_link";
  case SectionFlag::e_Link_order:
    return os << "Link_order";
  case SectionFlag::e_Os_nonconforming:
    return os << "Os_nonconforming";
  case SectionFlag::e_Group:
    return os << "Group";
  case SectionFlag::e_Tls:
    return os << "Tls";
  case SectionFlag::e_Maskos:
    return os << "Maskos";
  case SectionFlag::e_Maskproc:
    return os << "Maskproc";
  }
}

#endif // NOOBLINK_ELF_CONSTANTS_H
