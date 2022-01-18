#ifndef MCPU_H
#define MCPU_H
#include <stdio.h>
#define byte signed char
struct MCommand {
	byte Opcode; //操作码，必须是OPCODE中的，否则报错
	byte Funcode; //功能码
	byte Num1; //操作数1
	byte Num2; //操作数2
};
class MCPU {
	public:
		MCPU();
		~MCPU();
		void RGwriteData(int p, int size, void* data); //向寄存器写入数据
		void writeData(int p, int size, void* data); //写入数据
		void writeStr(int p, char* str); //写入字符串
		void *readData(int p);//返回RAM[p]的指针
		void addCommand(MCommand mc);
		void addCommand(byte opcode, byte funcode, byte num1, byte num2);
		void runCommands();
		void runCommand(MCommand mc);
		void printDebugInfo(int ramin, int ramax);

		int PC = 0; //当前指令执行位置
		int NOEC = 0; //总共执行过的指令，便于统计
		long AO = 0; //运算输出
		long ACC = 0; //累加器

		byte registerGroup[64] = {0};
		byte RAM[131072] = {0};
		int nflags;
		short* flags;
		int nStack;
		byte* stackBytes;
		int nCRG;
		MCommand* CommandRG;
		int ROM[1] = {0};
};
#endif
