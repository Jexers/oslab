#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

char buf[256];
FILE *thisFile;

int main()
{
  struct timeval nowtime;
  thisFile = fopen("/proc/my_clock", "r");
  fgets(buf, 128, thisFile);
  gettimeofday(&nowtime, NULL);
  printf("SystemTime is %d %d\n my_clockFileTime is %s\n", nowtime.tv_sec, nowtime.tv_usec, buf);
  fclose(thisFile);
  return 0;
}
