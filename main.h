#ifndef MAIN_H_
#define MAIN_H_

// #include "os_config.h"

#define OS 0
// C library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#if OS == 0

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
int open_port(char *portname);
int init_serial(char *portname);
char getch();
#endif
#endif /* MAIN_H_ */