#include "main.h"
#define EXIT_SUCCESS 0

int main(void)
{
    int filestream = -1;
    char *portname = "/dev/ttyUSB0";
    FILE *fptr;
    char sentence[1000];

    filestream = init_serial(portname);

    // this is for reset log file on every start
    fptr = fopen("log.txt", "w");
    if (fptr == NULL)
    {
    	printf("Error: Can not open file\n");
    	exit(1);
    }
    fclose(fptr);

    while(1)
    {
        int cnt = 1;
        time_t clk = time(NULL);
        struct tm *tm = localtime(&clk);
    	if (filestream != -1)
    	{
        	// Read up to 255 characters from the port if they are there
        	unsigned char rx_buffer[256],fbuffer[512];
        	int rx_length = read(filestream, (void*)rx_buffer, 255);          //Filestream, buffer to store in, number of bytes to read (max)
        	// printf("rx len: %d\n", rx_length);
        	
        	if (rx_length < 0)
        	{
                //An error occured (will occur if there are no bytes)
        		// printf("err\n");
        	}
        	else if (rx_length == 0)
        	{
                //No data waiting
        	} else {
                //Bytes received
                fptr = fopen("log.txt", "a+");
                rx_buffer[rx_length] = '\0';
                printf("%s", rx_buffer);
                fprintf(fptr, "%s" ,rx_buffer);
                fclose(fptr);
        	}
        	
        	// printf("rx: %s\n", rx_buffer);
        }
        
    // char key = getch();
    // if (key == 'q')		
    // {
    // 	printf("Serial port is closing\n");
    // 	close(filestream);
    // 	break;
    // }else {
    // 	continue;
    // }
    }
    fclose(fptr);
    close(filestream);

}


#if OS == 0

// char sp_name = "/dev/ttyUSB1"; 
char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
            perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror ("tcsetattr ~ICANON");
    return (buf);
}

int open_port(char *portname) {
   int fd;                                   /* File descriptor for the port */
 
   fd = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
 
   if (fd == -1)
   {                                              /* Could not open the port */
     printf("open_port: Unable to open %s - %s\n", portname, strerror(errno));
   }
 
   return (fd);
}

int init_serial(char *portname) {
	int fd;
	fd = open_port(portname);
    struct termios options;
    //tcgetattr(uart0_filestream, &options);
    options.c_cflag = CS8 | CLOCAL | CREAD;         //<Set baud rate
    options.c_iflag = 0;
    options.c_oflag = 0;
    options.c_lflag = 0;
    // options.c_cc[VMIN] = 255;
    // options.c_cc[VTIME] = 255;
    tcflush(fd, TCIFLUSH);


    if (cfsetospeed(&options, B600) || cfsetispeed(&options, B600))
    {
            printf("err0r\n");
            return 0;
    }

    cfmakeraw(&options);
    tcflush(fd, TCIFLUSH);

    tcsetattr(fd, TCSANOW, &options);

    printf("init complete, listening...\n\n");
    return fd;
}

#endif
