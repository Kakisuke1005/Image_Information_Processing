#include<stdio.h>
#include<stdlib.h>

#define HEADER_SIZE 54  // ヘッダー部のサイズ
#define IMAGE_SIZE 512  // データ部のサイズ

void get_data(void);  // 
int get_decimal_number(int start,int num);  //ヘッダーのデータを10進数として計算
void processing(void);  // 画像の加工
void put_data(void);  // 画像データを出力
void rgb_to_ybr(void);
void ybr_to_rgb(void);
int round_off(double num);  // 四捨五入をする
int round_off_cbcr(double num);  // Cb,Cr信号に対する整数化

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
  int y,b,r;
  printf("\nコピーモードを入力して下さい\n");
  printf("(コピーする場合：1，固定値に置き換える場合：0)\n");
  printf("Y  :");
  scanf("%d",&y);
  printf("Cb :");
  scanf("%d",&b);
  printf("Cr :");
  scanf("%d",&r);

  // 画像の処理
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      switch(y){
      case 1:
	imgout[0][j][i]=imgin[0][j][i];
	break;
      case 0:
	imgout[0][j][i]=128;
	break;
      }
      switch(b){
      case 1:
	imgout[1][j][i]=imgin[1][j][i];
	break;
      case 0:
	imgout[1][j][i]=128;
	break;
      }
      switch(r){
      case 1:
	imgout[2][j][i]=imgin[2][j][i];
	break;
      case 0:
	imgout[2][j][i]=128;
	break;
      }
    }
  }
  
  printf("\n出力画像データを作成しました\n");
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
{
  double ycbcr[3];
  double transformation_matrix[3][3]={
    {0.2990,0.5870,0.1140},
    {-0.1687,-0.3313,0.5000},
    {0.5000,-0.4187,-0.0813}
  };

  // YCbCr信号に変換
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      for(int k=0;k<3;k++){
        ycbcr[k]=transformation_matrix[k][0]*imgin[0][i][j]+transformation_matrix[k][1]*imgin[1][i][j]+transformation_matrix[k][2]*imgin[2][i][j];
      }
      ycbcr[0]=round_off(ycbcr[0]);
      ycbcr[1]=round_off_cbcr(ycbcr[1]);
      ycbcr[2]=round_off_cbcr(ycbcr[2]);
      imgin[0][i][j]=ycbcr[0];
      imgin[1][i][j]=ycbcr[1];
      imgin[2][i][j]=ycbcr[2];
    }
  }
}

void ybr_to_rgb(void)
{
  double rgb[3];
  double transformation_matrix[3][3]={
    {1.0000,0.0000,1.4020},
    {1.0000,-0.3441,-0.7141},
    {1.0000,1.7720,0.0000}
  };

  // RGB信号に変換
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      for(int k=0;k<3;k++){
        rgb[k]=transformation_matrix[k][0]*imgout[0][i][j]+transformation_matrix[k][1]*(imgout[1][i][j]-128)+transformation_matrix[k][2]*(imgout[2][i][j]-128);
      }
      rgb[0]=round_off(rgb[0]);
      rgb[1]=round_off(rgb[1]);
      rgb[2]=round_off(rgb[2]);
      imgout[0][i][j]=rgb[0];
      imgout[1][i][j]=rgb[1];
      imgout[2][i][j]=rgb[2];
    }
  }    
}

int round_off(double num)
{
  double offset;

  if(num>=0.0){
    offset=0.5;
  }else{
    offset=-0.5;
  }

  num+=offset;
  if(num>255){
    num=255;
  }else if(num<0){
    num=0;
  }
  
  return (int)num;
}

int round_off_cbcr(double num)
{
  double offset;
  int ans;

  if(num>=0.0){
    offset=0.5;
  }else{
    offset=-0.5;
  }

  ans=(int)(num+offset);
  ans+=128;

  if(ans>255){
    ans=255;
  }else if(ans<0){
    ans=0;
  }

  return ans;
}
