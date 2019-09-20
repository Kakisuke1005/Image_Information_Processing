#include<stdio.h>
#include<stdlib.h>

int main()
{
  FILE *fp;
  int c;
  int byte=0;

  fp=fopen("test.bmp","rb");
  if(fp==NULL){
    printf("ファイルをオープンできません．\n");
    exit(1);
  }

  printf("ファイルをオープンしました．\n");
  c=fgetc(fp);
  while(c!=EOF){
    printf("%3d\n",c);
    c=fgetc(fp);
    byte++;
  }

  printf("全部で%dバイト読み込みました．\n",byte);

  fclose(fp);
  printf("ファイルをクローズしました．\n");
  return 0;
}
