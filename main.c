/* small demonstration machine - simulator */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

char *memory;
int memoryImage = 0;
int16_t lIByte = 0;
int16_t rIByte = 1;
union {
    int16_t word;
    char bytesInWord[2];
} instruction;
char temp;
char acc;
int16_t arg;
int running = 1;

char out(int16_t arg);
void in(int16_t arg, char acc);

int main(int argc, char **argv){
    memoryImage = open(argv[1], 0);
    if (memoryImage == -1){
        perror(argv[1]);
        exit(1);
    }
    memory = calloc(1, 4096);
    read(memoryImage, memory, 4096);
    while (running){
        instruction.bytesInWord[1] = memory[lIByte];
        instruction.bytesInWord[0] = memory[rIByte];
        temp = instruction.bytesInWord[1] & 0xF0;
        arg = instruction.word & 0x0FFF;
        switch (temp){
            case '\x00':
                break;
            case '\x10':
                acc = acc + memory[arg];
                break;
            case '\x20':
                memory[arg] = acc + memory[arg];
                break;
            case '\x30':
                acc = acc - memory[arg];
                break;
            case '\x40':
                memory[arg] = memory[arg] - acc;
                break;
            case '\x50':
                acc = 0;
                break;
            case '\x60':
                memory[arg] = 0;
                break;
            case '\x70':
                rIByte = arg;
                lIByte = arg + 1;
                break;
            case '\x80':
                if (acc > 127){
                    rIByte = arg;
                    lIByte = arg + 1;
                }
                break;
            case '\x90':
                acc = out(arg);
                break;
            case '\xA0':
                in(arg, acc);
                break;
            case '\xB0':
                acc = memory[arg];
                break;
            case '\xC0':
                memory[arg] = acc;
                break;
            case '\xD0':
                acc = (char)arg;
                break;
            case '\xE0':
                if (acc == memory[arg]){
                    acc = 255;
                }
                break;
            case '\xF0':
                running = 0;
                break;
            default:
                fprintf(stderr,
                    "%s: fatal: invalid instruction (this should not happen)\n",
                    argv[0]);
            break;
        }
        rIByte++;
        rIByte++;
        lIByte++;
        lIByte++;
    }
    free(memory);
    return 0;
}

char out(int16_t arg){
    if (arg == 0x0){
        return getchar();
    }
    return 0;
}

void in(int16_t arg, char acc){
    if (arg == 0x0){
        putchar(acc);
    }
}
