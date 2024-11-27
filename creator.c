#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define DEBUG for(int i=0;i<9;i++){for(int j=0;j<9;j++) printf("%d ",unit[i][j]);printf("\n");}printf("\n");

int main(){
int blk = 0;
bool loop = true;
while(loop){
    printf("How many blanks[1~60] :");
    scanf("%d",&blk);
    if(1<=blk<=60) loop=false;
}

char unit[9][9];
int stnd[3]={0,3,6};
int clx,cly;

//初期化
for(int i=0;i<9;i++){
for(int j=0;j<9;j++){
    unit[i][j]=0;
}
}



for(int n=1;n<10;n++){
bool ok = false;
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
    while(!ok){
        ok = true;
        srand(clock());
        clx = rand()%3;
        cly = rand()%3; 
        //ブロックの重複確認

        if(unit[stnd[i]+cly][stnd[j]+clx]!=0) ok=false;   
        //列の重複確認
        for(int k=0;k<9&&ok;k++){
            if(unit[k][stnd[j]+clx]==n && k!=i) ok=false;
            if(unit[stnd[i]+cly][k]==n && k!=j) ok=false;
        }
        if(ok) unit[stnd[i]+cly][stnd[j]+clx] = n;
    }
    ok = false;
}
}
}
DEBUG

for(int i=0;i<9;i++){
        for(int j=0;j<9;j++) 
            printf("%d ",unit[i][j]);
        printf("\n");
    }

char t3unit[9][9];//tentative unit
loop = true;
while(loop){
    
    memcpy(t3unit, unit, sizeof(unit));
    for(int i=0;i<blk;i++){
        srand(clock());
        t3unit[rand()%9][rand()%9] = 0;
    }
    FILE* aux = fopen("create-aux.txt","w");
    for(int i=0;i<9;i++) fprintf(aux,"%s\n",t3unit[i]);
    fclose(aux);
    system("find Sudoku-Destroyer -name 'destroyer-aux'");
    char str[500];
    fgets(str, 500, stdout);
    system(str);
    loop=false;
}




    printf("Question:\n");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++) 
            printf("%d ",unit[i][j]);
        printf("\n");
    }
    loop = true;
    while(loop){
        char select[3];
        printf("Save this?[y/N]:");
        scanf("%s", &select);
        if(select=="y","Y","yes","Yes","YES","yep","Yep","YEP"){
            FILE* que; 
            que = fopen("queston.txt", "w");
            for(int i=0;i<9;i++) fprintf(que,"%s\n",unit[i]);
            fclose(que);
            printf("wrote to question.txt\n");
            loop = false;
        }
        else if(select=="N","n","no","NO","No","non","NON","Non")
            loop = false;
        else;
    }
return 0;
}
