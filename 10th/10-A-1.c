#include<stdio.h>

int main()
{
  double height,width;
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
  printf("水平(1.0以上1.0未満):");
  scanf("%lf",&width);
  printf("垂直(1.0以上1.1未満):");
  scanf("%lf",&height);

  printf("\n＜内挿点の画素値＞\n");
  printf("%d\n",d[(int)(width+0.5)][(int)(height+0.5)]);
}
