#include <stdio.h>
#include <stdlib.h>
#include <mach/machine.h>
#include <mach-o/loader.h>


bool is_mach_o(FILE* p_file);
bool is_mach_o_64(FILE* p_file);
const char* get_mach_o_cputype_str(cpu_type_t cpu_type, bool is_64);
const char* get_mach_o_cpusubtype_str(int cpusubtype);
const char* get_mach_o_filetype_str(uint32_t filetype);
const char* get_mach_o_load_command_name_str(uint32_t cmd);
const char* get_mach_o_seg_flag_str(uint32_t flag);
const char* get_mach_o_platform_str(uint32_t platform);
const char* get_mach_o_tool_str(uint32_t tool);
void get_mach_o_load_command(load_command* load_cmd, uint32_t ncmds, FILE* p_file);
//print_filetype() for flag description
void get_mach_o_header(FILE* p_file);
void print_mach_o_32_header_info(const mach_header* mach_header);
void print_mach_o_64_header_info(const mach_header_64* mach_header);
void print_mach_o_load_command(const load_command* load_cmd);
void print_mach_o_cmds_structure(const load_command* load_cmd, uint32_t ncmds, FILE* p_file); //need store it later
void start_analyse_mach_o(FILE* p_file);