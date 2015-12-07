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

int main(int argc, char **argv){
    memoryImage = open(argv[1], 0);
    if (memoryImage == -1){
        perror(argv[1]);
        exit(1);
    }
    memory = calloc(1, 4096);
    read(memoryImage, memory, 4096);

    free(memory)
    return 0;
}
