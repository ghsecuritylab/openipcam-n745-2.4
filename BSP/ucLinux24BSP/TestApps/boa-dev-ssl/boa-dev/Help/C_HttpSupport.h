#ifndef C_HTTPSUPPORT_H
#define C_HTTPSUPPORT_H

/* �ֽ�һ�������Ӵ��������һ��LIST�ṹ��˫��������
** eg: pcString = "name1=&name2=value2&name3=val%20ue3",
** �ֽ��õ�������Ϊ: "name1"��NULL, "name2"�� "value2", "name3"�� "val u3"
** ������ÿ���ڵ����һNAMEDSTRING_T����(CommonDef.h)������ */
LIST *ParseString(const char *pcString);

/* �ͷ�ParseString�������ɵ��������е��ַ�����Դ */
void DeleteParseString(LIST *pList);


/* ��ȡ��Get�������ص��ַ����������ַ��ֽ��Name,Value�Ե���ʽ��
** ��GetQueryString��ParseString���ۺ�
** ���ص�������ÿ���ڵ����һNAMEDSTRING_T���͵����� */
LIST *ReadQueryList(HTTPCONNECTION hc);
/* �ͷ�ReadQueryList���ɵ�������ʹ�õ���Դ */
void DeleteQueryList(LIST *pList);

/* http��ʽ�ϴ��ļ�
** �ϴ��ɹ�����0,ʧ�ܷ���һ�����Ĵ����.
** ע����ú���ͬ���Ĳ�����һ��HttpUploadClear
		- ���ppcSavePath��ΪNULL, ��ppcSavePath��Ϊ�����Ŀ¼
		- ���pFileList��ΪNULL, ���¼������ļ��б���Ҫ����
** return 0		�ɹ�
** return -1	��������
** return -2	�ļ�������С
** return -3	�ļ��������
*/
int HttpUpload(HTTPCONNECTION hConnection, char *pcReceiveBuf, int iReceiveLen, char *pcDefaultSavePath, char **ppcSavePath, LIST **ppFileList);
/* HttpUpload�ƺ� */
void HttpUploadClear(HTTPCONNECTION hConnection, char **ppcSavePath, LIST **ppFileList);

#endif
