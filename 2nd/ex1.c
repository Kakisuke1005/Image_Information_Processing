#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

int main()
{
  FILE *fp1,*fp2;
  int c1,c2;
  char file_name[2][MAX_SIZE];

  printf("比較するファイルを入力して下さい: ");
  scanf("%s %s",file_name[0],file_name[1]);

  fp1=fopen(file_name[0],"rb");
  if(fp1==NULL){
    printf("Cannot open the %s!!\n",file_name[0]);
    exit(1);
  }

  fp2=fopen(file_name[1],"rb");
  if(fp2==NULL){
    printf("Cannot open the %s!!\n",file_name[1]);
    exit(1);
  }

  c1=fgetc(fp1);
  c2=fgetc(fp2);
  while((c1!=EOF)||(c2!=EOF)){
    if(c1!=c2){
      printf("二つのファイルの内容は異なっています\n");
      exit(0);
    }else{
      c1=fgetc(fp1);
      c2=fgetc(fp2);
    }
  }

  printf("二つのファイルの内容は同じです\n");

  fclose(fp1);
  fclose(fp2);

  return 0;
}
