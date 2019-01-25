#include "hamming.h"

int main()
{
	const char *ham_code;
	const char *src_code;

	ham_code = encode("0101");
	puts(ham_code);
	src_code = decode("0100101");
	puts(src_code);
	return 0;
}