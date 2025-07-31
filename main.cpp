#include "pe/pe_main.h"
#include "mach-o/mach_o_main.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        char* file_path = argv[1];
        printf("INFO: Get a file: %s\n", file_path);

        FILE* file = fopen(file_path, "r");

        if (!file)
        {
            perror("ERROR: fopen() failed");
            exit(1);
        }

        if (is_pe(file))
        {
            printf("INFO: This is probably a PE-file\n");
        }
        else if (is_mach_o(file))
        {
            printf("INFO: This is probably a Mach-O-file\n");
            start_analyse_mach_o(file);
        } 
        //else if (is_elf(file_path))
        //{
        //    printf("INFO: This is probably an ELF-file\n");
        //}
        else printf("ERROR: I don't know what is it...\n");

        fclose(file);
    }
    else 
    {
        printf("ERROR: Need a file\n");
        exit(1);
    }

    return 0;
}