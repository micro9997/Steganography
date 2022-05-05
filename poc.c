
#include <stdio.h>
#include <string.h>

void printBits(unsigned char data);

int main(int argc, char **argv) {
    unsigned char data; char *ptr = &data;
    unsigned char infor = 0;

    FILE *fptr;
    fptr = fopen(argv[1], "r");

    if(fptr != NULL) {
        fseek(fptr, 54, SEEK_SET);
        for(int i = 0; i < 8; i++) {
            fread(ptr, sizeof(char), 1, fptr);
            printBits(*ptr);
            infor = infor << 1;
            infor = infor | (*ptr & 1);
        }
        printf("\nInfo: 0x%X : %c <-- Decoded from LSBs\n", infor, infor);

    } else {
        printf("Error\n");
    }

    return 0;
}

void printBits(unsigned char data) {
    for(int i = 0; i < 8; i++) {
        (data & (1 << (7 - i))) ? printf("1") : printf("0");
    }
    printf(" <-- 0x%X\n", data);
}

// fread(str, sizeof(char), 1, encInfo->fptr_stego_image);
// *str = i;
// printf("Bytes: %d\n", *str);
// unsigned short int mask = 1 << i;
// *str = *str << i;
// x = x & ~mask;
// x = x | *str;

// char ch = 'B';
// printf("%d\n", (ch & 1));

// char ch1[] = "Hello";
// char ch2[] = "hello";

// printf("%d\n", strcmp(ch1, ch2));

// FILE *fPtr;
// fPtr = fopen("hello.txt", "r");
// fseek(fPtr, 0, SEEK_SET);
// fseek(fPtr, 0, SEEK_END);
// printf("%ld\n", ftell(fPtr));

// check_operation_type                                         (Understood)
// Read and validate Encode args from argv                      (Understood)
// Perform the encoding
    // Get File pointers for i/p and o/p files                  (Understood)
    // check capacity                                           (Understood)
        // Get image size                                       (Understood)
        // Get file size                                        (Understood)
    // Copy bmp image header                                    (Understood)
    // Store Magic String                                       (Understood)
        // Encode function, which does the real encoding        (Understood)
            // Encode a byte into LSB of image data array       (Understood)
    // strcpy                                                   (Understood)
    // Encode secret file extenstion siz
        // Encode size to lsb
    // Encode secret file extenstion
        // Encode function, which does the real encoding
            // Encode a byte into LSB of image data array
    // Encode secret file size
        // Encode size to lsb
    // Encode secret file data
        // Encode a byte into LSB of image data array
    // Copy remaining image bytes from src to stego image after encoding



// printf("choosen encodeing process\n");
//     printf("SUCESS : Read and validate of encode args\n");
//     printf("Encodeing process started ......\n");
//         printf("SUCESS: Enodeing process\n");
//         printf("Falies: Encoding process\n");
//     printf("Failes : Read and validate of encode args\n");
// printf("choosen decodeing process\n");
// printf("Ivalid Input \n please pass Encode : ./a.out -e beautiful.bmp secret.txt stego.bmp\n Decode : .a/out -d stego.bmp decode.txt\n");


// printf("SUCESS: OPEN FILES\n");
//     printf ("SUCCESS: Check capacity\n");
//         printf("SUCCESS: Copy bmp header\n");
//             printf("SUCCESS: Magic string encodeing\n");
//                 printf( "SUCESS : SECRET FILE EXTENSION SIZE\n");
//                     printf("SUCESS: SECRETE FILE EXTENSION\n");
//                         printf( "SUCCESS: ENCODE SECRETE FILE SIZE \n");
//                             printf("SUCCESS: ENCODING SECRETE DATA\n" );
//                                 printf("SUCCESS: CPOY BMP REMAING DATA\n");

//                                 printf("FAILES: CPOY BMP REMAING DATA\n");
//                             printf("FAILES: ENCODING SECRETE DATA\n");
//                         printf("FAILES: ENCODE SECRETE FILE SIZE \n");
//                     printf("FAILES : SECRETE FILE EXTENSION\n");
//                 printf("FALIES: SECRET_FILE EXTENSION SIZE\n");
//             printf("FAILES: Magic string encodeing\n");
//         printf ("FAILES: Copy bmp header \n");
//     printf ("FAILES: Check capacity\n");
// printf("FAILES: OPEN FILES\n");
