#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stddef.h>
#include"sigscan.h"

// There are 16 possible values for a nibble
#define NIBBLE_VALUES 16 

void *NibbleSigScan(void *start, size_t range, unsigned char *pattern, size_t pattern_len, char *mask) {
    if (!start || !pattern || !mask || pattern_len == 0) return NULL;

    unsigned char *text = (unsigned char *)start;
    size_t shift_table[NIBBLE_VALUES];

    // Initialize shift table
    for (size_t i = 0; i < NIBBLE_VALUES; i++) {
        shift_table[i] = pattern_len;
    }

    // Populate shift table
    for (size_t i = 0; i < pattern_len - 1; i++) {
        unsigned char nibble = (pattern[i] & 0x0F); // Considering low nibble for shift
        shift_table[nibble] = pattern_len - i - 1;
    }

    size_t index = 0;
    while (index <= range - pattern_len) {
        ssize_t i = pattern_len - 1;
        while (i >= 0) {
            unsigned char text_nibble = text[index + i] & 0x0F; // Low nibble
            unsigned char pattern_nibble = pattern[i] & 0x0F;

            if (mask[i] == 'x' && text[index + i] != pattern[i]) break;
            if (mask[i] == 'h' && (text[index + i] & 0xF0) != (pattern[i] & 0xF0)) break;
            if (mask[i] == 'l' && text_nibble != pattern_nibble) break;

            i--;
        }
        if (i < 0) return &text[index]; // Match found

        unsigned char next_nibble = text[index + pattern_len - 1] & 0x0F;
        index += shift_table[next_nibble];
    }

    return NULL; // No match found
}
