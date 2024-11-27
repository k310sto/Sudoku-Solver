#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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
char unit[9][10];
bool error = false;
FILE* file;
file=fopen("question.txt","r");
for(int i=0; i<9; i++){
    error = false;
    fgets(unit[i], 11, file);
    for(int j=0; j<10; j++){
        if(unit[i][j]=='\n'){
            while(j<10){
                unit[i][j] = '0';
                j++;
            }
        }
        else if(!isdigit(unit[i][j])){
            printf("Error: Malformed\n");
            i--;
            for(int k=0; k<i; k++)
                printf("%s\n", unit[k]);
            error = true;
            break;
        }
        else if(j==9){
            while(getchar()!='\n');
        }else;
    }
    if(!error) {
        for(int k=0;k<9;k++){
            unit[i][k] -= 48;
        }
    }
}
fclose(file);

bool dup[9][9][9];  //true：無い　false：あるかも
bool duptmp[9];
bool end = false;
short resolved=0;
short last = 0;
short ans[9][9];
for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
        ans[i][j]=0;
    }
}

//解く
while(!end){
for(int proc=0;proc<2;proc++){
for(int i=0; i<9; i++){
for(int j=0; j<9; j++){
    if(proc==0){
        if(unit[i][j]==0){
            for(int k=0;k<9;k++) dup[i][j][k]=false;
            for(int k=0;k<9;k++){
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
    printf("Answer:\n");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++) printf("%d ",unit[i][j]);
        printf("\n");
    }
}

return 0;
}
