#include<stdio.h>
#include<stdlib.h>

#define SIZE 54

void get_data(void);
void show_data(int num);  //ヘッダーのデータを表示
int get_decimal_number(int start,int num);  //ヘッダーのデータを10進数として計算

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
    show_data(i);
    i++;
  }

  printf("\n\n＜ファイルサイズ＞\n");
  while(i<6){
    show_data(i);
    i++;
  }
  filesize=get_decimal_number(2,4);
  printf("\n%dバイト\n",filesize);

  printf("\n＜予約領域＞\n");
  while(i<10){
    show_data(i);
    i++;
  }

  printf("\n\n＜オフセット＞\n");
  while(i<14){
    show_data(i);
    i++;
  }
  offset=get_decimal_number(10,4);
  printf("\n%dバイト\n",offset);

  printf("\n＜情報ヘッダサイズ＞\n");
  while(i<18){
    show_data(i);
    i++;
  }

  printf("\n\n＜画像の幅＞\n");
  while(i<22){
    show_data(i);
    i++;
  }
  width=get_decimal_number(18,4);
  printf("\n%d画素\n",width);

  printf("\n＜画像の高さ＞\n");
  while(i<26){
    show_data(i);
    i++;
  }
  height=get_decimal_number(22,4);
  printf("\n%dライン\n",height);

  printf("\n＜色プレーン数＞\n");
  while(i<28){
    show_data(i);
    i++;
  }

  printf("\n\n＜1画素当たりのビット数＞\n");
  while(i<30){
    show_data(i);
    i++;
  }
  bits=get_decimal_number(28,2);
  printf("\n%dビット\n",bits);

  printf("\n＜圧縮方式＞\n");
  while(i<34){
    show_data(i);
    i++;
  }

  printf("\n\n＜画像データサイズ＞\n");
  while(i<38){
    show_data(i);
    i++;
  }

  printf("\n\n＜水平解像度＞\n");
  while(i<42){
    show_data(i);
    i++;
  }

  printf("\n\n＜垂直解像度＞\n");
  while(i<46){
    show_data(i);
    i++;
  }

  printf("\n\n＜色数＞\n");
  while(i<50){
    show_data(i);
    i++;
  }

  printf("\n\n＜重要な色数＞\n");
  while(i<54){
    show_data(i);
    i++;
  }

  printf("\n\n＜挿入ビット数＞\n");
  printf("%dバイト\n",filesize-offset-width*height*(bits/8));

  fclose(fp);
  printf("ファイルをクローズしました\n");
}

void show_data(int num)
{
  if(header[num]>=16){
      printf("header[%d]=%x ",num,header[num]);
    }else{
      printf("header[%d]=0%x ",num,header[num]);
    }
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