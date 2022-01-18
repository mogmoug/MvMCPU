#ifndef MCPU_H
#define MCPU_H
#define byte signed char
#include <stdio.h>
#include <stdlib.h>
struct MCOM{
	byte opc;
	byte fun;
	byte n1;
	byte n2;
};
struct MRG{
	byte a[24];
	int b[8];
};
struct MCPU{
	MRG RG;
	byte RAM[131072];
};

#endif
