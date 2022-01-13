//************main.cpp MVM程序测试启动入口**************//
#include <stdio.h>
#include "mcpu.h"
int main() {
	MCPU mcpu1 = MCPU();
	char a[] = "Hello,MVM!";
	mcpu1.writeData(0,10,&a);
	//print hello
	mcpu1.addCommand(2, 0, 1, 1);//设置寄存器1为-1
	mcpu1.addCommand(1,0,1,1);//寄存器1加1
	mcpu1.addCommand(7,2,0,2);//把内存AO的值传到寄存器2
	mcpu1.addCommand(9,0,2,0);//输出寄存器2的值
	mcpu1.addCommand(5,8,0,2);//判断寄存器2的值是否为0
	mcpu1.addCommand(3,0,0,0);//跳转到0(不执行0)
	mcpu1.runCommands();
	//mcpu1.printDebugInfo();
	return 0;
}
