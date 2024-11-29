// SPDX-FileCopyrightText: 2024 Kensuke Sato
// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

int block_y(int i, int *y){
    if(i==0 || i==3 || i==6){
        y[1] = 1;
        y[2] = 2;
    }
    else if(i==1 || i==4 || i==7){
        y[1] = -1;
        y[2] = 1;
    }
    else{
        y[1] = -1;
        y[2] = -2;
    }
    return 0;
}

int block_x(int j, int *x){
    if(j==0 || j==3 || j==6){
        x[1] = 1;
        x[2] = 2;
    }
    else if(j==1 || j==4 || j==7){
        x[1] = -1;
        x[2] = 1;
    }
    else{
        x[1] = -1;
        x[2] = -2;
    }
    return 0;
}

int main(){
unsigned int clmx=1;
unsigned int Vblock=0;
unsigned int Hblock=0;
while((!(2<=clmx&&clmx<=25))&&((clmx%2)!=0)){
    printf("max cell: ");
    scanf("%d", &clmx);
}
double clmxp = sqrt((double)clmx);
if(floor(clmxp)==(double)sqrt(clmx)){
    Vblock=clmxp;
    Hblock=clmxp;
}else{
    while(!(clmx%Vblock==0&&clmx%Hblock==0)){
        printf("Vertical axis number of blocks: ");
        scanf("%d", &Vblock);
        printf("Horizontal axis number of blocks: ");
        scanf("%d", &Hblock);
    }
}
int unit[clmx][clmx];
bool error = false;
bool reverse = false;

printf("Let's play :\n-------------------------\n\n");

for(int i=0; i<clmx; i++){
    error = false;
    reverse = false;
    char str[clmx*2];
    int ptr=0;      //unit配列の格納位置（添字）
    bool row=false; //前が数字ならtrue、文字ならfalse

    fgets(str, clmx*2, stdin);
    printf("\033[1A\033[0K");

    for(int j=0;j<sizeof(str)&&!error;j++){
        if(str[0]=='u'&&i>0){
            printf("\033[1A\033[0K\033[1A\033[0K");
            i-=2;
            printf("Undo\n");
            error = true;
        }
        else if(str[0]=='-'){
            reverse = true;
        }
        else if(str[j]=='\n'){
            for(int k=0;k<clmx;k++) unit[i][k] = '0';
            j=sizeof(str);
        }
        else if(isdigit(str[j])){
            if(row){
                unit[i][ptr] *= 10;
                unit[i][ptr] += (str[j]-48);
            }else{
                row = true;
                unit[i][ptr] = (str[j]-48);
            }
                    }
        else if(!isdigit(str[j])){
            ptr++;
            row = false;
        }
        printf("debug[%d]", unit[i][ptr]);
        sleep(1);
    }
    while(getchar()!='\n');

    if(reverse){
        for(int k=0;k<=((clmx-1)/2);k++){
            char tmp = unit[i][k];
            unit[i][k] = unit[i][clmx-1-k];
            unit[i][clmx-1-k] = tmp;
        }
    }

    if(!error) {
        //ASCII
        printf("\033[0K\033[1A| ");
        for(int j=0; j<clmx; j++){
            if(unit[i][j]==0) printf("_");
            else printf("%d", unit[i][j]);
            if(((j+1)%(clmx/Hblock))==0) printf(" | ");
            else printf(" ");
        }
        printf("\n");
        if(((i+1)%(clmx/Vblock))==0){
            if(i!=clmx-1){
                printf("|");
                for(int k=1;k<=Hblock;k++){
                     for(int l=0;l<((clmx/Hblock)*2+1);l++) printf("-");
                     if(k!=Hblock) printf("+");
                }
                printf("|\n");
            }else{
                for(int k=1;k<=(((clmx+Hblock)*2)+1);k++)printf("-");
                printf("\n");
            }
        }
    }

}

bool dup[clmx][clmx][clmx];  //true：無い　false：あるかも
bool duptmp[clmx];
bool end = false;
short resolved=0;
short last = 0;
short ans[clmx][clmx];
for(int i=0; i<clmx; i++){
    for(int j=0; j<clmx; j++){
        ans[i][j]=0;
    }
}
/*
//解く
while(!end){
for(int proc=0;proc<2;proc++){
for(int i=0; i<clmx; i++){
for(int j=0; j<clmx; j++){
    if(proc==0){
        if(unit[i][j]==0){
            for(int k=0;k<clmx;k++) dup[i][j][k]=false;
            for(int k=0;k<clmx;k++){
                if(unit[k][j]!=0) dup[i][j][unit[k][j]-1]=true;
                if(unit[i][k]!=0) dup[i][j][unit[i][k]-1]=true;
                }
            int x[3] = {0,0,0};
            int y[3] = {0,0,0};
            block_y(i, y);
            block_x(j, x);
            for(int k=0; k<3; k++){
            for(int l=0; l<3; l++){
                if(unit[i+y[k]][j+x[l]]!=0) 
                    dup[i][j][unit[i+y[k]][j+x[l]]-1] = true;
            }
            }
        }
        else if(unit[i][j]!=0){
            ans[i][j]=1;
            for(int k=0;k<9;k++) if((k+1)!=unit[i][j]) dup[i][j][k] = true;
        }        
    }
    if(proc==1){
        if(unit[i][j]==0){
            bool out = true;
            int x[3] = {0,0,0};
            int y[3] = {0,0,0};
            block_y(i, y);
            block_x(j, x);
            for(int mode=0;mode<3&&out;mode++){
                for(int k=0;k<9;k++)
                    duptmp[k]=true;
                if(mode==0){
                    for(int k=0;k<9;k++){
                    for(int l=0;l<9;l++){
                        if(k!=i) if(dup[k][j][l]==false) duptmp[l]=false;
                        else{
                            if(dup[k][j][l]==true) duptmp[l]=false;
                        }
                    }
                    }
                }
                else if(mode==1){
                    for(int k=0;k<9;k++){
                    for(int l=0;l<9;l++){
                        if(k!=j) if(dup[i][k][l]==false) duptmp[l]=false;
                        else{
                            if(dup[i][k][l]==true) duptmp[l]=false;
                        }
                    }
                    }
                }
                else if(mode==2){
                    for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                    for(int m=0;m<9;m++){
                        if(k!=0 || l!=0){
                            if(dup[i+y[k]][j+x[l]][m]==false) duptmp[m] = false;
                        }
                        else{
                            if(dup[i+y[k]][j+x[l]][m]==true) duptmp[m] = false;
                        }
                    }
                    }
                    }
                }

                //trueが残っている場合、該当数字であることが確定する
                for(int k=0;k<9;k++)
                     if(duptmp[k]==true){
                        unit[i][j] = (k+1);
                        ans[i][j] = 1;
                        out = false;
                     }
            }
        }
    }
}
}
}

resolved = 0;
for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
        resolved += ans[i][j];
    }
}
if(resolved==last){
    printf("Error: Unsolvable\n");
    end = true;
    error = true;
}
last = resolved;
if(resolved>=81) end=true;
}


if(!error){ 
    printf("Answer :\n-------------------------\n");
    for(int i=0;i<9;i++){
        printf("| ");
        for(int j=0; j<9; j++){
            if(unit[i][j]==0) printf(" ");
            else printf("%d", unit[i][j]);
            if(j==2||j==5||j==8) printf(" | ");
            else printf(" ");
        }
        printf("\n");
        if(i==2||i==5) printf("|-------+-------+-------|\n");
        if(i==8)       printf("-------------------------\n");
    }
    return 0;
}
else */return 0;
}

