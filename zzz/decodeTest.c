
#include <stdio.h>

#define START_LOC 166
#define NUM_OF_BYTE 25

void printBits(unsigned char data);

int main(int argc, char **argv) {
    unsigned char data; char *ptr = &data;
    unsigned char infor = 0;

    FILE *fptr;
    fptr = fopen(argv[1], "r");

    if(fptr != NULL) {
        fseek(fptr, START_LOC, SEEK_SET);
        for(int j = 0; j < NUM_OF_BYTE; j++) {
            for(int i = 0; i < 8; i++) {
                fread(ptr, sizeof(char), 1, fptr);
                // printBits(*ptr);
                infor = infor << 1;
                infor = infor | (*ptr & 1);
            }
            printf("\nInfo: 0x%X : %c <-- Decoded from LSBs\n\n", infor, infor);
        }

    } else {
        printf("Error\n");
    }

    return 0;
}

void printBits(unsigned char data) {
    for(int i = 0; i < 8; i++) {
        (data & (1 << (7 - i))) ? printf("1") : printf("0");
    }
    printf(" <---- 0x%X\n", data);
}
