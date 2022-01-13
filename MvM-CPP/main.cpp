//************main.cpp MVM程序测试启动入口**************//
#include <stdio.h>
#include "mcpu.h"
int main() {
	MCPU mcpu1 = MCPU();
	char a[] = "Hello,MVM!";
	mcpu1.writeData(0,10,&a);
	mcpu1.addCommand(1, 0, 2, 100);
	mcpu1.runCommands();
	mcpu1.printDebugInfo();
	return 0;
}
