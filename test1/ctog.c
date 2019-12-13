#include<stdio.h>
#include<stdlib.h>

#define IMG_SIZE 512
#define HEADER_SIZE 54

void get_data(char *argv[]);
void rgb_to_ybr(void);
int round_off(double num);
int round_off_br(double num);
void proccessing(void);
void ybr_to_rgb(void);
void put_data(char *argv[]);

unsigned char header[HEADER_SIZE];
unsigned char imgin[3][IMG_SIZE][IMG_SIZE];
unsigned char imgout[3][IMG_SIZE][IMG_SIZE];
int filesize,height,width;

int main(int argc,char *argv[])
{
  get_data(argv);
  rgb_to_ybr();
  proccessing();
  ybr_to_rgb();
  put_data(argv);
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
  
  for(int i=0;i<HEADER_SIZE;i++){
    header[i]=fgetc(fp);
  }
  
  filesize=*(int *)&header[2];
  printf("＜ファイルサイズ＞\n");
  printf("%dバイト\n",filesize);
  width=*(int *)&header[18];
  printf("＜画像の幅＞\n");
  printf("%d画素\n",width);
  height=*(int *)&header[22];
  printf("＜画像の高さ＞\n");
  printf("%dライン\n",height);
  
  for(int i=height-1;i>0;i--){
    for(int j=0;j<width;j++){
      imgin[2][j][i]=fgetc(fp);
      imgin[1][j][i]=fgetc(fp);
      imgin[0][j][i]=fgetc(fp);
    }
  }
  
  fclose(fp);
}

void rgb_to_ybr(void)
{
  double ycbcr[3];
  double transformation[3][3]={
    {0.2990,0.5870,0.1140},
    {-0.1687,-0.3313,0.5000},
    {0.5000,-0.4187,-0.0813}
  };
  
  for(int i=0;i<width;i++){
    for(int j=0;j<height;j++){
      for(int k=0;k<3;k++){
	ycbcr[k]=transformation[k][0]*imgin[0][i][j]+transformation[k][1]*imgin[1][i][j]+transformation[k][2]*imgin[2][i][j];
      }
      imgin[0][i][j]=round_off(ycbcr[0]);
      imgin[1][i][j]=round_off_br(ycbcr[1]);
      imgin[2][i][j]=round_off_br(ycbcr[2]);
    }
  }
}

int round_off(double num)
{
  double offset;
  
  if(num>=0){
    offset=0.5;
  }else{
    offset=-0.5;
  }
  
  num+=offset;
  if(num>255){
    num=255;
  }else if(num<=0){
    num=0;
  }
  
  return (int)num;
}

int round_off_br(double num)
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

void proccessing(void)
{
  for(int i=0;i<width;i++){
    for(int j=0;j<height;j++){
      imgout[0][i][j]=imgin[0][i][j];
      imgout[1][i][j]=128;
      imgout[2][i][j]=128;
    }
  }
}

void ybr_to_rgb(void)
{
  double rgb[3];
  double transformation[3][3]={
    {1.0000,0.0000,1.4020},
    {1.0000,-0.3441,-0.7141},
    {1.0000,1.7720,0.0000}
  };

  for(int i=0;i<width;i++){
    for(int j=0;j<height;j++){
      for(int k=0;k<3;k++){
	rgb[k]=transformation[k][0]*imgout[0][i][j]+transformation[k][1]*(imgout[1][i][j]-128)+transformation[k][2]*(imgout[2][i][j]-128);
      }
      for(int k=0;k<3;k++){
	imgout[k][i][j]=round_off(rgb[k]);
      }
    }
  }
}

void put_data(char *argv[])
{
  FILE *fp;
  fp=fopen(argv[2],"wb");
  if(fp==NULL){
    printf("Cannot open the file\n");
    exit(1);
  }else{
    printf("出力画像: %s\n",argv[2]);
  }
  
  for(int i=0;i<HEADER_SIZE;i++){
    fputc(header[i],fp);
  }
  
  for(int i=height-1;i>0;i--){
    for(int j=0;j<width;j++){
      fputc(imgout[2][j][i],fp);
      fputc(imgout[1][j][i],fp);
      fputc(imgout[0][j][i],fp);
    }
  }
  
  fclose(fp);
}
