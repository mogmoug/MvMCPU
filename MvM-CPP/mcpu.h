#ifndef MCPU_H
#define MCPU_H
#include <stdio.h>
#define byte signed char
struct MCommand {
	byte Opcode; //�����룬������OPCODE�еģ����򱨴�
	byte Funcode; //������
	byte Num1; //������1
	byte Num2; //������2
};
class MCPU {
	public:
		MCPU();
		~MCPU();
		void RGwriteData(int p, int size, void* data); //��Ĵ���д������
		void writeData(int p, int size, void* data); //д������
		void writeStr(int p, char* str); //д���ַ���
		void *readData(int p);//����RAM[p]��ָ��
		void addCommand(MCommand mc);
		void addCommand(byte opcode, byte funcode, byte num1, byte num2);
		void runCommands();
		void runCommand(MCommand mc);
		void printDebugInfo(int ramin, int ramax);

		int PC = 0; //��ǰָ��ִ��λ��
		int NOEC = 0; //�ܹ�ִ�й���ָ�����ͳ��
		long AO = 0; //�������
		long ACC = 0; //�ۼ���

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
