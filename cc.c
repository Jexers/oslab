#include <sys/time.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

long long realtime = 0, virtime = 0, protime = 0;

char *buf[256];

void init()
{
  struct itimerval real, vir, pro;
  real.it_value.tv_sec = 0;
  real.it_value.tv_usec = 1;
  real.it_interval.tv_sec = 0;
  real.it_interval.tv_usec = 1;
  
  vir.it_value.tv_sec = 0;
  vir.it_value.tv_usec = 1;
  vir.it_interval.tv_sec = 0;
  vir.it_interval.tv_usec = 1;

  pro.it_value.tv_sec = 0;
  pro.it_value.tv_usec = 1;
  pro.it_interval.tv_sec = 0;
  pro.it_interval.tv_usec = 1;

  setitimer(ITIMER_REAL, &real, NULL);
  setitimer(ITIMER_VIRTUAL, &vir, NULL);
  setitimer(ITIMER_PROF, &pro, NULL);
}

void sigalrm_handler(int sig)
{
  realtime++;
}

void sigvt_handler(int sig)
{
  virtime++;
}

void sigpro_handler(int sig)
{
  protime++;
}

int main()
{
  signal(SIGALRM, sigalrm_handler);
  signal(SIGVTALRM, sigvt_handler);
  signal(SIGPROF, sigpro_handler);
  init();

  int cnt = 100000;
  while(cnt--)
  {
    FILE *pf = fopen("in.file", "r");
    fgets(buf, 128, pf);
    fclose(pf);
  }

  printf("total realtime:%lldusec\n", realtime);
  printf("total virtime:%lldusec\n", virtime);
  printf("total protime:%lldusec\n", protime);

  return 0;
}
