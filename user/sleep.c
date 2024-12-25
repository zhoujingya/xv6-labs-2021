#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("%s", "pass an argument to sleep\n");
    exit(1);
  }
  int times = atoi(argv[1]);
  sleep(times);
  exit(0);
}
