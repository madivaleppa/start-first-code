#include"header.h"
void print_contact(void)
{
    char* s;
    char buffer[100];
    char* str;
    FILE* fptr=fopen(DEFAULT_FILE,"r");
    if(fptr==NULL)
        printf("\n file open failed!!");
    printf("S.no    Name                Phone number             Email id                 State");
    fflush(stdout);
    rewind(fptr);
    while(fscanf(fptr,"%s",buffer)!=EOF)
    {
        str=strtok(buffer,",");
        printf("\n%-8.3s",str);
        str=strtok(NULL,",");
        printf("%-20.19s",str);
        str=strtok(NULL,",");
        printf("%-20.19s",str);
        str=strtok(NULL,",");
        printf("%-30.29s",str);
        str=strtok(NULL,"\n");
        printf("%-20.19s\n",str);
    } 
    getchar();
WAIT_FOR_ENTER_KEY;
}


void save_contact(void)
{
    char buffer[100]={0};
    FILE* fptr=fopen("telephone.csv","r");
    FILE* sptr=fopen("contact.csv","w+");
    while(fscanf(fptr,"%s",buffer)!=EOF)
    {
        fprintf(sptr,"%s\n",buffer);
    }
    fclose(sptr);
    fclose(fptr);
    printf("\nSaved contacts successfully!");
}


