#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common/common.h"

void communicate(int socketFd, struct Arguments* args) {
	struct Benchmarks bench;
	int rc;
	bool first = true;
	void* buffer = malloc(args->size);

	Arguments argsCopy = *args;
	//int i = 0;

	for (; args->count > 0; --args->count) {
		if(first){
			// Receive data from the server
			rc = nn_recv(socketFd, buffer, args->size, 0);
			if (rc < 0) {
				/*  Any error here is unexpected. */
				fprintf(stderr, "nn_recv: %s\n", nn_strerror(nn_errno()));
				break;
			}
			setup_benchmarks(&bench);
			bench.single_start = now();
			benchmark(&bench);
			first = false;
		} else {
			bench.single_start = now();

			// Receive data from the server
			rc = nn_recv(socketFd, buffer, args->size, 0);
			if (rc < 0) {
				/*  Any error here is unexpected. */
				fprintf(stderr, "nn_recv: %s\n", nn_strerror(nn_errno()));
				break;
			}

			//printf("Client %d\n", i++);

			benchmark(&bench);
		}
	}
	evaluate(&bench, &argsCopy);
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
	socketFd = nn_socket(AF_SP, NN_SUB);
	if (socketFd < 0) {
		fprintf(stderr, "nn_socket: %s\n", nn_strerror(nn_errno()));
		return (-1);
	}

	// subscribe to everything ("" means all topics)
	nn_setsockopt(socketFd, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
	// 2MB limit on the inbound queue
	void* option;
	option = malloc(sizeof(int));
	*(int*)option = 12000000;
	nn_setsockopt (socketFd, NN_SOL_SOCKET , NN_RCVBUF, option, sizeof(int));

	address = "ipc:///tmp/nanomsg_ipc";

	if (nn_connect(socketFd, address) < 0) {
		fprintf(stderr, "nn_connect: %s\n", nn_strerror(nn_errno()));
		nn_close(socketFd);
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
