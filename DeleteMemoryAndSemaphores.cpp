#include "producerCustomer.h"

int memoryKey;
int semaphoreKey;
int main(int argc, char* argv[])
{
    DeleteMemory(atoi(argv[1]));
    DeleteSemaphores(atoi(argv[2]));
    return 0;
}

