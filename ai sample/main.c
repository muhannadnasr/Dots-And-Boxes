#include <stdio.h>
#include <stdlib.h>

int main (){

    int a[11][11];
    int turn = 1;
    int x,y;
    int sum;
    int check=0;

    for( int i=0;i<11;i++){

        for(int j=0;j<11;j++){

             if((i%2==0)&&(j%2==0)){

                    a[i][j]=2;
             }
             else{

            a[i][j]=0;
             }
        }

    }
    while (turn<101){

        if (turn%2==1){
            scanf("%d %d",&x,&y);
            if(a[x][y]==0){

                    a[x][y]=1;
                    system("cls");

                    for( int i=0;i<11;i++){

                        for(int j=0;j<11;j++){

                                printf("%d  ",a[i][j]) ;
                            }
                        printf("\n\n");
                    }
                    printf("\n");


            }

        }
        else{
            for(int i=1;i<11;i+=2){

                for(int j=1;j<11;j+=2){

                    if(a[i][j]==0){

                        sum = a[i][j-1]+a[i-1][j]+a[i][j+1]+a[i+1][j];
                        if(sum==3){
                            system("cls");
                            if(a[i][j-1]==0){

                                a[i][j-1]=1;
                                check = 1;
                            }
                            else if(a[i-1][j]==0){

                                a[i-1][j]=1;
                                check = 1;
                            }
                            else if(a[i][j+1]==0){

                                a[i][j+1]=1;
                                check = 1;
                            }
                            else{

                                a[i][j-1]=1;
                                check = 1;
                            }
                            for( int i=0;i<11;i++){

                                for(int j=0;j<11;j++){

                                    printf("%d  ",a[i][j]);
                                }
                                printf("\n\n");
                            }
                            }
                        else {
                            check = 0;
                        }

                        }
                    }

                }

          if (check==0) {
            while(1){
                x=rand()%10;
                y=rand()%10;
                if((a[x][y]==0)&&(!((x%2==1)&&(y%2==1)))){

                    a[x][y]=1;
                    break;
                }
            }
            system("cls");
                for( int i=0;i<11;i++){

                    for(int j=0;j<11;j++){

                        printf("%d  ",a[i][j]);
                    }
                    printf("\n\n");
                }
                printf("\n");

          }



        }
        turn++;
    }

    return 0;

}
