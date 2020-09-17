#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>  /* getopt */
unsigned char *read_input();
unsigned char* hex_to_base64(unsigned char *hex_input);
#define input_array_size 10000
int main(int argc, char *argv[]){
    int cmd_opt;
    char input_file_name[1000];
    char output_file_name[1000];
    // Handle command options
    while ((cmd_opt = getopt (argc, argv, "i:o:")) != -1){
        switch (cmd_opt){
            case 'i':
                strcpy(input_file_name,optarg);
                break;
            case 'o':
                strcpy(output_file_name,optarg);
                break;
        }
    }
    FILE *input_file;
    FILE *output_file;
    input_file = fopen(input_file_name, "r");
    output_file = fopen(output_file_name, "w");
    unsigned char *hex_input= malloc(input_array_size*sizeof(unsigned char));
    while(fscanf(input_file,"%s",hex_input)!=EOF){
    //unsigned char *hex_input=read_input();
    int input_size = strlen(hex_input);
    unsigned char *base64_output=hex_to_base64(hex_input);
    if((input_size/2)%3 == 0)
        fprintf (output_file,"%s\n",base64_output);
    else if((input_size/2)%3 == 1)
        fprintf (output_file,"%s==\n",base64_output);
    else if((input_size/2)%3 == 2)
        fprintf (output_file,"%s=\n",base64_output);
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}

unsigned char* hex_to_base64(unsigned char *hex_input){
    int input_size = strlen(hex_input);
    int output_size = (((input_size*2)%3)==0) ? (input_size*2)/3 : ((input_size*2)/3)+1;
    unsigned char *base64_output=calloc(output_size,1);
    // ancii to binary
    for(int i=0;i<input_size;i++){
        if('0'<=hex_input[i] && hex_input[i]<='9')
            hex_input[i] -= '0';
        else if ('A'<=hex_input[i] && hex_input[i]<='F')
            hex_input[i] -= 'A'-10;
    }
    // 4 bits merge to 6 bits
    for(int i=0,j=0;i<output_size;i++){
        if(i%2==0){
            base64_output[i] |= hex_input[j]<<2;
            if(j+1 < input_size)
                base64_output[i] |= hex_input[j+1]>>2;
        }
        else{
            base64_output[i] |= (hex_input[j+1]<<4) & 0x30;
            base64_output[i] |= hex_input[j+2];
            j += 3;
        }
    }
    // parse to base64 encoding
    for(int i=0;i<output_size;i++){
        if(0<=base64_output[i] && base64_output[i]<=25)
            base64_output[i] += 'A';
        else if(26<=base64_output[i] && base64_output[i]<=51)
            base64_output[i] += 'a'-26;
        else if(52<=base64_output[i] && base64_output[i]<=61)
            base64_output[i] += '0'-52;
        else if(base64_output[i]==62)
            base64_output[i] += '+'-62;
        else if(base64_output[i]==63)
            base64_output[i] += '/'-63;
    }
    return base64_output;
}