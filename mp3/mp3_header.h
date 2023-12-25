#ifndef MP3_H 
#define MP3_H
#include<stdio.h>

#include<string.h>
#include"types.h"
Status check_id_version(char *argv[],FILE* fptr);
Status edit(FILE* fptr,char* argv[],char* opt);
void get_data(FILE* fptr);
void view(FILE* fptr);
void print_tag_data(void);
void display_error(void);
void display_menu(void);
Status check_option(char* argv[]);
int convert_to_int(char *buff);
void print_success(char* opt,char* argv[]);
#endif
