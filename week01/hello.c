#include <stdio.h>

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		printf("hello %s\n", argv[i]);
	}
}
