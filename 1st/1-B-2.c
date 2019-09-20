#include<stdio.h>
#include<stdlib.h>

#define MAX_DATA 100

void File_result(FILE *fp);

int main()
{
  FILE *fp;
  int byte=0;
  int c;
  unsigned char array[MAX_DATA];

  fp=fopen("test.bmp","rb");
  File_result(fp);
  printf("読み込み用ファイルをオープンしました．\n");

  c=fgetc(fp);
  while(c!=EOF){
    array[byte]=c;
    c=fgetc(fp);
    byte++;
  }
  printf("%d個のデータを読み込み、配列に格納しました．\n",byte);

  fclose(fp);
  printf("読み込み用ファイルをクローズしました．\n\n");

  printf("配列の内容を表示します．\n");
  for(int i=0;i<byte;i++){
    printf("ary[%d]=%d\n",i,array[i]);
  }
  printf("\n");

  fp=fopen("testcp.bmp","wb");
  File_result(fp);
  printf("書き出し用ファイルをオープンしました．\n");

  for(int i=0;i<byte;i++){
    fputc(array[i],fp);
  }

  printf("配列に格納されていた%d個のデータを書き出しました．\n",byte);

  fclose(fp);
  printf("書き出し用ファイルをクローズしました．\n");

  return 0;
}

void File_result(FILE *fp)
{
  if(fp==NULL){
    printf("ファイルをオープンできません．\n");
    exit(1);
  }
}
