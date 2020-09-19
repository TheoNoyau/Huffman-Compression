#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "huffman.h"

// Buffersize est globale
int bufferSize;

unsigned char bitToCar(unsigned char *tab)
{
    int i ;
    unsigned char sum;

    sum = 0 ;
    for (i=0 ; i<8 ; i++){
        sum *= 2;
        sum += tab[i]-'0';
    }
    return sum;
}

void ecrire_2 (Bin_file * output, char bit) {
    unsigned char octet, b ;
    int i ;
    output->octet[output->i_octet++] = bit ;
    if (output->i_octet == 8){
        octet = 0 ;
        b = 0x80 ;
        for (i=0 ; i<8 ; i++){
            if (output->octet[i] == '1'){
                octet = octet|b ;
            }
            b = b>>1 ;
        }
        output->i_octet = 0 ;
        output->record[output->i_record] = octet ;
        output->i_record = output->i_record+1 ;
        output->nb_octets = output->nb_octets+1 ;
        fprintf(output->file, "%c", output->record[0]);
        output->i_record = 0;
        
        if (output->i_record == BLOCK_SIZE){
            //Ecriture de output->record dans output->file

            for (i = 0; i < output->record_length; i++) {
                fprintf(output->file, "%c", output->record[i]);
            }
            output->i_record = 0 ;
        }
    }
}

char lecture(Bin_file * input){
    unsigned char bit;
    int ch;

    if (input->record_length == 0){
        while ((ch = getc(input->file)) != EOF){
            input->record[input->i_record] = ch;
            input->i_record += 1;
            input->record_length += 1;
        }
        input->i_record = 0;
        chartobin(input, input->record[input->i_record]);
        input->i_record += 1;
        input->i_octet = 0;
        input->nb_octets += input->record_length;     
    }

    bit = input->octet[input->i_octet];
    input->i_octet += 1;
    if (input->i_octet == 8){
        chartobin(input, input->record[input->i_record]);
        input->i_record += 1;
        input->i_octet = 0;
        if (input->i_record == BLOCK_SIZE){
            input->record_length = 0;
        }
    }
    
    return bit;
}

void chartobin(Bin_file * input, int c)
{
    int i;
    for(i = 7; i >= 0; i--){
        input->octet[i] = c % 2;      
        c = c / 2;          
    }
}

void open_file_read(Bin_file * input, char * name){
    input->file = fopen(name, "r");
}
void open_file_write(Bin_file *input, char *name){
    input->file = fopen(name, "w");
}

void close_file(Bin_file * input){
    fclose(input->file);
}