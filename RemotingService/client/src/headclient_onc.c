#include <stdio.h>
#include <rpc/rpc.h>
// #include "array_xdr.h"
// #include "..\..\protocol\protos\headprotocol_onc.x"

#define PROG_NUM 100001   // Define program number
#define PROG_VERS 1       // Define program version

struct array {
    float arr_val[1000000];
};

int main(int argc, char **argv) {
    CLIENT *cl;
    array arr;
    int *result;

    if (argc != 4) {
        fprintf(stderr, "usage: %s hostname int1 int2 ...\n", argv[0]);
        exit(1);
    }

    cl = clnt_create(argv[1], PROG_NUM, PROG_VERS, "udp");
    if (cl == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    // Prepare the array to send
    arr.arr_len = argc - 2;
    arr.arr_val = (int *)malloc((argc - 2) * sizeof(int));
    for (int i = 0; i < argc - 2; i++) {
        arr.arr_val[i] = atoi(argv[i + 2]);
    }

    // Call the RPC function
    result = send_array_1(&arr, cl);
    if (result == NULL) {
        clnt_perror(cl, argv[1]);
        exit(1);
    }

    // Print the result received from the server
    printf("Received array length from server: %d\n", *result);

    clnt_destroy(cl);
    exit(0);
}
