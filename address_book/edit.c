#include"header.h"
extern contact_detail_t d_details;

void update(void)
{
    char buffer[100];
    FILE* fptr=fopen("telephone.csv","r");
    FILE* tfptr=fopen("temp.csv","w+");
    while(fscanf(fptr,"%s",buffer)!=EOF)
    {
        if(strstr(buffer,d_details.phone_number)||strstr(buffer,d_details.email_address))
        {
            fwrite(d_details.index,strlen(d_details.index),1,tfptr);
            fprintf(tfptr,",");
            fwrite(d_details.name,strlen(d_details.name),1,tfptr);
            fprintf(tfptr,",");
            fwrite(d_details.phone_number,strlen(d_details.phone_number),1,tfptr);
            fprintf(tfptr,",");
            fwrite(d_details.email_address,strlen(d_details.email_address),1,tfptr);
            fprintf(tfptr,",");
            fwrite(d_details.address,strlen(d_details.address),1,tfptr);
            fprintf(tfptr,"\n");
            continue;
        }
        fprintf(tfptr,"%s\n",buffer);
    }
    fclose(tfptr);
    fclose(fptr);
    fptr=fopen("telephone.csv","w+");
    tfptr=fopen("temp.csv","r");
    rewind(tfptr);
    rewind(fptr);
    while(fscanf(tfptr,"%s",buffer)!=EOF)
    {
        fprintf(fptr,"%s\n",buffer);
    }
    fclose(fptr);
    remove("temp.csv");
    printf("\n Edited contact successfully!");

}


int multiple_contacts(FILE* fptr)
{
    char *str;
    char buffer[100];
    char read_index[4]={0};
    printf("\nEnter the index number to be edited:");
    getchar();
    scanf("%s",read_index);
    rewind(fptr);
    while(fscanf(fptr,"%s",buffer)!=EOF)
    {
        str=strtok(buffer,",");
        if(!strcmp(str,read_index))
        {
            strcpy(d_details.index,str);
            printf("\n%-5.3s",str);
            str=strtok(NULL,",");
            strcpy(d_details.name,str);
            printf("%-20.19s",str);
            str=strtok(NULL,",");
            strcpy(d_details.phone_number,str);
            printf("%-20.19s",str);
            str=strtok(NULL,",");
            strcpy(d_details.email_address,str);
            printf("%-25.24s",str);
            str=strtok(NULL,"\n");
            strcpy(d_details.address,str);
            printf("%-20.19s\n",str);
        }
    }
}

int f_edit(char *index,FILE*fptr)
{
    FILE* tfptr;
    char *str;
    int opt;
    char set=1;
    char buffer[100];
    contact_detail_t details;
    printf("\nWhat do you want to edit?");
    printf("\n1.Name\n2.Phone number\n3.email id\n4.state");
    printf("\nEnter the option:");
    getchar();
    scanf("%d",&opt);
    while(1)
    {
        switch(opt)
        {
            case 1:
                printf("\n Enter the new name:");
                getchar();
                scanf("%[^\n]",details.name);
                strcpy(d_details.name,details.name);
                update();
                return SUCCESS;

            case 2:
                while(set)
                {
                    printf("\n Enter the new phone number:");
                    getchar();
                    scanf("%s",details.phone_number);
                    strcpy(d_details.phone_number,details.phone_number);
                    if(validate_number(details)==SUCCESS)
                    {
                        rewind(fptr);
                        while(!feof(fptr))
                        {
                            fscanf(fptr,"%s",buffer);
                            if(strstr(buffer,details.phone_number))
                            {
                                printf("\nnumber is already present!");
                                return FAILURE; 
                            }
                        } 
                        set=0;
                        update();
                    }
                    else
                        printf("\n Enter the valid phone number!\n");
                }
                return SUCCESS;
            case 3:
                while(set)
                {
                    printf("\n Enter the  new email id :");
                    getchar();
                    scanf("%s",details.email_address);
                    strcpy(d_details.email_address,details.email_address);
                    if(validate_email(details)==SUCCESS)
                    {
                        rewind(fptr);
                        while(!feof(fptr))
                        {
                            fscanf(fptr,"%s",buffer);
                            if(strstr(buffer,details.email_address))
                            {
                                printf("\nThis email is already present!");
                                return FAILURE; 
                            }
                        } 
                        set=0;
                        update();
                    }
                    else
                        printf("\n Enter the valid email id!\n");
                }
                return SUCCESS;
            case 4:
                printf("\n Enter the state:");
                getchar();
                scanf("%[^\n]",details.address);
                strcpy(d_details.name,details.address);
                update();
                return SUCCESS;

            default:
                printf("\n Enter the proper choice!!");
        }
    }
}



void edit_contact(void)
{
    int count;
    int opt;
    contact_detail_t details;
    FILE* fptr=fopen("telephone.csv","r");
    printf("\nWhich contact do you want to edit?");
    printf("\n1.Name\n2.Phone number\n3.email id\n");
    while(1)
    {
        getchar();
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                printf("\n Enter the name:");
                getchar();
                scanf("%[^\n]",details.name);
                count=search(1,details,fptr);
                if(count==1)
                    f_edit(d_details.index,fptr);
                else if(count>1)
                {
                    multiple_contacts(fptr);
                    f_edit(d_details.index,fptr);
                }
                return;

            case 2:
                printf("\n Enter the Phone number:");
                getchar();
                scanf("%s",details.phone_number);
                if(validate_number(details)==SUCCESS)
                {
                        search(2,details,fptr);
                    f_edit(d_details.index,fptr);
                }
                return;
            case 3:
                printf("\n Enter the email id:");
                getchar();
                scanf("%[^\n]",details.email_address);
                if(validate_email(details)==SUCCESS)
                {
                    search(3,details,fptr);
                    f_edit(d_details.index,fptr);
                }
                return;
            default:
                printf("\nEnter the valid choice");
        }
    }
    return;
}

