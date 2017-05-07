/******************************************************************************/
//	���̣�DES
//	���ܣ�DES�ӡ������ļ�
//  ���ߣ�epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <afxwin.h>

#include "des.h"

#define DECRYPT_FILE "DES��������.txt"
#define ENCRYPT_FILE "DES��������.txt"
//! Լ���ļ����2M
#define MAX_FILE	1024*1024*2

/******************************************************************************/
//	���ƣ�Decode
//	���ܣ����������ֻ�(unsigned char -> unsigned long int)
//  ������output:	ָ��unsigned long int�������������
//		  input:	ָ��unsigned char�������뻺����
//		  len:		�������ݳ���(�ֽ�)
//	���أ���

/******************************************************************************/
void Decode( unsigned long int *output, unsigned char *input, unsigned int len )
{
	unsigned int i, j;

	for( i=0, j=0; j<len; i++, j+=4 )
		output[i] = ((unsigned long int)input[j]) | (((unsigned long int)input[j+1]) << 8) |
		(((unsigned long int)input[j+2]) << 16) | (((unsigned long int)input[j+3]) << 24);
}

/******************************************************************************/
//	���ƣ�Encode
//	���ܣ����������ֻ�(unsigned long int -> unsigned char)
//  ������output:	ָ��unsigned char���������
//		  input:	ָ��unsigned long int���뻺����
//	���أ���

/******************************************************************************/
void Encode(unsigned char * output, unsigned long int * input){
	unsigned char * temp = (unsigned char *)input;
	output[0] = temp[0];
	output[1] = temp[1];
	output[2] = temp[2];
	output[3] = temp[3];
}

/******************************************************************************/
//	���ƣ�usage
//	���ܣ�������Ϣ
//  ������Ӧ�ó�������
//	���أ���ʾ��Ϣ

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: des -e �����ļ� 64λ��Կ\n" );
	printf( "\tusage: des -d �����ļ� 64λ��Կ\n" );
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
		(strlen( argv[3] ) >(64/8) ) )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! ����������
int main( int argc, char **argv )
{
	//! to-do
	//init cipher [64b]
	unsigned char cipher[100] = "ilikeyou";
	unsigned k1, k2;
	Decode(( unsigned long int *)&k1, cipher, 4);
	Decode(( unsigned long int *)&k2, &cipher[4], 4);
	
	unsigned char file[100] = "hackyard";
	unsigned m1, m2;
	Decode((unsigned long *)&m1, file, 4);
	Decode((unsigned long *)&m2, &file[4], 4);
	
	unsigned c1, c2;
	int i;

	//Des encode
	des_encrypt(k1, k2, m1, m2, c1, c2);
	
	//print encoded hex
	unsigned char * temp = (unsigned char *)&c1;

	for(i = 0; i< 4; i++){
		printf("%02X", temp[i]);
	}
	temp = (unsigned char *)&c2;
	
	for(i = 0; i< 4; i++){
		printf("%02X", temp[i]);
    }
    printf("\n");
    
    //Des decode
	des_decrypt(k1, k2, c1, c2, m1, m2);
	
	//print decoded hex
	temp = (unsigned char *)&m1;

	for(i = 0; i< 4; i++){
		printf("%02X", temp[i]);
	}
	temp = (unsigned char *)&m2;
	
	for(i = 0; i< 4; i++){
		printf("%02X", temp[i]);
    }
    printf("\n");
    
    //print string
    temp = (unsigned char *)&m1;
    for(i = 0; i< 4; i++){
		printf("%c", temp[i]);
	}
	temp = (unsigned char *)&m2;
	for(i = 0; i< 4; i++){
		printf("%c", temp[i]);
    }
    
    
/*	
	if(CheckParse(argc, argv)){
		if(argv[1][1] == 'e'){
			des_encrypt(k1, k2, m1, m2, c1, c2);
			unsigned char * temp = (unsigned char *)&c1;
			for(i = 0; i< 4; i++){
				printf("%02X", temp[i]);
			}
			temp = (unsigned char *)&c2;
			for(i = 0; i< 4; i++){
				printf("%02X", temp[i]);
			}
			
		}else{
			des_decrypt(k1, k2, c1, c2, m1, m2);
			
		}
	}
*/

}
