#include<stdio.h>

#include "querysort.h"

int
main(const int argc, const char *argv[])
{
	if (argc != 2) {
		printf("Usage : %s URL\n", argv[0]);
		return 1;
	}

	// TODO validate URL

	char *url = querysort(argv[1]);

	if (url) {
		puts(url);
		free(url);
	}
	else {
		puts("Couldn't create the sorted URL");
	}

	return 0;
}

