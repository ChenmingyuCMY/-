#include<cstdio>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;
string s,tmp;
char out[256],Std[256],My[256],Rand[256];
double tim;
int main(){
    system("@echo off");
//  system("@echo %cd%");
    puts("Imput Random File Name:");
    cin>>Rand;
    puts("Imput Std File Name:");
    cin>>Std;
    puts("Imput You File Name:");
    cin>>My;
    puts("Imput Standard Time Limit(s)");
    cin>>tim;
    tmp="";
    while(tmp!="n"&&tmp!="y"){
        puts("Needs to Compile?(y/n)");
        cin>>tmp;
        if(tmp=="y"){
            puts("Waiting...");
            sprintf(out,"g++ %s.cpp -o %s.exe",Rand,Rand);
            system(out);puts("Random File Has Compiled");
            sprintf(out,"g++ %s.cpp -o %s.exe",Std,Std);
            system(out);puts("Std File Has Compiled");
            sprintf(out,"g++ %s.cpp -o %s.exe",My,My);
            system(out);puts("Brute File Has Compiled");
        }
    }
    system("CLS");
    tmp="";
    while(tmp!="y"&&tmp!="n"){
        puts("Start?(y/n)");
        cin>>tmp;
        if(tmp=="n")return 0;
    }
    int i=0;
    while(++i){
        sprintf(out,"%s.exe >%d.in",Rand,i);
        system(out);
        double costs,costm,cost;
        {
            clock_t start,end;
            start=clock();
            system("");
            end=clock();
            cost=(double)(end-start)/CLOCKS_PER_SEC;
        }
        {
            clock_t start,end;
            start=clock();
            sprintf(out,"%s.exe <%d.in >%d.ans",Std,i,i);
            system(out);
            end=clock();
            costs=(double)(end-start)/CLOCKS_PER_SEC;
            costs-=cost;costs=max(0.0,costs);
            printf("Std time:%fs\n",costs);
        }
        {
            clock_t start,end;
            start=clock();
            sprintf(out,"%s.exe <%d.in >%d.out",My,i,i);
            system(out);
            end=clock();
            costm=(double)(end-start)/CLOCKS_PER_SEC;
            costm-=cost;costm=max(0.0,costm);
            printf("My  time:%fs\n",costm);
        }
        sprintf(out,"fc %d.out %d.ans",i,i);
        if(system(out)||costm>tim){
            printf("Failed Testdata %d\n",i);
            tmp="";
            while(tmp!="y"&&tmp!="n"){
                puts("Continue?(y/n)");
                cin>>tmp;
                if(tmp=="n")return 0;
                if(tmp=="y")break;
            }
        }else{
            printf("Passed Testdata %d\n",i);
            sprintf(out,"Del %d.in",i);
            system(out);
            sprintf(out,"Del %d.out",i);
            system(out);
            sprintf(out,"Del %d.ans",i);
            system(out);
        }
        Sleep(100);
        system("CLS");
    }
}
