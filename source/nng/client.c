#include "common/common.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <nng/nng.h>
#include <nng/protocol/reqrep0/req.h>
#include "nng/supplemental/util/platform.h"

void communicate(nng_socket* socket, struct Arguments* args) {
	void* buffer = malloc(args->size);
	size_t  sz = (size_t) args->size;

	for (; args->count > 0; --args->count) {
		// Send data to the server (flags = 0)
		if (nng_send(*socket, buffer, sz, 0) != 0) {
			printf("nng_send");
		}

		if (nng_recv(*socket, buffer, &(sz), 0) != 0) {
			printf("nng_recv");
		}

	}
	free(buffer);
}

void cleanup(nng_socket* socket) {
	nng_close(*socket);
}

nng_socket* create_socket() {
	// The socket we will create.
	nng_socket* socket =  (nng_socket*)malloc(sizeof(nng_socket));
	int rv;

	if ((rv = nng_req0_open(socket)) != 0) {
		printf("nng_socket");
	}

	rv = NNG_ECONNREFUSED;
	while(rv == NNG_ECONNREFUSED) {
		if ((rv = nng_dial(*socket, "ipc:///tmp/nng_ipc", NULL, 0)) != 0) {
			printf("nng_dial");
		}
		nng_msleep(50);
	}

	return socket;
}

int main(int argc, char* argv[]) {
	nng_socket *socket;

	// For parsing command-line arguments
	struct Arguments args;

	parse_arguments(&args, argc, argv);

	socket = create_socket();

	communicate(socket, &args);

	cleanup(socket);

	return EXIT_SUCCESS;
}
