#include<stdio.h>
#include<string.h>
#include"sigscan.h"

void *NibbleSigScan(void *start, size_t range, char *sig, size_t sig_len, char *mask, size_t mask_len){

	if(!start || !sig || !mask)
		return NULL;

	if(mask_len != sig_len ){
		fprintf(stderr, "NibbleSigScan : mask length mismatch\n");
		return NULL;
	}

	byte *ptr = (byte *)start;
	byte *end_ptr = ptr + range;

	byte *sig_ptr = (byte *)sig;

	// sig/ptr index
	size_t i;

	// current mask character
	char c;

	//  check a nibble at a time
	while(ptr + sig_len <= end_ptr){
		for(i = 0; i < sig_len;i++){

			c = mask[i];

			// both nibbles have to match
			if(c == 'x'){
				if(sig_ptr[i].high != ptr[i].high
						|| sig_ptr[i].low != ptr[i].low)
					break;

			// only the high nibble has to match
			}else if(c == 'h'){
				if(sig_ptr[i].high != ptr[i].high)
						break;

			// only the lower nibble has to match
			} else if(c == 'l'){
				if(sig_ptr[i].low != ptr[i].low)
						break;

			}else if(c == '?'){
				continue;
			} else{
				fprintf(stderr, "unknown mask character : %c\n", c);
				return NULL;
			}
		}

		if(i == sig_len)
			return ptr;

		ptr++;

	}

	return NULL;
}
