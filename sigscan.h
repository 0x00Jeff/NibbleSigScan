#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stddef.h>



// not my proudest function declaration
void *NibbleSigScan(void *start, size_t range, unsigned char *pattern, size_t pattern_len, char *mask)
