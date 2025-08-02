#include "mach_o_main.h"
#include "../utils.h"

bool is_mach_o(FILE* p_file)
{
    //TODO: fat binaries
    uint32_t magic;
    fread(&magic, sizeof(uint32_t), 1, p_file);
    rewind(p_file);

    if ((magic == MH_MAGIC) || (magic == MH_MAGIC_64)
        || (magic == MH_CIGAM) || (magic == MH_CIGAM_64)) 
    {
        printf("Found MH_Magic: 0x%x\n", magic);
        return true;
    }

    return false;
}

bool is_mach_o_64(FILE* p_file)
{
    uint32_t magic;
    fread(&magic, 1, 4, p_file);
    rewind(p_file);

    if ((magic == MH_MAGIC) || (magic == MH_CIGAM)) return false;

    if ((magic == MH_MAGIC_64) || (magic == MH_CIGAM_64)) return true;

    //TODO: add enum for error or success status 
    return false;
}

const char* get_mach_o_cputype_str(int cpu_type, bool is_64)
{
    int mask_64 = 0x00000000;
    if (is_64) mask_64 = 0x01000000;

    if (cpu_type == (0x00000001 | mask_64))
    {
        return "VAX";
    }
    else if (cpu_type == (0x00000002 | mask_64))
    {
        return "ROMP";
    }
    else if (cpu_type == (0x00000004 | mask_64))
    {
        return "NS32032";
    }
    else if (cpu_type == (0x00000005 | mask_64))
    {
        return "NS32332";
    }
    else if (cpu_type == (0x00000006 | mask_64))
    {
        return "MC680x0";
    }
    else if (cpu_type == (0x00000007 | mask_64))
    {
        return "x86";
    }
    else if (cpu_type == (0x00000008 | mask_64))
    {
        return "MIPS";
    }
    else if (cpu_type == (0x00000009 | mask_64))
    {
        return "NS32352";
    }
    else if (cpu_type == (0x0000000B | mask_64))
    {
        return "HP-PA";
    }
    else if (cpu_type == (0x0000000C | mask_64))
    {
        return "ARM";
    }
    else if (cpu_type == (0x0000000D | mask_64))
    {
        return "MC88000";
    }
    else if (cpu_type == (0x0000000E | mask_64))
    {
        return "SPARC";
    }
    else if (cpu_type == (0x0000000F | mask_64))
    {
        return "i860 (big-endian)";
    }
    else if (cpu_type == (0x00000010 | mask_64))
    {
        return "i860 (little-endian) or maybe DEC Alpha";
    }
    else if (cpu_type == (0x00000011 | mask_64))
    {
        return "RS/6000";
    }
    else if (cpu_type == (0x00000012 | mask_64))
    {
        return "PowerPC / MC98000";
    }
    else return "Unknown Mach-O cputype";
}

const char* get_mach_o_cpusubtype_str(int cpusubtype)
{
    //There are also a lot optimized filetypes
    if (cpusubtype == 0x00000000) return "All ARM processors";
    else if (cpusubtype == 0x00000003) return "All x86 processors";
    else return "Unknown Mach-O cpusubtype";
}

const char* get_mach_o_filetype_str(uint32_t filetype)
{
    if (filetype == 0x00000001) return "Relocatable object file";
    else if (filetype == 0x00000002) return "Demand paged executable file";
    else if (filetype == 0x00000003) return "Fixed VM shared library file";
    else if (filetype == 0x00000004) return "Core file";
    else if (filetype == 0x00000005) return "Preloaded executable file";
    else if (filetype == 0x00000006) return "Dynamically bound shared library file";
    else if (filetype == 0x00000007) return "Dynamic link editor";
    else if (filetype == 0x00000008) return "Dynamically bound bundle file";
    else if (filetype == 0x00000009) return "Shared library stub for static linking only, no section contents";
    else if (filetype == 0x0000000A) return "Companion file with only debug sections";
    else if (filetype == 0x0000000B) return "x86_64 kexts";
    else if (filetype == 0x0000000C) return "A file composed of other Mach-Os to be run in the same userspace sharing a single linkedit";
    else return "Unknown Mach-O filetype";
}

const char* get_mach_o_load_command_name_str(uint32_t cmd) 
{
    if (cmd == 0x1)       return "LC_SEGMENT";
    else if (cmd == 0x2)  return "LC_SYMTAB";
    else if (cmd == 0x3)  return "LC_SYMSEG";
    else if (cmd == 0x4)  return "LC_THREAD";
    else if (cmd == 0x5)  return "LC_UNIXTHREAD";
    else if (cmd == 0x6)  return "LC_LOADFVMLIB";
    else if (cmd == 0x7)  return "LC_IDFVMLIB";
    else if (cmd == 0x8)  return "LC_IDENT";
    else if (cmd == 0x9)  return "LC_FVMFILE";
    else if (cmd == 0xa)  return "LC_PREPAGE";
    else if (cmd == 0xb)  return "LC_DYSYMTAB";
    else if (cmd == 0xc)  return "LC_LOAD_DYLIB";
    else if (cmd == 0xd)  return "LC_ID_DYLIB";
    else if (cmd == 0xe)  return "LC_LOAD_DYLINKER";
    else if (cmd == 0xf)  return "LC_ID_DYLINKER";
    else if (cmd == 0x10) return "LC_PREBOUND_DYLIB";
    else if (cmd == 0x11) return "LC_ROUTINES";
    else if (cmd == 0x12) return "LC_SUB_FRAMEWORK";
    else if (cmd == 0x13) return "LC_SUB_UMBRELLA";
    else if (cmd == 0x14) return "LC_SUB_CLIENT";
    else if (cmd == 0x15) return "LC_SUB_LIBRARY";
    else if (cmd == 0x16) return "LC_TWOLEVEL_HINTS";
    else if (cmd == 0x17) return "LC_PREBIND_CKSUM";
    else if ((0x18 | LC_REQ_DYLD) == cmd) return "LC_LOAD_WEAK_DYLIB";
    else if (cmd == 0x19) return "LC_SEGMENT_64";
    else if (cmd == 0x1a) return "LC_ROUTINES_64";
    else if (cmd == 0x1b) return "LC_UUID";
    else if ((0x1c | LC_REQ_DYLD) == cmd) return "LC_RPATH";
    else if (cmd == 0x1d) return "LC_CODE_SIGNATURE";
    else if (cmd == 0x1e) return "LC_SEGMENT_SPLIT_INFO";
    else if ((0x1f | LC_REQ_DYLD) == cmd) return "LC_REEXPORT_DYLIB";
    else if (cmd == 0x20) return "LC_LAZY_LOAD_DYLIB";
    else if (cmd == 0x21) return "LC_ENCRYPTION_INFO";
    else if ((0x22 | LC_REQ_DYLD) == cmd) return "LC_DYLD_INFO";
    else if ((0x23 | LC_REQ_DYLD) == cmd) return "LC_LOAD_UPWARD_DYLIB";
    else if (cmd == 0x24) return "LC_VERSION_MIN_MACOSX";
    else if (cmd == 0x25) return "LC_VERSION_MIN_IPHONEOS";
    else if (cmd == 0x26) return "LC_FUNCTION_STARTS";
    else if (cmd == 0x27) return "LC_DYLD_ENVIRONMENT";
    else if ((0x28 | LC_REQ_DYLD) == cmd) return "LC_MAIN";
    else if (cmd == 0x29) return "LC_DATA_IN_CODE";
    else if (cmd == 0x2a) return "LC_SOURCE_VERSION";
    else if (cmd == 0x2b) return "LC_DYLIB_CODE_SIGN_DRS";
    else if (cmd == 0x2c) return "LC_ENCRYPTION_INFO_64";
    else if (cmd == 0x2d) return "LC_LINKER_OPTION";
    else if (cmd == 0x2e) return "LC_LINKER_OPTIMIZATION_HINT";
    else if (cmd == 0x2f) return "LC_VERSION_MIN_TVOS";
    else if (cmd == 0x30) return "LC_VERSION_MIN_WATCHOS";
    else if (cmd == 0x31) return "LC_NOTE";
    else if (cmd == 0x32) return "LC_BUILD_VERSION";
    else if ((0x33 | LC_REQ_DYLD) == cmd) return "LC_DYLD_EXPORTS_TRIE";
    else if ((0x34 | LC_REQ_DYLD) == cmd) return "LC_DYLD_CHAINED_FIXUPS";
    else if ((0x35 | LC_REQ_DYLD) == cmd) return "LC_FILESET_ENTRY";
    else return "Unknown";
}

const char* get_mach_o_seg_flag_str(uint32_t flag)
{
    if (flag == 0x1) return "SG_HIGHVM";
    else if (flag == 0x2) return "SG_FVMLIB";
    else if (flag == 0x4) return "SG_NORELOC";
    else if (flag == 0x8) return "SG_PROTECTED_VERSION_1";
    else if (flag == 0x10) return "SG_READ_ONLY";
    else if (flag == 0x0) return "default";
    else return "Unknown Mach-O segment flag";
}

void get_mach_o_load_command(load_command* load_cmd, uint32_t ncmds, FILE* p_file)
{
    uint32_t offset = sizeof(mach_header_64);

    for(size_t i = 0; i < ncmds; i++)
    {
        fread(&load_cmd[i], sizeof(load_command), 1, p_file);
        offset += load_cmd[i].cmdsize;
        fseek(p_file, offset, SEEK_SET);
    }

    //rewind(p_file); ???
}

void print_mach_o_32_header_info(const mach_header* mach_header)
{
    printf("\n======== MACH_HEADER ========\n");
    printf("32-bit Mach-O file\n");
    printf("magic: 0x%x\n", mach_header->magic);
    printf("cputype: 0x%x (%s)\n", (cpu_type_t)mach_header->cputype, get_mach_o_cputype_str((int)mach_header->cputype, false));
    printf("cpusubtype: 0x%x (%s)\n", (cpu_subtype_t)mach_header->cpusubtype, get_mach_o_cpusubtype_str((int)mach_header->cpusubtype));
    printf("filetype: 0x%x (%s)\n", mach_header->filetype, get_mach_o_filetype_str(mach_header->filetype));
    printf("ncmds: %d\n", mach_header->ncmds);
    printf("sizeofcmds: %d\n", mach_header->sizeofcmds);
    printf("flags: 0x%x\n", mach_header->flags);
}

void print_mach_o_64_header_info(const mach_header_64* mach_header)
{
    printf("\n======== MACH_HEADER_64 ========\n");
    printf("64-bit Mach-O file\n");
    printf("magic: 0x%x\n", mach_header->magic); //+
    printf("cputype: 0x%x (%s)\n", (cpu_type_t)mach_header->cputype, get_mach_o_cputype_str((int)mach_header->cputype, true)); //+
    printf("cpusubtype: 0x%x (%s)\n", (cpu_subtype_t)mach_header->cpusubtype, get_mach_o_cpusubtype_str((int)mach_header->cpusubtype));//+
    printf("filetype: 0x%x (%s)\n", mach_header->filetype, get_mach_o_filetype_str(mach_header->filetype));//+
    printf("ncmds: %d\n", mach_header->ncmds);
    printf("sizeofcmds: %d\n", mach_header->sizeofcmds);
    printf("flags: "); print_binary(mach_header->flags); printf("\n");
    printf("reserved: 0x%x\n", mach_header->reserved);
}

void print_mach_o_load_command(const load_command* load_cmd, size_t ncmds)
{
    printf("\n============== LOAD COMMANDS ==============\n");
    printf("index\t\tcmd\t\tcmd_size\n");
    for (size_t i = 0; i < ncmds; i++)
    {
        printf("[%lu]\t%16s\t%d\n", i, get_mach_o_load_command_name_str(load_cmd[i].cmd), load_cmd[i].cmdsize);
    }
}

void print_mach_o_cmds_structure(const load_command* load_cmd, uint32_t ncmds, FILE* p_file, bool is_64)
{
    uint32_t offset = sizeof(mach_header_64);
    if (!is_64) offset = sizeof(mach_header);

    fseek(p_file, offset, SEEK_SET);

    for(size_t i = 0; i < ncmds; i++)
    {
        printf("\n============== [%lu] COMMAND STRUCTURE INFO ==============\n", i);
        if (load_cmd[i].cmd == LC_SEGMENT_64)
        {
            segment_command_64 seg_cmd;
            fread(&seg_cmd, sizeof(segment_command_64), 1, p_file);

            printf("cmd: 0x%x (%s)\n", seg_cmd.cmd, get_mach_o_load_command_name_str(seg_cmd.cmd));
            printf("cmdsize: %d\n", seg_cmd.cmdsize);
            printf("segname: %s\n", seg_cmd.segname);
            printf("vmaddr: 0x%016llx\n", seg_cmd.vmaddr);
            printf("vmsize: 0x%016llx\n", seg_cmd.vmsize);
            printf("fileoff: %llu\n", seg_cmd.fileoff);
            printf("filesize: %llu\n", seg_cmd.filesize);
            printf("maxprot: 0x%08x\n", seg_cmd.maxprot);
            printf("initprot: 0x%08x\n", seg_cmd.initprot);
            printf("nsects: %d\n", seg_cmd.nsects);
            printf("flags: 0x%x (%s)\n", seg_cmd.flags, get_mach_o_seg_flag_str(seg_cmd.flags));
        }
        else if (load_cmd[i].cmd == LC_SEGMENT)
        {
            segment_command seg_cmd;
            fread(&seg_cmd, sizeof(segment_command), 1, p_file);

            printf("cmd: 0x%x (%s)\n", seg_cmd.cmd, get_mach_o_load_command_name_str(seg_cmd.cmd));
            printf("cmdsize: %d\n", seg_cmd.cmdsize);
            printf("segname: %s\n", seg_cmd.segname);
            printf("vmaddr: 0x%08x\n", seg_cmd.vmaddr);
            printf("vmsize: 0x%08x\n", seg_cmd.vmsize);
            printf("fileoff: %d\n", seg_cmd.fileoff);
            printf("filesize: %d\n", seg_cmd.filesize);
            printf("maxprot: 0x%08x\n", seg_cmd.maxprot);
            printf("initprot: 0x%08x\n", seg_cmd.initprot);
            printf("nsects: %d\n", seg_cmd.nsects);
            printf("flags: 0x%x (%s)\n", seg_cmd.flags, get_mach_o_seg_flag_str(seg_cmd.flags));
        }
        else if (load_cmd[i].cmd == LC_UUID)
        {
            uuid_command uuid_cmd;
            fread(&uuid_cmd, sizeof(uuid_command), 1, p_file);
            printf("cmd: 0x%x (%s)\n", uuid_cmd.cmd, get_mach_o_load_command_name_str(uuid_cmd.cmd));
            printf("cmdsize: %u\n", uuid_cmd.cmdsize);
            printf("uuid: ");
            print_hex(uuid_cmd.uuid, 16);

        }
        else if (load_cmd[i].cmd == LC_CODE_SIGNATURE ||
                load_cmd[i].cmd == LC_SEGMENT_SPLIT_INFO ||
                load_cmd[i].cmd == LC_FUNCTION_STARTS ||
                load_cmd[i].cmd == LC_DATA_IN_CODE ||
                load_cmd[i].cmd == LC_DYLIB_CODE_SIGN_DRS ||
                load_cmd[i].cmd == LC_LINKER_OPTIMIZATION_HINT ||
                load_cmd[i].cmd == LC_DYLD_EXPORTS_TRIE ||
                load_cmd[i].cmd == LC_DYLD_CHAINED_FIXUPS)
        {
            linkedit_data_command le_data_cmd;
            fread(&le_data_cmd, sizeof(linkedit_data_command), 1, p_file);
            printf("cmd: 0x%x (%s)\n", le_data_cmd.cmd, get_mach_o_load_command_name_str(le_data_cmd.cmd));
            printf("cmdsize: %d\n", le_data_cmd.cmdsize);
            printf("dataoff: %d\n", le_data_cmd.dataoff);
            printf("datasize: %d\n", le_data_cmd.datasize);
        }
        else printf("Unknown\n");
        
        offset += load_cmd[i].cmdsize;
        fseek(p_file, offset, SEEK_SET);
    }

}

void start_analyse_mach_o(FILE* p_file)
{
    bool is_64 = is_mach_o_64(p_file);
    if (is_64)
    {
        //get mach-o header
        mach_header_64 mach_header;
        fread(&mach_header, sizeof(mach_header_64), 1, p_file);
        print_mach_o_64_header_info(&mach_header);

        //get load commands
        load_command load_cmds[mach_header.ncmds];
        get_mach_o_load_command(load_cmds, mach_header.ncmds, p_file);
        print_mach_o_load_command(load_cmds, mach_header.ncmds);

        //get section
        print_mach_o_cmds_structure(load_cmds, mach_header.ncmds, p_file, is_64);
    }
    else 
    {
        mach_header mach_header;
        fread(&mach_header, sizeof(mach_header_64), 1, p_file);
    }
}