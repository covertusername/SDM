/* small demonstration machine - assembler */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    FILE *asmsource;
    char *line = NULL;
    size_t len = 0;

    asmsource = fopen(argv[1], "r");
    if (stream == NULL){
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
            argv[1]);
        exit(1);
    }
    while (getline(&line, &len, asmsource) != -1) {
        
    }
}
