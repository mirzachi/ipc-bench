#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "common/common.h"

void communicate(int socketFd, struct Arguments* args) {
	struct Benchmarks bench;
	int rc;
	int message;
	void* buffer;

	buffer = malloc(args->size);
	setup_benchmarks(&bench);

	for (message = 0; message < args->count; ++message) {
		bench.single_start = now();

		// Receive data from the client (flags = 0)
		rc = nn_recv (socketFd, buffer, args->size, 0);
		if (rc < 0) {
			/*  Any error here is unexpected. */
			fprintf (stderr, "nn_recv: %s\n", nn_strerror (nn_errno ()));
			break;
		}

		memset(buffer, '*', args->size);

		// Send data to the client
		rc = nn_send(socketFd, buffer, args->size, 0);

		if (rc < 0) {
			/*  There are several legitimate reasons this can fail.
					We note them for debugging purposes, but then ignore
					otherwise.  If the socket is closed or failing, we will
					notice in recv above, and exit then. */
			fprintf (stderr, "nn_send: %s (ignoring)\n",
							 nn_strerror (nn_errno ()));
		}

		benchmark(&bench);
	}

	evaluate(&bench, args);
	free(buffer);
}

void cleanup(int socketFd) {
	nn_close(socketFd);
}

int create_socket() {
	// The socket we will create.
	int socketFd;
	const char* address;

	/*  Create the socket. */
	socketFd = nn_socket (AF_SP, NN_REP);
	if (socketFd < 0) {
		fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
		return (-1);
	}

	address = "ipc:///tmp/nanomsg_ipc";

	if (nn_bind(socketFd, address) < 0) {
		fprintf (stderr, "nn_connect: %s\n", nn_strerror (nn_errno ()));
		nn_close (socketFd);
		return (-1);
	}

	return socketFd;
}


int main(int argc, char* argv[]) {
	int socketFd;

	// For parsing command-line arguments
	struct Arguments args;

	parse_arguments(&args, argc, argv);

	socketFd = create_socket();

	communicate(socketFd, &args);

	cleanup(socketFd);

	return EXIT_SUCCESS;
}
