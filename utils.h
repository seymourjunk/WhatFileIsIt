#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_binary(const int32_t num);
void print_hex(const uint8_t* arr, uint32_t num);
void convert_epoch_timestamp(char* str_ptr, size_t size, uint32_t timestamp);
void get_version_encoded_in_nibbles(uint32_t version, uint16_t* x, uint8_t* y, uint8_t* z);