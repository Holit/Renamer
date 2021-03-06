// Renamer.cpp: 定义控制台应用程序的入口点。
//
//用于批量更改文件名

//main.cpp : 接受文件夹并更改文件
#include "stdafx.h"
#include "FileOperator.h"
//////////////////////////////////////////////////////////////////////
//头文件吻合：FileOperator.h
//下述函数定义均来自FO.h

#pragma region FileOperatorFunctions
//	来自定义类file
bool file::setfile(char * fullpath)
{
	this->fullpath = fullpath;//填充全名
	//自右向左选取文件名
	int pos = sizeof(*fullpath);
	fullpath += pos;
	do
	{
		fullpath--;
		pos--;
	} while (pos == 0||*fullpath == '\\');
	strcat(filename, fullpath);
	//TODO:
	//自左向右取filename并查找到"."将"."后字符转移到filetype中，移除filename的这些字符
}
char * file::getfilename()
{
	return filename;
}
char * file::getfiletype() 
{ 
	return filename; 
}
char * file::getfile()
{
	return fullpath;
}
//	来自定义类folder
folder::folder(char * filespath)
{
	folderpath = filespath;
	filecount = 0;
	err = 0;
	if (strcmp(filespath, ""))err = 1;//防止有人使用空字符串抖机灵（提前判断达到节省内存？）
	handle = _findfirst(strcat(filespath, allfile_c), &fileinfo);//第一次查找文件（来自于path.*)
	if (handle == -1) { err = 1; }
	fs[0].setfile(fileinfo.name);
	filecount = 1;//文件数
	while (!_findnext(handle, &fileinfo) && filecount < 1024)//遍历文件夹
	{
		fs[filecount].setfile(fileinfo.name);
		filecount++;
	}
	_findclose(handle);//关闭句柄完成写入
}
int folder::getfilelist(char * filename[])
{
	if (sizeof(filename) / sizeof(filename[0]) < filecount)return -1;
	int i = 0;
	for (i; i < filecount; i++)		////断点：查看i第一次循环时是否被加一，若是说明有一个文件被略过
	{
		filename[i] = fs[filecount - i].getfile();
	}
	return 0;
}
int folder::getfilecount()
{
	return filecount;
}
int folder::dir()
{
	std::cout << "File dir : " << folderpath << std::endl;
	int i = 0;
	for (i; i < filecount; i++)		////断点：查看i第一次循环时是否被加一，若是说明有一个文件被略过
	{
		std::cout << "\t" << fs[filecount - i].getfile() << std::endl;
	}
	std::cout << "File dir end..." << std::endl;
	return 0;
}
bool folder::addfile(char * filename)
{
	if (filecount >= 1023) return false;
	if (strcmp(filename, ""))return false;
	if (handle != NULL) handle = NULL;//清空句柄
	handle = handle = _findfirst(filename, &fileinfo);//查找文件（来自于filename)
	if (handle == -1)
	{
		err = 3;
		_findclose(handle);
		return false;
	}
	else
	{
		filecount++;
		fs[filecount].setfile(filename);
		_findclose(handle);
		return true;
	}
}
bool folder::deletefile(char * filename)
{
	int is = 0;		//查找文件的索引
	do
	{
		if (strcmp(fs[is].getfile(), filename))
		{
			fs[is] = fs[is + 1];
			for (int i = is; i < filecount; i++)
			{
				fs[i] = fs[i + 1];	//数组前移
			}
			return true;
		}
		return false;
	} while (is <= filecount);
}
int folder::geterr()
{
	return err;
}
#pragma endregion

//////////////////////////////////////////////////////////////////////
//头函数吻合：SysCommand.h
//下述函数定义均来自SC.h
#pragma region SystemCommandFunctions
bool operatablefolder::sys_pause()
{
	system("pause");
}
#pragma endregion

int main(int argc, char*argv[])
{
	//TODO:
	//流程：选定文件夹->遍历文件夹->选择操作->完成操作
	if (argc == 0) return 0;//空参数返回
	if (strcmp(argv[0], ""))return 0;
	folder dir(argv[0]);//创建文件夹类
	dir.dir();//显示文件夹
	operatablefolder psf(folder);
	//dir.operate(argv[1],argv[2],argv[3],...,);//操作
	//dir.applicate();//应用操作
	dir.dir();//再次显示
	system("pause");
    return 0;
}

