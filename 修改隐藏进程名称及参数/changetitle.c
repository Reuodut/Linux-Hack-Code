/*
gcc changetitle.c -o changetitle
*/
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <sys/prctl.h>

# define MAXLINE 2048

extern char **environ;

static char **g_main_Argv = NULL;    /* pointer to argument vector */
static char *g_main_LastArgv = NULL;    /* end of argv */

void setproctitle_init(int argc, char **argv, char **envp)
{
    int i;

    for (i = 0; envp[i] != NULL; i++) // calc envp num
        continue;
    environ = (char **) malloc(sizeof (char *) * (i + 1)); // malloc envp pointer

    for (i = 0; envp[i] != NULL; i++)
    {
        environ[i] = malloc(sizeof(char) * strlen(envp[i]));
        strcpy(environ[i], envp[i]);
    }
    environ[i] = NULL;

    g_main_Argv = argv;
    if (i > 0)
        g_main_LastArgv = envp[i - 1] + strlen(envp[i - 1]);
    else
        g_main_LastArgv = argv[argc - 1] + strlen(argv[argc - 1]);
}

void setproctitle(const char *fmt, ...)
{
    char *p;
    int i;
    char buf[MAXLINE];

    extern char **g_main_Argv;
    extern char *g_main_LastArgv;
    va_list ap;
    p = buf;

    va_start(ap, fmt);
    vsprintf(p, fmt, ap);
    va_end(ap);

    i = strlen(buf);

    if (i > g_main_LastArgv - g_main_Argv[0] - 2)
    {
        i = g_main_LastArgv - g_main_Argv[0] - 2;
        buf[i] = '\0';
    }
    //修改argv[0]
    (void) strcpy(g_main_Argv[0], buf);

    p = &g_main_Argv[0][i];
    while (p < g_main_LastArgv)
        *p++ = '\0';
    g_main_Argv[1] = NULL;
    
    //调用prctl
    prctl(PR_SET_NAME,buf);
}

int main(int argc, char *argv[])
{
    char argv_buf[MAXLINE] = {0}; // save argv paramters
    int i;

    for( i = 1; i < argc; i++)
    {
        strcat(argv_buf, argv[i]);
        strcat(argv_buf, " ");
    }
    
    //修改argv[0]所指向的内存空间的内容
    setproctitle_init(argc, argv, environ);
    
    //调用prctl修改进程名
    setproctitle("%s@%s %s", "newname", "ip", argv_buf);

    for (i = 0; environ[i] != NULL; i++)
        free(environ[i]);
    getchar();

    return 0;
}