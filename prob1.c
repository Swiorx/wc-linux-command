#include <stdio.h>
#include <string.h>

void getCounts(FILE *fp, int *lines, int *words, int *bytes) {
    int ch, inWord = 0;

    *bytes = 0;
    *words = 0;
    *lines = 0;
    
    fseek(fp, 0, SEEK_END);
    *bytes = ftell(fp);
    rewind(fp);

    while((ch = fgetc(fp)) != EOF){
        if(ch == ' ' || ch == '\n' || ch == '\t'){
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


int main(int argc, char *argv[]){
    int l = 0, w = 0, b = 0;

    if (argc < 2)
    {
        printf("Usage: ./wc <flags> <file_name>\n");
        return 1;
    }

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

    if (i >= argc) {
        fprintf(stderr, "File isn't specified\n");
        printf("Usage: ./wc <flags> <file_name>\n");
        return 1;
    }
    
    char *fileName = argv[i];
    FILE *fp = fopen(fileName, "r");

    if(!fp){
        fprintf(stderr, "File name doesn't exist\n");
        return 1;
    }

    else{
        getCounts(fp, &l, &w, &b);

        if(fp && option){
            if(show_lines) printf("%d ",l);
            if(show_words) printf("%d ",w);
            if(show_bytes) printf("%d ",b);
            printf("%s\n",fileName);
            fclose(fp);
        }

        else if(fp && !option){
            printf("%d %d %d ",l,w,b);
            printf("%s\n",fileName);
            fclose(fp);
        }
    }

    return 0;
}