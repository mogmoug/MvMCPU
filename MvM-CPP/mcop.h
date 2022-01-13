#ifndef MCOP_H
#define MCOP_H
const char* OPCODE[] = {
	"NOT",//0 空指令
	"ADD",//1 加法
	"SUB",//2 减法
	"GOTO",//3 PC相关
	"LOC",//4 逻辑运算与一些复杂运算
	"IF",//5 判断
	"SAVE",//6 赋值，包含堆栈操作
	"LOAD",//7 取值，包含堆栈操作
	"INPUT",//8 输入
	"OUTPUT"//9 输出
};
#endif
