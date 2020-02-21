/*************************************************************************
	> File Name: my_ls.c
	> Author: 
	> Mail: 
	> Created Time: Fri 07 Feb 2020 06:56:09 PM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[]){
    if(argc<2){
        printf("enter the file name\n");
        exit(1);
    }
    struct stat buf;
    int ret=stat(argv[1],&buf);
    if(ret<0){
        perror("stat erro: ");
        exit(1);
    }
    char name[11]={0};
    switch(buf.st_mode&S_IFMT){
        case S_IFSOCK:
            name[0]='s';
            break;
        case S_IFLNK:
            name[0]='l';
            break;
        case S_IFREG:
            name[0]='r';
            break;
        case S_IFBLK:
            name[0]='b';
            break;
        case S_IFDIR:
            name[0]='d';
            break;
        case S_IFCHR:
            name[0]='c';
            break;
        case S_IFIFO:
            name[0]='f';
            break;
        default:
            break;
    }
    name[1]=(buf.st_mode&S_IRUSR)?'r':'-';
    name[2]=(buf.st_mode&S_IWUSR)?'w':'-';
    name[3]=(buf.st_mode&S_IXUSR)?'x':'-';
    name[4]=(buf.st_mode&S_IRGRP)?'r':'-';
    name[5]=(buf.st_mode&S_IWGRP)?'w':'-';
    name[6]=(buf.st_mode&S_IXGRP)?'x':'-';
    name[7]=(buf.st_mode&S_IROTH)?'r':'-';
    name[8]=(buf.st_mode&S_IWOTH)?'w':'-';
    name[9]=(buf.st_mode&S_IXOTH)?'x':'-';

    long linkNum=(long)buf.st_nlink;
    long fileSize=(long)buf.st_size;
    char out[1024]={0};
    sprintf(out,"%s %ld %ld",name,linkNum,fileSize);
    printf("%s",out);
    return 0;
}
