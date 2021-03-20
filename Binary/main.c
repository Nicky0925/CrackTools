#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]) {

  FILE *fp = NULL;
  char master_str[1000000] = {0};
  char *str = NULL;
  char *strarray[64] = {NULL};
  int getf = 0;
  int strn = 0;
  int i = 0;
  fp = fopen(argv[1], "r");

  while(1) {
    getf = fgetc(fp);
    if(getf == EOF) {
      break;
    }
    master_str[i] = (char)getf;
    i++;
  }

  fclose(fp);

  // master_strからargv[2]を部分文字列検索する
  str = strstr(master_str, argv[2]);

  if(str == NULL) {
    printf("検索結果：一致する文字列はありません\n");
  } else {
    printf("検索結果：");
    for (int i = 0; i < strlen(argv[2]); i++) {
      printf("%c", *(str + i));
    }
    printf("\n");
    printf("バイト:%x\n", (int)(str - master_str));
  }

  return 0;
}
