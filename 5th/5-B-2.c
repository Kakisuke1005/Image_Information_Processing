#include<stdio.h>
#include<stdlib.h>

#define HEADER_SIZE 54  // ヘッダー部のサイズ
#define IMAGE_SIZE 512  // データ部のサイズ

void get_data(void);
int get_decimal_number(int start,int num);  //ヘッダーのデータを10進数として計算
void processing(void);
void put_data(void);
void rgb_to_ybr(void);
void ybr_to_rgb(void);

unsigned char header[HEADER_SIZE];  // ヘッダー部のデータ
unsigned char imgin[3][IMAGE_SIZE][IMAGE_SIZE];  // データ部の画像データ
unsigned char imgout[3][IMAGE_SIZE][IMAGE_SIZE];  // 画像出力データ
int width,height,bytes;  // 画像の幅、画像の高さ、挿入バイト数

int main(void)
{
 get_data();
 rgb_to_ybr();
 processing();
 ybr_to_rgb();
 put_data();

 return 0;
}

void get_data(void)
{

  FILE *fp;
  char file_name[20];
  int i=0,j;
  int filesize,offset,bits;

  printf("入力ファイル名を入力して下さい:");
  scanf("%s",file_name);

  fp=fopen(file_name,"rb");
  if(fp==NULL){
    printf("ファイルを開けません\n");
    exit(1);
  }else{
    printf("ファイルをオープンしました\n");
  }

  while(i<HEADER_SIZE){  // ヘッダー部読み込み
    header[i]=fgetc(fp);
    i++;
  }

  printf("\n＜ファイルサイズ＞\n");
  filesize=get_decimal_number(2,4);
  printf("%dバイト\n",filesize);

  printf("\n＜オフセット＞\n");
  offset=get_decimal_number(10,4);
  printf("%dバイト\n",offset);

  printf("\n＜画像の幅＞\n");
  width=get_decimal_number(18,4);
  printf("%d画素\n",width);

  printf("\n＜画像の高さ＞\n");
  height=get_decimal_number(22,4);
  printf("%dライン\n",height);

  printf("\n＜1画素当たりのビット数＞\n");
  bits=get_decimal_number(28,2);
  printf("%dビット\n",bits);

  bytes=filesize-offset-width*height*(bits/8);
  printf("\n＜挿入ビット数＞\n");
  printf("%dバイト\n",bytes);

  for(i=height;i>0;i--){  // 画像データ読み込み
    for(j=0;j<width;j++){
      imgin[2][j][i-1]=fgetc(fp);
      imgin[1][j][i-1]=fgetc(fp);
      imgin[0][j][i-1]=fgetc(fp);
    }
  }

  fclose(fp);
  printf("\nファイルをクローズしました\n");
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

void processing(void)
{

  for(int i=0;i<3;i++){  // imginをimgoutにコピー
    for(int j=0;j<height;j++){
      for(int k=0;k<width;k++){
	      imgout[i][k][j]=imgin[i][k][j];
      }
    }
  }

  printf("入力画像データをコピーして出力画像データを作成しました\n");
}

void put_data()
{

  FILE *fp;
  char file_name[20];

  printf("出力ファイル名を入力して下さい:");
  scanf("%s",file_name);

  fp=fopen(file_name,"wb");
  if(fp==NULL){
    printf("ファイルを開けませんでした\n");
    exit(1);
  }
  printf("ファイルをオープンしました\n");

  for(int i=0;i<HEADER_SIZE;i++){  // ヘッダーのコピー
    fputc(header[i],fp);
  }

  for(int i=height;i>0;i--){  // 画像データ読み込み
    for(int j=0;j<width;j++){
      fputc(imgout[2][j][i-1],fp);
      fputc(imgout[1][j][i-1],fp);
      fputc(imgout[0][j][i-1],fp);
    }
  }

    fclose(fp);
    printf("ファイルをクローズしました\n");
}

void rgb_to_ybr(void)
{}

void ybr_to_rgb(void)
{}