/* small demonstration machine - simulator */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

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
int jumped = 0;
FILE *simlog;
char protSequence = 0;
char *call;
int16_t pointer;
char *openPathname;
union {
    int16_t address;
    char bytesInAddress[2];
} sdmAddress;

char out(int16_t arg);
void in(int16_t arg, char acc);

int main(int argc, char **argv){
    memoryImage = open(argv[1], 0);
    if (memoryImage == -1){
        perror(argv[1]);
        exit(1);
    }
    simlog = fopen("sim.log", "w");
    memory = calloc(1, 4096);
    read(memoryImage, memory, 4096);
    while (running){
        instruction.bytesInWord[1] = memory[lIByte];
        instruction.bytesInWord[0] = memory[rIByte];
        temp = instruction.bytesInWord[1] & 0xF0;
        arg = instruction.word & 0x0FFF;
        fprintf(simlog, "acc: %i ip: %i instruction: ", acc, lIByte);
        switch (temp){
            case '\x00':
                fprintf(simlog, "nop\n");
                break;
            case '\x10':
                fprintf(simlog, "adda 0x%x\n", arg);
                acc = acc + memory[arg];
                break;
            case '\x20':
                fprintf(simlog, "addm 0x%x\n", arg);
                memory[arg] = acc + memory[arg];
                break;
            case '\x30':
                fprintf(simlog, "suba 0x%x\n", arg);
                acc = acc - memory[arg];
                break;
            case '\x40':
                fprintf(simlog, "subm 0x%x\n", arg);
                memory[arg] = memory[arg] - acc;
                break;
            case '\x50':
                fprintf(simlog, "cla\n");
                acc = 0;
                break;
            case '\x60':
                fprintf(simlog, "clm 0x%x\n", arg);
                memory[arg] = 0;
                break;
            case '\x70':
                fprintf(simlog, "jmp 0x%x\n", arg);
                lIByte = arg;
                rIByte = arg + 1;
                jumped = 1;
                break;
            case '\x80':
                fprintf(simlog, "jin 0x%x\n", arg);
                if (acc < 0){
                    lIByte = arg;
                    rIByte = arg + 1;
                    jumped = 1;
                }
                break;
            case '\x90':
                fprintf(simlog, "out 0x%x\n", arg);
                acc = out(arg);
                break;
            case '\xA0':
                fprintf(simlog, "in 0x%x\n", arg);
                in(arg, acc);
                break;
            case '\xB0':
                fprintf(simlog, "mova 0x%x\n", arg);
                acc = memory[arg];
                break;
            case '\xC0':
                fprintf(simlog, "movm 0x%x\n", arg);
                memory[arg] = acc;
                break;
            case '\xD0':
                fprintf(simlog, "stoa 0x%x\n", arg);
                acc = (char)arg;
                break;
            case '\xE0':
                fprintf(simlog, "eq 0x%x\n", arg);
                if (acc == memory[arg]){
                    acc = -128;
                } else {
                    acc = 0;
                }
                break;
            case '\xF0':
                fprintf(simlog, "hlt\n");
                running = 0;
                break;
            default:
                fprintf(stderr,
                    "%s: fatal: invalid instruction (this should not happen)\n",
                    argv[0]);
            break;
        }
        if (!jumped){
            rIByte++;
            rIByte++;
            lIByte++;
            lIByte++;
        }
        jumped = 0;
    }
    free(memory);
    return 0;
}

char out(int16_t arg){
    if (arg == 0x0){ // generic stdin
        return getchar();
    } else if (arg == 0x1) { // retrieve the leftmost byte of the instruction
        return lIByte;       // pointer
    } else if (arg == 0x2) { // retrieve the rightmost byte of the instruction
        return rIByte;       // pointer
    }
    return 0;
}

void in(int16_t arg, char acc){
    if (arg == 0x0) { // generic stdout
        putchar(acc);
    } else if (arg == 0x1) { // plug the rightmost 4 bits of the accumulator
        lIByte = acc & 0x0F; // into the leftmost byte of the instruction
                             // pointer
    } else if (arg == 0x2) { // plug the accumulator into the rightmost byte
        rIByte = acc;        // of the instruction pointer
    }
}
