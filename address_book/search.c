#include "header.h"
char *str;
contact_detail_t d_details;
int search_contact(void)
{
    int count;
    char flag=1;
    int op;
    contact_detail_t details;
    FILE* fptr=fopen("telephone.csv","r");
    if(fptr==NULL)
    {
        printf("\n file open failed");
        return FAILURE;
    }

    printf("\n1.name\n2.Phone number\n3.email id\n4.state\n5.exit");
    printf("\nEnter the choice:");
    while(flag)
    {
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                printf("\n Enter the name:");
                getchar();
                scanf("%[^\n]",details.name);
                count=search(1,details,fptr);
                flag=0;
                break;

            case 2:
                printf("\n Enter the Phone number:");
                getchar();
                scanf("%[^\n]",details.phone_number);
                count=search(2,details,fptr);
                flag=0;
                break;
            case 3:
                printf("\n Enter the email id:");
                getchar();
                scanf("%[^\n]",details.email_address);
                count=search(3,details,fptr);
                flag=0;
                break;
            case 4:
                printf("\n Enter the state:");
                getchar();
                scanf("%[^\n]",details.address);
                count=search(4,details,fptr);
                flag=0;
                break;
            case 5:
                flag=0;
                break;
            default:
                CLR_SCREEN;
                printf("\n Enter the proper choice!!");
                break;
        }
    }
    return count;
}
int search(int op,contact_detail_t details,FILE* fptr)
{
    int count=0;
    char buffer[100];
    char* s;
    if(op==1)
        s=details.name;
    else if(op==2)
        s=details.phone_number;
    else if(op==3)
        s=details.email_address;
    else if(op==4)
        s=details.address;

    while(!feof(fptr))
    {
        fscanf(fptr,"%s",buffer);
        if(strstr(buffer,s))
        {
            count++;
            str=strtok(buffer,",");
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
    if(count==0)
        printf("\nNO DATA FOUND!");
    return count;

}



