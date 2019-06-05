#include <iostream>
#include <csignal>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define IPUNITY     "127.0.0.1"
#define IPHAPT      "127.0.0.1"
#define PORTUNITY   8080
#define PORTHAPT    8081

#define BUFLEN 24

using namespace std;

int main() {
    int sckt;
    struct sockaddr_in addrHapt, addrUnity;
    socklen_t addrLen = sizeof(addrUnity);

    // the port to bind (where we wait for the answer)
    memset((char *) &addrHapt, 0, sizeof(addrHapt));
    addrHapt.sin_family = AF_INET;
    addrHapt.sin_port = htons(PORTHAPT);
    //addrHapt.sin_addr.s_addr = htonl(inet_pton(IPHAPT));


    memset((char *) &addrUnity, 0, sizeof(addrUnity));
    addrUnity.sin_family = AF_INET;
    addrUnity.sin_port = htons(PORTUNITY);
    if (inet_aton(IPUNITY, &addrUnity.sin_addr)==0) {
        cout << "inet_aton() failed" << endl;
        return -1;
    }

    /* Setting Socket parameters */
    if ((sckt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == 0) {
        cout << "Socket creation failed" << endl;
        return -1;
    }

    if (bind(sckt, (struct sockaddr *)&addrHapt, sizeof(addrHapt))==-1) {
        cout << "Binding of socket failed" << endl;
        return -1;
    }

    double bufIn[2] = {0.0}, bufOut[3] = {0.0};

    while (true) {
        if (sendto(sckt, bufOut, sizeof(bufOut), 0, (struct sockaddr *)&addrUnity, sizeof(addrUnity))==-1) {
            cout << "sendTo of socket failed" << endl;
            return -1;
        }
        bufOut[0] += 0.1; bufOut[1] += 0.01; bufOut[2] += 0.001;
        //cout << bufOut[0] << ", " << bufOut[1] << endl;

        if (recvfrom(sckt, bufIn, BUFLEN, 0, (struct sockaddr *)&addrUnity, &addrLen)==-1) {
            cout << "recvfrom of socket failed" << endl;
            return -1;
        }
        cout << bufIn[0] << ", " << bufIn[1] << endl;
        usleep(100000);
    }

    return 0;
}
