/*************************************************************************
	> File Name: memory_stream.c
	> Author: 
	> Mail: 
	> Created Time: Sat 11 Jan 2020 03:23:23 AM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BSZ 48

int main(){
    char buf[BSZ];
    buf[BSZ-1]='X';
    buf[BSZ-2]='\0';
    memset(buf,'a',BSZ-2);
    printf("Initial string %s \n",buf);
    FILE *fp;
    if((fp=fmemopen(buf,BSZ,"w+"))==NULL){
        fprintf(stderr,"%s","fmemopen error");
        exit(0);
    }
    fputs("Hello World",fp);
    printf("before fflush: %s\n",buf);
    fflush(fp);//fp->off_set=11
    printf("after fflush: %s\n",buf);
    

    memset(buf,'b',BSZ-2);
    buf[BSZ-1]='X';
    buf[BSZ-2]='\0';
    fprintf(fp,"Hello World");
    printf("before fseek %s\n",buf);
    fseek(fp,0,SEEK_SET);//fseek leads to fflush,and first fflush,then fseek.
    printf("after fseek %s\n",buf);

    memset(buf,'c',BSZ-2);
    fprintf(fp,"Hello World");
    fclose(fp);
    printf("after close fp %s",buf);
    return 0;
}
