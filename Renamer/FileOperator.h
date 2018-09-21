#pragma once
//FileOperator.h : ���ڶ�������ļ�����ͻ�ȡ�ļ���
#include <io.h>
#include "SysCommand.h"
#include <iostream>
class file
{
public:
	bool setfile(char * fullpath);//�ļ������ļ����͵ļ��ϣ�����D:\\a.txt
	char * getfilename();
	char * getfiletype();
	char * getfile();//��ȡ�ļ�ȫ�񣬼�����setfile�е�fullpath
private:
	char*fullpath;//ȫ��
	char*filename;//�ļ���
	char*filetype;//�ļ�����
};
class folder		//�ļ�����
{
public:
	folder(char * filespath);				//���캯����ʹ��folderpath���ļ���λ�ô���ʵ������

	int getfilelist(char * filename[]);		//��filename[]���������뵱ǰfolder���ļ��б����Ŀ��filename[]�ĳ��Ȳ����򷵻�-1�����Ķ�filename
	int getfilecount();						//��ȡ�ļ������ļ���Ŀ
	int dir();								//��ʾ��ǰ�ļ��е������ļ����ļ���

	bool addfile(char * filename);			//������ļ�
	bool deletefile(char * filename);		//ʹ���ļ���ɾ���ļ�

	int geterr();//����ָʾ�Ƿ���ִ��󼰴�������
		/*
		err����
			0 - �޴���
			1 - ���Թ��캯����_findfirst(...)�Ҳ����ļ��Լ����촫���˿��ִ�
			2 - �����ļ����飺��������ļ�������(1024���ļ�)
			3 - ����addfile���Ҳ����ļ�
		*/
private:
	char * folderpath;
	const char * allfile_c = "\\*.*";
	long handle;
	struct _finddata_t fileinfo;			//�������������ڵ����ļ�������io�еĽṹ������handleΪ���Ҿ����fileinfoΪ����Ľṹ����
	
	file fs[1024];				//�ļ������ڴ洢�ļ���Ϣ����߿�������1024���ļ�
	int filecount;//�ļ���

	int err;

};