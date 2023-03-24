#include<stdio.h>


unsigned int getf_size(const char* filename){
    int c = 0;
    FILE* file = fopen(filename, "r");
    while(fgetc(file) != EOF){
        c++;
    }
    fclose(file);
    return c;
}

int main(int argc, char* argv[]){
    printf("%d\n",getf_size(argv[1]));
}