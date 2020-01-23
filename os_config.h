/*
 * os_config.h
 *
 *  Created on: Jan 13, 2020
 *      Author: isa
 */

#ifndef OS_CONFIG_H_
#define OS_CONFIG_H_

#define OS 0
// C library headers
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#if OS == 0

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
void read_SP();
#endif

#endif /* OS_CONFIG_H_ */
