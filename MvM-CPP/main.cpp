//************main.cpp**************//
#include <stdio.h>
#include <string.h>
#include "mcpu.h"
#include "mcop.h"
int main() {
	MCPU mcpu1 = MCPU();
	char a[] = "Hello\n";
	mcpu1.writeData(0, 52, &a);
//	print hello
	mcpu1.addCommand(2, 0, 1, 1);//SUBI r1,1
	mcpu1.addCommand(1, 0, 1, 1); //ADDI r1,1
	mcpu1.addCommand(7, 2, 0, 2); //LOAD m[AO],r2
	mcpu1.addCommand(9, 0, 2, 0); //OUTPUT 0,r2
	mcpu1.addCommand(5, 8, 0, 2); //IFNOTZERO r2
	mcpu1.addCommand(3, 0, 0, 0); //JMP 0
	mcpu1.runCommands();
	mcpu1.printDebugInfo(0, 128);
	return 0;
}
