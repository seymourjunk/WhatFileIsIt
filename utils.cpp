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