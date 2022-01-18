#ifndef MCOP_H
#define MCOP_H
#include "mcpu.h"
struct CompOut {
	int size;
	MCommand *p;
};
CompOut compile(char* code);
#endif
