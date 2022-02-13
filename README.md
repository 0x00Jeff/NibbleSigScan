# NibbleSigScan
a signature scan program that let you specify nibble wildcards

# what does it do

unlike byte-signature scanners, it let you specify nibble wildcards with the help of a 4 mask chataters

  - `x` : whole byte has to match
  - `h` : higher nibble has to match
  - `l` : lower nibble has to match
  - `?` : ignore the whole byte

example : if you're looking to search for the pattern `{0x1?, 0x20, 0x?3}`, set the signature to `{0x10, 0x20, 0x30}`, and the mask to "hxl", this tells the program to look for a bytes that has the higher nibble equals to 0x1, followed by a `0x20` followed by a byte that has the lowest nibble equals to `0x3`

# how to use

```c
int main(void){

	char arr[] = {0x19, 0x28, 0x37, 0x46, 0x55, 0x64, 0x73, 0x82, 0x91, 0x00};

	char sig[] = {0x05, 0x04, 0x00, 0x82};

	// the lower nibble in the first byte should match
	// same thing goes for the second byte
	// 3rd byte is ingnored
	// the whole 4th byte should match
	// this is the equivalent of {0x?5, 0x4?, ??, 0x73} pattern
	char *mask = "ll?x";

	void *found = NibbleSigScan(arr, sizeof(arr), sig, sizeof(sig), mask, strlen(mask));
	if(!found){
		fprintf(stderr, "couldn't find signature\n");
		return -1;
	}

	printf("sig found @ index %p\n", (void *)((int64_t)found - (int64_t)arr));

	return 0;
}
```

output:
```
sig found @ index 0x4
```
