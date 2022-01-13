#ifndef MCPU_H
#define MCPU_H
#include <stdio.h>
#include <vector>
#include <stack>
#define byte signed char
using namespace std;
struct MCommand;
class MCPU {
	public:
		MCPU();
		~MCPU();
		void RGwriteData(int p,int size,void* data); //��Ĵ���д������
		void writeData(int p, int size, void* data); //д������
		void writeStr(int p, char* str); //д���ַ���
		void *readData(int p);//����RAM[p]��ָ��
		void addCommand(MCommand mc);
		void addCommand(byte opcode, byte funcode, byte num1, byte num2);
		void runCommands();
		void runCommand(MCommand mc);
		void printDebugInfo();

		int PC = 0; //��ǰָ��ִ��λ��
		int NOEC = 0; //�ܹ�ִ�й���ָ�����ͳ��
		long AO = 0; //�������
		long ACC = 0; //�ۼ���

		byte registerGroup[64] = {0};
		byte RAM[4096] = {0};
		vector< short> flags;
		stack< byte> stackBytes;
		vector< MCommand> CommandRegisterGroup;
		int ROM[1] = {0};
};
#endif
