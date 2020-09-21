#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>


int main(int argc, char **argv) {

    printf("========== Before the modification ============\n");
    printf("ProcessName: %s\n", argv[0]);
    for(int i = 1; i < argc; i ++){
        printf("Argv%d: %s\n", i, argv[i]);
    }

    /* Start the modification */
    int new_argc = argc;
    char ** new_argv = malloc((argc+1) * sizeof(*new_argv));
    for(int j = 0; j < argc; j++)
    {
        size_t length = strlen(argv[j]) + 1;
        new_argv[j] = malloc(length);
        memcpy(new_argv[j], argv[j], length);
        memset(argv[j], '\0', length);
    }

    printf("========== After the modification ============\n");
    printf("ProcessName: %s\n", argv[0]);
    for(int i = 1; i < argc; i ++){
        printf("Argv%d: %s\n", i, argv[i]);
    }

    printf("========== Copy data ============\n");
    printf("ProcessName: %s\n", new_argv[0]);
    for(int k = 1; k < new_argc; k ++){
        printf("Argv%d: %s\n", k, new_argv[k]);
    }
    return 0;
}
