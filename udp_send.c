

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <math.h>



#define BUFLEN 512
#define NPACK 600

#define BLENDER_IP "127.0.0.1"
#define BLENDER_PORT 21567
#define PORT_BIND 21568

void diep(char *s)
{
    perror(s);
    exit(1);
}



int main(void)
{
    struct sockaddr_in si_me, si_other;
    int s, i, slen=sizeof(si_other);
     
    double buf[3],buf_in[3];
    
    // Create our socket. 
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    diep("socket");
    
    // define the host (blender)
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(BLENDER_PORT);
    if (inet_aton(BLENDER_IP, &si_other.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    
    // the port to bind (where we wait for the answer)
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT_BIND);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, &si_me, sizeof(si_me))==-1)
    diep("bind");
    

    
    // generate some data then send/receive
    for (i=0; i<NPACK; i++) 
    {
    
      buf[0] =  3 * sin(i/60.);
      buf[1] =  3 * cos(i/60.);
      buf[2] =  cos(i/20.);
    
      printf("Sending packet %d\n", i);
      
        
    //Send, break on error
      if (sendto(s, buf, sizeof(buf), 0, &si_other, slen)==-1)
                diep("sendto()");
      
    //Receive, break on error
      if (recvfrom(s, buf_in, BUFLEN, 0, &si_other, &slen)==-1)
          diep("recvfrom()");
      
      printf("Received packet from %s:%d\nData: %f, %f, %f\n\n", 
            inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf_in[0], buf_in[1], buf_in[2]);
    
        
     //usleep(16666);
  
    }
        
                close(s);
                return 0;
      
    
 
    
 }
