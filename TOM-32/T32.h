#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;

typedef int8_t		s8;
typedef int16_t		s16;
typedef int32_t		s32;

enum instructions {
	//Misc
	NOOP,
	//Load into A
	LDBA_val,
	LDWA_val,
	LDBA_addr,
	LDWA_addr,
	LDBA_ptr,
	LDWA_ptr,

	STBA_reg,
	STWA_reg,
	STBA_addr,
	STWA_addr,

	//Increment
	INCA,
	INCB,
	INCC,
	INCD,
	INCW,
	INCX,
	INCY,
	INCZ,

	//Decrement
	DECA,
	DECB,
	DECC,
	DECD,
	DECW,
	DECX,
	DECY,
	DECZ,

	//Left shift
	LSFA,
	LSFB,
	LSFC,
	LSFD,
	LSFW,
	LSFX,
	LSFY,
	LSFZ,

	//Right shift
	RSFA,
	RSFB,
	RSFC,
	RSFD,
	RSFW,
	RSFX,
	RSFY,
	RSFZ,
};

enum addrsize {
	addr_byte,
	addr_word,
	addr_long,
	addr_dword,
};

enum regind {
	reg_a,
	reg_b,
	reg_c,
	reg_d,
	reg_w,
	reg_x,
	reg_y,
	reg_z,
};

enum regptr {
	ptr_a,
	ptr_b,
	ptr_w,
	ptr_x,
	ptr_y,
	ptr_z,
};

enum flags {
	flag_c =	0x01,			//carry flag
	flag_z =	0x02,			//zero flag
	flag_n =	0x04,			//negative flag
	flag_o =	0x08,			//overflow flag
	flag_nmi =	0x10,			//NMI flag
	flag_dec =	0x20,			//decimal flag
};

const u32 ERROR0_VEC =	0xFFFFFFE4;
const u32 ERROR1_VEC =	0xFFFFFFE8;
const u32 ERROR2_VEC =	0xFFFFFFEC;
const u32 ERROR3_VEC =	0xFFFFFFF0;
const u32 POWER_VEC =	0xFFFFFFF4;
const u32 NMI_VEC =		0xFFFFFFF8;
const u32 RESET_VEC =	0xFFFFFFFC;
const u32 STACK =		0x00000800;


class T32
{
public:
	std::vector<u8> memory;

	u16 A, B;				//General purpose registers
	u32 C : 24, D : 24;		//Arithmetic registers
	u32 W, X, Y, Z;			//Address registers

	u32 PC;					//Program counter
	u8 S;					//Status

	void StartCPU(int size);

	void ReadInstruction();

	u8	LoadByte_Val();
	u16 LoadWord_Val();
	u32 LoadLong_Val();
	u32 LoadDWord_Val();

	u8	LoadByte_Addr();
	u16 LoadWord_Addr();
	u32 LoadLong_Addr();
	u32 LoadDWord_Addr();

	u8	LoadByte_Ptr(int reg);
	u16 LoadWord_Ptr(int reg);
	u32 LoadLong_Ptr(int reg);
	u32 LoadDWord_Ptr(int reg);

	void StoreByte_Addr(int reg);
	void StoreWord_Addr(int reg);
	void StoreLong_Addr(int reg);
	void StoreDWord_Addr(int reg);

	void IncrementRegister(int reg);
	void DecrementRegister(int reg);
	void LeftShiftRegister(int reg);
	void RightShiftRegister(int reg);

	void Debug_PrintContents();
};