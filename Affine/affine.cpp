#include<stdio.h>
#include<string.h>

//����������� 
int encode(int a, int b, char * str){
	int len = strlen(str);
	int i;
	for(i = 0; i < len; i++){
		int temp = a*(str[i] - 'a') + b;
		temp %= 26;
		str[i] = (char)(temp + 'a');
	}
}

//��һ��������26���� 
int aa(int a){
	int i;
	for(i = 0; i < 26; i++){
		int temp = (i*a)%26;
		if(temp == 1){
			return i;
		}
	}
}

//����������� 
int decode(int a, int b, char * str){
	int k = aa(a);
	int i, len = strlen(str);
	for(i = 0; i< len; i++){
		int temp = k*(str[i] - 'a' -b);
		temp %= 26;
		str[i] = (char) temp + 'a';
	}
}

//��ʾ������dumb�� 
void display(char * str){
	printf("%s\n", str);
}

int main(){
	char input[1024];
	int a,b;
	//input a and b
	scanf("%s", input);
	scanf("%d", &a);
	
	//loop until a is vaild
	//˼�����⣺a��26���뻥�ʣ���Ȼa���治���� 
	while(a%2 == 0 || a%13 == 0){
		scanf("%d", &a);
	}
	scanf("%d", &b);
	
	//test it 
	decode(a, b, input);
//	encode(a, b, input);
	display(input);
} 
