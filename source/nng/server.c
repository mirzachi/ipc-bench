#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>

#include "common/common.h"


void communicate(nng_socket* socket, struct Arguments* args) {
	struct Benchmarks bench;
	int message;
	void* buffer = NULL;

	buffer = malloc(args->size);
	size_t  sz = (size_t) args->size;

	setup_benchmarks(&bench);

	for (message = 0; message < args->count; ++message) {
		bench.single_start = now();

		// Receive data from the client (flags = 0)
		if (nng_recv(*socket, buffer, &sz, 0) != 0) {
			printf("nng_recv");
		}

		memset(buffer, '*', args->size);

		// Send data to the client
		if (nng_send(*socket, buffer, sz, 0) != 0) {
			printf("nng_send");
		}

		benchmark(&bench);
	}

	evaluate(&bench, args);
	free(buffer);
	//nng_free(buffer, sz);
}

void cleanup(nng_socket* socket) {
	nng_close(*socket);
}

nng_socket* create_socket() {
	// The socket we will create.
	nng_socket* socket =  (nng_socket*)malloc(sizeof(nng_socket));

	if ((nng_rep0_open(socket)) != 0) {
		printf("nng_socket");
	}

	if ((nng_listen(*socket, "ipc:///tmp/nng_ipc", NULL, 0)) != 0) {
		printf("nng_listen");
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
