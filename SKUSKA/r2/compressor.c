#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressor.h"
#define BUFSIZE 1024
#define MAX_LOOKAHEAD 32
#define MAX_DICT_SIZE 2048

// int find_match(const char *dict, int dict_size, const char *lookahead, int lookahead_size) {
//   int best_offset = 0;
//   int best_length = 0;

//   for (int i = 0; i < dict_size; i++) {
//     int length = 0;
//     while (dict[i + length] == lookahead[length] && length < lookahead_size && length < MAX_LOOKAHEAD) {
//       length++;
//     }

//     if (length > best_length) {
//       best_offset = i;
//       best_length = length;
//     }
//   }

//   return best_length;
// }

void compress(FILE* infile,FILE* outfile){

    char buffer[BUFSIZE];
    memset(buffer,0,BUFSIZE);
    while(1){
        int insize = fread(buffer,sizeof(char),BUFSIZE,infile);
        if (insize == 0){
            if (feof(infile)){
                // end of file
                break;
            }
            assert(!ferror(infile));
        }
        char outbuf[BUFSIZE*3];
        for (int i = 0; i < BUFSIZE*3; i++)
        {
            outbuf[i] = '\0';
        }
        
        /// Long run compress
        int Matching = 0;  //number of matching chars
        int NotMatching = 0; //number of not matching chars
        int pointerIn = 0; // position of input buffer
        int pointerOut = 0; // position of output buffer
        for (int i = 0; i < insize; i++)
        {
            if(pointerIn + 1 > insize){
                break;
            }
            if(buffer[pointerIn] != buffer[pointerIn + 1]){  //if the next char is not matching
                for (int j = pointerIn; j < insize; j++) {
                    if(j > insize){ //if the end of the buffer is reached
                        break;
                    }
                    if(buffer[j] != buffer[j + 1]){
                        NotMatching++;  //searching for not matching
                    } else {
                        break;
                    }
                }
                //toto nastane iba ak nenajde ziadne ktore nematchuju
                if(NotMatching == 0) { // should not reach ever
                    break;
                }
                char temp[20];
                //convert number to text
                sprintf(temp, "%i", 1 - NotMatching - 1);
                /// writing number of characters like -1
                for(int k = 0; k < strlen(temp); k++){
                    outbuf[pointerOut] = temp[k];
                    pointerOut++;  //write the number of not matching
                }
                /// writing the characters
                for (int k = 0; k < NotMatching; k++) {
                    outbuf[pointerOut] = buffer[pointerIn];
                    pointerOut++; //write the not matching chars
                    pointerIn++;
                }
                NotMatching = 0;
            }
            if(buffer[pointerIn] == buffer[pointerIn + 1]){ //if the next char is matching
                for (int j = pointerIn; j < insize; j++) {
                    if(j > insize){
                        break;
                    }
                    if(buffer[j] == buffer[j + 1]){
                        Matching++; //searching for matching
                    }  else {
                        Matching++;
                        break;
                    }
                }
                if(Matching == 0) { // should not reach ever
                    break;
                }
                char temp[20];
                sprintf(temp, "%i", Matching); //convert number to text
                for(int k = 0; k < strlen(temp); k++){
                    outbuf[pointerOut] = temp[k];
                    pointerOut++; //write the number of matching
                } 
                outbuf[pointerOut] = buffer[pointerIn]; //write the matching char
                pointerOut = pointerOut + 1; /// +1 for the char thats left

                pointerIn = pointerIn + Matching;
                Matching = 0;
            }
        }
        outbuf[pointerOut] = '\0'; //end of the buffer

        //LZ77////////////////////////////
        // printf("LZ77 \n");
        // char text[BUFSIZE*3];  // Example input string
        // memcpy(text,buffer,BUFSIZE*3);
        // for (int i = 0; i < BUFSIZE*3; i++) {
        //     outbuf[i] = '\0'; //clear the buffer
        // }
        // int text_size = strlen(text);
        // char dict[MAX_DICT_SIZE];
        // int dict_size = 0;
        // char lookahead[MAX_LOOKAHEAD];
        // int lookahead_size = 0;
        // pointerOut = 0;
        // for (int i = 0; i < text_size; i++) {
        //     // Move the lookahead into the dictionary
        //     if (lookahead_size > 0) {
        //     memcpy(dict + dict_size, lookahead, lookahead_size);
        //     dict_size += lookahead_size;
        //     dict_size = dict_size > MAX_DICT_SIZE ? MAX_DICT_SIZE : dict_size;
        //     }

        //     // Refill the lookahead buffer
        //     lookahead_size = text_size - i;
        //     lookahead_size = lookahead_size > MAX_LOOKAHEAD ? MAX_LOOKAHEAD : lookahead_size;
        //     memcpy(lookahead, text + i, lookahead_size);

        //     // Find the best match in the dictionary
        //     int length = find_match(dict, dict_size, lookahead, lookahead_size);

        //     // Emit the offset and length of the match
        //     int offset = dict_size - length;

        //     ///write to buffer 
        //     char temp[MAX_DICT_SIZE + 20];
        //     sprintf(temp, "(%d, %d, %s)\n", offset, length, dict); //convert number to text
        //     for(int k = 0; k < strlen(temp); k++){
        //         outbuf[pointerOut] = temp[k];
        //         pointerOut++; //write the number of matching
        //     } 
        //     //printf("(%d, %d)\n", offset, length);

        //     // Consume the matched characters
        //     i += length - 1;
        // }
        ////////////////
        if (pointerOut > 0){ // if there is something to write
            fwrite(outbuf,sizeof(char),pointerOut,outfile);
        }

        ///////////////Cleanup/////////////////////
        NotMatching = 0;
        Matching = 0;
        pointerIn = 0;
        pointerOut = 0;
    }
}


void decompress(FILE* infile,FILE* outfile){
    char buffer[BUFSIZE];
    memset(buffer,0,BUFSIZE);

    int pointerIn = 0;  // position of input buffer
    int pointerOut = 0; // position of output buffer
    int numToSkip = 0;  //number of chars with negative number to skip
    int numToWrite = 0; //number of chars to repeat with positive number
    int notFinishedNotMatching = 0; //if the end of the buffer is reached while reading number for not matching chars
    int notFinishedWritingNotMatching = 0; //if the end of the buffer is reached while writing not matching chars
    int notFinishedMatching = 0; //if the end of the buffer is reached while reading number for matching chars
    int x = 0;

    char outbuf[BUFSIZE*4];
    while(1){
        int insize = fread(buffer,sizeof(char),BUFSIZE,infile);
        if (insize == 0){
            if (feof(infile)){
                // end of file
                break;
            }
            assert(!ferror(infile));
        }
        char temp[500];
        /// Long run compress
        for (int i = 0; i < BUFSIZE; i++)
        {
            if(pointerIn + 1 > insize){
                break;
            }
            if(notFinishedWritingNotMatching){  //if writing was not done because of buffer ending. Write rest of them from new buffer.
                for (int l = 0; l < numToSkip; l++)
                {
                    outbuf[pointerOut] = buffer[pointerIn]; //write the not matching chars
                    pointerOut++;
                    pointerIn++;
                }
                notFinishedWritingNotMatching = 0;
            }
            /////look for number of not matching
            if(buffer[pointerIn] == '-' || notFinishedNotMatching){
                if(pointerIn + 1 > insize){ //if the end of the buffer is reached
                    notFinishedNotMatching = 1;
                    break;
                }
                pointerIn++;
                if(!notFinishedNotMatching){
                    x = 0; //if buffer was finished set temp for number to zero
                } else {
                    notFinishedNotMatching = 0;  //if buffer was not finished continue with temp
                }
                
                while (buffer[pointerIn] >= '0' && buffer[pointerIn] <= '9')
                {
                    temp[x] = buffer[pointerIn]; //read the number of not matching
                    if(pointerIn + 1 > insize){ //if the end of the buffer is reached in middle of reading number
                        notFinishedNotMatching = 1;
                        //printf("Not finished not matching %s. ", temp);
                        break;
                    }
                    pointerIn++;
                    x++;
                }
                if (notFinishedNotMatching){
                    break;
                }
                
                temp[x] = '\0';
                numToSkip = 0;
                sscanf(temp, "%d", &numToSkip); //convert the number to int
                for (int l = 0; l < numToSkip; l++)
                {
                    outbuf[pointerOut] = buffer[pointerIn]; //write the not matching chars
                    pointerOut++;
                    pointerIn++;
                    if(pointerIn + 1 > insize){ //if the end of the buffer is reached in middle of writing not matching chars
                        notFinishedWritingNotMatching = 1;
                        numToSkip -= l + 1; // subtract written characters from number of chars to write
                        break;
                    }
                }
            }

            if(notFinishedWritingNotMatching || notFinishedNotMatching){
                break;
            }

            /////look for number of matching
            if((buffer[pointerIn] >= '0' && buffer[pointerIn] <= '9') || notFinishedMatching){
                if(!notFinishedMatching){ //if buffer was finished set temp for number to zero
                    x = 0;
                } else {
                    notFinishedMatching = 0; //if buffer was not finished continue with temp
                }
                while (buffer[pointerIn] >= '0' && buffer[pointerIn] <= '9')
                {
                    temp[x] = buffer[pointerIn];
                    if(pointerIn + 1 > insize){ //if the end of the buffer is reached in middle of reading number
                        notFinishedMatching = 1;
                        //printf("Not finished matching %s. ", temp);
                        break;
                    }
                    pointerIn++;
                    x++;
                }
                if (notFinishedMatching){
                    break;
                }
                temp[x] = '\0';
                numToWrite = 0;
                sscanf(temp, "%d", &numToWrite); //convert the number to int
                for (int l = 0; l < numToWrite; l++)
                {   
                    outbuf[pointerOut] = buffer[pointerIn]; //write the matching chars repeatedly
                    pointerOut++;
                }
                pointerIn++;
            }
        }

        if (pointerOut > 0){
            int outsize = pointerOut;
            fwrite(outbuf,sizeof(char),outsize,outfile);
        }

        pointerIn = 0;
        pointerOut = 0;
        for (int i = 0; i < BUFSIZE*4; i++) 
        {
            outbuf[i] = '\0'; //clear the buffer
        }
    }
}