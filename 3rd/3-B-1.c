#include<stdio.h>
#include<stdlib.h>

#define SIZE 54

void get_data(void);

unsigned char header[SIZE];  // ヘッダー部のデータ

int main(void)
{

  get_data();

  return 0;
}

void get_data(void)
{

  FILE *fp;
  char file_name[20];
  int c;
  int i=0;
  int byte=0;
  int buff;

  printf("入力ファイル名を入力して下さい:");
  scanf("%s",file_name);

  fp=fopen(file_name,"rb");
  if(fp==NULL){
    printf("ファイルを開けません\n");
    exit(1);
  }else{
    printf("ファイルをオープンしました\n");
  }

  c=(char)fgetc(fp);
  while(i<SIZE){
    header[i]=c;
    c=fgetc(fp);
    i++;
  }
  i=0;

  printf("\n＜ファイルタイプ＞\n");
  while(i<2){
    if(header[i]>16){
      printf("header[%d]=%2x ",i,header[i]);
    }else{
      printf("header[%d]=0%x ",i,header[i]);
    }
    i++;
  }
  printf("\n");

  printf("\n＜ファイルサイズ＞\n");
  while(i<6){
    if(header[i]>16){
      printf("header[%d]=%2x ",i,header[i]);
    }else{
      printf("header[%d]=0%x ",i,header[i]);
    }
    if(i==2){
      buff=1;
    }else if(i==3){
      buff=256;
    }else if(i==4){
      buff=65536;
    }else if(i==5){
      buff=16777216;
    }
    byte+=header[i]*buff;
    i++;
  }

  printf("\n%dバイト\n",byte);

  fclose(fp);
}
