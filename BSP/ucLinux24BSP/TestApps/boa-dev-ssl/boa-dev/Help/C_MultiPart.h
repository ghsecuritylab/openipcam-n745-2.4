#ifndef C_MULTIPART_H
#define C_MULTIPART_H

typedef struct
{
	LIST *plPartDiscription;	//LIST of MULTIPART_DESCRIPTION_T;
	char *pcPartBody;
	int	iPartBodyLength;
} INNERPART_T;

typedef struct
{
	char *pcSegStart;//������
	char *pcSegEnd;	//������
} SPLIT_ITEM_T;

/* �ָ�pcBuffer, (iBufferLength - pBuffer����)
   iMaxReturn, ���ķָ���Ŀ

	�ָ��ж�����
	char *pcSeperator(char *pcBeing, char *pcEnd, char *pcCur, void *pSeperatorParam);
		pcBegin - pBuffer
		pcEnd - pBuffer + iBufferLength
		pcCur - λ��[pcBegin, pcEnd)֮���ĳ��λ��
		���pcCur�����Ϸָ��ж�����, ������һ�ε�λ��
		����, ����NULL
*/

LIST *SplitBuffer(char *pcBuffer, int iBufferLength, int iMaxReturn, char *pcSeperator(char *pcBeing, char *pcEnd, char *pcCur, void *pSeperatorParam), void *pSeperatorParam);
void DeleteSplitBuffer(LIST *pList);

LIST *ParseDescriptionLine(char *pcDescription, int iDescriptionLength);
void DeleteDescriptionLine(LIST *pList);

LIST *ParseDescription(char *pcDescription, int iDescriptionLength);
void DeleteDescription(LIST *pList);

INNERPART_T *ParseSinglePart(char *pcSinglePartSource, int iSinglePartSourceLength);
void DeleteSinglePart(INNERPART_T *pInnerPart);

LIST *ParseMultiPart(char *pcMultiPartSource, int iMultiPartSourceLength, char *pcBoundary);
void DeleteMultiPart(LIST *pList);

#endif
