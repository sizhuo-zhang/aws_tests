#include "GeneratedTypes.h"
#include "LoopReq.h"
#include "LoopInd.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

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
