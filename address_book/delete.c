#include"header.h"
void delete_contact(void)
{
    int op;
    char flag=1;
    contact_detail_t details;
    details.index[0]=0;
    details.index[1]=0;
    details.index[2]=0;
    details.index[3]=0;
    printf("\n What you want to delete?\n");
    while(flag)
    {
        printf("1.Name\n2.phone number\n3.email address\n");
        printf("\nEnter the choice:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                printf("\n Enter the name:");
                getchar();
                scanf("%[^\n]",details.name);
                delt(1,details);
                flag=0;
                break;

            case 2:
                printf("\n Enter the Phone number:");
                getchar();
                scanf("%[^\n]",details.phone_number);
                delt(2,details);
                flag=0;
                break;
            case 3:
                printf("\n Enter the email id:");
                getchar();
                scanf("%[^\n]",details.email_address);
                delt(3,details);
                flag=0;
                break;
            
            default:
                CLR_SCREEN;
                printf("\nEnter the proper choice!\n");
        }
    }



}

void delt(int op,contact_detail_t details)
{

    int count=0;
    char buffer[100];
    int index;
    char sr_no[5];
    char *str;
    char copystring[100];
    char ans;
    FILE* fptr=fopen("telephone.csv","r");
    FILE* tfptr=fopen("temp.csv","w+");
    char* s;
    if(op==1)
        s=details.name;
    else if(op==2)
        s=details.phone_number;
    else if(op==3)
        s=details.email_address;
    rewind(fptr);
    while(fscanf(fptr,"%s",buffer)!=EOF)
    {
        if(op==0)
        { 
          strcpy(copystring,buffer);
           str=strtok(copystring,",");
           if(!strcmp(str,details.index))
           {
               printf("%s\n",buffer);
                s=details.index;
                count=1;
           }
        }
        else if(strstr(buffer,s))
        {
            count++;
            printf("%s\n",buffer);
        }
    }
    if(count==0)
    {
        printf("\nNOT FOUND!!");
        return;
    }
    if(count==1)
    {

        printf("\nDELETE CONTACT?(y/n):");
        getchar();
        scanf("%c",&ans);
        if(ans=='y'||ans=='Y')
        {
            rewind(fptr);
            rewind(tfptr);
            while(fscanf(fptr,"%s",buffer)!=EOF)
            {
                if(op==0)
                { 
                    strcpy(copystring,buffer);
                    str=strtok(copystring,",");
                    if(!strcmp(str,details.index))
                        break;         
                }
                else if(strstr(buffer,s))
                {   
                    break;
                }
                fprintf(tfptr,"%s\n",buffer);
            }
            while(fscanf(fptr,"%s",buffer)!=EOF)
            {
                str=strtok(buffer,",");
                sscanf(str,"%d",&index);
                index--;
                sprintf(sr_no,"%d",index);
                fprintf(tfptr," %s,",sr_no);
                str=strtok(NULL,",");
                fprintf(tfptr,"%s,",str);
                str=strtok(NULL,",");
                fprintf(tfptr,"%s,",str);
                str=strtok(NULL,",");
                fprintf(tfptr,"%s,",str);
                str=strtok(NULL,",");
                fprintf(tfptr,"%s\n",str);
            }
            fclose(fptr);
            fclose(tfptr);

            tfptr=fopen("temp.csv","r");
            fptr=fopen("telephone.csv","w");
            rewind(fptr);
            rewind(tfptr);
            while(fscanf(tfptr,"%s",buffer)!=EOF)
            {
                if(buffer[0]==0)
                    break;
                fprintf(fptr," %s\n",buffer);
            }
            fclose(fptr);
            fclose(tfptr);

            remove("temp.csv"); 
            printf("\nContact deleted successfully");
            return;
        }
        else
            return;
    }
    else
        printf("\nEnter the index to be deleted : ");
    getchar();
    scanf("%d",&index);
    sprintf(details.index,"%d",index);
    delt(0,details);
    return;
}


