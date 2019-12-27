#include<stdio.h>

int main()
{
  double height,width;
  int ans;
  int d[2][2];
  d[0][0]=10;
  d[1][0]=20;
  d[0][1]=30;
  d[1][1]=40;

  printf("＜使用する４つの画素値＞\n");
  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      printf("%d ",d[j][i]);
    }
    printf("\n");
  }
  printf("\n");

  printf("内挿点の座標を入力して下さい\n");
  printf("水平(0.0以上1.0未満):");
  scanf("%lf",&width);
  printf("垂直(0.0以上1.1未満):");
  scanf("%lf",&height);

  // バイリニア補間法計算
  ans=(1-(height-(int)height))*(1-(width-(int)width))*d[(int)width][(int)height]+
    (1-(height-(int)height))*(width-(int)width)*d[(int)width+1][(int)height]+
    (height-(int)height)*(1-(width-(int)width))*d[(int)width][(int)height+1]+
    (height-(int)height)*(width-(int)width)*d[(int)width+1][(int)height+1];

  printf("\n＜内挿点の画素値＞\n");
  printf("%d\n",ans);
}
