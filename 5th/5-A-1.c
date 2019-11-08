#include<stdio.h>

int main()
{
  double rgb_in[3];
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
  printf("信号値を入力して下さい(実数値)\n");
  printf("R:  ");
  scanf("%lf",&rgb_in[0]);
  printf("G:  ");
  scanf("%lf",&rgb_in[1]);
  printf("B:  ");
  scanf("%lf",&rgb_in[2]);

  printf("\n＜入力されたRGB信号(実数値)＞\n");
  printf("R:  %4.4f\n",rgb_in[0]);
  printf("G:  %4.4f\n",rgb_in[1]);
  printf("B:  %4.4f\n",rgb_in[2]);

  // RGB信号からYCbCrに変換
  for(int i=0;i<3;i++){
    ycbcr[i]=rgb_to_ycbcr[i][0]*rgb_in[0]+rgb_to_ycbcr[i][1]*rgb_in[1]+rgb_to_ycbcr[i][2]*rgb_in[2];
  }

  printf("\n＜変換されたYCbCr信号(実数値)＞\n");
  printf("Y:  %4.4f\n",ycbcr[0]);
  printf("Cb: %4.4f\n",ycbcr[1]);
  printf("Cr: %4.4f\n",ycbcr[2]);

  // 再度RGB変換
  for(int i=0;i<3;i++){
    rgb_out[i]=ycbcr_to_rgb[i][0]*ycbcr[0]+ycbcr_to_rgb[i][1]*ycbcr[1]+ycbcr_to_rgb[i][2]*ycbcr[2];
  }

  printf("\n＜再度変換されたRGB信号(実数値)＞\n");
  printf("R:  %4.4f\n",rgb_out[0]);
  printf("G:  %4.4f\n",rgb_out[1]);
  printf("B:  %4.4f\n",rgb_out[2]);

  return 0;
}
