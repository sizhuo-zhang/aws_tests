#include "GeneratedTypes.h"
#include "LoopReq.h"
#include "LoopInd.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

uint32_t recv_val = 0;
sem_t sem;

class LoopInd : public LoopIndWrapper {
public:
    LoopInd(unsigned int id) : LoopIndWrapper(id) {}

    virtual void resp(uint32_t x) {
        recv_val = x;
        sem_post(&sem);
    }
};

int main() {
    LoopInd indication(IfcNames_LoopIndH2S);
    LoopReqProxy *reqProxy = new LoopReqProxy(IfcNames_LoopReqS2H);

    long actualFrequency = 0;
    long requestedFrequency = 1e9 / MainClockPeriod;
    int status = setClockFrequency(0, requestedFrequency, &actualFrequency);
    fprintf(stderr, "Requested main clock frequency %5.2f, "
            "actual clock frequency %5.2f MHz status=%d errno=%d\n",
	        (double)requestedFrequency * 1.0e-6,
	        (double)actualFrequency * 1.0e-6,
	        status, (status != 0) ? errno : 0);

    sem_init(&sem, 0, 0);
    for (int i = 0; i < 100; i++) {
        uint32_t send_val = i;
        printf("Test %d: Sending %d\n", i, unsigned(send_val));
        reqProxy->req(send_val);
        sem_wait(&sem);
        printf("Receive %d\n", unsigned(recv_val));
        if (send_val != recv_val) {
            fprintf(stderr, "ERROR!\n");
            exit(1);
        }
    }
    fprintf(stderr, "PASS!\n");
    return 0;
}
