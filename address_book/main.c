/*
	C Project
	Address Book

	MAIN CONSOLE PROGRAM

*/
#include "header.h"

int main(void)
{
    int opt;
    char flag=0;
    main_menu();
    while(1)
    {
        printf("\nEnter the option: ");
        getchar();
        scanf("%d",&opt);
        
            switch(opt)
            {
                case 1:
                    add_contact();
                    break;
                case 2:
                    edit_contact();
                    break;
                case 3:
                    search_contact();
                    break;
                case 4:
                    delete_contact();
                    break;
                case 5:
                    print_contact();
                    break;
                case 6:
                    save_contact();
                    break;
                case 7:
                    CLR_SCREEN;
                    main_menu();
                    break;
                case 8:
                    flag=1;
                    break;
                default:
                    printf("\n Enter the valid option!\n\n");

            }
    

        if(flag)
            break;
    }
    return 0;
}

void main_menu(void)
{
    printf("\n1.Add contact");
    printf("\n2.Edit contact");
    printf("\n3.Search contact");
    printf("\n4.Delete contact");
    printf("\n5.print contacts");
    printf("\n6.Save contacts");
    printf("\n7.Clear the screen");
    printf("\n8.exit");
}
