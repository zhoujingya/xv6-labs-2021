#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>

int main(int argc, char *argv[]) {
  int p1[2];  // parent -> child pipe 
  int p2[2];  // child -> parent pipe

  pipe(p1);
  pipe(p2);

  int pid = fork();
  if (pid == 0) {
    // child process
    close(p1[1]);  // close write end of parent->child pipe
    close(p2[0]);  // close read end of child->parent pipe

    char buf[4];
    read(p1[0], buf, 4);  // read "ping" from parent
    printf("%d: received %s\n", getpid(), buf);

    write(p2[1], "pong", 5);  // send "pong" to parent

    close(p1[0]);
    close(p2[1]);
    exit(0);
  } else {
    // parent process
    close(p1[0]);  // close read end of parent->child pipe
    close(p2[1]);  // close write end of child->parent pipe

    write(p1[1], "ping", 5);  // send "ping" to child

    char buf[4];
    read(p2[0], buf, 4);  // read "pong" from child
    printf("%d: received %s\n", getpid(), buf);

    close(p1[1]);
    close(p2[0]);
    wait(0);
  }
  exit(0);
}
