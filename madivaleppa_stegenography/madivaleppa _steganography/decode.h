#ifndef DECODE_H
#define DECODE_H


#include "types.h"


typedef struct Decode
{
    char * src_fname;
    FILE* fptr_stego_image;

    //secret file

    char extn_extn_secret_file[4];
    int extn_size;
    int data_size;

    //op file name
    char output_fname[20];
    FILE* fptr_output_fname;
}DecodeInfo;


//Status check_operation_type(char *agv[]);

Status read_and_validate_decode_args(char* argv[],DecodeInfo* decInfo);

Status do_decoding(DecodeInfo* decInfo);

Status decode_open_files(DecodeInfo* decInfo);

Status skip_header(DecodeInfo* decInfo);

Status decode_magic_string(DecodeInfo* decInfo);

Status decode_file_extn_size(DecodeInfo* decInfo);

char decode_byte_to_lsb(char* buffer);

int decode_size_to_lsb(char* buffer);

Status decode_extn_size(DecodeInfo* decInfo);

Status decode_file_extn(DecodeInfo* decInfo);

Status decode_secret_file_data_size(DecodeInfo* decInfo);

Status decode_secret_file_data(DecodeInfo* decInfo);


#endif
