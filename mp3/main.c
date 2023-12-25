#include "mp3_header.h"
#include<stdio.h>
#include"types.h"
#include<string.h>
char *opt=NULL;
char *tags[]={"TIT2","TALB"};
int main(int argc ,char* argv[])
{
    if(argv[1]==NULL||argc>5)
    {
        display_error();
        return 0;
    }
    if(!strcmp(argv[1],"--help"))
    {
        display_menu();
        return 0;
    }

    if(!strcmp(argv[1],"-v"))
    {
        if(argc>3)
        {
            printf("\n-------------------selected view details------------------------");
            printf("\nplease pass tag arguments like");
            printf("\nex:./a.out -v mp3file_name\n");
            return 0;
        }
        char* str;
        str=strstr(argv[2],".mp3");
        if(str!=NULL)
        {
            FILE* fptr=fopen(argv[2],"r");
            if(fptr!=NULL)
            {
                if( check_id_version(argv,fptr)!=e_success)
                    return 0;
                view(fptr);                                                //view function call         
            }
            else
            {
                printf("\n file not open failed!!");
            }
        }

        else
        {
            printf("\n file is not a mp3 ");
            return 0;
        }
    }

    else if(!strcmp(argv[1],"-e"))
    {
        char* str;
        char new_data[100];
        if(argc<5)
        {
            printf("\n-------------------selected edit option------------------------");
            printf("\nplease pass tag arguments like \n");
            printf("\nTo edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c new_data mp3file_name\n");
            return 0;
        }
        if(check_option(argv)==e_success)
        {
            str=strstr(argv[4],".mp3");
            if(str!=NULL)
            {
                if(strcmp(str,".mp3")==0)
                {
                    printf("its a .mp3");

                    FILE* fptr=fopen(argv[4],"r+");
                    if(fptr!=NULL)
                    {
                        if(check_id_version(argv,fptr)!=e_success)
                            return 0;

                        if(edit(fptr,argv,opt)==e_success)
                            return 0;
                        else
                        {
                            printf("\nfailed edit");
                            return 0;
                        }
                    }
                    else
                    {
                        printf("\n file open failed");
                    }
                }
                else
                {
                    printf("\nfile is not mp3 ,please pass mp3 file.");
                    return 0;
                }
            }
            else
            {    
                printf("\n operation failed file is not mp3");
                return 0;
            }
        }
        else 
        {
            printf("\n-------------------selected edit details------------------------");
            printf("\nplease pass tag arguments which you want to edit");
            printf("\nex:./a.out -e -t/-a/-A/-m/-y/-c new_data file_name.mp3\n");

            return 0;
        }
    }
    else
        display_error();

    return 0;
}

void display_error(void)
{
    printf("------------------------------------------------------------------------------");
    printf("\nERROR: ./a.out : INVALID ARGUMENTS");
    printf("\n USAGE :");
    printf("\nTo view please pass like: ./a.out -v mp3file_name");
    printf("\nTo edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c new_data mp3file_name");
    printf("\nFOR help please pass like: ./a.out --help");
    printf("\n----------------------------------------------------------------------------\n");
}
void display_menu(void)
{

    printf("---------------------------------HELP MENU-------------------------------------");
    printf("\n1. -v -> view mp3 file contents");
    printf("\n2. -e -> to edit mp3 file contents");
    printf("\n      2.1 -t -> to edit song title");
    printf("\n      2.2 -a -> to edit artist name");
    printf("\n      2.3 -A -> to edit album name");
    printf("\n      2.4 -y -> to edit year");
    printf("\n      2.5 -m -> to edit content");
    printf("\n      2.6 -c -> to edit comment");
    printf("\n----------------------------------------------------------------------------\n");
}

Status check_id_version(char *argv[],FILE* fptr)
{
    char data[30]={0};
    fread(data,3,1,fptr);
    if(strcmp(data,"ID3")!=0)
    {
        printf("tag is not ID3!!");
        return e_failure;
    }
    fread(data,2,1,fptr);
    if(data[0]!=0x03 &&data[1]!=0x00)
    {
        printf("\nfile is not ID3 V2 version");
        return e_failure;
    }
    return e_success;
}

Status check_option(char* argv[])
{
    if(!strcmp(argv[2],"-t"))
    {
        extern char* opt;
        opt=tags[0];
        printf("option is %s",opt);
    }
    else if(!strcmp(argv[2],"-a"))
    {
        opt="TPE1";
    }
    else if(!strcmp(argv[2],"-A"))
    {
        opt="TALB";
    }
    else if(!strcmp(argv[2],"-m"))
    {
        opt="TCON";
    }
    else if(!strcmp(argv[2],"-y"))
    {
       opt="TYER";
    }
    else if(!strcmp(argv[2],"-c"))
    {
        opt="COMM";
    }
    else{
        return e_failure;
    }
    return e_success;
}
