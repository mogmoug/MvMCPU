//***************MVM编译器**************//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <vector>
#include "mcop.h"
#include "mcpu.h"
using namespace std;

CompOut compile(char* code) {
	int codelen = strlen(code);
	vector< char*> token;
	vector< MCommand> mcs;
	MCommand temp = {0, 0, 0, 0};
	char buff[16] = {'\0'};
	int nn = 0;
	int j = 0;
	//提取token
	for (int i = 0; * (code + i) != 0; i++) {
		buff[j] = *(code + i);
		j++;
		//如果是空格或换行就结束一个token
		if (*(code + i) == ' ' || *(code + i) == '\n') {
			token.push_back(buff);
			//清空buff
			for (int a = 0; a <= 15; a++) {
				buff[a] = 0;
			}
			j = 0;
		}
	}

	for (int i = 0; i < token.size(); i++) {
		//如果第i个token的第一个字符是a-z或A-Z之间的就是opcode
		if ((*token.at(i) > 96 && *token.at(i) < 123) || (*token.at(i) > 64 && *token.at(i) < 91)) {
			if (i != 0) {
				mcs.push_back(temp);
				nn=0;
			}
			//如果是小写就转换为大写
			if (*token.at(i) > 96 && *token.at(i) < 123) {
				for (int a = 0; a < strlen(token.at(i)); a++) {
					*(token.at(i) + a) -= 32;
				}
			}
			//查找OPCODE
			for (int a = 0; a < 10; a++) {
				if (strcmp(token.at(i), OPCODE[a])) {
					temp.Opcode = a;
				}
			}
		}
		if(*token.at(i) > 47 && *token.at(i) < 58){
			nn++;
			switch (nn) {
			case 1:
				temp.Funcode=atoi(token.at(i));
				break;
			case 2:
				temp.Num1=atoi(token.at(i));
				break;
			case 3:
				temp.Num2=atoi(token.at(i));
				break;
			}
		}
	}
	MCommand *p = (MCommand*)malloc(sizeof(MCommand)*mcs.size());
	return {mcs.size(), p};
}
