#include <unistd.h>
#include <string.h>


void print_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        write(1, env[i], strlen(env[i]));
        write(1, "\n", 1);
        i++;
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argc;    // Avoid unused parameter warning
    (void)argv;    // Avoid unused parameter warning
    
    write(1, "Environment Variables:\n", 23);
    print_env(env);
    
    write(1, "OK\n", 3);
    return (0);
}