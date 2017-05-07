/******************************************************************************/
//	���̣�AES
//	���ܣ�AES�ӡ������ļ�
//  ���ߣ�epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <afxwin.h>

#include "aes.h"

#define DECRYPT_FILE "AES��������.txt"
#define ENCRYPT_FILE "AES��������.txt"
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
	printf( "\n\tusage: aes -e �����ļ� 128λ��Կ\n" );
	printf( "\tusage: aes -d �����ļ� 128λ��Կ\n" );
}

/******************************************************************************/
//	���ƣ�FileOut
//	���ܣ���/���ܽ���������ǰĿ¼�����ļ���
//  ������strOutָ������ַ��������������Сlen��strFileΪ����ļ�
//	���أ����³ɹ�����ʵ��������ȣ����򷵻�0

/******************************************************************************/
int FileOut( const void *strOut, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iWrite=0;

	if( strOut == NULL || len ==0 )
		goto out;

	//! ���ļ����
	if( (fp = fopen( strFile,"wb" )) == NULL ) // ������д
		goto out;

	iWrite = fwrite( strOut, 1, len, fp );
	fclose(fp);

out:
	return iWrite;
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
	if( (argc != 4) || 
		(argv[1][1]!='e' && argv[1][1]!='d') ||
		(strlen( argv[3] ) >(128/8) ) )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//��len���ȵ�uchar��������ת����ulong����
//������ôת����Ҫ��AES api�����uint���������ʹ�õ� 
void Decode( unsigned long int *output, unsigned char *input, unsigned int len )
{
	unsigned int i, j;

	for( i=0, j=0; j<len; i++, j+=4 )
		output[i] = ((unsigned long int)input[j]) | (((unsigned long int)input[j+1]) << 8) |
		(((unsigned long int)input[j+2]) << 16) | (((unsigned long int)input[j+3]) << 24);
}

//ÿ�ΰ�һ��ulong���͵�����ת�����ĸ�uchar������ӡ���� 
void Encode(unsigned char * output, unsigned long int * input){
	unsigned char * temp = (unsigned char *)input;
	output[0] = temp[0];
	output[1] = temp[1];
	output[2] = temp[2];
	output[3] = temp[3];
	int i;
	for(i = 0; i < 4; i++){
		printf("%c", output[i]);
	}
}

//! ����������
int main( int argc, char **argv )
{
	//in -> out
	unsigned char keytemp[100] = "hacking1hacking2hacking3hacking4";//256b -> 32B ->4int
	
	char intemp[100] = "hackingwhackinge";
	unsigned int * minwen = (unsigned int *)malloc(16);
	Decode((unsigned long *)minwen, (unsigned char *)intemp, 16);
	
	//Aes encode 
	aes_encrypt(keytemp, minwen);	
 	
 	//Aes decode
	//���������Ѿ����ܣ���ʱminwen�����ŵ��������� 
 	aes_decrypt(keytemp, minwen);
 	unsigned char * output = (unsigned char *)malloc(16);
 	Encode(output, (unsigned long *)minwen);
 	Encode(output, (unsigned long *)&minwen[1]);
 	Encode(output, (unsigned long *)&minwen[2]);
 	Encode(output, (unsigned long *)&minwen[3]);
	return 0;
}
