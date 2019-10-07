#include<stdio.h>
#include<stdlib.h>

#define SIZE 54

void get_data(void);
int get_decimal_number(int start,int num);

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
  int filesize,offset,width,height,bits;

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
      printf("header[%d]=%x ",i,header[i]);
    }else{
      printf("header[%d]=0%x ",i,header[i]);
    }
    i++;
  }

  printf("\n\n＜ファイルサイズ＞\n");
  while(i<6){
    if(header[i]>16){
      printf("header[%d]=%x ",i,header[i]);
    }else{
      printf("header[%d]=0%x ",i,header[i]);
    }
    i++;
  }
  filesize=get_decimal_number(2,4);
  printf("\n%dバイト\n",filesize);

  printf("\n＜予約領域＞\n");
  while(i<10){
    if(header[i]>16){
      printf("header[%d]=%x ",i,header[i]);
    }else{
      printf("header[%d]=0%x ",i,header[i]);
    }
    i++;
  }

  printf("\n\n＜オフセット＞\n");
  while(i<14){
    if(header[i]>16){
      printf("header[%d]=%x ",i,header[i]);
    }else{
      printf("header[%d]=0%x ",i,header[i]);
    }
    i++;
  }
  offset=get_decimal_number(10,4);
  printf("\n%dバイト\n",offset);

  printf("\n＜情報ヘッダサイズ＞\n");
  while(i<18){
    if(header[i]>16){
      printf("header[%d]=%x ",i,header[i]);
    }else{
      printf("header[%d]=0%x ",i,header[i]);
    }
    i++;
  }

  printf("\n\n＜画像の幅＞\n");
  while(i<22){
    if(header[i]>16){
      printf("header[%d]=%x ",i,header[i]);
    }else{
      printf("header[%d]=0%x ",i,header[i]);
    }
    i++;
  }
  width=get_decimal_number(18,4);
  printf("\n%d画素\n",width);

  fclose(fp);
  printf("ファイルをクローズしました\n");
}

int get_decimal_number(int start,int num)
{
  int ans=0;
  int i=0;
  int tmp;

  while(i<num){
     if(i==0){
      tmp=1;
    }else if(i==1){
      tmp=256;
    }else if(i==2){
      tmp=65536;
    }else if(i==3){
      tmp=16777216;
    }
    ans+=(header[start]*tmp);
    start++;
    i++;
  }
  return ans;
}