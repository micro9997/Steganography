
#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"

int main(int argc, char**argv) {
    if(check_operation_type(argv) == e_encode) {
        printf("choosen encodeing process\n");
        EncodeInfo encInfo;
        if(read_and_validate_encode_args(argv, &encInfo) == e_success) {
            printf("SUCESS : Read and validate of encode args\n");
            printf("Encodeing process started ......\n");
            if(do_encoding(&encInfo) == e_success) {
                printf("SUCESS: Enodeing process\n");
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

    } else {
        printf("Ivalid Input \n please pass Encode : ./a.out -e beautiful.bmp secret.txt stego.bmp\n Decode : .a/out -d stego.bmp decode.txt\n");

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
