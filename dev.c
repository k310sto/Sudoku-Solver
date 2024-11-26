#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int main(){

char c;
char unit[9][10];
bool error = false;
FILE* file;
printf("Let's play :\n");
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

bool dup[9][9][9];
short comx[9],comy[9]
bool end = false;
short resolved=0;
short last = 0;
short ans[9][9];
bool once = false;
bool skip = false;
for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
        ans[i][j]=0;
    }
}

//解く
while(!end){
for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){

        if(unit[i][j]!=0){
            for(int k=0;k<9;k++){
                if(k!=unit[i][j]-1) dup[i][j][k]=true;
            }
        }


        if(unit[i][j]==0){
            for(int mode=0;mode<3;mode++){
            for(int k=0;k<9;k++){
               switch (mode){
                    case 0:
                        dup[i][j][k]=false;
                        comx[k]=0;
                        comy[k]=0;
                        break;
                    case 1:
                        if(unit[k][j]!=0)
                            dup[i][j][unit[k][j]-1]=true;
                        else{
                        if(once){
                            zeroy++;
                            for(int l=0;l<9;l++){
                                if(dup[k][j][l]==true){
                                    comy[l]++;
                                }
                            }
                        }
                        }
                        if(unit[i][k]!=0)
                            dup[i][j][unit[i][k]-1]=true;
                        else{

                        }
                        break;
                    case 2:
                        if(comx[k]==zerox)




                        break;
               }
            }
            }

            int x[3] = {0,0,0};
            int y[3] = {0,0,0};

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
            for(int k=0; k<3; k++){
                for(int l=0; l<3; l++){
                    if(unit[i+y[k]][j+x[l]]!=0)
                        dup[i][j][unit[i+y[k]][j+x[l]]] = true;
                }
            }

            bool flag=false;
            for(int k=0;k<9;k++){
                if(dup[i][j][k]==false){
                    if(!flag){
                        unit[i][j]=k+1;
                        flag=true;
                    }else unit[i][j]=0;
                }
            }




        }
        if(unit[i][j]!=0) ans[i][j]=1;
    }
}
resolved = 0;
for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
        resolved += ans[i][j];
    }
}
if(resolved==last&&once){
    printf("Error: Unsolvable\n");
    end = true;
    error = true;
}
last = resolved;
if(resolved>=81) end=true;
if(!once) once=true;
}


if(!error){ 
    printf("MyAnswer:\n");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++) printf("%d ",unit[i][j]);
        printf("\n");
    }
}

return 0;
}
