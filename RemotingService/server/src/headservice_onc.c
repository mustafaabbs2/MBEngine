#include <stdio.h>
#include <rpc/rpc.h>
#include "array_xdr.h"

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
    register SVCXPRT *transp;

    pmap_unset(PROG_NUM, PROG_VERS);
    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL) {
        fprintf(stderr, "%s: cannot create udp service.\n", argv[0]);
        exit(1);
    }
    if (!svc_register(transp, PROG_NUM, PROG_VERS, send_array_1, IPPROTO_UDP)) {
        fprintf(stderr, "%s: unable to register (PROG_NUM, PROG_VERS, udp).\n", argv[0]);
        exit(1);
    }

    svc_run();
    fprintf(stderr, "%s: svc_run returned\n", argv[0]);
    exit(1);
}
