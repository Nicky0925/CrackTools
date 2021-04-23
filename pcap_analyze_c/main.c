#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
  int macAddr_d[6];
  int macAddr_s[6];
  int ipAddr_d[4];
  int ipAddr_s[4];
}NET_DATA;


// get mac addr function 
void getMacAddr_d(FILE *, NET_DATA *);
void getMacAddr_s(FILE *, NET_DATA *);
 
// get ip addr function 
void getIPAddr_d(FILE *, NET_DATA *);
void getIPAddr_s(FILE *, NET_DATA *);

// show struct function
void showstruct(NET_DATA *);


int main() {
  char fileName[128] = "ip_header.pcapng";
  FILE *fp;
  NET_DATA net_data;
  int getf;
  int cnt;

  fp = fopen(fileName, "r");
  getMacAddr_d(fp, &net_data);
  getMacAddr_s(fp, &net_data);
  getIPAddr_d(fp, &net_data);
  getIPAddr_s(fp, &net_data);

  showstruct(&net_data);

  fclose(fp);
  return 0;
}

void getMacAddr_d(FILE *fp, NET_DATA *net) {
  int cnt = 0;
  int getf;
  fseek(fp, 180, SEEK_SET);
  while(1) {
    net->macAddr_d[cnt] = fgetc(fp);
    if(cnt == 6) break;
    cnt++; 
  }
}

void getMacAddr_s(FILE *fp, NET_DATA *net) {
  int cnt = 0;
  int getf;
  fseek(fp, 186, SEEK_SET);
  while(1) {
    net->macAddr_s[cnt] = fgetc(fp);
    if(cnt == 6) break;
    cnt++; 
  }
}

void getIPAddr_d(FILE *fp, NET_DATA *net) {
  int cnt = 0;
  int getf;
  fseek(fp, 206, SEEK_SET);
  while(1) {
    net->ipAddr_d[cnt] = fgetc(fp);
    if(cnt == 4) break;
    cnt++;
  }
}

void getIPAddr_d(FILE *fp, NET_DATA *net) {
  int cnt = 0;
  int getf;
  fseek(fp, 210, SEEK_SET);
  while(1) {
    net->ipAddr_s[cnt] = fgetc(fp);
    if(cnt == 4) break;
    cnt++;
  }
}

void getIPAddr_s(FILE *fp, NET_DATA *net) {
}

void showstruct(NET_DATA *net) {
  printf("MAC ADDR DEST   : ");
  for(int i = 0; i < 6; i++) {
    printf("%02x:", net->macAddr_d[i]);
  }
  printf("\n");

  printf("MAC ADDR SOURCE : ");
  for(int i = 0; i < 6; i++) {
    printf("%02x:", net->macAddr_s[i]);
  }
  printf("\n");

  printf("IP ADDR DEST    : ");
  for(int i = 0; i < 4; i++) {
    printf("%d.", net->ipAddr_d[i]);
  }
  printf("\n");

  printf("IP ADDR SOURCE  : ");
  for(int i = 0; i < 4; i++) {
    printf("%d.", net->ipAddr_s[i]);
  }
  printf("\n");
}


