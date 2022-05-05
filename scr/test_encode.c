
#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"

int main(int argc, char**argv) {
    if(check_operation_type(argv) == e_encode) {
        printf("choosen encodeing process\n");
        EncodeInfo encInfo;
        if(read_and_validate_encode_args(argv, &encInfo) == e_success) {
            printf("SUCCESS: Read and validate of encode args\n");
            printf("Encodeing process started ......\n");
            if(do_encoding(&encInfo) == e_success) {
                printf("SUCCESS: Enodeing process\n");
            } else {
                printf("Falies: Encoding process\n");
                return 1;
            }
        } else {
            printf("Failes : Read and validate of encode args\n");
            return 1;
        }

    } else if(check_operation_type(argv) == e_decode) {
        printf("choosen decodeing process\n");
        EncodeInfo encInfo;
        if(read_and_validate_decode_args(argv, &encInfo) == e_success) {
            printf("SUCCESS: Read and validate of decode args\n");
            printf("Decodeing process started ......\n");
            if(do_decoding(&encInfo) == e_success) {
                printf("SUCCESS: Deodeing process\n");
            } else {
                printf("Falies: Decoding process\n");
                return 1;
            }
        } else {
            printf("Failes : Read and validate of decode args\n");
            return 1;
        }

    } else {
        // printf("Ivalid Input \n please pass Encode : ./a.out -e beautiful.bmp secret.txt stego.bmp\n Decode : .a/out -d stego.bmp decode.txt\n");
        printf("Invalid Input\n  Please pass\n    Encode: %s -e beautiful.bmp secret.txt stego.bmp\n    Decode: %s -d stego.bmp decode.txt\n", argv[0], argv[0]);

    }

    return 0;
}

OperationType check_operation_type(char *argv[]) {
    if(strcmp(argv[1], "-e") == 0) {
        return e_encode;

    } else if(strcmp(argv[1], "-d") == 0) {
        return e_decode;

    } else {
        e_unsupported;

    }
}
