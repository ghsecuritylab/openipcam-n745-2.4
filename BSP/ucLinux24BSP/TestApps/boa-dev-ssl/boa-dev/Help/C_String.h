#ifndef C_STRING_H
#define C_STRING_H

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif

typedef struct
{
	char *pcName;
	char *pcValue;
} NAMEDSTRING_T;

char *MyStrncpy(char *pcDest, const char *pcSrc, int iLength);

/* ��pcString��cSeparator��Ϊ�ָ�����һ��LIST�ṹ��˫�������� */
LIST *SplitString(const char *pcString, char cSeparator);

/* �ͷ�SplitString�������ɵ��������е��ַ�����Դ */
void DeleteSplitString(LIST *pList);

/* �õ�һ��ȥ��ǰ��հ׵��ַ�����������Ҫfree */
char *GetTrimString(const char *pcString);

/* �õ�һ����Cת�廯���ַ�����������Ҫfree
** ��ab"cd, ��õ�ab\"cd */
char *GetCStyleString(const char *pcString);

/* �õ�һ����webת�廯���ַ�����������Ҫfree
**   ab<cd, ��õ�ab&lt;cd */
char *GetWebStyleString(const char *pcString);

/* �õ�һ���Ⱦ�webת�廯���پ�C/javaת�廯���ַ���������Ҫfree */
char *GetWebInCString(const char *pcStr);

/* ���ַ���ת��ΪIP��ַ */
unsigned long String2IP(const char *pcString);
/* ��IP��ַת��Ϊ�ַ���, pcStringOut�ռ����>=16, ����pcStringOut�ַ����ĳ��� */
int IP2String(unsigned long ulIP, char *pcStringOut);

/* ���ַ���ת��Ϊlong */
long String2Long(const char *pcString);
/* ��longת��Ϊ�ַ���, pcStringOut�ռ����>=32, ����pcStringOut�ַ����ĳ��� */
int Long2String(long lVal, char *pcStringOut);

/* ���ַ���ת��ΪBOOL */
BOOL String2Bool(const char *pcString);
/* ��BOOLת��Ϊ�ַ���, pcStringOut�ռ����>=6("true"��"false"), ����pcStringOut�ַ����ĳ��� */
int Bool2String(BOOL bVal, char *pcStringOut);

/* ��ʮ�������ַ���ת��Ϊ��Ӧ��ASC�ַ�,��"41"ת��ΪA */
char Hex2Char(const char *str);
/* ��ASC�ַ�ת��Ϊʮ�������ַ���, ����2 */
int Char2Hex(char ch, char *pcRtHex);


/* ����һ���ֵ� */
LIST *CreateDict();

/* ����һ���ֵ� */
void DeleteDict(LIST *pList);

/* ���ֵ���ɾ��һ�� */
BOOL DelDictParam(LIST *pList, const char *pcName);

/* ���һ���ֵ�(NAMEDSTRING_T, Name,Value��)���������Ƿ���ָ������
** ���������,���溯���ķ���ֵΪ:
	GetString()	""
	GetIP()		0
	GetIP4()	0
	GetInt32()	0
	GetBool()	0
*/
LISTNODE *IsExistParam(const LIST *pList, const char *pcName);

/* �����ĺ�������pcName��list������ȡ��ֵ��
** ��������ÿ���ڵ�Ԫ��ΪNAMEDSTRING_T(Name,Value��)���� */
const char *GetString(const LIST *pList, const char *pcName);
unsigned long GetIP(const LIST *pList, const char *pcName);
unsigned long GetIP4(const LIST *pList, const char *pcName);
long GetLong(const LIST *pList, const char *pcName);
BOOL GetBool(const LIST *pList, const char *pcName);

/* �����ĺ�����������list��pcName��pcValue */
LISTNODE *SetString(LIST *pList, const char *pcName, const char *pcValue);
LISTNODE *SetIP(LIST *pList, const char *pcName, unsigned long ulValue);
LISTNODE *SetLong(LIST *pList, const char *pcName, long lValue);
LISTNODE *SetBool(LIST *pList, const char *pcName, BOOL bValue);


/* Define XML structure */
typedef struct tagXML
{
	struct tagXML *pParXML;
	LISTNODE *pParXMLNode;

	char *pcName;
	LIST *plAttrib;
	LIST *plSubXML;
} XML;

XML *CreateXML(const char *pcName);
XML *CreateXMLText(const char *pcText);
void DeleteXML(XML *pXML);
XML *InsertXMLBefore(XML *pXML, XML *pInsert);
XML *InsertXMLAfter(XML *pXML, XML *pInsert);
XML *AppendXML(XML *pXML, XML *pSubXML);
XML *DetachXML(XML *pXML, XML *pSubXML);
inline XML *GetParentXML(XML *pXML);
void DumpXML(XML *pXML, void (*Dumper)(const char *, void *), void *pParam);

#endif
