#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "ncurses.h"

int exist(const char* fname);
int sizeoffile(int fd);
int copier(int fd1, int fd2);