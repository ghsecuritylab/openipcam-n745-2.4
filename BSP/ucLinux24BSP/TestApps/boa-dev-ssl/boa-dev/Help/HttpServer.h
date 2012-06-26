#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#define weak_alias(name, aliasname) \
extern __typeof (name) aliasname __attribute__ ((weak, alias (#name)));

typedef void *HTTPCONNECTION;
typedef int (*REQUEST_CALLBACK_PFUN)(HTTPCONNECTION hc, void *pParam);

typedef void *HTTPSERVER;

#include <sys/time.h>
#include "C_List.h"
#include "C_String.h"
#include "C_ConfigFile.h"
#include "C_HttpSupport.h"
#include "C_SendFile.h"
#include "C_MultiPart.h"

/* ����һ��������, ���û��ύhttp://hostname/<cpAccessName>?[parameters]������ʱ��
** ת��ô�������
** ����������0��ʾ�����ٽ���ȱʡ�������ط�0��ʾ��Ҫ����ȱʡ���� */
int RegisterEmbedFun(const char *pcAccessName, REQUEST_CALLBACK_PFUN funRequestCallBack, void *pParam);
/* ����ô������Ĺ��� */
int UnregisterEmbedFun(const char *pcAccessName);
/* ��������Ѿ����صĺ��� */
void ClearEmbedFun(void);

/* ���嵱���ݷ�����Ϻ�Ļص����� */
typedef int (*SEND_DATA_OVER_PFUN)(HTTPCONNECTION hConnection, time_t *tLastFill, void *pParam);
void SetSendDataOverFun(HTTPCONNECTION hConnection, SEND_DATA_OVER_PFUN funOnSendDataOver, void *pParam);

/* �����յ�POST������Ļص�����
** Return 0, �����������, ���رմ˴�����
** Return 1, ��������Ҫ��������, �����ִ˴�����
** Return -1, ������������, ���رմ˴����� */
typedef int (*POST_DATA_PFUN)(HTTPCONNECTION hConnection,
								int *piPostState,
								char **ppcPostBuf,
								int *piPostBufLen,
								int *piPostDataLen,
								char *pcFillData,
								int iFillDataLen,
								int iIsMoreData/*bool*/,
								void *pParam/*other parameter for extend use*/);

void SetPostDataFun(HTTPCONNECTION hConnection, POST_DATA_PFUN funPostDataGot, void *pParam);
void AddHttpBody(HTTPCONNECTION hConnection, const char *pcBuf2Add, int iBufLen);
void AddHttpBodyString(HTTPCONNECTION hConnection, const char *pcString);

/* ����Http KeepAlive����, must be called before SetHttpHeader() */
void SetKeepAliveMode(HTTPCONNECTION hConnection, BOOL bIsKeepAlive);
void SetHttpHeader(HTTPCONNECTION hConnection, int iStatus, const char *pcTitle, const char *pcEncodings, const char *pcExtraheads, const char *pcContentType, BOOL bShowLength);
/* ȡ�ü���document root����ַ���, ������Ҫfree */
char *GetDocumentBasedPath(char *pcUriPath);
/* ����Http��������֧��ssl */
HTTPSERVER StartThttpdEx3(char *pcServerRoot,
				int *piPort,
				int *piSSLPort,
				int iKeepAliveTimeout,
				int iKeepAliveMax,
				int iMaxConnections,
				int (*pOnListenSocketCreate)(int fd, int iPort),
				int (*pOnHttpInit)(HTTPSERVER hServer),
				REQUEST_CALLBACK_PFUN pOnRequestBegin);
/* ����Http������, ֧�ָ���listen socket�Ľ��� */
HTTPSERVER StartThttpdEx2(char *pcServerRoot,
				int *piPort,
				int iKeepAliveTimeout,
				int iKeepAliveMax,
				int iMaxConnections,
				int (*pOnListenSocketCreate)(int fd, int iPort),
				int (*pOnHttpInit)(HTTPSERVER hServer),
				REQUEST_CALLBACK_PFUN pOnRequestBegin);
/* ����Http������, ֧�ֶ��port */
HTTPSERVER StartThttpdEx(char *pcServerRoot,
				int *piPort,
				int iKeepAliveTimeout,
				int iKeepAliveMax,
				int iMaxConnections,
				int (*pOnHttpInit)(HTTPSERVER hServer),
				REQUEST_CALLBACK_PFUN pOnRequestBegin);
/* ����Http������ */
HTTPSERVER StartThttpd(char *pcServerRoot,
				int iPort,
				int iKeepAliveTimeout,
				int iKeepAliveMax,
				int iMaxConnections,
				int (*pOnHttpInit)(HTTPSERVER hServer),
				REQUEST_CALLBACK_PFUN pOnRequestBegin);


/****************** METHODS *****************/
#define	M_INVALID	-1
#define	M_SHORT	0
#define M_GET		1
#define M_HEAD		2
#define M_PUT		3
#define M_POST		4
#define M_DELETE	5
#define M_LINK		6
#define M_UNLINK	7
/* ȡ������ķ��� HEAD, GET, POST, ...*/
int GetHttpMethod(HTTPCONNECTION hConnection);
/* ȡ��Client��ַ */
struct in_addr GetClientAddr(HTTPCONNECTION hConnection);
/* ȡ��Client MAC��ַ, ����һ������Ϊ6���ַ����� */
char *GetClientMac(HTTPCONNECTION hConnection);
/* ȡ���û���GET�����ύ����ʱ���ӵĲ���, δ���� */
char *GetQueryString(HTTPCONNECTION hConnection);
/* ȡ�ý���������·��, ip�Ժ�Ĳ���, ����query */
char *GetRequestPath(HTTPCONNECTION hConnection);
/* ȡ�������ʵ���ļ�·�� */
char *GetRequestFilePath(HTTPCONNECTION hConnection);
/* ȡ��Referer */
char *GetReferer(HTTPCONNECTION hConnection);
/* ȡ��Content-type */
char *GetContentType(HTTPCONNECTION hConnection);
/* ȡ��Content-length */
int GetContentLength(HTTPCONNECTION hConnection);



/* ����Ȩ�޴ӵ͵��ߣ���Ҫ�ı���ֵ! */
#define AUTH_ANY -1
#define AUTH_USER 0
#define AUTH_ADMIN 1
#define AUTH_SYSTEM 2
int RegisterEmbedFunEx(const char *pcAccessName, REQUEST_CALLBACK_PFUN funRequestCallBack, int iPrivilegeRequired, void *pParam);
BOOL IsRegisterEmbedFunEx(const char *pcAccessName, REQUEST_CALLBACK_PFUN *pfunRequestCallBack, int *piPrivilegeRequired, void **ppParam);

char *GetCurrentUser(HTTPCONNECTION hConnection, char *pcUser, int iUserLen);
int GetAuthPrivilege(HTTPCONNECTION hConnection);
int SendAuthRequired(HTTPCONNECTION hConnection, int iPrivilege);
void SetAuthPrompt(const char *pcUserPrompt, const char *pcAdminPrompt, const char *pcSystemPrompt);
BOOL AuthGetUser(const char *pcUserName, char *pcPassword, int iMaxPassLen, int *piPrivilege);
int AuthSetUser(const char *pcUserName, const char *pcPassword, int iPrivilege);
int AuthDelUser(const char *pUserName);
LIST **GetAuthUserList();
void EnableUserCheck(BOOL bIsEnable);
BOOL IsEnableUserCheck(void);


#endif
