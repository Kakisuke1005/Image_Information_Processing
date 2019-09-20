#include<stdio.h>
#include<stdlib.h>

int main()
{
  FILE *fp;
  int c;
  int byte;

  fp=fopen("test.bmp","wb");
  if(fp==NULL){
    printf("ファイルをオープンできません．\n");
    exit(1);
  }
  printf("ファイルをオープンしました．\n");

  printf("何バイト書き出しますか：");
  scanf("%d",&byte);

  printf("0 以上 255 以下の値を %d 個入力して下さい．\n",byte);

  for(int i=1;i<=byte;i++){
    printf("No.%d:",i);
    scanf("%d",&c);
    fputc(c,fp);
  }

  fclose(fp);
  printf("\nファイルをクローズしました．\n");

  return 0;
}
