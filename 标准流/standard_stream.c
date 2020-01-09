/*************************************************************************
	> File Name: standard_stream.c
	> Author: 
	> Mail: 
	> Created Time: Mon 06 Jan 2020 08:46:32 PM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int is_line_buffered(FILE *fp);
int buffer_size(FILE *fp);
int is_no_buffered(FILE *fp);
void pr_stdio(const char *name,FILE *fp);
void err_sys(const char *msg);

int main(){
    fputs("stderr\n",stderr);
    if(getchar()==EOF)
        err_sys("stdin error");
    fputs("stdout",stdout);
    pr_stdio("stdin",stdin);
    pr_stdio("stdout",stdout);
    pr_stdio("stderr",stderr);
    FILE *fp=fopen("/etc/passwd","r");
    if(!fp)
        err_sys("fopen error password");
    if(getc(fp)==EOF)
        err_sys("getc error");
    return 0;
}

void err_sys(const char *msg){
    fputs(msg,stderr);
    exit(0);
}

void pr_stdio(const char *name,FILE *fp){
    printf("This  is %s\n",name);
    if(is_line_buffered(fp))
        printf("%s is line buffered\n",name);
    else if(is_no_buffered(fp))
        printf("%s is no buffered\n",name);
    else 
        printf("%s is full buffered\n",name);
    printf("The buffer size is %d",buffer_size(fp));
}

#if defined (_IO_UNBUFFERED)
int is_no_buffered(FILE *fp){
    return (fp->_flags&_IO_UNBUFFERED);
}

int is_line_buffered(FILE *fp){
    return (fp->_flags&_IO_LINE_BUF);
}

int buffer_size(FILE *fp){
    return (fp->_IO_buf_end-fp->_IO_buf_base);
}

#elif defined(_SNBF)
int is_no_buffered(FILE *fp){
    return (fp->_flags&_SNBF);
}

int is_line_buffered(FILE *fp){
    return (fp->_flags&_SLBF);
}

int buffer_size(FILE *fp){
    return (fp->_buf._size);
}

#elif defined(_IONBF)
#ifdef _LP64
#define _flag _pad[4]
#define _ptr _pad[1]
#define _base _pad[2]
#endif
int is_no_buffered(FILE *fp){
    return (fp->_flag&_IONBF);
}

int is_line_buffered(FILE *fp){
    return (fp->_flag&_IOLBF);
}

int buffer_size(FILE *fp){
    #ifdef _LP64
    return(fp->_base-fp->_ptr);
    #else
    return(BUFSIZ);
    #endif
}
#endif

