#include<stdio.h>
#include"mp3_header.h"
#include"types.h"
Status edit(FILE* fptr,char* argv[],char* opt)
{
    extern char size;
    extern char tag[];
    extern char buffer[];
    rewind(fptr);     
    fseek(fptr,10,SEEK_SET);
    char empty[100]={0};
    int len=strlen(argv[3])+1;
    for(int i=0;i<6;i++)
    {

        fread(tag,4,1,fptr);
        fread(buffer,4,1,fptr);
        size=buffer[3];
        fseek(fptr,3,SEEK_CUR);
     
        if(!strcmp(tag,opt))
        {  
            fwrite(empty,size-1,1,fptr);
            fseek(fptr,-(size-1),SEEK_CUR);
            fwrite(argv[3],len-1,1,fptr);
            fclose(fptr);
            print_success(opt,argv);
            return e_success;
        }
        fseek(fptr,size-1,SEEK_CUR);
    }
    
    return e_failure;
}
    


void print_success(char* opt,char* argv[])
{
    printf("\n------------------------------------select_edit_option---------------------------------------");


    if(!strcmp(opt,"-t"))
    {
        printf("\n----------------------------------select_title_change_option------------------------------");
        printf("\n                   new title       :    %s",argv[3]);
        printf("\n----------------------------------title changed successfully------------------------------");
    }
    else if(!strcmp(argv[2],"-a"))
    {
        printf("\n----------------------------------select_artist_change_option------------------------------");
        printf("\n                   new artist       :    %s",argv[3]);
        printf("\n----------------------------------artist changed successfully------------------------------");
    }
    else if(!strcmp(argv[2],"-A"))
    {
        printf("\n----------------------------------select_album_change_option------------------------------");
        printf("\n                   new album       :    %s",argv[3]);
        printf("\n----------------------------------album changed successfully------------------------------");
    }
    else if(!strcmp(argv[2],"-m"))
    {
        printf("\n----------------------------------select_content_change_option------------------------------");
        printf("\n                    new content       :    %s",argv[3]);
        printf("\n----------------------------------content changed successfully------------------------------");
    }
    else if(!strcmp(argv[2],"-y"))
    {
        printf("\n----------------------------------select_year_change_option------------------------------");
        printf("\n                    new year       :    %s",argv[3]);
        printf("\n----------------------------------year changed successfully------------------------------");
    }
    else if(!strcmp(argv[2],"-c"))
    {
        printf("\n----------------------------------select_comment_change_option------------------------------");
        printf("\n                    new comment       :    %s",argv[3]);
        printf("\n----------------------------------comment changed successfully------------------------------");
    }
}
