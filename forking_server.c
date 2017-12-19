#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  int cts;
  int pidc;
  while(1) {
    
    cts = server_setup();

    pidc = fork();

    if(!pidc) {
      subserver(cts);
    }
    else {
      close(cts);
    }
    
  }
}

void subserver(int from_client) {
  int stc;
  char buf[1024];
  stc = server_connect(from_client);
  while(read(from_client,buf,sizeof(buf))) {
    
    process(buf);
    
  }
}

void process(char * s) {
  printf("[server] received %s",s);
}
