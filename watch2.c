#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <poll.h>


void setpfd(struct pollfd *pfd, int gpio)
{
   char str[256];
   int fd;
   char buf[8];

   sprintf(str, "/sys/class/gpio/gpio%d/value", gpio);
   if ((fd = open(str, O_RDONLY)) < 0)
   {
      fprintf(stderr, "Failed, gpio %d not exported.\n", gpio);
      exit(1);
   }
   pfd->fd = fd;
   pfd->events = POLLPRI;
   lseek(pfd->fd, 0, SEEK_SET);    /* consume any prior interrupt */
   read(pfd->fd, buf, sizeof buf);

}

int main(int argc, char *argv[])
{
   struct pollfd pfd[10];
   int i;

   /*
      Prior calls assumed.
      sudo sh -c "echo 4      >/sys/class/gpio/export"
      sudo sh -c "echo in     >/sys/class/gpio/gpio4/direction"
      sudo sh -c "echo rising >/sys/class/gpio/gpio4/edge"
   */

   for(i=1;i<argc;i++)
	   setpfd(pfd+i-1  ,atoi(argv[i]));

   poll(pfd, argc-1, -1);         /* wait for interrupt */

   //lseek(fd, 0, SEEK_SET);    /* consume interrupt */
   //read(fd, buf, sizeof buf);

   exit(0);
}
