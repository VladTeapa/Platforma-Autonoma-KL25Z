#include "Utils.h"

void copiereVector(void* destination, void* source, uint8_t size)
{
	register int i=0;
	for(;i<size;i++)
		destination[i] = source[i];
}