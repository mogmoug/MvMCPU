//*********************MVM Core 1.0***************//
#include <stdio.h>  //基础的IO接口，用来实现MVM基础输入输出
#include <vector>  //STL的动态数组，用于指令的存储
#include <stack>  //STL的堆栈库，用于程序中的堆栈
#include "mcpu.h"
#define byte signed char
using namespace std;

//LEN = 10
const char* OPCODE[10] = {
	"NOT",//0 空指令
	"ADD",//1 加法
	"SUB",//2 减法
	"GOTO",//3 PC相关
	"LOC",//4 逻辑运算与一些复杂运算
	"IF",//5 判断
	"MOVE",//6 赋值，包含堆栈操作
	"LOAD",//7 取值，包含堆栈操作
	"INPUT",//8 输入
	"OUTPUT"//9 输出
};
struct MCommand {
	byte Opcode; //操作码，必须是OPCODE中的，否则报错
	byte Funcode; //功能码
	byte Num1; //操作数1
	byte Num2; //操作数2
};


MCPU::MCPU() {
	printf("cpu:{\n");
	CommandRegisterGroup.reserve(0);
	flags.reserve(0);
}
MCPU::~MCPU() {
	printf("\n}\n");
}
void MCPU::writeData(int p, int size, void *data) {
	for (int i = 0; i < size; i++) {
		//把data指针强行转化为byte类型再加上i，然后取值
		RAM[p + i] = *(((byte *)data) + i);
	}
}
//此函数有漏洞，不建议使用
void MCPU::RGwriteData(int p, int size, void *data) {
	for (int i = 0; i < size; i++) {
		//把data指针强行转化为byte类型再加上i，然后取值
		registerGroup[p + i] = *(((byte *)data) + i);
	}
}
void MCPU::writeStr(int p, char *str) {
	for (int i = 0; * (str + i) == 0; i++) {
		//把data指针强行转化为byte类型再加上i，然后取值
		RAM[p + i] = *(str + i);
	}
}
void *MCPU::readData(int p) {
	//返回一个指向内存的第p个元素的空类型指针
	void *p1 = (void *)&RAM[p];
	return p1;
}
void MCPU::addCommand(MCommand mc) {
	CommandRegisterGroup.push_back(mc);
}

void MCPU::addCommand(byte opc, byte fun, byte n1, byte n2) {
	CommandRegisterGroup.push_back({opc, fun, n1, n2});
}

void MCPU::runCommands() {
	for (PC = 0; PC < (int)(CommandRegisterGroup.size()); PC++) {
		runCommand(CommandRegisterGroup[PC]);
	}
}

void MCPU::runCommand(MCommand mc) {
	registerGroup[0] = 0; //寄存器0始终为0
	byte opc = mc.Opcode;
	byte fun = mc.Funcode;
	byte n1 = mc.Num1;
	byte n2 = mc.Num2;
	switch (opc) {
	case 0:
		//NOT
	case 1:
		//ADD
		switch (fun) {
		case 0:
			//把寄存器n1加上立即数n2
			AO = registerGroup[(int)n1] + n2;
			registerGroup[(int)n1] += n2;
			break;
		case 1:
			//把寄存器n1加上寄存器n2
			AO = registerGroup[(int)n1] + registerGroup[(int)n2];
			registerGroup[(int)n1] += registerGroup[(int)n2];
			break;
		case 2:
			//把寄存器(n1+AO)加上n2
			AO = registerGroup[(int)n1 + AO] + n2;
			registerGroup[(int)n1 + AO] += n2;
			break;
		case 3:
			//把寄存器(n1+AO)加上寄存器n2
			AO = registerGroup[(int)n1 + AO] + registerGroup[(int)n2];
			registerGroup[(int)n1 + AO] += registerGroup[(int)n2];
			break;
		}
		break;
	case 2:
		//SUB
		switch (fun) {
		case 0:
			//把寄存器n1减去立即数n2
			AO = registerGroup[(int)n1] - n2;
			registerGroup[(int)n1] -= n2;
			break;
		case 1:
			//把寄存器n1减去寄存器n2
			AO = registerGroup[(int)n1] - registerGroup[(int)n2];
			registerGroup[(int)n1] -= registerGroup[(int)n2];
			break;
		case 2:
			//把寄存器(n1+AO)减去n2
			AO = registerGroup[(int)n1 + AO] - n2;
			registerGroup[(int)n1 + AO] -= n2;
			break;
		case 3:
			//把寄存器(n1+AO)减去寄存器n2
			AO = registerGroup[(int)n1 + AO] - registerGroup[(int)n2];
			registerGroup[(int)n1 + AO] -= registerGroup[(int)n2];
			break;
		}
		break;
	case 3:
		//GOTO
		switch (fun) {
		case 0:
			//跳转到n2+寄存器n1的位置
			PC = n2 + registerGroup[n1];
			break;
		case 1:
			//跳转到标志位n2+寄存器n1
			PC = flags[n2] + registerGroup[n1];
			break;
		case 2:
			//跳转到寄存器n1*寄存器n2+AO
			//寄存器n1和n2都可为0，因为0号寄存器永远是0
			PC = registerGroup[n1] * registerGroup[n2] + AO;
			break;
		case 3:
			//添加标志位为当前位置
			//加1是为了不让添加标志位的指令重复
			flags.push_back(PC + 1);
			break;
		}
		break;
	case 4:
		//LOC
		switch (fun) {
		case 0:
			//取模 (mod)
			AO = registerGroup[(int)n1] % registerGroup[(int)n2];
			registerGroup[(int)n1] %= registerGroup[(int)n2];
			break;
		case 1:
			//左移，0补位
			AO = registerGroup[(int)n1] << registerGroup[(int)n2];
			registerGroup[(int)n1] <<= registerGroup[(int)n2];
			break;
		case 2:
			//右移，0补位
			AO = registerGroup[(int)n1] >> registerGroup[(int)n2];
			registerGroup[(int)n1] >>= registerGroup[(int)n2];
			break;
		case 3:
			//或运算
			AO = registerGroup[(int)n1] & registerGroup[(int)n2];
			registerGroup[(int)n1] &= registerGroup[(int)n2];
			break;
		case 4:
			//与运算
			AO = registerGroup[(int)n1] | registerGroup[(int)n2];
			registerGroup[(int)n1] |= registerGroup[(int)n2];
			break;
		case 5:
			//异或运算
			AO = registerGroup[(int)n1] ^ registerGroup[(int)n2];
			registerGroup[(int)n1] ^= registerGroup[(int)n2];
			break;
		case 6:
			//乘法
			AO = registerGroup[(int)n1] * registerGroup[(int)n2];
			registerGroup[(int)n1] *= registerGroup[(int)n2];
			break;
		case 7:
			//取反（非门）
			AO = ~registerGroup[(int)n2];
			registerGroup[(int)n1] = ~registerGroup[(int)n2];
			break;
		case 8:
			//取补码（补码对于取反后加1）
			AO = ~registerGroup[(int)n2] + 1;
			registerGroup[(int)n1] = ~registerGroup[(int)n2] + 1;
			break;
		case 9:
			//除法（不保留小数）
			AO = registerGroup[(int)n1] / registerGroup[(int)n2];
			registerGroup[(int)n1] /= registerGroup[(int)n2];
			break;
		}
		break;
	case 5:
		//IF
		switch (fun) {
			//PC++是为了让下一句指令不执行
		case 0:
			//判断AO是否等于0
			if (AO == 0) {
				PC++;
			}
			break;
		case 1:
			//判断AO是否不等于0
			if (AO != 0) {
				PC++;
			}
			break;
		case 2:
			//判断溢出
			if (AO > 255) {
				PC++;
			}
			break;
		case 3:
			//判断无溢出
			if (AO <= 255) {
				PC++;
			}
			break;
		case 4:
			//测试是否等于
			if (registerGroup[n1] == registerGroup[n2]) {
				PC++;
			}
			break;
		case 5:
			//测试是否不等于
			if (registerGroup[n1] != registerGroup[n2]) {
				PC++;
			}
			break;
		case 6:
			//测试是否大于
			if (registerGroup[n1] > registerGroup[n2]) {
				PC++;
			}
			break;
		case 7:
			//测试是否小于
			if (registerGroup[n1] < registerGroup[n2]) {
				PC++;
			}
			break;
		}
		break;
	case 6:
		//MOVE
		switch (fun) {
		case 0:
			//把内存n1的值设为寄存器n2
			RAM[n1] = registerGroup[n2];
			break;
		case 1:
			//把内存AO的值设为寄存器n1+n2
			RAM[AO] = registerGroup[n1 + n2];
			break;
		case 2:
			//把寄存器n2压入栈顶
			stackBytes.push(registerGroup[n2]);
			break;
		case 3:
			//把累加器设为AO
			ACC = AO;
			break;
		case 4:
			//重置累加器
			ACC = 0;
			break;
		}
		break;
	case 7:
		//LOAD
		switch (fun) {
		case 0:
			//把内存n1的值传入寄存器n2
			registerGroup[n2] = RAM[n1];
			break;
		case 1:
			//把内存AO的值传入寄存器n1+n2
			registerGroup[n1 + n2] = RAM[AO];
			break;
		case 2:
			//把栈顶的值传入寄存器n2并弹出
			registerGroup[n2] = stackBytes.top();
			stackBytes.pop();
			break;
		case 3:
			//把栈顶的值传入寄存器n2但不弹出
			registerGroup[n2] = stackBytes.top();
			break;
		}
		break;
	case 8:
		//INPUT
		switch (fun) {
		case 0:
			//输入一个字符并存入寄存器n1
			registerGroup[n1] = (signed char)getchar();
			break;
		case 1:
			//可根据需求增加更多功能
			break;
		}
		break;
	case 9:
		//OUTPUT
		switch (fun) {
		case 0:
			//输出寄存器n1的字符到屏幕
			putchar(registerGroup[n1]);
			break;
		case 1:
			//可根据需求增加更多功能
			break;
		}
		break;
		default:
			//指令错误
			printf("ERROR:Not a command.     >>PC=%d\n", PC);
			break;
	}
	//如果AO是-1就清空
	if (AO != -1) {
		ACC += AO;
	} else {
		ACC = 0;
	}
}
void MCPU::printDebugInfo() {
	//调试信息
	printf("\
Debug:{\n\
PC:%d\n\
NOEC:%d\n\
AO:%ld\n\
RG:\n", PC, NOEC, AO);
	//把%c改成%d就可以显示数字
	for (int i = 0; i <= 63; i++) {
		printf("%c,", registerGroup[i]);
	}
	printf("\nRAM:\n");
	for (int i = 0; i <= 4095; i++) {
		printf("%c,", (unsigned char)RAM[i]);
	}
	printf("\n");
}
