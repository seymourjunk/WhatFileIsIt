#include "utils.h"

void print_binary(const int32_t num) {
    for (size_t i = sizeof(num) * 8; i--;)
    {
        printf("%d", (num >> i) & 1);
        if ((i % 4) == 0) printf(" ");
    }
}

void print_hex(const uint8_t* arr, uint32_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        printf("%02x", arr[i]);
    }
}

void convert_epoch_timestamp(char* str_ptr, size_t size, uint32_t timestamp)
{ 
    time_t epoch_time = timestamp;
    tm *time_info = localtime(&epoch_time);

    strftime(str_ptr, size, "%a %d-%m-%Y %H:%M:%S", time_info);
}