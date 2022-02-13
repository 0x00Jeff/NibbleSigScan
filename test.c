#include<stdio.h>
#include<string.h>
#include<stdint.h>

typedef struct {
	unsigned char low:4;
	unsigned char high:4;
} byte;

// not really proud of this declaration
void *NibbleSigScan(void *start, size_t range, char *sig, size_t sig_len, char *mask, size_t mask_len);
int main(void){

	char arr[] = {0x19, 0x28, 0x37, 0x46, 0x55, 0x64, 0x73, 0x82, 0x91, 0x00};

	char sig[] = {0x60};

	// higher nibble in th first nibble should be correct
	// as well as lower
	// this is the equivalent of {0x6?, 0x?8} sig
	char *mask = "x";

	void *found = NibbleSigScan(arr, sizeof(arr), sig, sizeof(sig), mask, strlen(mask));
	if(!found){
		fprintf(stderr, "couldn't find signature\n");
		return -1;
	}

	printf("sig found @ index %p\n", (void *)((int64_t)found - (int64_t)arr));

	return 0;
}
