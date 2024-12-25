#include "T32.h"

void T32::StartCPU(int size)
{
	memory.resize(size+8);
	S = 0;
	A = 0;
	B = 0;
	C = 0;
	D = 0;
	W = 0;
	X = 0;
	Y = 0;
	Z = 0;
	//PC = POWER_VEC;
	PC = 0;
}

void T32::ReadInstruction()
{
	int inst = memory[PC++];	//Current instruction
	if (inst == NOOP)
	{
		PC++;
	}
	else if (inst == LDBA_val)
	{
		A = LoadByte_Val();
	}
	else if (inst == LDWA_val)
	{
		A = LoadWord_Val();
	}
	else if (inst == LDBA_addr)
	{
		A = LoadByte_Addr();
	}
	else if (inst == LDBA_addr)
	{
		A = LoadByte_Addr();
	}
	else if (inst == LDWA_addr)
	{
		A = LoadWord_Addr();
	}
	else if (inst == STBA_reg)
	{
		StoreByte_Addr((int)reg_a);
	}
	else if (inst == STWA_reg)
	{
		StoreWord_Addr((int)reg_a);
	}
	else if (inst >= INCA && inst <= INCZ)
	{
		IncrementRegister(inst - INCA);
	}
	else if (inst >= DECA && inst <= DECZ)
	{
		DecrementRegister(inst - DECA);
	}
	else if (inst >= LSFA && inst <= LSFZ)
	{
		LeftShiftRegister(inst - LSFA);
	}
	else if (inst >= RSFA && inst <= RSFZ)
	{
		RightShiftRegister(inst - RSFA);
	}

	Debug_PrintContents();
}

u8 T32::LoadByte_Val()
{
	return memory[PC++];
}

u16 T32::LoadWord_Val()
{
	return memory[PC++] << 8 | memory[PC++];
}

u32 T32::LoadLong_Val()
{
	return memory[PC += 3] & 0x00FFFFFF;
}

u32 T32::LoadDWord_Val()
{
	return memory[PC += 4];
}

u8 T32::LoadByte_Addr()
{
	u32 addr = memory[PC++] << 0x18 | memory[PC++] << 0x10 | memory[PC++] << 0x08 | memory[PC++];
	return memory[addr];
}

u16 T32::LoadWord_Addr()
{
	u32 addr = memory[PC++] << 0x18 | memory[PC++] << 0x10 | memory[PC++] << 0x08 | memory[PC++];
	return memory[addr];
}

u32 T32::LoadLong_Addr()
{
	u32 addr = memory[PC++] << 0x18 | memory[PC++] << 0x10 | memory[PC++] << 0x08 | memory[PC++];
	return memory[addr] & 0xFFFFFF00;
}

u32 T32::LoadDWord_Addr()
{
	u32 addr = memory[PC++] << 0x18 | memory[PC++] << 0x10 | memory[PC++] << 0x08 | memory[PC++];
	return memory[addr];
}

u8 T32::LoadByte_Ptr(int reg)
{
	u32 laddr = 0;
	u16 waddr = 0;
	switch (reg)
	{
	case ptr_a:
		waddr = A;
		break;
	case ptr_b:
		waddr = B;
		break;
	case ptr_w:
		laddr = W;
		break;
	case ptr_x:
		laddr = X;
		break;
	case ptr_y:
		laddr = Y;
		break;
	case ptr_z:
		laddr = Z;
		break;
	}
	if (laddr == 0) return memory[(PC & 0xFFFF0000) | waddr];
	else return memory[laddr];
}

u16 T32::LoadWord_Ptr(int reg)
{
	u32 laddr = 0;
	u16 waddr = 0;
	switch (reg)
	{
	case ptr_a:
		waddr = A;
		break;
	case ptr_b:
		waddr = B;
		break;
	case ptr_w:
		laddr = W;
		break;
	case ptr_x:
		laddr = X;
		break;
	case ptr_y:
		laddr = Y;
		break;
	case ptr_z:
		laddr = Z;
		break;
	}
	if (laddr == 0) return memory[(PC & 0xFFFF0000) | waddr];
	else return memory[laddr];
}

u32 T32::LoadLong_Ptr(int reg)
{
	u32 laddr = 0;
	u16 waddr = 0;
	switch (reg)
	{
	case ptr_a:
		waddr = A;
		break;
	case ptr_b:
		waddr = B;
		break;
	case ptr_w:
		laddr = W;
		break;
	case ptr_x:
		laddr = X;
		break;
	case ptr_y:
		laddr = Y;
		break;
	case ptr_z:
		laddr = Z;
		break;
	}
	if (laddr == 0) return memory[(PC & 0xFFFF0000) | waddr] & 0xFFFFFF00;
	else return memory[laddr];
}

u32 T32::LoadDWord_Ptr(int reg)
{
	u32 laddr = 0;
	u32 waddr = 0;
	switch (reg)
	{
	case ptr_a:
		waddr = A;
		break;
	case ptr_b:
		waddr = B;
		break;
	case ptr_w:
		laddr = W;
		break;
	case ptr_x:
		laddr = X;
		break;
	case ptr_y:
		laddr = Y;
		break;
	case ptr_z:
		laddr = Z;
		break;
	}
	if (laddr == 0) return memory[(PC & 0xFFFF0000) | waddr];
	else return memory[laddr];
}

void T32::StoreByte_Addr(int reg)
{
	u32 addr = memory[PC++] << 0x18 | memory[PC++] << 0x10 | memory[PC++] << 0x08 | memory[PC++];
	switch (reg)
	{
	case reg_a:
		memory[addr] = A & 0xFF;
		break;
	case reg_b:
		memory[addr] = B & 0xFF;
		break;
	case reg_c:
		memory[addr] = C & 0xFF;
		break;
	case reg_d:
		memory[addr] = D & 0xFF;
		break;
	case reg_w:
		memory[addr] = W & 0xFF;
		break;
	case reg_x:
		memory[addr] = X & 0xFF;
		break;
	case reg_y:
		memory[addr] = Y & 0xFF;
		break;
	case reg_z:
		memory[addr] = Z & 0xFF;
		break;
	}
}

void T32::StoreWord_Addr(int reg)
{
	u32 addr = memory[PC++] << 0x18 | memory[PC++] << 0x10 | memory[PC++] << 0x08 | memory[PC++];
	switch (reg)
	{
	case reg_a:
		memory[addr] = (A & 0xFF);
		memory[(addr+1)] = (A >> 8 & 0xFF);
		break;
	case reg_b:
		memory[addr] = (B & 0xFF);
		memory[(addr + 1)] = (B >> 8 & 0xFF);
		break;
	case reg_c:
		memory[addr] = (C & 0xFF);
		memory[(addr + 1)] = (C >> 8 & 0xFF);
		break;
	case reg_d:
		memory[addr] = (D & 0xFF);
		memory[(addr + 1)] = (D >> 8 & 0xFF);
		break;
	case reg_w:
		memory[addr] = (W & 0xFF);
		memory[(addr + 1)] = (W >> 8 & 0xFF);
		break;
	case reg_x:
		memory[addr] = (X & 0xFF);
		memory[(addr + 1)] = (X >> 8 & 0xFF);
		break;
	case reg_y:
		memory[addr] = (Y & 0xFF);
		memory[(addr + 1)] = (Y >> 8 & 0xFF);
		break;
	case reg_z:
		memory[addr] = (Z & 0xFF);
		memory[(addr + 1)] = (Z >> 8 & 0xFF);
		break;
	}
}

void T32::StoreLong_Addr(int reg)
{
	u32 addr = memory[PC++] << 0x18 | memory[PC++] << 0x10 | memory[PC++] << 0x08 | memory[PC++];
	switch (reg)
	{
	case reg_c:
		memory[addr] = (C & 0xFF);
		memory[(addr + 1)] = (C >> 8 & 0xFF);
		memory[(addr + 2)] = (C >> 16 & 0xFF);
		break;
	case reg_d:
		memory[addr] = (D & 0xFF);
		memory[(addr + 1)] = (D >> 8 & 0xFF);
		memory[(addr + 2)] = (D >> 16 & 0xFF);
		break;
	case reg_w:
		memory[addr] = (W & 0xFF);
		memory[(addr + 1)] = (W >> 8 & 0xFF);
		memory[(addr + 2)] = (W >> 16 & 0xFF);
		break;
	case reg_x:
		memory[addr] = (X & 0xFF);
		memory[(addr + 1)] = (X >> 8 & 0xFF);
		memory[(addr + 2)] = (X >> 16 & 0xFF);
		break;
	case reg_y:
		memory[addr] = (Y & 0xFF);
		memory[(addr + 1)] = (Y >> 8 & 0xFF);
		memory[(addr + 2)] = (Y >> 16 & 0xFF);
		break;
	case reg_z:
		memory[addr] = (Z & 0xFF);
		memory[(addr + 1)] = (Z >> 8 & 0xFF);
		memory[(addr + 2)] = (Z >> 16 & 0xFF);
		break;
	}
}

void T32::StoreDWord_Addr(int reg)
{
	u32 addr = memory[PC++] << 0x18 | memory[PC++] << 0x10 | memory[PC++] << 0x08 | memory[PC++];
	switch (reg)
	{
	case reg_w:
		memory[addr] = (W & 0xFF);
		memory[(addr + 1)] = (W >> 8 & 0xFF);
		memory[(addr + 2)] = (W >> 16 & 0xFF);
		memory[(addr + 3)] = (W >> 24 & 0xFF);
		break;
	case reg_x:
		memory[addr] = (X & 0xFF);
		memory[(addr + 1)] = (X >> 8 & 0xFF);
		memory[(addr + 2)] = (X >> 16 & 0xFF);
		memory[(addr + 3)] = (X >> 24 & 0xFF);
		break;
	case reg_y:
		memory[addr] = (Y & 0xFF);
		memory[(addr + 1)] = (Y >> 8 & 0xFF);
		memory[(addr + 2)] = (Y >> 16 & 0xFF);
		memory[(addr + 3)] = (Y >> 24 & 0xFF);
		break;
	case reg_z:
		memory[addr] = (Z & 0xFF);
		memory[(addr + 1)] = (Z >> 8 & 0xFF);
		memory[(addr + 2)] = (Z >> 16 & 0xFF);
		memory[(addr + 3)] = (Z >> 24 & 0xFF);
		break;
	}
}


void T32::IncrementRegister(int reg)
{
	switch (reg)
	{
	case reg_a:
		A++;
		break;
	case reg_b:
		B++;
		break;
	case reg_c:
		C++;
		break;
	case reg_d:
		D++;
		break;
	case reg_w:
		W++;
		break;
	case reg_x:
		X++;
		break;
	case reg_y:
		Y++;
		break;
	case reg_z:
		Z++;
		break;
	}
}

void T32::DecrementRegister(int reg)
{
	switch (reg)
	{
	case reg_a:
		A--;
		break;
	case reg_b:
		B--;
		break;
	case reg_c:
		C--;
		break;
	case reg_d:
		D--;
		break;
	case reg_w:
		W--;
		break;
	case reg_x:
		X--;
		break;
	case reg_y:
		Y--;
		break;
	case reg_z:
		Z--;
		break;
	}
}

void T32::LeftShiftRegister(int reg)
{
	switch (reg)
	{
	case reg_a:
		A <<= 1;
		break;
	case reg_b:
		B <<= 1;
		break;
	case reg_c:
		C <<= 1;
		break;
	case reg_d:
		D <<= 1;
		break;
	case reg_w:
		W <<= 1;
		break;
	case reg_x:
		X <<= 1;
		break;
	case reg_y:
		Y <<= 1;
		break;
	case reg_z:
		Z <<= 1;
		break;
	}
}

void T32::RightShiftRegister(int reg)
{
	switch (reg)
	{
	case reg_a:
		A >>= 1;
		break;
	case reg_b:
		B >>= 1;
		break;
	case reg_c:
		C >>= 1;
		break;
	case reg_d:
		D >>= 1;
		break;
	case reg_w:
		W >>= 1;
		break;
	case reg_x:
		X >>= 1;
		break;
	case reg_y:
		Y >>= 1;
		break;
	case reg_z:
		Z >>= 1;
		break;
	}
}

void T32::Debug_PrintContents()
{
	std::cout << std::hex << "\n\n\nA: $" << A << "\nB: $" << B << "\n\nC: $" << C << "\nD: $" << D << "\n\nW: $" << W << "\nX: $" << X << "\nY: $" << Y << "\nZ: $" << Z << "\n\nStatus: $" << S << "\n\nProgram Counter: $" << PC;
}
