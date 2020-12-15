#include <poll.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


void poll_pin() {
  struct pollfd fdlist[1];
  int fd;

  fd = open("/sys/class/gpio/gpio53/value", O_RDONLY);
  fdlist[0].fd = fd;
  fdlist[0].events = POLLPRI;

  while (1) {
    int err;
    char buf[3];

    err = poll(fdlist, 1, -1);
    if (-1 == err) {
      perror("poll");
      return;
    }

    err = read(fdlist[0].fd, buf, 2);
    printf("event on pin 53!\n");
  }
}

int main(int argc, char *argv[]) {
  poll_pin();
}
