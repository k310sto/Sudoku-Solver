#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int main(){

char c;
char unit[9][10];
bool erorr = false;

printf("Let's play :\n");

for(int i=0; i<9; i++){
    erorr = false;
    fgets(unit[i], 11, stdin);
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
    if(!error) unit[i] = atoi(unit[i]);
}

short line[9];
short block[9];
//解く
for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
        if(unit[i][j]!=0){

            if(i)



        }
    }
}

return 0;
}
