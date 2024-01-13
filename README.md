# Nooblink
Goal: write a simplified linker from more or less scratch

**Supported**
ELF Low endian 64 bits

## Dev steps
- **Decode header & sections**
   
    *01/08* - Elf header decoded, can search for section header entry of a particular type
````
{"Abi":"None","AbiVersion":0,"AddressClass":"64bits","Architecture":"Advanced Micro Devices X86-64 processor","Endianness":"LowEndian","ExecutionAddress":"0x00015860","Flags":"0x0000","HeaderSize":64,"HeaderVersion":1,"ObjectFileType":"Shared","ObjectFileVersion":1,"Padding":"       ","ProgramTableAddress":"0x00000040","ProgramTableCount":7,"ProgramTableSize":56,"SectionNameIndex":25,"SectionTableAddress":"0x001175d8","SectionTableCount":26,"SectionTableSize":64}
Found 'Strtab' entry at: 0x1089fe6d8
Found 'Strtab' entry at: 0x1089fec18
````

- Display symbols defined and undefined 
- Handle multiple object files 
- Describe layout of the result file 
- Resolve symbol references
- Relocate entries

## Notes
- Make this into a wasm + D3 UI drag & drop multiple obj files and see how they link into final task ?
