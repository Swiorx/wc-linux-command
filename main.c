#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

void getCounts(FILE *fp, int *lines, int *words, int *bytes) {
    char buffer[4096];
    int inWord = 0;
    size_t bytesRead = 0;

    *bytes = 0;
    *words = 0;
    *lines = 0;
    

    while((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0){
        *bytes += bytesRead;
        for(size_t i = 0; i < bytesRead; i++){
            char ch = buffer[i];
            if(isspace(ch)){
                inWord = 0;
            } else if(!inWord){
                inWord = 1;
                (*words)++;
            }
            if(ch == '\n'){
                (*lines)++;
            }
        }
    }
}


int main(int argc, char *argv[]){
    int l = 0, w = 0, b = 0;

    

    int i = 1;
    int show_lines = 0, show_words = 0, show_bytes = 0, option = 0;
    
    while (i < argc && argv[i][0] == '-') {

        if (strcmp(argv[i], "-h") == 0) {
            printf("Usage: wc <filename>\n");
            printf("Optional flags:\n");
            printf("  -c : show byte count\n");
            printf("  -w : show word count\n");
            printf("  -l : show line count\n");
            return 0;
        }

        for (int j = 1; argv[i][j] != '\0'; j++) {

            switch (argv[i][j]) {
                case 'c':
                    show_bytes = 1;
                    option = 1;
                    break;
                case 'w':
                    show_words = 1;
                    option = 1;
                    break;
                case 'l':
                    show_lines = 1;
                    option = 1;
                    break;
                default:
                    fprintf(stderr, "Invalid Option '-%c'.\n", argv[i][j]);
                    printf("./wc -h for help\n");
                    return 1;
            }
        }
        i++;
    }

    FILE *fp;
    char *fileName = "";

    if (i >= argc) {
        fp = stdin;
        fileName = "";
    } else{
        fileName = argv[i];
        fp = fopen(fileName, "r");
        if(!fp){
            perror(fileName);
            return 1;
        }
    }

    getCounts(fp, &l, &w, &b);

    if (ferror(fp)) {
        perror(argv[0]);
        if (fp != stdin) {
            fclose(fp);
        }
        return 1; 
    }

    if(option){
        if(show_lines) printf("%d ",l);
        if(show_words) printf("%d ",w);
        if(show_bytes) printf("%d ",b);
    } else {
        printf("%d %d %d ",l,w,b);
    }

    if (fp != stdin) {
        printf("%s\n", fileName);
        fclose(fp);
    } else {
        printf("\n");
    }

    return 0;
}