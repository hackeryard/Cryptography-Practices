/******************************************************************************/
//	���̣�Singletable
//	���ܣ�Singletable�ӡ������ļ�
//  ���ߣ�epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "singletable.h"

#define DECRY_FILE "��������.txt"
#define ENCRY_FILE "��������.txt"

/******************************************************************************/
//	���ƣ�usage
//	���ܣ�������Ϣ
//  ������Ӧ�ó�������
//	���أ���ʾ��Ϣ

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: singletable -e �����ļ� ��Կ����\n" );
	printf( "\tusage: singletable -d �����ļ� ��Կ����\n" );
}

/******************************************************************************/
//	���ƣ�FileIN
//	���ܣ���/����  ���  �������ǰĿ¼�����ļ���
//  ������strFile --> strIn
//	���أ����³ɹ�����ʵ��������ȣ����򷵻�0
 
/******************************************************************************/

int FileIn( const char *strIn, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iRead=0;

	if( strIn == NULL || len ==0 )
		return false;


	//! ���ļ����
	if( (fp = fopen( strFile,"r" )) == NULL )	// �ı�ģʽд
		return false;


	iRead = fread((void *)strIn, 1, len, fp );//len 3 [0]
	printf("%d", iRead);

	char * hjk = (char *)strIn;
	*(hjk+iRead) = '\0';
//	strIn[iRead] = '\0';
	fclose(fp);

	if( iRead>0 )
		return true;
	else
		return false;
}

/******************************************************************************/
//	���ƣ�FileOut
//	���ܣ���/���ܽ���������ǰĿ¼�����ļ���
//  ������strOutָ������ַ��������������Сlen��strFileΪ����ļ�
//	���أ����³ɹ�����ʵ��������ȣ����򷵻�0

/******************************************************************************/
int FileOut( const char *strOut, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iWrite=0;

	if( strOut == NULL || len ==0 )
		return false;

	//! ���ļ����
	if( (fp = fopen( strFile,"w" )) == NULL )	// �ı�ģʽд
		return false;

	iWrite = fwrite( strOut, 1, len, fp );
	fclose(fp);

	if( iWrite>0 )
		return true;
	else
		return false;
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
	if( argc != 4 )
	{
		Usage( argv[0] );
		return false;
	}

	if( argv[1][1]!='e' && argv[1][1]!='d')
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! ����������
int main( int argc, char **argv )
{

	char plain[1024];
	char crpt[1024];


	char * k = argv[3];

	if(CheckParse(argc, argv)){//true
		if(argv[1][1] == 'e'){

			FileIn( plain, 1024, argv[2]);
			printf("%s\n", plain);//qqq
			printf("%d\n", strlen(plain));//3

			if(UpdateChrTab(k, strlen(k) ) ){
				Encry(plain, strlen(plain), crpt, sizeof(crpt));
				printf("%d\n", strlen(plain));//3
				FileOut(crpt, strlen(plain), DECRY_FILE);
			}else{
				exit(0);
			}

		}else if(argv[1][1] == 'd'){
			FileIn( crpt, 1024, argv[2]);
			printf("%s\n", crpt);//qqq
			printf("%d\n", strlen(crpt));//3


			if(UpdateChrTab(k, strlen(k) ) ){
				Decry(crpt , strlen(crpt), plain, sizeof(plain));
				printf("%d\n", strlen(crpt));//3
				FileOut(plain, strlen(crpt), ENCRY_FILE);
			}else{
				exit(0);
			}
		}
		
	}else{
		printf("error argc!\n");
		exit(0);//false
	}

	return 0;
}