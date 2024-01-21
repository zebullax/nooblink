# Nooblink

Write a simplified (:poop:) linker from more or less scratch

**Supported**
ELF Low endian 64 bits

## Dev steps
- :point_right: Decode header & sections
- :bow: Display symbols defined and undefined 
- :bow: Handle multiple object files 
- :bow: Describe layout of the result file 
- :bow: Resolve symbol references
- :bow: Relocate entries

## Todo
~~- (WIP) Introduce an object file type to wrap over vocabulary types as they get vivifed from decoding the header~~
- Write a Context` component that keep state of current linking session, this should be passed around or installed, so that client can find out what offset to apply to object files for example...

## Timeline

- 01/21 - Decode name of section header from the string table
  ````json 
   {
    "ELFHeader": {
      "abi": "None",
      "abiVersion": 0,
      "addressClass": "64bits",
      "architecture": "Advanced Micro Devices X86-64 processor",
      "endianness": "LowEndian",
      "executionAddress": "0x00015860",
      "flags": "0x0000",
      "headerSize": 64,
      "headerVersion": 1,
      "objectFileType": "Shared",
      "objectFileVersion": 1,
      "padding": "       ",
      "programTableAddress": "0x00000040",
      "programTableCount": 7,
      "programTableSize": 56,
      "sectionNameIndex": 25,
      "sectionTableAddress": "0x001175d8",
      "sectionTableCount": 26,
      "sectionTableSize": 64
    },
    "sectionHeaders": [
      {
        "content": {
          "addr": 0,
          "addrAlign": 0,
          "entrySize": 0,
          "flags": "[]",
          "info": 0,
          "link": 0,
          "nameIndex": 0,
          "offset": 0,
          "size": 0,
          "type": "Null"
        },
        "name": ""
      },
      { 
        "...": "..."
      },
      {
        "content": {
          "addr": 0,
          "addrAlign": 1,
          "entrySize": 0,
          "flags": "[]",
          "info": 0,
          "link": 0,
          "nameIndex": 1,
          "offset": 1144064,
          "size": 211,
          "type": "Strtab"
        },
        "name": ".shstrtab"
      }
    ]
  }
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

- 01/08 - ELF header decoded, can search for section header entry of a particular type
  ````text
  {"Abi":"None","AbiVersion":0,"AddressClass":"64bits","Architecture":"Advanced Micro Devices X86-64 processor","Endianness":"LowEndian","ExecutionAddress":"0x00015860","Flags":"0x0000","HeaderSize":64,"HeaderVersion":1,"ObjectFileType":"Shared","ObjectFileVersion":1,"Padding":"       ","ProgramTableAddress":"0x00000040","ProgramTableCount":7,"ProgramTableSize":56,"SectionNameIndex":25,"SectionTableAddress":"0x001175d8","SectionTableCount":26,"SectionTableSize":64}
  Found 'Strtab' entry at: 0x1089fe6d8
  Found 'Strtab' entry at: 0x1089fec18
  ````
