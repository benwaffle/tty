#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
        int fd = posix_openpt(O_RDWR);
        grantpt(fd);
        unlockpt(fd);

        if (fork() > 0) { // parent
                puts("parent");
        } else { // child
                setsid();
                int pts = open(ptsname(fd), O_RDWR);
                dup2(pts, STDIN_FILENO);
                dup2(pts, STDOUT_FILENO);
                dup2(pts, STDERR_FILENO);
                puts("child");
        }

        return 0;
} 
