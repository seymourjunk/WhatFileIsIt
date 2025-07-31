#include "utils.h"

void print_binary(int32_t num) {
    for (size_t i = sizeof(num) * 8; i--;)
    {
        printf("%d", (num >> i) & 1);
        if ((i % 4) == 0) printf(" ");
    }
}