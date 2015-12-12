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
    int16_t *instruction = calloc(1, sizeof(int16_t));
    int16_t temp = 0;

    while (read(imagefd, instruction, 2) > 0){
        temp = *instruction & 0xF000;
        switch (temp){
            case 0x0000:
                printf("nop\n");
                break;
            case 0x1000:
                printf("adda 0x%x\n", *instruction & 0x0FFF);
                break;
            case 0x2000:
                printf("addm 0x%x\n", *instruction & 0x0FFF);
                break;
            case 0x3000:
                printf("suba 0x%x\n", *instruction & 0x0FFF);
                break;
            case 0x4000:
                printf("subm 0x%x\n", *instruction & 0x0FFF);
                break;
            case 0x5000:
                printf("cla\n");
                break;
            case 0x6000:
                printf("clm 0x%x\n", *instruction & 0x0FFF);
                break;
            case 0x7000:
                printf("jmp 0x%x\n", *instruction & 0x0FFF);
                break;
            case 0x8000:
                printf("jin 0x%x\n", *instruction & 0x0FFF);
                break;
            case 0x9000:
                printf("out 0x%x\n", *instruction & 0x0FFF);
                break;
            case 0xA000:
                printf("in 0x%x\n", *instruction & 0x0FFF);
        }
    }
}
