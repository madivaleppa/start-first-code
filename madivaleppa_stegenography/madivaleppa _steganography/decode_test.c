
#include<string.h>
#include<stdio.h>
#include"decode.h"
#include"types.h"




Status read_and_validate_decode_args(char* argv[],DecodeInfo* decInfo)
{
    char* ptr;
    ptr=strstr(argv[2],".bmp");
    if(ptr!=NULL && strcmp(ptr,".bmp")==0)
    {//store the name into src_fname
        decInfo->src_fname=argv[2];
        if(argv[3]== NULL)
        {
            strcpy(decInfo->output_fname,"output");
        }
        else
           strcpy(decInfo->output_fname,argv[3]);

        return e_success;
    }
    else
        printf("\nError: input file is not .bmp file");
        fflush(stdout);
    return e_failure;
}
Status do_decoding(DecodeInfo* decInfo)
{
    if(decode_open_files(decInfo)==e_success)
    {
        printf("\nfile open success");
        fflush(stdout);
        if(skip_header(decInfo)==e_success)
        {
            printf("\nsuccess skip header");
            fflush(stdout);
           if(decode_magic_string(decInfo) == e_success)
           {
                printf("\nmagic strin decode success");
                fflush(stdout);
                if(decode_file_extn_size(decInfo) ==e_success)
                {
                    printf("\nsuccess decode extn size");
                    if(decode_file_extn(decInfo)==e_success)
                    {
                        printf("\nsuccess decode file extension");
                        if(decode_secret_file_data_size(decInfo)==e_success)
                        {
                            printf("\n success secret file data size");
                            if(decode_secret_file_data(decInfo)==e_success)
                            {
                                printf("\n decoding secret file data success");
                                return e_success;
                            }
                        }

                        
                    }
                    else
                    {
                        printf("\nfailed decode file extension");
                    }
                }


           }
           else
           {
               printf("\n decode magic string failed");
               return e_failure;
           }
        }


    }
    else
    {
        printf("\n file open faiure");
        return e_failure;
    }
    return e_success;
}


Status decode_open_files(DecodeInfo* decInfo)
{
    decInfo->fptr_stego_image=fopen(decInfo->src_fname,"r");
    if(decInfo->fptr_stego_image== NULL)
    {
        printf("\nfile Open failed");
        fflush(stdout);
        return e_failure;
    }
    return e_success;
}

Status skip_header(DecodeInfo* decInfo)
{
    fseek(decInfo->fptr_stego_image,54,SEEK_SET);
    return e_success;
}

Status decode_magic_string(DecodeInfo* decInfo)
{
    char magic_string[3];//to store the decoded magic string
    char buffer[8];
    int i;
    for(i=0;i<2;i++)
    {
        fread(buffer,8,1,decInfo->fptr_stego_image);
        magic_string[i]=decode_byte_to_lsb(buffer);

    }
    magic_string[i]='\0';

    if(!strcmp(magic_string,"#*"))
        return e_success;
    else
        return e_failure;
}
 

char decode_byte_to_lsb(char* buffer)
{
    char ch=0;
    for(int i=0;i<8;i++)
    {
        ch=ch|((buffer[i]&1)<<i);
    }
    return ch;
}

Status decode_file_extn_size(DecodeInfo* decInfo)
{
    char buffer[32];
    fread(buffer,32,1,decInfo->fptr_stego_image);
    decInfo->extn_size=decode_size_to_lsb(buffer);
    return e_success; 
}
int decode_size_to_lsb(char *buffer)
{
    int n;
    for(int i=0;i<32;i++)
    {
        n=n|((buffer[i]&1)<<i);
    }
    return n;
}
Status decode_file_extn(DecodeInfo* decInfo)
{
    char buffer[8];
    char file_extn[decInfo->extn_size+1];
    int i;
    for(i=0;i<decInfo->extn_size;i++)
    {
        fread(buffer,8,1,decInfo->fptr_stego_image);
        file_extn[i]=decode_byte_to_lsb(buffer);
    }
    file_extn[i]='\0';
    strcat(decInfo->output_fname,file_extn);
    decInfo->fptr_output_fname=fopen(decInfo->output_fname,"w");
    if(decInfo->fptr_output_fname==NULL)
    {
        printf("\n open output file failed");
        return e_failure;
    }
    return e_success;
}

Status decode_secret_file_data_size(DecodeInfo* decInfo)
{
    char buffer[32];
    fread(buffer,32,1,decInfo->fptr_stego_image);
    decInfo->data_size=decode_size_to_lsb(buffer);
    return e_success;
}

Status decode_secret_file_data(DecodeInfo* decInfo)
{
    char buffer[8];
    char secret_data[decInfo->data_size+1];
    int i;
    for(i=0;i<decInfo->data_size;i++)
    {
        fread(buffer,8,1,decInfo->fptr_stego_image);
        secret_data[i]=decode_byte_to_lsb(buffer);
    }
    secret_data[i]='\0';
    fwrite(secret_data,decInfo->data_size,1,decInfo->fptr_output_fname);
    fclose(decInfo->fptr_output_fname);
    return e_success;
}
