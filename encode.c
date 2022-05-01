
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "types.h"
#include "encode.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo) {
    if (strcmp(strstr(argv[2], ".bmp"), ".bmp") == 0) {
        encInfo->src_image_fname = argv[2] ;
    } else {
        return e_failure;
    }
    if(strcmp(strstr(argv[3],".txt"),".txt") == 0) {
        encInfo->secret_fname = argv[3];
    } else {
        return e_failure;
    }
    if (argv[4] != NULL ) {
        encInfo->stego_image_fname = argv[4];
    } else {
        encInfo->stego_image_fname = "stego.bmp";
    }
    return e_success;
}

uint get_image_size_for_bmp(FILE *fptr_image) {
    uint width, heght;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread (&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&heght, sizeof(int), 1, fptr_image);
    printf("height = %u\n", heght);

    // Return image capacity
    return width * heght * 3;
}

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: _success or _failure, on file errors
 */

Status open_files (EncodeInfo *encInfo) {
    // Sc Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if(encInfo->fptr_src_image == NULL) {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret == fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if(encInfo->fptr_secret == NULL) {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);
    
        return e_failure;
    }
    
    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "W");
    // Do Error handling
    if(encInfo->fptr_stego_image == NULL) {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);
        return e_failure;
    }
    // No failure return e_success
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo) {
    encInfo->image_capacity = get_image_size_for_bmp(encInfo-> fptr_src_image);
    encInfo->size_secret_file = get_file_size(encInfo-> fptr_secret);

    printf("secrete file size - %lu \n", encInfo->size_secret_file);
    printf("BMP file size - %u \n", encInfo->image_capacity);

    if(encInfo->image_capacity > 54 + 16 + 32 + 32 + 32 + (8 * encInfo->size_secret_file));
    return e_success;
}

uint get_file_size(FILE *fptr) {
    fseek(fptr, 0, SEEK_SET);
    fseek(fptr, 0, SEEK_END);
    return ftell(fptr);
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image) {
    char str[54];
    fseek(fptr_src_image, 0, SEEK_SET);
    fread(str, sizeof(char), 54, fptr_src_image);
    fwrite(str, sizeof(char), 54, fptr_dest_image);
    return e_success;
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo) {
    encode_data_to_image(magic_string, strlen(magic_string), encInfo->fptr_src_image, encInfo->fptr_stego_image, encInfo);
    return e_success;
}

// Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image);
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image, EncodeInfo * encInfo) {
    int i;
    for(i = 0; i < size; i++) {
        fread(encInfo->image_data,sizeof(char), 8, encInfo->fptr_src_image);
        encode_byte_to_lsb(data[i], encInfo->image_data);
        fwrite(encInfo->image_data, sizeof(char), 8, encInfo->fptr_stego_image);
    }
    return e_success;
}

Status encode_byte_to_1sb(char data, char *image_buffer) {
    unsigned int mask = 1 << 7;
    int i;
    for(i= 0; i < 8; i++) {
        image_buffer[i] = ((image_buffer[i] & 0xFE) | (data & mask) >> (7 - i));
    }    
}

Status encode_size_to_lsb(char *image_buffer, int size) {
    unsigned int mask = 1 << 31;
    int i;
    for(i = 0; i < 32; i++) {
        image_buffer[i] = ((image_buffer[i] & 0xFE) | (size & mask) >> (31 - i));
        mask = mask - 1;
    }
}

Status encode_secret_file_extn_size(int size,FILE *fptr_src_image, FILE *fptr_stego_image) {
    char str[32];
    fread(str, 32, 1, fptr_src_image);
    encode_size_to_lsb(str,size);
    fwrite(str, 32, 1, fptr_stego_image);
    return e_success;
}

// Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo);
Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo) {
    encode_data_to_image(file_extn, strlen(file_extn), encInfo->fptr_src_image, encInfo->fptr_stego_image, encInfo);
    return e_success;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo) {
    char str[32];
    fread(str, 32, 1, encInfo->fptr_src_image);
    encode_size_to_lsb(str, encInfo->size_secret_file);
    fwrite(str, 32, 1, encInfo->fptr_stego_image);
    return e_success;
}

Status encode_secret_file_data(EncodeInfo *encInfo) {
    fseek(encInfo->fptr_secret, 0, SEEK_SET);
    int i;
    char ch;
    for (i = 0; i < encInfo->size_secret_file; i++) {
        fread(encInfo->image_data, 8, 1, encInfo->fptr_src_image);
        fread(&ch, 1, 1, encInfo->fptr_secret);
        encode_byte_to_lsb(ch, encInfo->image_data);
        fwrite(encInfo->image_data, 8, 1, encInfo->fptr_stego_image);
    }
    return e_success;
}

Status copy_remaining_ing_data(FILE *fptr_src, FILE *fptr_dest) {
    printf("in function copy");
    char ch;
    while(fread(&ch, 1, 1, fptr_src) > 0) {
        fwrite(&ch, 1, 1, fptr_dest);
    }
    return e_success;
}

Status do_encoding(EncodeInfo *encInfo) {
    if(open_files(encInfo) == e_success) {
        printf("SUCESS: OPEN FILES\n");
        if (check_capacity(encInfo) == e_success) {
            printf ("SUCCESS: Check capacity\n");
            if (copy_bmp_header (encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success) {
                printf("SUCCESS: Copy bmp header\n");
                if(encode_magic_string (MAGIC_STRING, encInfo) == e_success) {
                    printf("SUCCESS: Magic string encodeing\n");
                    strcpy(encInfo->extn_secret_file, strstr(encInfo->secret_fname, "."));
                    if(encode_secret_file_extn_size(strlen(encInfo->extn_secret_file), encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success) {
                        printf( "SUCESS : SECRET FILE EXTENSION SIZE\n");
                        if(encode_secret_file_extn(encInfo->extn_secret_file, encInfo) == e_success) {
                            printf("SUCESS: SECRETE FILE EXTENSION\n");
                            if(encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_success) {
                                printf( "SUCCESS: ENCODE SECRETE FILE SIZE \n");
                                if(encode_secret_file_data(encInfo) == e_success) {
                                    printf("SUCCESS: ENCODING SECRETE DATA\n" );
                                    if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success) {
                                        printf ("SUCCESS: CPOY BMP REMAING DATA\n");

                                    } else {
                                        printf("FAILES: CPOY BMP REMAING DATA\n");

                                        return e_failure;
                                    }

                                } else {
                                    printf("FAILES: ENCODING SECRETE DATA\n");

                                    return e_failure;
                                }

                            } else {
                                printf("FAILES: ENCODE SECRETE FILE SIZE \n");

                                return e_failure;
                            }

                        } else {
                            printf("FAILES : SECRETE FILE EXTENSION\n");

                            return e_failure;
                        }

                    } else {
                        printf("FALIES: SECRET_FILE EXTENSION SIZE\n");

                        return e_failure;
                    }

                } else {
                    printf("FAILES: Magic string encodeing\n");

                    return e_success;
                }

            } else {
                printf ("FAILES: Copy bmp header \n");

                return e_failure;
            }

        } else {
            printf ("FAILES: Check capacity\n");

            return e_failure;
        }

    } else {
        printf("FAILES: OPEN FILES\n");

        return e_failure;
    }

    return e_success;
}
