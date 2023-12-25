#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include"common.h"
Status encode_magic_string(const char *magic_string,EncodeInfo *encInfo)
{
    encode_data_to_image(MAGIC_STRING,strlen(MAGIC_STRING),encInfo->fptr_src_image,encInfo->fptr_stego_image);
    return e_success;    
}

Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buffer[8];
    for(int i=0;i<size;i++)
    {
        fread(buffer,8,1,fptr_src_image);
        encode_byte_to_lsb(data[i],buffer);
        fwrite(buffer,8,1,fptr_stego_image);
    }
    return e_success;


}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    for(int i=0;i<8;i++)
    {
        image_buffer[i]= (image_buffer[i] &0xFE)|((data&(1<<i))>>i);
    }
    return e_success;
}

Status encode_secret_file_extn_size(char* file_extn, EncodeInfo *encInfo)
{
    encode_size_to_lsb(strlen(file_extn),encInfo);
    return e_success;
}

Status encode_size_to_lsb(long ext_size,EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer,32,1,encInfo->fptr_src_image);
    for(int i=0;i<32;i++)
    {
        buffer[i]=(buffer[i] &0xFE)|((ext_size&(1<<i))>>i);
    }
    fwrite(buffer,32,1,encInfo->fptr_stego_image);
    return e_success;
}

Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo)
{
    encode_data_to_image(file_extn,strlen(file_extn),encInfo->fptr_src_image,encInfo->fptr_stego_image);
    return e_success;
}

Status encode_secret_file_size(long size,EncodeInfo *encInfo)
{
    encode_size_to_lsb(size,encInfo);
    return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    rewind(encInfo->fptr_secret);                   //brings the file index to the starting point
    for(int i=0;i<encInfo->size_secret_file;i++)
    {
        char ch;
        char buffer[8];
        fread(&ch,1,1,encInfo->fptr_secret);
        fread(buffer,8,1,encInfo->fptr_src_image);
        encode_byte_to_lsb(ch,buffer);
        fwrite(buffer,8,1,encInfo->fptr_stego_image);
    }
    return e_success;
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch;
    while(fread(&ch,1,1,fptr_src)>0)
    {
        fwrite(&ch,1,1,fptr_dest);
    }
    return e_success;
}






Status check_capacity(EncodeInfo* encInfo)
{
    int magic_len=strlen(MAGIC_STRING)*8;
    int extension_len=strlen(strstr(encInfo->secret_fname ,"."));
    int secret_file_size=get_file_size(encInfo->fptr_secret);
    int sum=magic_len+32+(extension_len*8)+32+(secret_file_size*8);
    int src_image_size=get_image_size_for_bmp(encInfo->fptr_src_image);
    encInfo->size_secret_file=secret_file_size;
    if(sum <(src_image_size-54))
        return e_success;
    else
        return e_failure;
}


OperationType check_operation_type(char* argv[])
{
    if(strcmp(argv[1],"-e")==0)
        return e_encode;
    else if(strcmp(argv[1],"-d")==0)
        return e_decode;
    return e_unsupported;
}


Status copy_bmp_header(FILE* src_fptr,FILE* dest_fptr)
{
    char buffer[54];
    rewind(src_fptr);
    rewind(dest_fptr);
    fread(buffer,1,54,src_fptr);
    fwrite(buffer,1,54,dest_fptr);
    if(ftell(dest_fptr)==54)
    {
        printf("\nheader file copy success");
        fflush(stdout);
        return e_success;
    }
    else
    {
        printf("header file copy failed!!");
        fflush(stdout);
        return e_failure;
    }

}

uint get_file_size(FILE* fptr)
{
    fseek(fptr,0,SEEK_END);
    return ftell(fptr);
}


Status read_and_validate_encode_args(char* argv[],EncodeInfo* encInfo)
{
    char*str=strstr(argv[2],".bmp");

    if(str!=NULL&&strcmp(str,".bmp")==0)
    {
        printf("\nargv[2] is .bmp extension");
        fflush(stdout);
        encInfo->src_image_fname=argv[2];

    }
    else
    {
        printf("\nsource file is not .bmp file");
        fflush(stdout);
        return e_failure;
    }
    str=strstr(argv[3],".");
    if(str!=NULL)
    {
        if(((strcmp(strstr(argv[3],"."),".txt"))==0)||((strcmp(strstr(argv[3],"."),".sh"))==0)||((strcmp(strstr(argv[3],"."),".c"))==0))
        {
            printf("\nargv[3] is . extension");
            fflush(stdout);
            encInfo->secret_fname=argv[3];
            strcpy(encInfo->extn_secret_file,strstr(argv[3],"."));
        }
    
    else
    {
        printf("\ninvalid secret file type");
        fflush(stdout);
        return e_failure;
    }
    }
    if(argv[4]== NULL)
    {
        printf("\ndefault name is saved");
        encInfo->stego_image_fname="stego.bmp";
        return e_success;
    }
    else
    {
        str=strstr(argv[4],".bmp");
        if(str!=NULL)
        {
            if(!strcmp(str,".bmp"))
            {
                printf("\ndestination file extension is .bmp");
                encInfo->stego_image_fname=argv[4];
            }
        }
        else
        {
            printf("\ndestinaion file is not bmp");
            fflush(stdout);
            return e_failure;
        }
    }
    return e_success;
}            
Status do_encoding(EncodeInfo* encInfo)
{//function to open the files 
    if(open_files(encInfo)==e_success)
    {
        printf("\nfile opening success\n");
        fflush(stdout);
        if(check_capacity(encInfo)==e_success)
        {
            printf("\ncheck capacity success");
            fflush(stdout);
            if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
            {
                printf("\nheader copy success!!");
                if(encode_magic_string(MAGIC_STRING,encInfo)==e_success)
                {
                    printf("\nsuccess encode magic string.");
                    if(encode_secret_file_extn_size(encInfo->extn_secret_file,encInfo)==e_success)
                    {
                        printf("\n succes encode secret file extension size");
                        if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_success)
                        {
                            printf("\n success encode secret file extension ");
                            if(encode_secret_file_size(encInfo->size_secret_file,encInfo)== e_success)
                            {
                                printf("\n success encode secret file size");
                                if(encode_secret_file_data(encInfo)==e_success)
                                {

                                    printf("\nsuccess encode secret file data");
                                    if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
                                    {
                                        printf("\nsuccess copy of remaining image data");
                                        return e_success;
                                    }


                                }


                            } 
                        }

                    }

                }

            }

        }


    }
}




uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    fseek(fptr_image, 18, SEEK_SET);
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}
