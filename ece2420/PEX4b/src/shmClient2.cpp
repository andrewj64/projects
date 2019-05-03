#include "MathObj.hpp"

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>           
#include <iostream>           
#include <semaphore.h>           
#include <map>
#include <functional>
#include <sys/wait.h>
#include <cstring>
#include <errno.h>

int main(int argc, char **argv)
{ 
	// Initialize semaphores
	sem_t *probHasRoom;
    sem_t *probHasContent;
    probHasRoom = sem_open(problemNotFullSem.c_str(), O_RDWR, 0666, ARRAY_SIZE);
    probHasContent = sem_open(problemNotEmptySem.c_str(), O_RDWR, 0666, 0);
    sem_t *ansHasRoom;
    sem_t *ansHasContent;
    ansHasRoom = sem_open(answerNotFullSem.c_str(), O_RDWR, 0666, ARRAY_SIZE);
    ansHasContent = sem_open(answerNotEmptySem.c_str(), O_RDWR, 0666, 0);

    // open shared memory
    int prob = shm_open(problemMem.c_str(), O_RDWR, 0666);
    int ans = shm_open(answerMem.c_str(), O_RDWR, 0666);
    void *pHead = mmap(NULL, (sizeof(Problem)*ARRAY_SIZE), PROT_READ | PROT_WRITE, MAP_SHARED, prob, 0);
    void *aHead = mmap(NULL, (sizeof(Answer)*ARRAY_SIZE), PROT_READ | PROT_WRITE, MAP_SHARED, ans, 0);
    Problem *p = (Problem *) pHead;
    Answer *a = (Answer *) aHead;
	std::srand(time(NULL));
	int offset = 0;
	
    // process command line arguments
    int loopCount;
    if(argc > 1)
	{
		sscanf(argv[argc - 1], "%d", &loopCount);
	}
	else
	{
		loopCount = 1;
		std::cout << "no command line arg. loop once" << std::endl;
	}
	//std::cout<< "loopCount: " << loopCount << std::endl;
  int pid = fork();
  if(pid == 0)
  {
    for(int i = 0; i < loopCount; i++)
    {
			for (int j = 0; j < ARRAY_SIZE; j++)
			{
				//std::cout << "loop #"<< (j+1)*(i+1) << std::endl;
				sem_wait(probHasRoom);
				//perr("1");
				//std::cout << "retval" << retVal << std::endl;
				//std::cout << "Yup" << std::endl;
				p[offset].m_opcode = (Operation) (std::rand() % 4);
				p[offset].m_op1 = (std::rand() % 10) + 1;
				p[offset].m_op2 = (std::rand() % 10) + 1;
				sem_post(probHasContent);
				//perr("2");
				// send problem to queue

				offset = (offset + 1) % ARRAY_SIZE;
			}
    }
	
  }
  else
  {
    for(int i = 0; i < loopCount; i++)
    {
			for (int j = 0; j < ARRAY_SIZE; j++)
			{
				float ans;
				sem_wait(ansHasContent);
				//perr("sem wait ans");
				memcpy(&ans, &(a[offset].m_answer), sizeof(Answer));
				// calculate answer to check if message queue worked
			/*	switch (p[offset].m_opcode)
				{
					case eADD:
						ans = p[offset].m_op1 + p[offset].m_op2;
						break;
					case eSUB:
						ans = p[offset].m_op1 - p[offset].m_op2;
						break;
					case eMUL:
						ans = p[offset].m_op1 * p[offset].m_op2;
						break;
					case eDIV:
						ans = p[offset].m_op1 / p[offset].m_op2;
						break;
				}
				if(a[offset].m_answer != ans)
				{
					std::cout << "shm_ans != ans" << "\t(" << a[offset].m_answer << " != " << ans << ")" << std::endl;	
				}
					// receive answer from queue

				}*/
				offset = (offset + 1) % ARRAY_SIZE;
				sem_post(ansHasRoom);
			}
    }

    //This call will force the parent process to wait for the child to die.  It may ensure
    //that all problems are processed.  Also ensure a clean teardown, (i.e. no zombie/orphaned 
    //processes)
	
    int status;
    waitpid(pid, &status, 0);
  }
	return 0;
}
