/**
 * @author Matthew Wilder
 * @since 12/7/2022
 * Program that masks page number and offset from an
 * unsigned 32-bit address.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PAGE_NUMBER_MASK 0xFFFFF000
#define OFFSET_MASK 0x00000FFF
#define SHIFT 12

int main(int argc, char *argv[]) {

	int page_num, offset;
	unsigned int reference;

	reference = (unsigned int)atoi(argv[1]);
	printf("The address %d contains:\n",reference);

	//  mask the page number 
	//-------------[TO BE COMPLETED]-------------
	page_num = reference >> SHIFT;
	offset = reference & OFFSET_MASK;

	printf("page number = %d\n",page_num);
	printf("offset = %d\n",offset);

	return 0;
}
