//***************MVM������**************//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <vector>
#include "mcop.h"
#include "mcpu.h"
const char* OPCODE[] = {
	"NOT",//0 ��ָ��
	"ADD",//1 �ӷ�
	"SUB",//2 ����
	"GOTO",//3 PC���
	"LOC",//4 �߼�������һЩ��������
	"IF",//5 �ж�
	"SAVE",//6 ��ֵ��������ջ����
	"LOAD",//7 ȡֵ��������ջ����
	"INPUT",//8 ����
	"OUTPUT"//9 ���
};
CompOut compile(char* code) {
}
