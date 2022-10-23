
#ifndef ENCODE_H
#define ENCODE_H

#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _EncodeInfo {
    /* Source Image info */
    char *src_image_fname;
    FILE *fptr_src_image;
    uint image_capacity;
    uint bits_per_pixel;
    char image_data[MAX_IMAGE_BUF_SIZE];

    /* Secret File Info */
    char *secret_fname;
    FILE *fptr_secret;
    long extn_size_secret_file;
    char extn_secret_file[MAX_FILE_SUFFIX];
    char secret_data[MAX_SECRET_BUF_SIZE];
    long size_secret_file;

    /* Stego Image Info */
    char *stego_image_fname;
    FILE *fptr_stego_image;

} EncodeInfo;

/* Encoding function prototype */

/* 01. Check operation type */
OperationType check_operation_type(char *argv[]);

/* 02. Read and validate Encode args from argv */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo); // Done // Understand

/* 03. Perform the encoding */
Status do_encoding(EncodeInfo *encInfo); // Done // Understood -

/* 04. Get File pointers for i/p and o/p files */
Status open_files(EncodeInfo *encInfo); // Done // Understand

/* 05. check capacity */
Status check_capacity(EncodeInfo *encInfo); // Done // Understood -

/* 06. Get image size */
uint get_image_size_for_bmp(FILE *fptr_image); // Done // Understand

/* 07. Get file size */
uint get_file_size(FILE *fptr); // Done // Understood

/* 08. Copy bmp image header */
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image); // Done // Understood

/* 09. Store Magic String */
// Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo);
Status encode_magic_string(char *magic_string, EncodeInfo *encInfo); // Done // Understood

/* 10. Encode secret file extenstion siz */
Status encode_secret_file_extn_size(int size, FILE *fptr_src_image, FILE *fptr_stego_image); // Done // Understood

/* 11. Encode secret file extenstion */
Status encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo); // Done // Understood

/* 12. Encode secret file size */
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo); // Done // Understood

/* 13. Encode secret file data */
Status encode_secret_file_data(EncodeInfo *encInfo); // Done // Understood -

/* 14. Encode function, which does the real encoding */
// Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image);
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image, EncodeInfo *encInfo); // Done // Understood

/* 15. Encode a byte into LSB of image data array */
Status encode_byte_to_lsb(char data, char *image_buffer); // Done // Understood // Impo

/* 16. Encode size to lsb */
Status encode_size_to_lsb(char *image_buffer, int size); // Done // Understood

/* 17. Copy remaining image bytes from src to stego image after encoding */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest); // Done // Understood


// Decoding

// Read and validate Encode args from argv
Status read_and_validate_decode_args(char *argv[], EncodeInfo *encInfo);

// Get File pointers for i/p and o/p files
Status open_files_for_decoding(EncodeInfo *encInfo);

// Read Magic String
Status decode_magic_string(char *magic_string, EncodeInfo *encInfo);

// Decode function, which does the real encoding
// Status decode_data_from_image(char *data, int size, FILE *fptr_stego_image);
Status decode_data_from_image(char *data, int size, EncodeInfo *encInfo);

// Decode a byte into LSB of image data array
// Status decode_byte_from_lsb(char data, char *image_buffer);
Status decode_byte_from_lsb(EncodeInfo *encInfo);

// Decode secret file extenstion size
// Status decode_secret_file_extn_size(int size, FILE *fptr_src_image, FILE *fptr_stego_image);
Status decode_secret_file_extn_size(EncodeInfo *encInfo);

// Decode secret file extenstion
Status decode_secret_file_extn(EncodeInfo *encInfo);

// Decode secret file size
Status decode_secret_file_size(EncodeInfo *encInfo);

// Decode secret file data
Status decode_secret_file_data(EncodeInfo *encInfo);

// Perform the decoding
Status do_decoding(EncodeInfo *encInfo);

#endif
