/******************************************************************************/
//	���̣�RSA
//	���ܣ�RSA�ӡ������ļ�
//  ���ߣ�epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
//#include <afxwin.h>
#include <math.h>
#include "rsa.h"
#include<string.h>
#include<stdlib.h>

#define DECRYPT_FILE "RSA��������.txt"
#define ENCRYPT_FILE "RSA��������.txt"
//! Լ���ļ����2M
#define MAX_FILE	1024*1024*2

/******************************************************************************/
//	���ƣ�usage
//	���ܣ�������Ϣ
//  ������Ӧ�ó�������
//	���أ���ʾ��Ϣ

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage:rsa -k ����P ����Q\n" );
	printf( "\tusage: rsa -e �����ļ� ��Կe ��Կn\n" );
	printf( "\tusage: rsa -d �����ļ� ˽Կd ˽Կn\n" );
}

/******************************************************************************/
//	���ƣ�IsNumber
//	���ܣ��ж������ַ�����
//  ������strNumber:�ַ�����
//	���أ������������鷵��true�����򷵻�false;

/******************************************************************************/
bool IsNumber( const char *strNumber )
{
	unsigned int i;

	if( !strNumber )
		return false;

	for ( i = 0 ; i < strlen(strNumber) ; i++ )
	{
		if ( strNumber[i] < '0' || strNumber[i] > '9' )
			return false;
	}

	return true;
}

/******************************************************************************/
//	���ƣ�IsPrimeNumber
//	���ܣ��ж�����
//  ������num: ��������
//	���أ���������true�����򷵻�false;

/******************************************************************************/
bool IsPrimeNumber( unsigned int num )
{
	unsigned int i;
	if( num <= 1 )
		return false;

	unsigned int sqr = (unsigned int)sqrt((double)num);
	for( i = 2; i <= sqr; i++ )
	{
		if( num % i == 0 )
			return false;
	}

	return true;
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
	bool bRes = false;

	if( argc != 4 && argc != 5 )
		goto out;

	if( argc == 4 && argv[1][1] == 'k' )
	{
		//! ���ɹ���˽Կ��
		if( !IsNumber( argv[2] ) || 
			!IsNumber( argv[3] ) ||
			atoi( argv[2] ) > MAX_PRIME ||
			atoi( argv[3] ) > MAX_PRIME )
			goto out;
	}
	else if( (argc == 5) && (argv[1][1] == 'e' || argv[1][1] == 'd') )
	{
		//! ���ܡ����ܲ���
		if( !IsNumber( argv[3] ) ||
			!IsNumber( argv[4] ) ||
			atoi( argv[3] ) > MAX_NUM ||
			atoi( argv[4] ) > MAX_NUM )
			goto out;
	}
	bRes = true;

out:
	return bRes;
}

/******************************************************************************/
//	���ƣ�kOption1
//	���ܣ�����kѡ�������������P��Q����˽Կd����
//  ������uiP: ������ڲ���P; uiQ: ������ڲ���Q
//	���أ�ִ����ȷ��������˽Կ��Ŀ�����򷵻�0

/******************************************************************************/
unsigned int kOption1( unsigned int uiP, unsigned int uiQ )
{
	unsigned int uiRes = 0;

	if( !IsPrimeNumber( uiP ) )
	{
		printf( "P�������P����Ϊ(0, %d]����", MAX_PRIME );
		return uiRes;
	}
	if( !IsPrimeNumber( uiQ ) )
	{
		printf( "Q�������Q����Ϊ(0, %d]����", MAX_PRIME );
		return uiRes;
	}
	if( uiP == uiQ )
	{
		printf( "����P������Q��ͬ�������׸��ݹ�Կn��ƽ���ó�����P��Q�����ּ��ܲ���ȫ�����������!\n" );
		return uiRes;
	}
	printf( "��������˽Կd����......\n" );
	uiRes = MakePrivatedKeyd( uiP, uiQ );

	return uiRes;
}
#define Max 1000
unsigned int d, e, n;
unsigned int p, q;
char ctemp[Max];
int itemp[Max];
//! ����������(Use MFC in a Shared DLL)
int main( int argc, char **argv )
{
	//rsa -k ����P ����Q 
	if(argv[1][1] == 'k'){
		p = atoi(argv[2]);
		q = atoi(argv[3]);
		int size = kOption1(p, q);	//num size
		printf("private key size is %d, please choose one: \n", size);
		scanf("%d", &size);
		int ret = MakePairkey(p, q, size);
		if(ret == ERROR_NOPUBLICKEY){
			printf("ERROR_NOPUBLICKEY");
		}else if(ret == ERROR_GENERROR){
			printf("ERROR GENERROR");
		}else if(ret == OK){
			//e private d public
			printf("ret ok\n");
			n = GetPairKey(d, e);
			printf("d is %d, e is %d, n is %d\n", d, e, n);
		}else{
			printf("debug info\n");
		}
	}
		
		scanf("%s", ctemp);
		int clen = strlen(ctemp);
		
		//rsa -e ����string ��Կe ��Կn
		rsa_encrypt(n, d, ctemp, clen, itemp);
		int i;
		for(i = 0; i < clen; i++){
			printf("%d ", itemp[i]);
		}
		printf("\n");
		rsa_decrypt(n, e, itemp, clen, ctemp);
		for(i = 0; i < clen; i++){
			printf("%c ", ctemp[i]);
		}
	/*
	if(CheckParse(argc, argv)){
		if(argv[1][1] == 'k'){
			p = atoi(argv[2]);
			q = atoi(argv[3]);
			int size = kOption1(p, q);	//num size
			printf("private key size is %d,please choose one: \n", size);
			scanf("%d", size);
			int ret = MakePairkey(p, q);
			if(ret == ERROR_NOPUBLICKEY){
				printf("ERROR_NOPUBLICKEY");
			}else if(ret == ERROR_GENERROR){
				printf("ERROR GENERROR");
			}else if(ret == OK){
				//e private d public
				n = GetPairKey(d, e);
			}
			
		}else if(argv[1][1] == 'e'){
			//rsa -e ����string ��Կe ��Կn
			//rsa_encrypt( int n, int e, char *mw, int mLength, int *&cw )
			rsa_encrypt(n, d, argv[2], sizeof(argv[2]), itemp);
			int i;
			int len = sizeof(argv[2]);
			for(i = 0; i < len; i++){
				printf("%d ", itemp[i]);
			}
		}else{
			//rsa -d ����ints e n
		//	rsa_encrypt( int n, int e, char *mw, int mLength, int *&cw )
			e = atoi(argv[3]);
			n = atoi(argv[4]);

			rsa_decrypt(n, e, argv[2], sizeof(argv[2]), ctemp);
			int i;
			int len = sizeof(argv[2]);
			for(i = 0; i < len; i++){
				printf("%c ", itemp[i]);
			}
		}
	}
	*/

//	return true;
}
