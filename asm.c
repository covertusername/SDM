/* small demonstration machine - assembler */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char **argv){
    FILE *asmsource;
    char *line = NULL;
    size_t len = 0;
    int outputImageFD;
    char *mnemonic;
    union {
        int16_t word;
        char bytesInWord[2];
    } instruction;
    char *addressString = "a";
    char delimitor[3] = {' ', '\x0A', '\0'};

    if (argv[1] == NULL){
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(4);
    }
    asmsource = fopen(argv[1], "r");
    if (asmsource == NULL){
        perror("input file error");
        exit(1);
    }
    outputImageFD = open("image.sdm", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (outputImageFD == -1){
        perror("cannot create output file");
        exit(2);
    }
    while (getline(&line, &len, asmsource) != -1) {
        mnemonic = strtok(line, delimitor);
        if (!strcmp(mnemonic, "nop")){
            instruction.word = 0;
        } else if (!strcmp(mnemonic, "adda")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0x1000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "addm")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0x2000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "suba")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0x3000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "subm")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0x4000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "cla")){
            instruction.word = 0x5000;
        } else if (!strcmp(mnemonic, "clm")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0x6000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "jmp")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0x7000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "jin")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0x8000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "out")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0x9000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "in")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0xA000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "mova")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0xB000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "movm")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0xC000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "stoa")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0xD000 + (int16_t)strtol(addressString, NULL, 0);
        } else if (!strcmp(mnemonic, "eq")){
            addressString = strtok(NULL, delimitor);
            instruction.word = 0xE000 + (int16_t)strtol(addressString, NULL, 0);
        } else {
            fprintf(stderr, "%s: invalid instruction %s, exiting\n", argv[0],
                mnemonic);
            exit(3);
        }
        write(outputImageFD, &instruction.bytesInWord[1], sizeof(char));
        write(outputImageFD, &instruction.bytesInWord[0], sizeof(char));
    }
    return 0;
}
