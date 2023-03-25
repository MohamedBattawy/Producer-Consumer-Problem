#include <iostream>
#include <queue>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unistd.h>
#include <iomanip>
#include <sys/types.h>
#include <sys/sem.h>
#include <fstream>
using namespace std;
void red()
{
    printf("\033[1;31m");
}
void cyan()
{
    printf("\033[1;36m");
}
void green()
{
    printf("\033[1;32m");
}
void finish()
{
    printf("\033[0m");
}
struct commodity
{
    int id;
    float price;
};
struct product
{
    float currentprice=0.0;
    float oldprice=0.0;
    int id;
    float counter=0.0;
    float avgprice2=0.0;
    float avgprice1=0.0;
    float price0=0.0;
    float price1=0.0;
    float price2=0.0;
    float price3=0.0;
    float price4=0.0;
};
int main(int argc,char** argv)
//int main()
{
    remove("Gold.txt");
    remove("Silver.txt");
    ofstream("Gold.txt");
    ofstream("Silver.txt");
    int n=stoi(argv[1]);
    printf("\e[1;1H\e[2J");
    vector <product> x(11);
    int i;
    for(i=0; i<11; i++)
    {
        x[i].id=i;
    }
 //       for(i=0;i<n;i++){
  //      x[i].oldprice=0;
   //     x[i].avgprice1=0;
    //    x[i].avgprice2=0;
     //   x[i].currentprice=0;
      //  x[i].counter=0;
       // x[i].price0=0;
        //x[i].price1=0;
        //x[i].price2=0;
        //x[i].price3=0;
        //x[i].price4=0;
        //x[i].id=100;
    //}
    //////////////////////////  START OF PRINT  /////////////////////////////////////////

    cout<<"+---------------------------------------+"<<endl;
    cout<<"| Currency        |  Price  |  AvgPrice |"<<endl;
    cout<<"| GOLD            |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| SILVER          |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| COTTON          |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| ALUMINUM        |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| NICKEL          |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| CRUDEOIL        |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| NATURALGAS      |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| COPPER          |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| LEAD            |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| ZINC            |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"| METHANEOIL      |";
    cyan();
    printf("%8.2lf ",0.0);
    finish();
    cout<<"|";
    cyan();
    printf("%8.2lf   ",0.0);
    finish();
    cout<<"|";
    cout<<endl;
    cout<<"+---------------------------------------+"<<endl;
    //////////////////////////  END OF PRINT START OF MEMORY  /////////////////////////////////////////
    int shmid;
    key_t key;
    commodity *ptr;
    if ((key = ftok("Silver.txt", 70)) == -1) /*Here the file must exist */
    {
        perror("ftok");
        exit(1);
    }
    shmid = shmget(key, sizeof(struct commodity)*(n+1), 0666|IPC_CREAT);
    if (shmid<0)
    {
        cout << "smsget - error\n";
        exit(1);
    }
    ptr=(commodity*)shmat(shmid,NULL,0);
    memset(ptr,0,sizeof(commodity)*n+1);
    int shmid2;
    key_t key2;
    int *ptr2;
    if ((key2 = ftok("Gold.txt", 75)) == -1) /*Here the file must exist */
    {
        perror("ftok");
        exit(1);
    }
    shmid2 = shmget(key2, sizeof(int) * 2, 0666|IPC_CREAT);
    if (shmid<0)
    {
        cout << "smsget - error\n";
        exit(1);
    }
    ptr2=(int*)shmat(shmid2,NULL,0);
    *ptr2=1;
    int j=1;
    int m;
    printf("\033[1;1H");
    /////////////////END OF MEMORY START OF SEMAPHORE////////////
        int semid;
    semid=semget(key,3,0666|IPC_CREAT);
    int mutual; //s
    int full; //e
    int emptybuf; //n
    mutual = semctl(semid,0,SETVAL,1);
    full = semctl(semid,1,SETVAL,1024);
    emptybuf=semctl(semid,2,SETVAL,0);
    sembuf waitmutual={0,-1,0};
    sembuf signalmutual={0,1,0};
    sembuf waitfull={1,-1,0};
    sembuf signalfull={1,1,0};
    sembuf waitempty={2,-1,0};
    sembuf signalempty={2,1,0};
    //for(i=0;i<n;i++){
    //    ptr[i].price=0;
    //    ptr[i].id=100;
    //}
    while(true)
    {
        semop(semid,&waitempty,1);
        semop(semid,&waitmutual,1);
        //printf("\033[1;1H");
        cout<<endl;
        if(j==n+1)
            j=1;
        commodity l=ptr[j];
        for(m=0; m<11; m++)
        {
            printf("\033[1;1H");
            if (l.id==m)
            {
                if((int)x[m].counter%5==0)
                    x[m].price0=l.price;
                else if((int)x[m].counter%5==1)
                    x[m].price1=l.price;
                else if((int)x[m].counter%5==2)
                    x[m].price2=l.price;
                else if((int)x[m].counter%5==3)
                    x[m].price3=l.price;
                else if((int)x[m].counter%5==4)
                    x[m].price4=l.price;
                x[m].counter++;
                if(l.price>x[m].currentprice)   //price increase so red color
                {
                    printf("\033[%d;20H",3+l.id);
                    red();
                    printf("%8.2lf",l.price);
                    cout<<"↑";
                    finish();
                    x[m].oldprice=x[m].currentprice;
                    x[m].currentprice=l.price;
                }
                else if(l.price<x[m].currentprice)  //price decrease so green
                {
                    green();
                    printf("\033[%d;20H",3+l.id);
                    printf("%8.2lf",l.price);
                    cout<<"↓";
                    finish();
                    x[m].oldprice=x[m].currentprice;
                    x[m].currentprice=l.price;
                }
                else
                {
                    cyan();
                    printf("\033[%d;20H",3+l.id);       //no change
                    printf("%9.2lf",l.price);
                    finish();
                    x[m].oldprice=x[m].currentprice;
                    x[m].currentprice=l.price;
                }
                if(x[m].counter>=5.0)
                    x[m].avgprice2=(x[m].price0+x[m].price1+x[m].price2+x[m].price3+x[m].price4)/5.0;
                else
                    x[m].avgprice2=(x[m].price0+x[m].price1+x[m].price2+x[m].price3+x[m].price4)/x[m].counter;
                printf("\033[1;1H");
                if(x[m].avgprice2>x[m].avgprice1)
                {
                    printf("\033[%d;30H",3+l.id);
                    red();
                    printf("%8.2lf",x[m].avgprice2);
                    cout<<"↑";
                    finish();
                    x[m].avgprice1=x[m].avgprice2;
                }
                else if(x[m].avgprice2<x[m].avgprice1)
                {
                    green();
                    printf("\033[%d;30H",3+l.id);
                    printf("%8.2lf",x[m].avgprice2);
                    cout<<"↓";
                    finish();
                    x[m].avgprice1=x[m].avgprice2;

                }
                else
                {
                    cyan();
                    printf("\033[%d;30H",3+l.id);       //no change
                    printf("%9.2lf",x[m].avgprice2);
                    finish();
                    x[m].avgprice1=x[m].avgprice2;

                }
            }
        }
        j++;
        semop(semid,&signalmutual,1);
        semop(semid,&signalfull,1);
        usleep(200000);
    }
    return 0;
}
