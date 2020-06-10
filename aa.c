#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

int num = 0;

void realtimer_set()
{
  struct itimerval itv, oldtv;
  itv.it_interval.tv_sec = 1;
  itv.it_interval.tv_usec = 0;
  itv.it_value.tv_sec = 1;
  itv.it_value.tv_usec = 0;
  setitimer(ITIMER_REAL, &itv, &oldtv);
}

void sigalrm_handler(int sig)
{
  num++;
}

int main()
{
  signal(SIGALRM, sigalrm_handler);
  realtimer_set();
  printf("You have only 10sec\n");
  while(num < 10){}
  printf("Now time is up\n");
  return 0;
}
