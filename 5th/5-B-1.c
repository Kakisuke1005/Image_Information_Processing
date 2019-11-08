#include<stdio.h>

int round_off(double num);  // 四捨五入をする
int round_off_cbcr(double num);  // Cb,Cr信号に対する整数化

int main()
{
  int rgb_in[3];
  double ycbcr[3];
  double rgb_out[3];
  double rgb_to_ycbcr[3][3]={
    {0.2990,0.5870,0.1140},
    {-0.1687,-0.3313,0.5000},
    {0.5000,-0.4187,-0.0813}
  };
  double ycbcr_to_rgb[3][3]={
    {1.0000,0.0000,1.4020},
    {1.0000,-0.3441,-0.7141},
    {1.0000,1.7720,0.0000}
  };

  // 信号値の入力
  printf("信号値を入力して下さい(整数値)\n");
  printf("R:  ");
  scanf("%d",&rgb_in[0]);
  printf("G:  ");
  scanf("%d",&rgb_in[1]);
  printf("B:  ");
  scanf("%d",&rgb_in[2]);

  // 入力されたRGB信号の表示
  printf("\n＜入力されたRGB信号(整数値)＞\n");
  printf("R:  %d\n",rgb_in[0]);
  printf("G:  %d\n",rgb_in[1]);
  printf("B:  %d\n",rgb_in[2]);

  // 実数値としてYCbCr信号に変換
  for(int i=0;i<3;i++){
    ycbcr[i]=rgb_to_ycbcr[i][0]*rgb_in[0]+rgb_to_ycbcr[i][1]*rgb_in[1]+rgb_to_ycbcr[i][2]*rgb_in[2];
  }

  // YCbCr信号を実数値で表示
  printf("\n＜変換されたYCbCr信号(実数値)＞\n");
  printf("Y:  %4.4f\n",ycbcr[0]);
  printf("Cb: %4.4f\n",ycbcr[1]);
  printf("Cr: %4.4f\n",ycbcr[2]);

  // YCbCr信号を整数値で表示
  printf("\n＜変換されたYCbCr信号(整数値)＞\n");
  printf("Y:  %d\n",round_off(ycbcr[0]));
  printf("Cb: %d\n",ycbcr[1]);
  printf("Cr: %d\n",ycbcr[2]);


  return 0;
}

int round_off(double num)
{
  double offset;
  if(num>=0.0){
    offset=0.5;
  }else{
    offset=-0.5;
  }

  return (int)(num+offset);
}

int round_off_cbcr(double num)
{}
