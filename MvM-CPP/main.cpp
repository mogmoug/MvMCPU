//************main.cpp MVM��������������**************//
#include <stdio.h>
#include "mcpu.h"
int main() {
	MCPU mcpu1 = MCPU();
	char a[] = "Hello,MVM!";
	mcpu1.writeData(0,10,&a);
	//print hello
	mcpu1.addCommand(2, 0, 1, 1);//���üĴ���1Ϊ-1
	mcpu1.addCommand(1,0,1,1);//�Ĵ���1��1
	mcpu1.addCommand(7,2,0,2);//���ڴ�AO��ֵ�����Ĵ���2
	mcpu1.addCommand(9,0,2,0);//����Ĵ���2��ֵ
	mcpu1.addCommand(5,8,0,2);//�жϼĴ���2��ֵ�Ƿ�Ϊ0
	mcpu1.addCommand(3,0,0,0);//��ת��0(��ִ��0)
	mcpu1.runCommands();
	//mcpu1.printDebugInfo();
	return 0;
}
