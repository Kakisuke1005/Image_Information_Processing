#include<stdio.h>
#include<stdlib.h>

#define IMG_SIZE 512
#define HEADER_SIZE 54

void get_data(char *argv[]);

unsigned char header[HEADER_SIZE];
unsigned char imgin[3][HEADER_SIZE][HEADER_SIZE];
unsigned char imgout[3][HEADER_SIZE][HEADER_SIZE];
int filesize,height,width;

int main(int argc,char *argv[])
{
	get_data(argv);
	return 0;
}

void get_data(char *argv[])
{
	FILE *fp;
	fp=fopen(argv[1],"rb");
	if(fp==NULL){
		printf("Cannot open the file\n");
		exit(1);
	}else{
		printf("入力画像:%s\n",argv[1]);
	}
}