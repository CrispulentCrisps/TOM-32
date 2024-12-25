#define _CRT_SECURE_NO_WARNINGS
#include "T32.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "\n" << argv[0];
	std::cout << "\n" << argv[1];
	FILE* file = fopen(argv[1], "rb");
	
	fseek(file, 0, SEEK_END); // seek to end of file
	int size = ftell(file); // get current file pointer
	fseek(file, 0, SEEK_SET); // seek back to beginning of file

	if (size > UINT32_MAX)
	{
		std::cout << "\nERROR: FILE TOO BIG";
		return 1;
	}

	T32 t32 = T32();
	t32.StartCPU(size);
	fread(&t32.memory[0], 1, size, file);

	t32.Debug_PrintContents();
	while (t32.PC < size)
	{
		t32.ReadInstruction();
	}

	fclose(file);

	return 0;
}