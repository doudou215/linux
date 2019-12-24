/*************************************************************************
	> File Name: myftw.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 23 Dec 2019 11:56:48 PM PST
 ************************************************************************/
#include<dirent.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

using namespace std;



#define MAX_NAME 256

long nreg,ndir,nblk,nchr,nfifo,nslink,nsock;
typedef void (*FUNC)(const char *,const struct stat *,int);
FUNC myfun;

void dopath(char *pathname,FUNC myfun);
void myfunc(const char *,const struct stat *,int);

int main(int argc, char *argv[]){
    if(argc!=2){
        cout<<"usage ./myftw filename"<<endl;
        return 0;
    }
    char *pathname=new char[MAX_NAME];
    pathname=strcpy(pathname,argv[1]);
    if(pathname==NULL){
        cout<<"realloc failed"<<endl;
        return 0;
    }
    dopath(pathname,myfunc);
    cout<<"total reg "<<nreg<<endl;
    cout<<"total blk "<<nblk<<endl;
    cout<<"total char "<<nchr<<endl;
    cout<<"total fifo "<<nfifo<<endl;
    cout<<"total link "<<nslink<<endl;
    cout<<"total dir "<<ndir<<endl;
    cout<<"total sock "<<nsock<<endl;
    delete pathname;
    return 0;

}
#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

void dopath(char *pathname,FUNC myfunc){
    struct dirent *dirp;
    DIR *dp;
    struct stat statptr;
    if(lstat(pathname,&statptr)<0){
        myfunc(pathname,&statptr,FTW_NS);
        return;
    }
    if(S_ISDIR(statptr.st_mode)==0){
        myfunc(pathname,&statptr,FTW_F);
        return;
    }
    myfunc(pathname,&statptr,FTW_D);
    int n=strlen(pathname); 
    pathname[n++]='/';
    pathname[n]=0;
    dp=opendir(pathname);
    if(!dp){
        myfunc(pathname,&statptr,FTW_DNR);
        return;
    }
    while((dirp=readdir(dp))!=NULL){
        if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
            continue;
        strcpy(&pathname[n],dirp->d_name);
        dopath(pathname,myfunc);
    }

}
void myfunc(const char *pathname,const struct stat *statptr,int type){
    switch(type){
        case FTW_F :
        switch(statptr->st_mode & S_IFMT){
            case S_IFREG: nreg++; break;
            case S_IFBLK: nblk++; break;
            case S_IFCHR: nchr++; break;
            case S_IFIFO: nfifo++; break;
            case S_IFLNK: nslink++; break;
            case S_IFSOCK: nsock++; break;
            default: return;
        }
        break;
        case FTW_D :
            ndir++;
            break;
        case FTW_NS:
            cout<<"cannot stat"<<endl;
        case FTW_DNR:
            cout<<"cannot open dir"<<endl;
        default:
            return;
    }
}
