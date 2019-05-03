#include <fcntl.h>
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <iostream>

#define ARRAY_LEN 1024

//consumer
int main()
{
  sem_t *hasRoom;    //initialize to ARRAY_LEN
  sem_t *hasContent; //initialize to 0
  hasRoom = sem_open("/hasRoom", O_RDWR);
  hasContent = sem_open("/hasContent", O_RDWR);

  int count = 0;
  while(1)
  {
    //check for room in array
    sem_wait(hasContent);
    //consume problem
    std::cout << "Solving problem: " << count++ << std::endl;
    sem_post(hasRoom);
  }
}
