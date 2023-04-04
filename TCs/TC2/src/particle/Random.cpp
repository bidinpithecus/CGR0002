#include "Random.hpp"

unsigned int randomNum(int max) {
	FILE* fPtr;
	unsigned int num;

	fPtr = fopen("/dev/random", "r");
	fread(&num, sizeof(num), 1, fPtr);
	fclose(fPtr);

	num %= max + 1;

	return num;
}
