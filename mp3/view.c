#include"mp3_header.h"
int size;
char title[100]={0};
char artist[100]={0};
char album[100]={0};
char year[4]={0};
char comment[100]={0};
char content[100]={0};
char buffer[100]={0};
char tag[5]={0};

int convert_to_int(char *buff)
{
    size=0;

        for(int i=3;i>=0;i--)
        {
            size=size|buff[i]<<((3-i)*8);
        }
    return size;
}

void view(FILE* fptr)
{
    get_data(fptr);
    print_tag_data();
}



void get_data(FILE* fptr)
{
    rewind(fptr);
    fseek(fptr,10,SEEK_SET);

    for(int i=0;i<6;i++)
    {

        fread(tag,4,1,fptr);
        fread(buffer,4,1,fptr);
        size=convert_to_int(buffer);
        fseek(fptr,3,SEEK_CUR);
        if(!strcmp(tag,"TPE1"))
        {
            fread(buffer,size-1,1,fptr);
            strcpy(artist,buffer);
        }
        else if(!strcmp(tag,"TIT2"))
        {
            fread(buffer,size-1,1,fptr);
            strcpy(title,buffer);
        }
        else if(!strcmp(tag,"TALB"))
        {
            fread(album,size-1,1,fptr);
            
        }
        else if(!strcmp(tag,"TYER"))
        {
            fread(year,size-1,1,fptr);
        }
        else if(!strcmp(tag,"TCON"))
        {
            fread(content,size-1,1,fptr);
        }
        else if(!strcmp(tag,"COMM"))
        {
            fread(comment,size-1,1,fptr);
        }

    }

}


void print_tag_data(void)
{
    printf("\n-----------------------------------------------------------------------------:");
    printf("\nMP3 Tag reader and Editor  for ID3V2");
    printf("\n-----------------------------------------------------------------------------:");
    printf("\n Title          :           %s",title);
    printf("\n Artist         :           %s",artist);
    printf("\n Album          :           %s",album);
    printf("\n year           :           %s",year);
    printf("\n Content        :           %s",content);
    printf("\n Comment        :           %s",comment);
    printf("\n-----------------------------------------------------------------------------:");
}

