
#include"header.h"

char buffer[100]={0};
return_t add_contact(void)
{
    FILE *fptr=fopen("telephone.csv","r");
    contact_detail_t details;
    
    while(1)
    {
        getchar();
        printf("\n Enter the name :");
        scanf("%[^\n]",details.name);
        printf("\n Enter the phone number: ");
        while(1)
        {
            scanf("%s",details.phone_number);
            if(validate_number(details)==SUCCESS)
                break;
            else
            {
                CLR_SCREEN;
                printf("\nEnter the correct phone number!!\n");
            }
        }
        printf("\n Enter email id : ");
        getchar();
        while(1)
        {
            scanf("%s",details.email_address);
            if(validate_email(details)==SUCCESS)
                break;
            else
            {
                CLR_SCREEN;
                printf("\nEnter the correct email id!!\n");
            }
        }
        printf("\n Enter the state:");
        while(1)
        {
            getchar();
            scanf("%s",details.address);
            if(validate_state(details)==SUCCESS)
                break;
            else
            {
                CLR_SCREEN;
                printf("\n Enter the state correctly!!\n");
            }
        }

        if(add_to_file(details,fptr)==SUCCESS)
        {
            fclose(fptr);
            return SUCCESS;
        }
    }
    getchar();
    WAIT_FOR_ENTER_KEY;
        
}

int add_to_file(contact_detail_t details,FILE* fptr)
{
    char ch;
    int n;
    char *str;
    int count=0;
    fscanf(fptr,"%s",buffer);
    FILE* sfptr=fopen("telephone.csv","a+");
    if(buffer[0]==0)
    {
        fwrite("1",1,1,sfptr);
        fwrite(",",1,1,sfptr);
        fwrite(details.name,strlen(details.name),1,sfptr);
        fwrite(",",1,1,sfptr);
        fwrite(details.phone_number,strlen(details.phone_number),1,sfptr);
        fwrite(",",1,1,sfptr);
        fwrite(details.email_address,strlen(details.email_address),1,sfptr);
        fwrite(",",1,1,sfptr);
        fwrite(details.address,strlen(details.address),1,sfptr);
        fwrite("\n",1,1,sfptr);
        fclose(sfptr);
        return SUCCESS;
    }
    rewind(fptr);
    while(!feof(fptr))
    {
        fscanf(fptr,"%s",buffer);
        if(strstr(buffer,details.phone_number))
        {
            printf("\nnumber is already present!");
            fclose(sfptr);
            return FAILURE;
        }

    }   
    rewind(fptr);
    while(!feof(fptr))
    {
        fscanf(fptr,"%s",buffer);
        if(strstr(buffer,details.email_address))
        {
            printf("\n email already present");
            fclose(sfptr);
            return FAILURE;
        }
    }
   // fclose(fptr);
   // printf("%s",buffer);
    char* ind=strtok(buffer,",");
    sscanf(ind,"%d",&count);
    count++;
    fprintf(sfptr," %d",count);
    fwrite(",",1,1,sfptr);
    fwrite(details.name,strlen(details.name),1,sfptr);
    fwrite(",",1,1,sfptr);
    fwrite(details.phone_number,strlen(details.phone_number),1,sfptr);
    fwrite(",",1,1,sfptr);
    fwrite(details.email_address,strlen(details.email_address),1,sfptr);
    fwrite(",",1,1,sfptr);
    fwrite(details.address,strlen(details.address),1,sfptr);
    fwrite("\n",1,1,sfptr);
    fclose(sfptr);
    return SUCCESS;
}






int validate_state(contact_detail_t details)
{
    int i=0;
    while(details.address[i])
    {
        if(details.address[i]>=65&&details.address[i]<=90||details.address[i]>=97&&details.address[i]<=122)
        {
            i++;
            continue;
        }
        else
            return FAILURE;
    }
    return SUCCESS;
}



int validate_number(contact_detail_t details)
{
    int i=0;
    char flag=0;
    if(strlen(details.phone_number)!=10)
        return FAILURE;
    for(int i=0;i<10;i++)
    {
        if(details.phone_number[i]>=48&&details.phone_number[i]<=57)
            continue;
        else
            return FAILURE;
    }
    return SUCCESS;
}

int validate_email(contact_detail_t details)
{
    int flag=0;
    char *s=strstr(details.email_address,"@");
    if(s==NULL)
    {
        return FAILURE;
        printf("%s",s);
    }
    else
    {
        if(!(strcmp(s,"@gmail.com")&&strcmp(s,"@yahoo.com")))
            return SUCCESS;
        printf("%s",s);
    }
    return FAILURE;
}



int search_mobile_num(contact_detail_t details,FILE* fptr)
{
    rewind(fptr);
    char ch;
    while(ch=fgetc(fptr)!=EOF)
    {
        fscanf(fptr,"%s",buffer);
        if(strstr(buffer,details.phone_number))
            return FAILURE;
    }
    return SUCCESS;
}
int search_email_id(contact_detail_t details,FILE* fptr)
{
    rewind(fptr);
    while(!feof(fptr))
    {
        fscanf(fptr,"%s",buffer);
        if(strstr(buffer,details.email_address))
            return FAILURE;
    }
    return SUCCESS;
}
        
