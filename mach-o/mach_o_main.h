#include <stdio.h>
#include <stdlib.h>
#include <mach/machine.h>

#define MH_MAGIC    0xFEEDFACE //32-bit Mach-O binary 
#define MH_MAGIC_64 0xFEEDFACF //64-bit Mach-O binary 
#define MH_CIGAM    0xCEFAEDFE //NXSwapInt(MH_MAGIC)
#define MH_CIGAM_64 0xCFFAEDFE //NXSwapInt(MH_MAGIC_64)

//28 bytes
#pragma pack(push,1)
struct mach_header{
    uint32_t magic;             //Mach magic number identifier
	cpu_type_t cputype;         //CPU specifier  
	cpu_subtype_t cpusubtype;   //Machine specifier
	uint32_t filetype;          //Type of file
	uint32_t ncmds;             //Number of load commands  
	uint32_t sizeofcmds;        //Size of all load commands
	uint32_t flags;             //Flags 
};
#pragma pack(pop)

//32 bytes
#pragma pack(push, 1)
struct mach_header_64 {
	uint32_t magic;             //Mach magic number identifier
	cpu_type_t cputype;         //CPU specifier
	cpu_subtype_t cpusubtype;   //Machine specifier
	uint32_t filetype;          //Type of file
	uint32_t ncmds;             //Number of load commands
	uint32_t sizeofcmds;        //The size of all the load commands
	uint32_t flags;             //Flags
	uint32_t reserved;          //Reserved
};
#pragma pack(pop)


bool is_mach_o(FILE* p_file);
bool is_mach_o_64(FILE* p_file);
const char* get_mach_o_cputype_str(cpu_type_t cpu_type, bool is_64);
const char* get_mach_o_cpusubtype_str(int cpusubtype);
const char* get_mach_o_filetype_str(uint32_t filetype);
//print_filetype() for flag description
void get_mach_o_header(FILE* p_file);
void print_mach_o_32_header_info(const mach_header* mach_header);
void print_mach_o_64_header_info(const mach_header_64* mach_header);
void start_analyse_mach_o(FILE* p_file);