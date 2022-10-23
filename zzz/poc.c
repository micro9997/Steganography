
#include <stdio.h>
#include <string.h>

void printBits(unsigned char data);

int main(int argc, char **argv) {
    unsigned char data[] = {0b00110011, 0b00110011, 0b00110011, 0b00110011,
                            0b00110011, 0b00110011, 0b00110011, 0b00110011};

    char sec = '#';
    // char sec = 0b11111111;

    for(int i = 0; i < 8; i++) {
        unsigned short int mask = 1 << (7 - i);
        data[i] = data[i] & 0b11111110;
        data[i] = data[i] | ((sec & mask) >> (7 - i));
    }

    for(int i = 0; i < 8; i++) {
        printBits(data[i]);
    }

    return 0;
}

void printBits(unsigned char data) {
    for(int i = 0; i < 8; i++) {
        (data & (1 << (7 - i))) ? printf("1") : printf("0");
    }
    printf("\n");
}

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
    // Encode secret file extenstion size
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
