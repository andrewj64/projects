#include <fcntl.h>
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <iostream>

#define ARRAY_LEN 1024

//producer
int main()
{
  sem_t *hasRoom;    //initialize to ARRAY_LEN
  sem_t *hasContent; //initialize to 0
  hasRoom = sem_open("/hasRoom", O_CREAT | O_RDWR, 0666, ARRAY_LEN);
  hasContent = sem_open("/hasContent", O_CREAT | O_RDWR, 0666, 0);

  int count = 0;
  while(1)
  {
    //check for room in array
    sem_wait(hasRoom);
    //add item to array
    std::cout << "Posting problem: " << count++ << std::endl;
    sem_post(hasContent);
  }
}
