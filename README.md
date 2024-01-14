# Nooblink
Goal: write a simplified linker from more or less scratch

**Supported**
ELF Low endian 64 bits

## Dev steps
- **Decode header & sections**
   
  - 01/08 - ELF header decoded, can search for section header entry of a particular type
  ````text
  {"Abi":"None","AbiVersion":0,"AddressClass":"64bits","Architecture":"Advanced Micro Devices X86-64 processor","Endianness":"LowEndian","ExecutionAddress":"0x00015860","Flags":"0x0000","HeaderSize":64,"HeaderVersion":1,"ObjectFileType":"Shared","ObjectFileVersion":1,"Padding":"       ","ProgramTableAddress":"0x00000040","ProgramTableCount":7,"ProgramTableSize":56,"SectionNameIndex":25,"SectionTableAddress":"0x001175d8","SectionTableCount":26,"SectionTableSize":64}
  Found 'Strtab' entry at: 0x1089fe6d8
  Found 'Strtab' entry at: 0x1089fec18
  ````
  - 01/14 - Extract all section headers from ELF header
  ````text
  === Elf header ===
  {"Abi":"None","AbiVersion":0,"AddressClass":"64bits","Architecture":"Advanced Micro Devices X86-64 processor","Endianness":"LowEndian","ExecutionAddress":"0x00015860","Flags":"0x0000","HeaderSize":64,"HeaderVersion":1,"ObjectFileType":"Shared","ObjectFileVersion":1,"Padding":"       ","ProgramTableAddress":"0x00000040","ProgramTableCount":7,"ProgramTableSize":56,"SectionNameIndex":25,"SectionTableAddress":"0x001175d8","SectionTableCount":26,"SectionTableSize":64}
  === Section table header ===
  {"addr":0,"addrAlign":0,"entrySize":0,"flags":"[]","info":0,"link":0,"nameIndex":0,"offset":0,"size":0,"type":"Null"}
  === Section table header ===
  {"addr":456,"addrAlign":8,"entrySize":4,"flags":"[]","info":0,"link":456,"nameIndex":15,"offset":456,"size":7352,"type":"Hash"}
  === Section table header ===
  {"addr":7808,"addrAlign":8,"entrySize":0,"flags":"[]","info":0,"link":7808,"nameIndex":11,"offset":7808,"size":5184,"type":"Unknown (0x6ffffff6)"}
  === Section table header ===
  {"addr":12992,"addrAlign":8,"entrySize":24,"flags":"[]","info":2,"link":12992,"nameIndex":21,"offset":12992,"size":19560,"type":"Dynsym"}
  ...
  ````
  
- Display symbols defined and undefined 
- Handle multiple object files 
- Describe layout of the result file 
- Resolve symbol references
- Relocate entries

## TODOs
- Introduce an object file type to wrap over vocabulary types as they get vivifed from decoding the header

## Notes
- Make this into a wasm
  - D3 UI drag & drop multiple obj files and see how they link into final task ?
