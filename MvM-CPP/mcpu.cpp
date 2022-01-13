//*********************MVM Core 1.0***************//
#include <stdio.h>  //������IO�ӿڣ�����ʵ��MVM�����������
#include "mcpu.h"
#define byte signed char
using namespace std;

//LEN = 10

struct MCommand {
	byte Opcode; //�����룬������OPCODE�еģ����򱨴�
	byte Funcode; //������
	byte Num1; //������1
	byte Num2; //������2
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
		//��dataָ��ǿ��ת��Ϊbyte�����ټ���i��Ȼ��ȡֵ
		RAM[p + i] = *(((byte *)data) + i);
	}
}
//�˺�����©����������ʹ��
void MCPU::RGwriteData(int p, int size, void *data) {
	for (int i = 0; i < size; i++) {
		//��dataָ��ǿ��ת��Ϊbyte�����ټ���i��Ȼ��ȡֵ
		registerGroup[p + i] = *(((byte *)data) + i);
	}
}
void MCPU::writeStr(int p, char *str) {
	for (int i = 0; * (str + i) == 0; i++) {
		//��dataָ��ǿ��ת��Ϊbyte�����ټ���i��Ȼ��ȡֵ
		RAM[p + i] = *(str + i);
	}
}
void *MCPU::readData(int p) {
	//����һ��ָ���ڴ�ĵ�p��Ԫ�صĿ�����ָ��
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
	registerGroup[0] = 0; //�Ĵ���0ʼ��Ϊ0
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
					//�ѼĴ���n1����������n2
					AO = registerGroup[(int)n1] + n2;
					registerGroup[(int)n1] += n2;
					break;
				case 1:
					//�ѼĴ���n1���ϼĴ���n2
					AO = registerGroup[(int)n1] + registerGroup[(int)n2];
					registerGroup[(int)n1] += registerGroup[(int)n2];
					break;
				case 2:
					//�ѼĴ���(n1+AO)����n2
					AO = registerGroup[(int)n1 + AO] + n2;
					registerGroup[(int)n1 + AO] += n2;
					break;
				case 3:
					//�ѼĴ���(n1+AO)���ϼĴ���n2
					AO = registerGroup[(int)n1 + AO] + registerGroup[(int)n2];
					registerGroup[(int)n1 + AO] += registerGroup[(int)n2];
					break;
			}
			break;
		case 2:
			//SUB
			switch (fun) {
				case 0:
					//�ѼĴ���n1��ȥ������n2
					AO = registerGroup[(int)n1] - n2;
					registerGroup[(int)n1] -= n2;
					break;
				case 1:
					//�ѼĴ���n1��ȥ�Ĵ���n2
					AO = registerGroup[(int)n1] - registerGroup[(int)n2];
					registerGroup[(int)n1] -= registerGroup[(int)n2];
					break;
				case 2:
					//�ѼĴ���(n1+AO)��ȥn2
					AO = registerGroup[(int)n1 + AO] - n2;
					registerGroup[(int)n1 + AO] -= n2;
					break;
				case 3:
					//�ѼĴ���(n1+AO)��ȥ�Ĵ���n2
					AO = registerGroup[(int)n1 + AO] - registerGroup[(int)n2];
					registerGroup[(int)n1 + AO] -= registerGroup[(int)n2];
					break;
			}
			break;
		case 3:
			//GOTO
			switch (fun) {
				case 0:
					//��ת��n2+�Ĵ���n1��λ��
					PC = n2 + registerGroup[n1];
					break;
				case 1:
					//��ת����־λn2+�Ĵ���n1
					PC = flags[n2] + registerGroup[n1];
					break;
				case 2:
					//��ת���Ĵ���n1*�Ĵ���n2+AO
					//�Ĵ���n1��n2����Ϊ0����Ϊ0�żĴ�����Զ��0
					PC = registerGroup[n1] * registerGroup[n2] + AO;
					break;
				case 3:
					//��ӱ�־λΪ��ǰλ��
					//��1��Ϊ�˲�����ӱ�־λ��ָ���ظ�
					flags.push_back(PC + 1);
					break;
			}
			break;
		case 4:
			//LOC
			switch (fun) {
				case 0:
					//ȡģ (mod)
					AO = registerGroup[(int)n1] % registerGroup[(int)n2];
					registerGroup[(int)n1] %= registerGroup[(int)n2];
					break;
				case 1:
					//���ƣ�0��λ
					AO = registerGroup[(int)n1] << registerGroup[(int)n2];
					registerGroup[(int)n1] <<= registerGroup[(int)n2];
					break;
				case 2:
					//���ƣ�0��λ
					AO = registerGroup[(int)n1] >> registerGroup[(int)n2];
					registerGroup[(int)n1] >>= registerGroup[(int)n2];
					break;
				case 3:
					//������
					AO = registerGroup[(int)n1] & registerGroup[(int)n2];
					registerGroup[(int)n1] &= registerGroup[(int)n2];
					break;
				case 4:
					//������
					AO = registerGroup[(int)n1] | registerGroup[(int)n2];
					registerGroup[(int)n1] |= registerGroup[(int)n2];
					break;
				case 5:
					//�������
					AO = registerGroup[(int)n1] ^ registerGroup[(int)n2];
					registerGroup[(int)n1] ^= registerGroup[(int)n2];
					break;
				case 6:
					//�˷�
					AO = registerGroup[(int)n1] * registerGroup[(int)n2];
					registerGroup[(int)n1] *= registerGroup[(int)n2];
					break;
				case 7:
					//ȡ�������ţ�
					AO = ~registerGroup[(int)n2];
					registerGroup[(int)n1] = ~registerGroup[(int)n2];
					break;
				case 8:
					//ȡ���루�������ȡ�����1��
					AO = ~registerGroup[(int)n2] + 1;
					registerGroup[(int)n1] = ~registerGroup[(int)n2] + 1;
					break;
				case 9:
					//������������С����
					AO = registerGroup[(int)n1] / registerGroup[(int)n2];
					registerGroup[(int)n1] /= registerGroup[(int)n2];
					break;
			}
			break;
		case 5:
			//IF
			switch (fun) {
				//PC++��Ϊ������һ��ָ�ִ��
				case 0:
					AO == 0 ? PC++ : 0;
					break;//�ж�AO�Ƿ����0
				case 1:
					AO != 0 ? PC++ : 0;
					break;//�ж�AO�Ƿ񲻵���0
				case 2:
					AO > 255 ? PC++ : 0;
					break;//�ж����
				case 3:
					AO <= 255 ? PC++ : 0;
					break;//�ж������
				case 4:
					registerGroup[n1] == registerGroup[n2] ? PC++ : 0;
					break;//�����Ƿ����
				case 5:
					registerGroup[n1] != registerGroup[n2] ? PC++ : 0;
					break;//�����Ƿ񲻵���
				case 6:
					registerGroup[n1] > registerGroup[n2] ? PC++ : 0;
					break;//�����Ƿ����
				case 7:
					registerGroup[n1] < registerGroup[n2] ? PC++ : 0;
					break;//�����Ƿ�С��
				case 8:
					registerGroup[n2] == 0 ? PC++ : 0;
					break;//�жϼĴ���n2�Ƿ����0
				case 9:
					registerGroup[n2] != 0 ? PC++ : 0;
					break;//�жϼĴ���n2�Ƿ񲻵���0
			}
			break;
		case 6:
			//SAVE
			switch (fun) {
				case 0:
					//�ѼĴ���n1ֵ������ƴ�ӼĴ���n1+1��ֵ��һ�������ֽڵ�ֵΪ��ַ�ѼĴ���n2��ֵ�����ڴ�
					RAM[(((short)(registerGroup[n1])) << 8) + registerGroup[n1 + 1]] = registerGroup[n2];
					break;
				case 1:
					//���ڴ�n1��ֵ��Ϊ�Ĵ���n2
					RAM[n1] = registerGroup[n2];
					break;
				case 2:
					//���ڴ�AO��ֵ��Ϊ�Ĵ���n1+n2
					RAM[AO] = registerGroup[n1 + n2];
					break;
				case 3:
					//�ѼĴ���n2ѹ��ջ��
					stackBytes.push(registerGroup[n2]);
					break;
				case 4:
					//���ۼ�����ΪAO
					ACC = AO;
					break;
				case 5:
					//�����ۼ���
					ACC = 0;
					break;
			}
			break;
		case 7:
			//LOAD
			switch (fun) {
				case 0:
					//�ѼĴ���n1ֵ������ƴ�ӼĴ���n1+1��ֵ��һ�������ֽڵ�ֵΪ��ַ���ڴ��ֵ�浽�Ĵ���n2
					registerGroup[n2] = RAM[(((short)(registerGroup[n1])) << 8) + registerGroup[n1 + 1]];
					break;
				case 1:
					//���ڴ�n1��ֵ����Ĵ���n2
					registerGroup[n2] = RAM[n1];
					break;
				case 2:
					//���ڴ�AO��ֵ����Ĵ���n1+n2
					registerGroup[n1 + n2] = RAM[AO];
					break;
				case 3:
					//��ջ��q��ֵ����Ĵ���n2������
					registerGroup[n2] = stackBytes.top();
					stackBytes.pop();
					break;
				case 4:
					//��ջ����ֵ����Ĵ���n2��������
					registerGroup[n2] = stackBytes.top();
					break;
			}
			break;
		case 8:
			//INPUT
			switch (fun) {
				case 0:
					//����һ���ַ�������Ĵ���n1
					registerGroup[n1] = (signed char)getchar();
					break;
				case 1:
					//�ɸ����������Ӹ��๦��
					break;
			}
			break;
		case 9:
			//OUTPUT
			switch (fun) {
				case 0:
					//����Ĵ���n1���ַ�����Ļ
					putchar(registerGroup[n1]);
					break;
				case 1:
					//�ɸ����������Ӹ��๦��
					break;
			}
			break;
		default:
			//ָ�����
			printf("ERROR:Not a command.     >>PC=%d\n", PC);
			break;
	}
	//���AO��-1�����
	if (AO != -1) {
		ACC += AO;
	} else {
		ACC = 0;
	}
}
void MCPU::printDebugInfo() {
	//������Ϣ
	int min;
	int max;
	printf("\
Debug:{\n\
PC:%d\n\
NOEC:%d\n\
AO:%ld\n\
RG:\n", PC, NOEC, AO);
	//��%c�ĳ�%d�Ϳ�����ʾ����
	for (int i = 0; i <= 63; i++) {
		printf("%c,", registerGroup[i]);
	}
	printf("\nRAM:\n");

	printf("min?,max?");
	scanf("%d", &min);
	scanf("%d", &max);
	for (int i = min; i <= max; i++) {
		printf("%c,", (unsigned char)RAM[i]);
	}
	printf("\n");
}
