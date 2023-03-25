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
#include <chrono>
#include <sys/time.h>
using namespace std;
struct commodity{
    int id;
    float price;
};
int main(int argc,char** argv)
{
        int n=stoi(argv[5]);
    int shmid;
    key_t key;
    commodity *ptr;
    if ((key = ftok("Silver.txt", 70)) == -1) /*Here the file must exist */
    {
        perror("ftok");
        exit(1);
    }
    shmid = shmget(key, sizeof(struct commodity) *n, 0666);
    if (shmid<0)
    {
        cout << "smsget - error\n";
        exit(1);
    }
    ptr=(commodity*)shmat(shmid,NULL,0);
    int shmid2;
    key_t key2;
    int *ptr2;
    if ((key2 = ftok("Gold.txt", 75)) == -1) /*Here the file must exist */
    {
        perror("ftok");
        exit(1);
    }
    shmid2 = shmget(key2, sizeof(int)*2, 0666);
    if (shmid<0)
    {
        cout << "smsget - error\n";
        exit(1);
    }
    ptr2=(int*)shmat(shmid,NULL,0);
    string name;
    float mean,deviation;
    int wait_time;
    float number;
    name=argv[1];
    mean=stof(argv[2]);
    deviation=stof(argv[3]);
    wait_time=atoi(argv[4]);
    default_random_engine generator;
    normal_distribution<double> distribution(mean,deviation);
      int semid;
    semid=semget(key,3,0666);
    int mutual; //s
    int full; //e
    int emptybuf; //n
    //mutual = semctl(semid,0,SETVAL,1);
    //full = semctl(semid,1,SETVAL,1024);
    //emptybuf=semctl(semid,2,SETVAL,0);
    sembuf waitmutual={0,-1,0};
    sembuf signalmutual={0,1,0};
    sembuf waitfull={1,-1,0};
    sembuf signalfull={1,1,0};
    sembuf waitempty={2,-1,0};
    sembuf signalempty={2,1,0};
    timeval now;
    char time[100];
    while(true){
    commodity l;
            if (name=="GOLD")
                l.id=0;
            if (name=="SILVER")
                l.id=1;
            if (name=="COTTON")
                l.id=2;
            if (name=="ALUMINUM")
                l.id=3;
            if (name=="NICKEL")
                l.id=4;
            if (name=="CRUDEOIL")
                l.id=5;
            if (name=="NATURALGAS")
                l.id=6;
            if (name=="COPPER")
                l.id=7;
            if (name=="LEAD")
                l.id=8;
            if (name=="ZINC")
                l.id=9;
            if (name=="METHANEOIL")
                l.id=10;
    number=distribution(generator);
    l.price=number;
    //auto time=std::chrono::high_resolution_clock::now();
    gettimeofday(&now,NULL);
    strftime(time,100,"%m/%d/%Y %H:%M:%S",localtime(&now.tv_sec));
    cout<<time<<"."<<now.tv_usec;
    cout<<" "<<name<<" Generating new value "<<number<<endl;
    //auto time=high_resolution_clock::now();
    gettimeofday(&now,NULL);
    strftime(time,100,"%m/%d/%Y %H:%M:%S",localtime(&now.tv_sec));
    cout<<time<<"."<<now.tv_usec;
    cout<<"  "<<name<<" Trying to access mutex"<<endl;
    semop(semid,&waitfull,1);
    semop(semid,&waitmutual,1);
    //cout<<" "<<name<<" ENTERED CRITICAL SECTION"<<endl;
    gettimeofday(&now,NULL);
    strftime(time,100,"%m/%d/%Y %H:%M:%S",localtime(&now.tv_sec));
    cout<<time<<"."<<now.tv_usec;
    cout<<" "<<name<<" placed "<<number<<" in buffer"<<endl;
    gettimeofday(&now,NULL);
    strftime(time,100,"%m/%d/%Y %H:%M:%S",localtime(&now.tv_sec));
    cout<<time<<"."<<now.tv_usec;
    cout<<" "<<name<<" Sleeping for "<<wait_time<<endl;
    ptr[*ptr2]=l;
    *ptr2+=1;
    if (*ptr2==n+1)
    *ptr2=1;
    //usleep(1000*1000*5);
    semop(semid,&signalmutual,1);
    semop(semid,&signalempty,1);
    usleep(wait_time*1000);
    }
    return 0;
}
