#pragma once
//SysCommand.h : ��������ϵͳ������ʵ��ϵͳָ�����
#include "FileOperator.h"
#include <Windows.h>
#include <string>

class operatablefolder : public folder
{
public:
	operatablefolder(folder * f);
	bool sys_pause();
};