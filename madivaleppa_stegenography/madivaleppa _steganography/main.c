/*

Name:Madivaleppa Suresh Dadigundi
Date:21/11/2023
Description:LSB Image Staganography

   */
//header files
#include<stdio.h>
#include "encode.h"
#include "types.h"
#include "common.h"
#include "decode.h"
#include<string.h>
int main(int argc,char *argv[])

{
    
    /*
        * checks the number of arguments are passed correct or not
        * Print error message and return 0 if number of arguments are not correct
        *continue if argument counts are correct.
    */
    if(argc<4)
    {
        if(argc<3)
        {
            printf("Error : please pass the valid argument \n ./a.out -d <file_name.bmp> <output_file_name>");
            return 0;
        }
        else if(!strcmp(argv[1],"-e"))
        {
        printf("Error : please pass the valid argument \n ./a.out -e <source_file.bmp> <sectet_file> <output_file>");
        return 0;
        }
    }

    /*
       * creates structure named encInfo
       * check the operation type by passing argument vector
       * returns e_encode if the -e passed in the cl
       * returns e_decode if the -d is passed in the cl
       * returns e_unsupported if the 2nd argument is nither -e not -d 
       * check read and validate encode arguments  
        
     */

    EncodeInfo encInfo;
    DecodeInfo decInfo;
    if (check_operation_type(argv)== e_encode)
    {
        printf("\nchoice is encoding");
        fflush(stdout);
        if(read_and_validate_encode_args(argv,&encInfo)==e_success)
        {
            printf("\narguments are correct");
            fflush(stdout);
            if (do_encoding(&encInfo)==e_success)
            {   
                printf("\ndo_encoding success");
            }
        }
        else
        {
            printf("\nread and validate args failed!");
            return 0;
        }
    }

    else if(check_operation_type(argv)==e_decode)
    {
        printf("\n choice is decoding");
        fflush(stdout);

        if(read_and_validate_decode_args(argv,&decInfo)==e_success)
        {
            printf("\n arguments are correct");
            fflush(stdout);
            if(do_decoding(&decInfo)==e_success)
            {
                printf("\n decoding is success!!");
            }
        }
    }
    else
    {
        printf("Please the pass valid argument -e or -d");
    }
    return 0;

}

