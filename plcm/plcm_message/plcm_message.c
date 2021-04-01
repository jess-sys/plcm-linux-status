/*
 * Lanner Paralle LCM Driver Test Program
 */
#include <sys/file.h>
#include <stdio.h>
#include <string.h>
#include "plcm_ioctl.h"

int main(int argc, char *argv[])
{
    int devfd;
    
    devfd = open("/dev/plcm_drv", O_RDWR);
    if(devfd == -1) {
    	printf("Can't open /dev/plcm_drv\n");
    	return -1;
    }
    if(argc >= 2) {
	ioctl(devfd, PLCM_IOCTL_DISPLAY_B, 0);
	ioctl(devfd, PLCM_IOCTL_SHIFT_SC, 0);
	ioctl(devfd, PLCM_IOCTL_DISPLAY_C, 0);
    	if(strcmp("-h", argv[1]) == 0) {
		printf("Usage: %s [--display-on | --display-off | --display-blink X | --message-line-1 | --message-line-2] MESSAGE\n");
    		close(devfd);
    		return 0;
    	}
    	if(strcmp("--display-on", argv[1]) == 0) {
    		ioctl(devfd, PLCM_IOCTL_BACKLIGHT, 1);
    		//sleep(1);
    		close(devfd);
    		return 0;
    	}
    	if(strcmp("--display-off", argv[1]) == 0) {
    		ioctl(devfd, PLCM_IOCTL_BACKLIGHT, 0);
    		//sleep(1);
    		close(devfd);
    		return 0;
    	}
    	if(strcmp("--display-blink", argv[1]) == 0) {
		if (argc < 3)
		    return 1;
		for (int i = 0 ; i < atoi(argv[2]) ; i++) {
    		    ioctl(devfd, PLCM_IOCTL_BACKLIGHT, 0);
    		    sleep(1);
    		    ioctl(devfd, PLCM_IOCTL_BACKLIGHT, 1);
    		    sleep(1);
		}
    		close(devfd);
    		return 0;
    	}
    	if(strcmp("--message-line-1", argv[1]) == 0) {
		if (argc < 3)
		    return 1;
    		ioctl(devfd, PLCM_IOCTL_SET_LINE, 1);
    		write(devfd, argv[2], strlen(argv[2]));
    		close(devfd);
    		return 0;
    	}
    	if(strcmp("--message-line-2", argv[1]) == 0) {
		if (argc < 3)
		    return 1;
    		ioctl(devfd, PLCM_IOCTL_SET_LINE, 2);
    		write(devfd, argv[2], strlen(argv[2]));
    		close(devfd);
    		return 0;
    	}
    }
    close(devfd);
    return 0;
}

