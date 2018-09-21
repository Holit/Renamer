#pragma once
//FileOperator.h : 用于定义基本文件夹类和获取文件名
#include <io.h>
#include "SysCommand.h"
#include <iostream>
class file
{
public:
	bool setfile(char * fullpath);//文件名及文件类型的集合，比如D:\\a.txt
	char * getfilename();
	char * getfiletype();
	char * getfile();//获取文件全民，即传递setfile中的fullpath
private:
	char*fullpath;//全名
	char*filename;//文件名
	char*filetype;//文件类型
};
class folder		//文件夹类
{
public:
	folder(char * filespath);				//构造函数，使用folderpath即文件夹位置创建实例对象

	int getfilelist(char * filename[]);		//在filename[]数组中填入当前folder的文件列表，如果目标filename[]的长度不足则返回-1并不改动filename
	int getfilecount();						//获取文件夹中文件数目
	int dir();								//显示当前文件夹的所有文件和文件名

	bool addfile(char * filename);			//添加新文件
	bool deletefile(char * filename);		//使用文件名删除文件

	int geterr();//用于指示是否出现错误及错误类型
		/*
		err类型
			0 - 无错误
			1 - 来自构造函数，_findfirst(...)找不到文件以及构造传递了空字串
			2 - 来自文件数组：超过最高文件遍历数(1024个文件)
			3 - 来自addfile，找不到文件
		*/
private:
	char * folderpath;
	const char * allfile_c = "\\*.*";
	long handle;
	struct _finddata_t fileinfo;			//这两个变量用于调用文件属性类io中的结构，其中handle为查找句柄，fileinfo为具体的结构对象
	
	file fs[1024];				//文件类用于存储文件信息，最高可以申请1024个文件
	int filecount;//文件数

	int err;

};