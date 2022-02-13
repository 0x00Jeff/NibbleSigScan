#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include"sigscan.h"

int main(void){

	char arr[] = {0x19, 0x28, 0x37, 0x46, 0x55, 0x64, 0x73, 0x82, 0x91, 0x00};

	char sig[] = {0x05, 0x04, 0x00, 0x82};

	// higher nibble in th first nibble should be correct
	// as well as lower
	// this is the equivalent of {0x6?, 0x?8} sig
	char *mask = "ll?x";

	void *found = NibbleSigScan(arr, sizeof(arr), sig, sizeof(sig), mask, strlen(mask));
	if(!found){
		fprintf(stderr, "couldn't find signature\n");
		return -1;
	}

	printf("sig found @ index %p\n", (void *)((int64_t)found - (int64_t)arr));

	return 0;
}
