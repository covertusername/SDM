/* small demonstration machine - disassembler */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    int imagefd = open("image.sdm", O_RDONLY);
    union {
        int16_t word;
        char bytesInWord[2];
    } instruction;
    char temp = 0;
    int addr = 0;

    while (read(imagefd, &instruction.bytesInWord[1], 1) > 0){
        read(imagefd, &instruction.bytesInWord[0], 1);
        temp = instruction.bytesInWord[1] & 0xF0;
        switch (temp){
            case '\x00':
                printf("%x\tnop\n", addr);
                break;
            case '\x10':
                printf("%x\tadda 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\x20':
                printf("%x\taddm 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\x30':
                printf("%x\tsuba 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\x40':
                printf("%x\tsubm 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\x50':
                printf("%x\tcla\n", addr);
                break;
            case '\x60':
                printf("%x\tclm 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\x70':
                printf("%x\tjmp 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\x80':
                printf("%x\tjin 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\x90':
                printf("%x\tout 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\xA0':
                printf("%x\tin 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\xB0':
                printf("%x\tmova 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\xC0':
                printf("%x\tmovm 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\xD0':
                printf("%x\tstoa 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\xE0':
                printf("%x\teq 0x%x\n", addr, instruction.word & 0x0FFF);
                break;
            case '\xF0':
                printf("%x\thlt\n", addr);
                break;
            default:
                fprintf(stderr, "%s: opcode value out of range\n", argv[0]);
                exit(1);
                break;
        }
        addr++;
        addr++;
    }
    return 0;
}
