批量重命名工具
=========
中文
* 编写及调试环境
  Microsoft Visual Studio 2017 Community
* 基础运行(Debug)
  Windows 10 Enterprise x64
---------
* 目的
创建一个命令行命令“renamer”，该命令能够把文件夹内的文件进行文件名操作
* 原理
  * 原理很麻烦。。。。
  * 读入_finddata_t，使用这个函数获取指定文件夹内的文件并存入数组（来自argv[0]）
  * 使用循环写字符串
  * 使用system函数重命名，其中命令使用strcat和strcmp制作
  * 应用操作
* 难点
  * 大量使用指针...（现在作者也很晕）
  * 字符串操作（实际上就是char指针）
  * system操作
  * _finddata_t结构不熟悉
* _finddata_t简析
```C++
struct _finddata_t
        {
             unsigned attrib;
             time_t time_create;
             time_t time_access;
             time_t time_write;
             _fsize_t size;
             char name[_MAX_FNAME];
        };
```
  * attrib                  文件属性，相当于使用attrib命令获取文件属性
  * char name[_MAX_FNAME]   文件名，其中_MAX_NAME是内定的常量
  * 使用条件和方法
    *  #include <io.h>
    * 采用下述方法得到所有文件
```C++
//详见文件Rename.cpp
folder::folder(char * filespath)
{
	folderpath = filespath;
	filecount = 0;
	err = 0;
	if (strcmp(filespath, ""))err = 1;                            //防止有人使用空字符串抖机灵（提前判断达到节省内存？）
	handle = _findfirst(strcat(filespath, allfile_c), &fileinfo); //第一次查找文件（来自于path.*)
	if (handle == -1) { err = 1; }
	fs[0].setfile(fileinfo.name);
	filecount = 1;//文件数
	while (!_findnext(handle, &fileinfo) && filecount < 1024)     //遍历文件夹
	{
		fs[filecount].setfile(fileinfo.name);
		filecount++;
	}
	_findclose(handle);                                           //关闭句柄完成写入
}
```

Batch rename tool
=========
English - Translated by Google(R)
* Writing and debugging environment
  Microsoft Visual Studio 2017 Community
* Basic operation (Debug)
  Windows 10 Enterprise x64
---------
* Purpose
Create a command line command "renamer", which can perform file name operations on files in the folder.
* Principle
  * The principle is very troublesome. . . .
  * Read _finddata_t, use this function to get the files in the specified folder and store them in an array (from argv[0])
  * Write a string using a loop
  * Rename using the system function, where the command is made using strcat and strcmp
  * Application operation
* Difficulties
  * Use pointers a lot... (now the author is also dizzy)
  * String operations (actually char pointers)
  * system operation
  * _finddata_t structure is not familiar
* _finddata_t analysis
```C++
struct _finddata_t
        {
             unsigned attrib;
             time_t time_create;
             time_t time_access;
             time_t time_write;
             _fsize_t size;
             char name[_MAX_FNAME];
        };
```

  * attrib file attribute, equivalent to using the attrib command to get file attributes
  * char name[_MAX_FNAME] filename, where _MAX_NAME is the default constant
  * Conditions and methods of use
    * #include <io.h>
    * Get all the files in the following way
    
```C++
/ / See the file Rename.cpp
folder::folder(char * filespath)
{
Folderpath = filespath;
Filecount = 0;
Err = 0;
If (strcmp(filespath, ""))err = 1; //Prevent someone from using an empty string to shake the body (predetermine to save memory in advance?)
Handle = _findfirst(strcat(filespath, allfile_c), &fileinfo); //First look up the file (from path.*)
If (handle == -1) { err = 1; }
Fs[0].setfile(fileinfo.name);
Filecount = 1; / / number of files
While (!_findnext(handle, &fileinfo) && filecount < 1024) // traverse the folder
{
Fs[filecount].setfile(fileinfo.name);
Filecount++;
}
_findclose(handle); //Close the handle to complete the write
}
```
