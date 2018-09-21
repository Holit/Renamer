#pragma once
//SysCommand.h : 用于连接系统函数以实现系统指令调用
#include "FileOperator.h"
#include <Windows.h>
#include <string>

class operatablefolder : public folder
{
public:
	operatablefolder(folder * f);
	bool sys_pause();
};