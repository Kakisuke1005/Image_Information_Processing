#include<stdio.h>
#include<stdlib.h>

#define HEADER_SIZE 54  // ヘッダー部のサイズ
#define IMAGE_SIZE 512  // データ部のサイズ

void get_data(void);
void show_data(int num);  //ヘッダーのデータを表示
int get_decimal_number(int start,int num);  //ヘッダーのデータを10進数として計算
void processing(void);
void show_imgin_data(int num,int x,int y);  // 画像データの表示
void put_data(void);

unsigned char header[HEADER_SIZE];  // ヘッダー部のデータ
unsigned char imgin[3][IMAGE_SIZE][IMAGE_SIZE];  // データ部の画像データ
unsigned char imgout[3][IMAGE_SIZE][IMAGE_SIZE];  // 画像出力データ
int width,height,bytes;  // 画像の幅、画像の高さ、挿入バイト数

int main(void)
{
  get_data();
  processing();
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

  bytes=filesize-offset-width*height*(bits/8);
  printf("\n\n＜挿入ビット数＞\n");
  printf("%dバイト\n",bytes);

  for(i=height;i>0;i--){  // 画像データ読み込み
    for(j=0;j<width;j++){
      imgin[2][j][i-1]=fgetc(fp);
      imgin[1][j][i-1]=fgetc(fp);
      imgin[0][j][i-1]=fgetc(fp);
    }
  }

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

void processing(void)
{
  printf("\n入力データを表示します\n\n");

  if(width>25){
    printf("画像サイズが大きいため出力しません\n");
  }else{
    printf("＜R信号＞\n");
    for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
	      show_imgin_data(0,j,i);
      }
      printf("\n");
    }
    
    printf("\n＜G信号＞\n");
    for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
	      show_imgin_data(1,j,i);
      }
      printf("\n");
    }
    
    printf("\n＜B信号＞\n");
    for(int i=0;i<height;i++){
      for(int j=0;j<width;j++){
        show_imgin_data(2,j,i);
      }
      printf("\n");
    }
  }

  for(int i=0;i<3;i++){  // imginをimgoutにコピー
    for(int j=0;j<height;j++){
      for(int k=0;k<width;k++){
	      imgout[i][k][j]=imgin[i][k][j];
      }
    }
  }

  printf("出力画像データを作成しました");
}

void show_imgin_data(int num,int x,int y)
{
  if(imgin[num][x][y]>=16){
    printf("%x ",imgin[num][x][y]);
  }else{
    printf("0%x ",imgin[num][x][y]);
  }
}

void put_data()
{

  FILE *fp;
  char file_name[20];

  printf("出力ファイル名を入力して下さい");
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
