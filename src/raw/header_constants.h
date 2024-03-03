// -*-C++-*-
//
// File: header_constants.h
// Project: nooblink
//
// Description: This component provides values describing object file characteristics wrt architecture, file type, etc.
//

#ifndef NOOBLINK_HEADER_CONSTANTS_H
#define NOOBLINK_HEADER_CONSTANTS_H

// std
#include <cstdint>
#include <iomanip>
#include <ostream>
#include <utility>

namespace nooblink {

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
  // No machine
  e_None = 0,
  // AT&T WE 32100
  e_M32 = 1,
  // SUN SPARC
  e_Sparc = 2,
  // Intel 80386
  e_386 = 3,
  // Motorola m68k family
  e_68k = 4,
  // Motorola m88k family
  e_88k = 5,
  // Intel 80486
  e_486 = 6,
  // Intel 80860
  e_860 = 7,
  // MIPS R3000 (officially, big-endian only)
  e_Mips = 8,
  // IBM System/370
  e_S370 = 9,
  // MIPS R3000 little-endian (Oct 4 1999 Draft) Deprecated
  e_Mips_rs3_le = 10,
  // Reserved
  e_res011 = 11,
  // Reserved
  e_res012 = 12,
  // Reserved
  e_res013 = 13,
  // Reserved
  e_res014 = 14,
  // HPPA
  e_Parisc = 15,
  // Reserved
  e_res016 = 16,
  // Fujitsu VPP500
  e_Vpp550 = 17,
  // Sun's "v8plus"
  e_Sparc32plus = 18,
  // Intel 80960
  e_960 = 19,
  // PowerPC
  e_Ppc = 20,
  // 64-bit PowerPC
  e_Ppc64 = 21,
  // IBM S/390
  e_S390 = 22,
  // Sony/Toshiba/IBM SPU
  e_Spu = 23,
  // Reserved
  e_res024 = 24,
  // Reserved
  e_res025 = 25,
  // Reserved
  e_res026 = 26,
  // Reserved
  e_res027 = 27,
  // Reserved
  e_res028 = 28,
  // Reserved
  e_res029 = 29,
  // Reserved
  e_res030 = 30,
  // Reserved
  e_res031 = 31,
  // Reserved
  e_res032 = 32,
  // Reserved
  e_res033 = 33,
  // Reserved
  e_res034 = 34,
  // Reserved
  e_res035 = 35,
  // NEC V800 series
  e_V800 = 36,
  // Fujitsu FR20
  e_Fr20 = 37,
  // TRW RH32
  e_Rh32 = 38,
  // MCore
  e_Mcore = 39,
  // ARM
  e_Arm = 40,
  // Digital Alpha
  e_Old_alpha = 41,
  // Renesas (formerly Hitachi) / SuperH SH
  e_Sh = 42,
  // SPARC v9 64-bit
  e_Sparcv9 = 43,
  // Siemens Tricore embedded processor
  e_Tricore = 44,
  // ARC Cores
  e_Arc = 45,
  // Renesas (formerly Hitachi) H8/300
  e_H8_300 = 46,
  // Renesas (formerly Hitachi) H8/300H
  e_H8_300h = 47,
  // Renesas (formerly Hitachi) H8S
  e_H8s = 48,
  // Renesas (formerly Hitachi) H8/500
  e_H8_500 = 49,
  // Intel IA-64 Processor
  e_Ia_64 = 50,
  // Stanford MIPS-X
  e_Mips_x = 51,
  // Motorola Coldfire
  e_Coldfire = 52,
  // Motorola M68HC12
  e_68hc12 = 53,
  // Fujitsu Multimedia Accelerator
  e_Mma = 54,
  // Siemens PCP
  e_Pcp = 55,
  // Sony nCPU embedded RISC processor
  e_Ncpu = 56,
  // Denso NDR1 microprocessor
  e_Ndr1 = 57,
  // Motorola Star*Core processor
  e_Starcore = 58,
  // Toyota ME16 processor
  e_Me16 = 59,
  // STMicroelectronics ST100 processor
  e_St100 = 60,
  // Advanced Logic Corp. TinyJ embedded processor
  e_Tinyj = 61,
  // Advanced Micro Devices X86-64 processor
  e_X86_64 = 62,
  // Sony DSP Processor
  e_Pdsp = 63,
  // Digital Equipment Corp. PDP-10
  e_Pdp10 = 64,
  // Digital Equipment Corp. PDP-11
  e_Pdp11 = 65,
  // Siemens FX66 microcontroller
  e_Fx66 = 66,
  // STMicroelectronics ST9+ 8/16-bit microcontroller
  e_St9plus = 67,
  // STMicroelectronics ST7 8-bit microcontroller
  e_St7 = 68,
  // Motorola MC68HC16 Microcontroller
  e_68hc16 = 69,
  // Motorola MC68HC11 Microcontroller
  e_68hc11 = 70,
  // Motorola MC68HC08 Microcontroller
  e_68hc08 = 71,
  // Motorola MC68HC05 Microcontroller
  e_68hc05 = 72,
  // Silicon Graphics SVx
  e_Svx = 73,
  // STMicroelectronics ST19 8-bit cpu
  e_St19 = 74,
  // Digital VAX
  e_Vax = 75,
  // Axis Communications 32-bit embedded processor
  e_Cris = 76,
  // Infineon Technologies 32-bit embedded cpu
  e_Javelin = 77,
  // Element 14 64-bit DSP processor
  e_Firepath = 78,
  // LSI Logic's 16-bit DSP processor
  e_Zsp = 79,
  // Donald Knuth's educational 64-bit processor
  e_Mmix = 80,
  // Harvard's machine-independent raw
  e_Huany = 81,
  // SiTera Prism
  e_Prism = 82,
  // Atmel AVR 8-bit microcontroller
  e_Avr = 83,
  // Fujitsu FR30
  e_Fr30 = 84,
  // Mitsubishi D10V
  e_D10v = 85,
  // Mitsubishi D30V
  e_D30v = 86,
  // Renesas V850 (formerly NEC V850)
  e_V850 = 87,
  // Renesas M32R (formerly Mitsubishi M32R)
  e_M32r = 88,
  // Matsushita MN10300
  e_Mn10300 = 89,
  // Matsushita MN10200
  e_Mn10200 = 90,
  // picoJava
  e_Pj = 91,
  // OpenRISC 1000 32-bit embedded processor
  e_Or1k = 92,
  // ARC Cores Tangent-A5
  e_Arc_a5 = 93,
  // Tensilica Xtensa Architecture
  e_Xtensa = 94,
  // Alphamosaic VideoCore processor
  e_Videocore = 95,
  // Thompson Multimedia General Purpose Processor
  e_Tmm_gpp = 96,
  // National Semiconductor 32000 series
  e_Ns32k = 97,
  // Tenor Network TPC processor
  e_Tpc = 98,
  // Trebia SNP 1000 processor
  e_Snp1k = 99,
  // STMicroelectronics ST200 microcontroller
  e_St200 = 100,
  // Ubicom IP2022 micro controller
  e_Ip2k = 101,
  // MAX Processor
  e_Max = 102,
  // National Semiconductor CompactRISC
  e_Cr = 103,
  // Fujitsu F2MC16
  e_F2mc16 = 104,
  // TI msp430 micro controller
  e_Msp430 = 105,
  // ADI Blackfin
  e_Blackfin = 106,
  // S1C33 Family of Seiko Epson processors
  e_Se_c33 = 107,
  // Sharp embedded microprocessor
  e_Sep = 108,
  // Arca RISC Microprocessor
  e_Arca = 109,
  // Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University
  e_Unicore = 110,
  // eXcess: 16/32/64-bit configurable embedded CPU
  e_Excess = 111,
  // Icera Semiconductor Inc. Deep Execution Processor
  e_Dxp = 112,
  // Altera Nios II soft-core processor
  e_Altera_nios2 = 113,
  // National Semiconductor CRX
  e_Crx = 114,
  // Motorola XGATE embedded processor
  e_Xgate = 115,
  // Infineon C16x/XC16x processor
  e_C166 = 116,
  // Renesas M16C series microprocessors
  e_M16c = 117,
  // Microchip Technology dsPIC30F Digital Signal Controller
  e_Dspic30f = 118,
  // Freescale Communication Engine RISC core
  e_Ce = 119,
  // Renesas M32C series microprocessors
  e_M32c = 120,
  // Reserved
  e_res121 = 121,
  // Reserved
  e_res122 = 122,
  // Reserved
  e_res123 = 123,
  // Reserved
  e_res124 = 124,
  // Reserved
  e_res125 = 125,
  // Reserved
  e_res126 = 126,
  // Reserved
  e_res127 = 127,
  // Reserved
  e_res128 = 128,
  // Reserved
  e_res129 = 129,
  // Reserved
  e_res130 = 130,
  // Altium TSK3000 core
  e_Tsk3000 = 131,
  // Freescale RS08 embedded processor
  e_Rs08 = 132,
  // Reserved
  e_res133 = 133,
  // Cyan Technology eCOG2 microprocessor
  e_Ecog2 = 134,
  // Sunplus S+core7 RISC processor
  e_Score7 = 135,
  // New Japan Radio (NJR) 24-bit DSP Processor
  e_Dsp24 = 136,
  // Broadcom VideoCore III processor
  e_Videocore3 = 137,
  // RISC processor for Lattice FPGA architecture
  e_Latticemico32 = 138,
  // Seiko Epson C17 family
  e_Se_c17 = 139,
  // Texas Instruments TMS320C6000 DSP family
  e_Ti_c6000 = 140,
  // Texas Instruments TMS320C2000 DSP family
  e_Ti_c2000 = 141,
  // Texas Instruments TMS320C55x DSP family
  e_Ti_c5500 = 142,
  // Reserved
  e_res143 = 143,
  // Reserved
  e_res144 = 144,
  // Reserved
  e_res145 = 145,
  // Reserved
  e_res146 = 146,
  // Reserved
  e_res147 = 147,
  // Reserved
  e_res148 = 148,
  // Reserved
  e_res149 = 149,
  // Reserved
  e_res150 = 150,
  // Reserved
  e_res151 = 151,
  // Reserved
  e_res152 = 152,
  // Reserved
  e_res153 = 153,
  // Reserved
  e_res154 = 154,
  // Reserved
  e_res155 = 155,
  // Reserved
  e_res156 = 156,
  // Reserved
  e_res157 = 157,
  // Reserved
  e_res158 = 158,
  // Reserved
  e_res159 = 159,
  // STMicroelectronics 64bit VLIW Data Signal Processor
  e_Mmdsp_plus = 160,
  // Cypress M8C microprocessor
  e_Cypress_m8c = 161,
  // Renesas R32C series microprocessors
  e_R32c = 162,
  // NXP Semiconductors TriMedia architecture family
  e_Trimedia = 163,
  // QUALCOMM DSP6 Processor
  e_Qdsp6 = 164,
  // Intel 8051 and variants
  e_8051 = 165,
  // STMicroelectronics STxP7x family
  e_Stxp7x = 166,
  // Andes Technology compact code size embedded RISC processor family
  e_Nds32 = 167,
  // Cyan Technology eCOG1X family
  e_Ecog1x = 168,
  // Dallas Semiconductor MAXQ30 Core Micro-controllers
  e_Maxq30 = 169,
  // New Japan Radio (NJR) 16-bit DSP Processor
  e_Ximo16 = 170,
  // M2000 Reconfigurable RISC Microprocessor
  e_Manik = 171,
  // Cray Inc. NV2 vector architecture
  e_Craynv2 = 172,
  // Renesas RX family
  e_Rx = 173,
  // Imagination Technologies Meta processor architecture
  e_Metag = 174,
  // MCST Elbrus general purpose hardware architecture
  e_Mcst_elbrus = 175,
  // Cyan Technology eCOG16 family
  e_Ecog16 = 176,
  // National Semiconductor CompactRISC 16-bit processor
  e_Cr16 = 177,
  // Freescale Extended Time Processing Unit
  e_Etpu = 178,
  // Infineon Technologies SLE9X core
  e_Sle9x = 179,
  // Intel L1OM
  e_L1om = 180,
  // Intel K1OM
  e_K1om = 181,
  // Reserved by Intel
  e_Intel182 = 182,
  // ARM 64-bit architecture
  e_Aarch64 = 183,
  // Reserved by ARM
  e_Arm184 = 184,
  // Atmel Corporation 32-bit microprocessor family
  e_Avr32 = 185,
  // STMicroeletronics STM8 8-bit microcontroller
  e_Stm8 = 186,
  // Tilera TILE64 multicore architecture family
  e_Tile64 = 187,
  // Tilera TILEPro multicore architecture family
  e_Tilepro = 188,
  // Xilinx MicroBlaze 32-bit RISC soft processor core
  e_Microblaze = 189,
  // NVIDIA CUDA architecture
  e_Cuda = 190,
  // Tilera TILE-Gx multicore architecture family
  e_Tilegx = 191,
  // Renesas RL78 family.
  e_Rl78 = 197,
  // Renesas 78K0R.
  e_78k0r = 199,
  // Reserved by Intel
  e_Intel205 = 205,
  // Reserved by Intel
  e_Intel206 = 206,
  // Reserved by Intel
  e_Intel207 = 207,
  // Reserved by Intel
  e_Intel208 = 208,
  // Reserved by Intel
  e_Intel209 = 209,
  // Controls and Data Services VISIUM core processor
  e_Visium = 221,
  // Moxie processor family
  e_Moxie = 223,
};
std::ostream &operator<<(std::ostream &os, const Architecture &architecture);

enum class SpecialSectionIndex : uint16_t {
  // This value marks an undefined, missing, irrelevant, or otherwise meaningless section reference. For example, a
  // symbol `defined' relative to section number SHN_UNDEF is an undefined symbol
  e_Undefined = 0,
  // This value specifies absolute values for the corresponding reference. For example, symbols defined relative to
  // section number SHN_ABS have absolute values and are not affected by relocation.
  e_Abs = 0xfff1,
  // Symbols defined relative to this section are common symbols, such as FORTRAN COMMON or unallocated C external
  // variables.
  e_Common = 0xfff2,
};
std::ostream &operator<<(std::ostream &os, const SpecialSectionIndex &sectionIndex);

enum class SectionType : uint32_t {
  e_Null = 0,
  // Info defined by the program
  e_Progbits = 1,
  // Linker symbol table
  e_Symtab = 2,
  // String table
  e_Strtab = 3,
  // "Rela" type relocation
  e_Rela = 4,
  // Symbol hash table
  e_Hash = 5,
  // Dynamic linking table
  e_Dynamic = 6,
  // Note info
  e_Note = 7,
  // Uninitialized space; does not occupy any space in the file
  e_Nobits = 8,
  // "Rel" type relocation
  e_Rel = 9,
  // Reserved
  e_Shlib = 10,
  // Dynamic loader symbol table
  e_Dynsym = 11,
  e_InitArray = 14,
  e_FiniArray = 15,
  e_PreinitArray = 16,
  e_Group = 17,
  e_Symtab_shndx = 18,
  // Low bound for OS specific: e_LoOs = 0x60000000,
  e_SunCapchain = 0x6fffffef,
  e_SunCapInfo = 0x6ffffff0,
  e_SunSymSort = 0x6ffffff1,
  e_SunTlsSort = 0x6ffffff2,
  e_SunLdynSym = 0x6ffffff3,
  e_SunDof = 0x6ffffff4,
  e_SunCap = 0x6ffffff5,
  e_SunSignature = 0x6ffffff6,
  e_SunAnnotate = 0x6ffffff7,
  e_SunDebugStr = 0x6ffffff8,
  e_SunDebug = 0x6ffffff9,
  e_SunMove = 0x6ffffffa,
  e_SunCOMDAT = 0x6ffffffb,
  e_SunSymInfo = 0x6ffffffc,
  e_SunVerDef = 0x6ffffffd,
  e_SunVerneed = 0x6ffffffe,
  e_SunVerSym = 0x6fffffff,
  // Top bound for OS specific: e_HiOs = 0x6fffffff,
  // Low bound for CPU specific: e_LoProc = 0x70000000,
  e_SparcGotData = 0x70000000,
  e_AMD64Unwind = 0x70000001,
  // Top bound for CPU specific: e_HiProc = 0x7fffffff,
  // Low bound for User specific: e_LoUser = 0x80000000,
  // Top bound for User specific: e_HiUser = 0xffffffff,
};
std::ostream &operator<<(std::ostream &os, const SectionType &sectionType);

enum class SectionFlag : uint64_t {
  // Writable
  e_Write = 0x1,
  // Occupies memory at runtime
  e_Alloc = 0x2,
  // Executable
  e_Execinstr = 0x4,
  // Might be merged
  e_Merge = 0x10,
  // Contains C-style string
  e_Strings = 0x20,
  e_Info_link = 0x40,
  // Preserve order after combining
  e_Link_order = 0x80,
  e_Os_nonconforming = 0x100,
  e_Group = 0x200,
  // Section hold thread local data
  e_Tls = 0x400,
  e_Maskos = 0x0ff00000,
  e_Maskproc = 0xf0000000,
};
std::ostream &operator<<(std::ostream &os, const SectionFlag &sectionFlag);

enum class SymbolBinding : uint8_t {
  // Local symbols are not visible outside the object file containing their definition. Local symbols of the same name
  // may exist in multiple files without interfering with each other.
  e_Local = 0,
  // Global symbols are visible to all object files being combined. One file's definition of a global symbol will
  // satisfy another file's undefined reference to the same global symbol.
  e_Global = 1,
  // Weak symbols resemble global symbols, but their definitions have lower precedence.
  e_Weak = 2,
  // Low and upper bound for os specific
  // e_LoOs = 10,
  // e_HiOs = 12,
  // Low and upper bound for CPU specific
  // e_LoProc = 13,
  // e_HiProc = 15,
  e_Invalid,
};
std::ostream &operator<<(std::ostream &os, const SymbolBinding &symbolBinding);

enum class SymbolType : uint8_t {
  // The symbol's type is not specified.
  e_NoType = 0,
  // The symbol is associated with a data object, such as a variable, an array, and so on.
  e_Object = 1,
  // The symbol is associated with a function or other executable code.
  e_Func = 2,
  // The symbol is associated with a section. Symbol table entries of this type exist primarily for
  // relocation and normally have e_Local binding.
  e_Section = 3,
  // Conventionally, the symbol's name gives the name of the source file associated with the object file. A file symbol
  // has STB_LOCAL binding, its section index is SHN_ABS, and it precedes the other e_Local symbols for the file, if it
  // is present.
  e_File = 4,
  // The symbol labels an uninitialized common block
  e_Common = 5,
  // Low and upper bound for OS specific
  // e_LOOS = 10,
  // e_HIOS = 12,
  // Low and upper bound for CPU specific
  // e_LOPROC = 13,
  // e_HIPROC = 15,
  e_Invalid,

};
std::ostream &operator<<(std::ostream &os, const SymbolType &symbolType);

enum class SymbolVisibility : uint8_t {
  // The visibility of symbols with the e_Default attribute is as specified by the symbol's binding type. That is,
  // global and weak symbols are visible outside their defining component (executable file or shared object). Local
  // symbols are hidden, as described below. Global and weak symbols are also preemptable, that is, they may be
  // preempted by definitions of the same name in another component.
  e_Default = 0,
  // The meaning of this visibility attribute may be defined by processor supplements to further constrain hidden
  // symbols. A processor supplement's definition should be such that generic tools can safely treat internal symbols as
  // hidden. An internal symbol contained in a relocatable object must be either removed or converted to STB_LOCAL
  // binding by the link-editor when the relocatable object is included in an executable file or shared object.
  e_Internal = 1,
  // A symbol defined in the current component is hidden if its name is not visible to other components. Such a symbol
  // is necessarily protected. This attribute may be used to control the external interface of a component. Note that an
  // object named by such a symbol may still be referenced from another component if its address is passed outside.
  e_Hidden = 2,
  // A symbol defined in the current component is protected if it is visible in other components but not preemptable,
  // meaning that any reference to such a symbol from within the defining component must be resolved to the definition
  // in that component, even if there is a definition in another component that would preempt by the default rules. A
  // symbol with e_Local binding may not have e_Protected visibility. If a symbol definition with e_Protected visibility
  // from a shared object is taken as resolving a reference from an executable or another shared object, the 'undef'
  // symbol table entry created has e_Default visibility.
  e_Protected = 3,
  e_Invalid,
};
std::ostream &operator<<(std::ostream &os, const SymbolVisibility &symbolVisibility);

}  // namespace nooblink

inline std::ostream &nooblink::operator<<(std::ostream &os, const AddressClass &addressClass) {
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

inline std::ostream &nooblink::operator<<(std::ostream &os, const Endianness &endianness) {
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

inline std::ostream &nooblink::operator<<(std::ostream &os, const ObjectFileType &objectFileType) {
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

inline std::ostream &nooblink::operator<<(std::ostream &os, const Abi &abi) {
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

inline std::ostream &nooblink::operator<<(std::ostream &os, const Architecture &architecture) {
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
      return os << "Harvard's machine-independent raw";
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
      return os << "Microprocessor series from PKU-Unity Ltd. and MPRC of "
                   "Peking University";
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
      return os << "Andes Technology compact code size embedded RISC processor "
                   "family";
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

inline std::ostream &nooblink::operator<<(std::ostream &os, const SpecialSectionIndex &sectionIndex) {
  switch (sectionIndex) {
    case SpecialSectionIndex::e_Undefined:
      return os << "Undef";
    case SpecialSectionIndex::e_Abs:
      return os << "Abs";
    case SpecialSectionIndex::e_Common:
      return os << "Common";
    default:
      break;
  }
}

inline std::ostream &nooblink::operator<<(std::ostream &os, const SectionType &sectionType) {
  switch (sectionType) {
    case SectionType::e_Null:
      return os << "Null";
    case SectionType::e_Progbits:
      return os << "Progbits";
    case SectionType::e_Symtab:
      return os << "Symtab";  // Symbol table
    case SectionType::e_Strtab:
      return os << "Strtab";  // String table
    case SectionType::e_Rela:
      return os << "Elf64_Rela";  // Relocation with addend
    case SectionType::e_Hash:
      return os << "Hash";  // Symbol hash table
    case SectionType::e_Dynamic:
      return os << "Dynamic";  // Dynamic linking info
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
    case SectionType::e_InitArray:
      return os << "InitArray";
    case SectionType::e_FiniArray:
      return os << "FiniArray";
    case SectionType::e_PreinitArray:
      return os << "PreinitArray";
    case SectionType::e_Group:
      return os << "Group";
    case SectionType::e_Symtab_shndx:
      return os << "Symtab_shndx";
    case SectionType::e_SunCapchain:
      return os << "SunCapchain";
    case SectionType::e_SunCapInfo:
      return os << "SunCapInfo";
    case SectionType::e_SunSymSort:
      return os << "SunSymSort";
    case SectionType::e_SunTlsSort:
      return os << "SunTlsSort";
    case SectionType::e_SunLdynSym:
      return os << "SunLdynSym";
    case SectionType::e_SunDof:
      return os << "SunDof";
    case SectionType::e_SunCap:
      return os << "SunCap";
    case SectionType::e_SunSignature:
      return os << "SunSignature";
    case SectionType::e_SunAnnotate:
      return os << "SunAnnotate";
    case SectionType::e_SunDebugStr:
      return os << "SunDebugStr";
    case SectionType::e_SunDebug:
      return os << "SunDebug";
    case SectionType::e_SunMove:
      return os << "SunMove";
    case SectionType::e_SunCOMDAT:
      return os << "SunCOMDAT";
    case SectionType::e_SunSymInfo:
      return os << "SunSymInfo";
    case SectionType::e_SunVerDef:
      return os << "SunVerDef";
    case SectionType::e_SunVerneed:
      return os << "SunVerneed";
    case SectionType::e_SunVerSym:
      return os << "SunVerSym";
    case SectionType::e_SparcGotData:
      return os << "SparcGotData";
    case SectionType::e_AMD64Unwind:
      return os << "AMD64Unwind";
    default:
      return os << "Unknown (0x" << std::hex << std::setw(8) << std::setfill('0') << std::to_underlying(sectionType)
                << ")";
  }
}

inline std::ostream &nooblink::operator<<(std::ostream &os, const SectionFlag &sectionFlag) {
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

inline std::ostream &nooblink::operator<<(std::ostream &os, const SymbolBinding &symbolBinding) {
  switch (symbolBinding) {
    case SymbolBinding::e_Local:
      return os << "Local";
    case SymbolBinding::e_Global:
      return os << "Global";
    case SymbolBinding::e_Weak:
      return os << "Weak";
    case SymbolBinding::e_Invalid:
    default:
      return os << "Invalid";
  }
}

inline std::ostream &nooblink::operator<<(std::ostream &os, const SymbolType &symbolType) {
  switch (symbolType) {
    case SymbolType::e_NoType:
      return os << "NoType";
    case SymbolType::e_Object:
      return os << "Object";
    case SymbolType::e_Func:
      return os << "Func";
    case SymbolType::e_Section:
      return os << "Section";
    case SymbolType::e_File:
      return os << "File";
    case SymbolType::e_Common:
      return os << "Common";
    default:
    case SymbolType::e_Invalid:
      return os << "Invalid";
  }
}

inline std::ostream &nooblink::operator<<(std::ostream &os, const SymbolVisibility &symbolVisibility) {
  switch (symbolVisibility) {
    case SymbolVisibility::e_Default:
      return os << "Default";
    case SymbolVisibility::e_Internal:
      return os << "Internal";
    case SymbolVisibility::e_Hidden:
      return os << "Hidden";
    case SymbolVisibility::e_Protected:
      return os << "Protected";
    default:
    case SymbolVisibility::e_Invalid:
      return os << "Invalid";
  }
}

#endif  // NOOBLINK_HEADER_CONSTANTS_H
