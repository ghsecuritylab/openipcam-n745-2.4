#ifndef C_CONFIGFILE_H
#define C_CONFIGFILE_H

/* ����pcSegmentָ���Ķζ�ȡ�ļ����ݣ��������һ��������,
** ��������ÿ���ڵ�Ԫ��ΪNAMEDSTRING_T(Name,Value��)����
eg: ʾ���ļ�config.ini����(������---------------------)��
-------------------------------
#This is file config.ini
[Test Segment]
name1=test1
name2=test2

name3=test3

	[New Segment]
name1=new1
#new2, this line won't be read
name2=new2
--------------------------------
�κ���#��ͷ���ж�����Ϊע�ⲻ�ƣ��հ��в��ƣ�ǰ���հײ��ơ�
ʹ������Ҫ����DeleteConfigSegmentList(..)�Է��ص������ͷ� */
LIST *ReadConfigSegment(const char *pcFileName, const char *pcSegName);
BOOL WriteConfigSegment(const char *pcFileName, const char *pcSegName, LIST *pListConfigItem);
void DeleteConfigSegmentList(LIST *pList);

BOOL ReadConfigValue(const char *pcFileName, const char *pcSegName, const char *pcVarName, char *pcVarValue, int iMaxReadSize);
BOOL WriteConfigValue(const char *pcFileName, const char *pcSegName, const char *pcVarName, const char *pcVarValue);

/* �������ļ�����ppFileBuf�У�����Ҫfree */
BOOL ReadWholeFile(const char *pcFileName, char **ppcFileBuf, int *piFileLength);

/* ���ļ�buffer(pFileBuf)�е�pcThisLinePos���õ�һ�У���ָ����һ�е�����ָ��*ppcNextLinePos
** ���û����һ���ˣ�*ppcNextLinePos��ָ���ļ���β�ַ�+1��
** �����pcThisLinePos���Ժ�û�����ˣ�����FALSE; ��֮����TRUE */
BOOL ReadLineFromFileBuf(char *pcFileBuf, int iFileLength, char *pcThisLinePos, char **ppcNextLinePos);
#endif
