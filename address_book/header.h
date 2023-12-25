
#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdlib.h>

#define MAX_BUF 32

#define DEFAULT_FILE "telephone.csv"
#define DEFAULT_LIST_SIZE 32

#define SAVED 0
#define NOT_SAVED 1


#define INITIAL_SIZE 32
#define NAME_SIZE 32 // size of a contact name 
#define NUMBER_SIZE 32 // size of a phone number
#define EMAIL_SIZE 32 // size of an email address

//#define PHONE_NUMBER_COUNT 5 // maximum number of phones per contact
//#define EMAIL_ADDRESS_COUNT 1 // maximum number of email addresses per contact

//#define DETAIL_SIZE 32
//#define DETAIL_ITEM_COUNT 5

#define MSG_VALID_CHOICE "Please enter a valid choice.\n"

#define CLR_SCREEN system("clear") // command for clearing the console

#define WAIT_FOR_ENTER_KEY  while(getchar() != '\n')

typedef int bool_t;
#define FALSE 0
#define TRUE 1

typedef enum
{
	FAILURE,
	ADDRESS_BOOK_NULL,
	FILE_NOT_AVAILABLE,
	FILE_COULD_NOT_BE_CREATED,
	FILENAME_NULL,
	MEMORY_ALLOCATION_FAILURE,
	SUCCESS,
	WRONG_FILE_FORMAT,
} return_t;

typedef struct
{
	char name[NAME_SIZE];
	char phone_number[NUMBER_SIZE];
	char email_address[EMAIL_SIZE];
    char address[NAME_SIZE];
    char index[4];
} contact_detail_t;

return_t add_contact(void);
int search_contact(void);
void print_contact(void);
void main_menu(void);
void save_contact(void);
void delete_contact(void);
void delt(int,contact_detail_t);
void update(void);
void edit_contact(void);
int f_edit(char *index,FILE*fptr);
int multiple_contacts(FILE* fptr);
int search(int,contact_detail_t details,FILE*);
int validate_state(contact_detail_t details);
int validate_number(contact_detail_t details);
int validate_email(contact_detail_t details);
int add_to_file(contact_detail_t,FILE*);
int search_mobile_num(contact_detail_t,FILE*);
int search_email_id(contact_detail_t,FILE*);

#endif
