/*
    run user mode command in kernel
*/

void usermode_exec(char * command){

    char *argv[] = { "/bin/bash", "-c", command, NULL};

    char *envp[] = {"SHELL=/bin/bash", "PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/root/bin", NULL};

    call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT);
}
