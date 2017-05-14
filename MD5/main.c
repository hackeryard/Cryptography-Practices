/******************************************************************************/
//	���̣�MD5
//	���ܣ�MD5�ӡ������ļ�
//  ���ߣ�epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
//#include <afxwin.h>
#include <string.h>
#include <stdlib.h>
#include "md5.h"

//! �ļ����2M
#define MAX_FILE 1024*1024*2

typedef int bool;
#define true 1
#define false 0

/******************************************************************************/
//	���ƣ�usage
//	���ܣ�������Ϣ
//  ������Ӧ�ó�������
//	���أ���

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: md5 �ļ�\n" );
}

/******************************************************************************/
//	���ƣ�CheckParse
//	���ܣ�У��Ӧ�ó�����ڲ���
//  ������argc����main������argc������argvָ��main������argv����
//	���أ��������Ϸ�����true�����򷵻�false
//  ��ע���򵥵���ڲ���У��

/******************************************************************************/
bool CheckParse( int argc, char** argv )
{
	if( argc != 2 )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! ������(Use MFC in a Shared DLL)
int main( int argc, char **argv )
{
	//! �ڴ˴���д����......
	int i;
	char input[1024];
	scanf("%s", input);
	unsigned int len = strlen(input);
	printf("%d\n", len);
	unsigned char out[16];
	md5_digest( input, len, out);
	for(i = 0; i < 16; i++){
		printf("%02X", out[i]);
	}
	return 0;
}
