#ifndef C_SENDFILE_H
#define C_SENDFILE_H

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif

/* �ÿɱ����...�滻�ַ����е�<!--Bfmt-->[text]<!--E-->���֣�
** fmtΪһ�ַ���(��������),д������printf�е�fmt,Ŀǰ��֧��:
**	%s	�ַ���
**	%d	����int
**	%u	�޷���int
**	%p	ip��ַunsigned long
**	%C	�ַ������ɺ���	int Fun(HTTPCONNECTION hc, char *pcFillBegin), �ú�����pcFillBegin��������Ӵ���������д���ַ���
*/
void SendBufferWithParam( HTTPCONNECTION hc, char *pcBuffer, int iBufLen, ...);

/* �ÿɱ����...�滻�ļ��е�<!--Bfmt-->[text]<!--E-->���֣�
** fmtΪһ�ַ���(��������),д������printf�е�fmt,Ŀǰ��֧��:
**	%s	�ַ���
**	%d	����int
**	%u	�޷���int
**	%p	ip��ַunsigned long
**	%C	�ַ������ɺ���	int Fun(HTTPCONNECTION hc, char *pcFillBegin), �ú�����pcFillBegin��������Ӵ���������д���ַ���
*/
void SendHtmlWithParam( HTTPCONNECTION hc, const char *pcFileName, ... );

#endif
