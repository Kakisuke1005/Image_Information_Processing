#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

void file_open_result(FILE *fp,char file_name[MAX_SIZE]);

int main()
{
  FILE *fp;
  int count=0;
  int c;
  unsigned char ary[MAX_SIZE];
  char file_name[2][MAX_SIZE];

  printf("コピー元のファイル名を入力して下さい: ");
  scanf("%s",file_name[0]);
  printf("コピー先のファイル名を入力して下さい: ");
  scanf("%s",file_name[1]);
  printf("\n");

  fp=fopen(file_name[0],"rb");
  file_open_result(fp,file_name[0]);

  c=fgetc(fp);
  while(c!=EOF){
    ary[count]=c;
    c=fgetc(fp);
    count++;
  }

  printf("%sから%d個のデータを配列にコピーしました\n",file_name[0],count);

  fclose(fp);
  printf("%sをクローズしました\n",file_name[0]);

  printf("\n配列の内容を表示します\n");
  for(int i=0;i<count;i++){
    printf("ary[%d]=%d\n",i,ary[i]);
  }
  printf("\n");

  fp=fopen(file_name[1],"wb");
  file_open_result(fp,file_name[1]);

  for(int i=0;i<count;i++){
    fputc(ary[i],fp);
  }
  printf("配列から%d個のデータを%sにコピーしました\n",count,file_name[1]);

  fclose(fp);
  printf("%sをクローズしました\n",file_name[0]);

  return 0;
}

void file_open_result(FILE *fp,char file_name[MAX_SIZE])
{
  if(fp==NULL){
    printf("ファイルをオープンできません\n");
    exit(1);
  }
  printf("%sをオープンしました\n",file_name); 
}
