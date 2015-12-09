/* small demonstration machine - assembler */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv){
    FILE *asmsource;
    char *line = NULL;
    size_t len = 0;
    int outputImageFD;

    asmsource = fopen(argv[1], "r");
    if (stream == NULL){
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
            argv[1]);
        exit(1);
    }
    outputImageFD = open("image.sdm", O_WRONLY, O_CREAT);
    if (outputImageFD == -1){
        perror("cannot create output file");
        exit(2);
    }
    while (getline(&line, &len, asmsource) != -1) {
        
    }
}
