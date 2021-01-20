#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#define N 128

int aflag = 0, lflag = 0;

void displayfile(char *name, char *showname){
    struct stat buf;
    struct tm *p;
    int i=8;
    if(lflag==0){
        fprintf(stdout, "%s ", showname);
        return;
    }
    if(stat(name, &buf)==-1){
        perror("stat");
        exit(-1);
    }
    
    switch (buf.st_mode & S_IFMT){
        case S_IFSOCK:
            fprintf(stdout, "s");
            break;
        case S_IFLNK:
            fprintf(stdout, "l");
            break;
        case S_IFREG:
            fprintf(stdout, "-");
            break;
        case S_IFBLK:
            fprintf(stdout, "b");
            break;
        case S_IFDIR:
            fprintf(stdout, "d");
            break;
        case S_IFCHR:
            fprintf(stdout, "c");
            break;
        case S_IFIFO:
            fprintf(stdout, "p");
            break;
        default:
            fprintf(stdout, "?");
            break;
    }
    while(i>=0){
        if((buf.st_mode)>>i & 1){
            switch (i%3){
                case 2:
                    printf("r");
                    break;
                case 1:
                    printf("w");
                    break;
                default:
                    printf("x");
                    break;
            }
        }else{
            printf("-");
        }
        i--;
    }
    printf(" ");
    // hard links
    printf("%d", buf.st_nlink);
    
    //uid gid
    printf(" %s %s ", getpwuid(buf.st_uid)->pw_name, getgrgid(buf.st_gid)->gr_name);

    printf("%ld ", buf.st_size);

    p = localtime(&buf.st_mtime);
    printf("%d-%d-%d %d:%d ", p->tm_year+1900, p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min);
    printf("%s\n", showname);
}

void displaydir(const char *name){
    DIR *dir;
    struct dirent *diritem;
    char str[N];
    dir = opendir(name);
    while((diritem=readdir(dir)) != NULL){
        if(strncmp(".", diritem->d_name, 1)==0 && aflag==0){
            continue;
        }
        sprintf(str, "./%s", diritem->d_name);
        displayfile(str, diritem->d_name);
    }
}

int main(int argc, char * argv[]){
    struct stat buf;
    int ch, i;
    if(argc < 2){
        fprintf(stdout, "usage: %s filename\n", argv[0]);
        exit(-1);
    }

    while((ch = getopt(argc, argv, "al"))!=-1){
        switch(ch){
            case 'a':
                aflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            default:
                fprintf(stdout, "wrong option %c\n", optopt);
        }
    }
    fprintf(stdout, "optind: %d\n", optind);
    for(i=optind; i<argc; i++){
        if(stat(argv[i], &buf)==-1){
            perror("stat");
            exit(-1);
        }
        if(!S_ISDIR(buf.st_mode))
            displayfile(argv[i], argv[i]);
        else 
            displaydir(argv[i]);
        
    }
    if(lflag == 0)
        fprintf(stdout, "\n");
    return 0;
}