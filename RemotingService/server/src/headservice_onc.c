#include <stdio.h>
#include <rpc/rpc.h>
#include "array_xdr.h"

#define PROG_NUM 100001   // Define program number
#define PROG_VERS 1       // Define program version

//this function is probably automatically invoked?
int *send_array_1_svc(array *arr, struct svc_req *rqstp) {
    static int result;
    result = arr->arr_len; // Just return the length of the array received
    return (&result);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <progname>\n", argv[0]);
        exit(1);
    }

    // Register the RPC server
    register SVCXPRT *transp;
    pmap_unset(PROG_NUM, PROG_VERS);
    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL) {
        fprintf(stderr, "%s: cannot create UDP service.\n", argv[0]);
        exit(1);
    }
    if (!svc_register(transp, PROG_NUM, PROG_VERS, send_array_1, IPPROTO_UDP)) {
        fprintf(stderr, "%s: unable to register (PROG_NUM, PROG_VERS, UDP).\n", argv[0]);
        exit(1);
    }

    // Start the RPC server
    svc_run();
    fprintf(stderr, "%s: svc_run returned\n", argv[0]);
    exit(1);  // Exit with error status if svc_run returns (should not happen)
}