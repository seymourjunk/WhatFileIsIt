#include "pe_main.h"


bool is_pe(FILE* p_file)
{
    uint16_t magic;
    fread(&magic, 1, 2, p_file);
    rewind(p_file);

    if (magic == PE_MAGIC) 
    {
        printf("Found e_magic: 0x%x\n", magic);
        //TODO: also PE header
        return true;
    }

    return false;
}