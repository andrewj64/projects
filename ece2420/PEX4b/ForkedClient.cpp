#include "MathObj.hpp"

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>           
#include <iostream>           
#include <semaphore.h>           
#include <map>
#include <functional>
#include <mqueue.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	char *buff;
	// Open message queues
	mqd_t pQueue = mq_open(problemQueueName.c_str(), O_RDWR, 0666, NULL);
	mqd_t aQueue = mq_open(answerQueueName.c_str(), O_RDWR, 0666, NULL);
	mq_attr pAttr;
	mq_attr aAttr;
	mq_getattr(pQueue, &pAttr);
	mq_getattr(aQueue, &aAttr);
	buff = new char[aAttr.mq_msgsize];
	
	// Initialize Problem and answer variables
	Problem p;
	Answer* a = (Answer*) buff;
	unsigned int prio;
	
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
  int pid = fork();
  if(pid == 0)
  {
    for(int i = 0; i < loopCount; i++)
    {
		for ( int j = 0; j < ARRAY_SIZE; j++)
		{
			//make problem
			/*
			p.m_opcode = (Operation) (std::rand() % 4);
			p.m_op1 = (std::rand() % 10) + 1;
			p.m_op2 = (std::rand() % 10) + 1;
			*/
			p.m_opcode = (Operation) (j % 4);
			p.m_op1 = 1;
			p.m_op2 = 1;
			
			// send problem to queue
			mq_send(pQueue, (char *) &p, sizeof(Problem), prio);
		}
    }
	
  }
  else
  {
    for(int i = 0; i < loopCount; i++)
    {
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			// receive answer from queue
			mq_receive(aQueue, buff, aAttr.mq_msgsize, &prio);
		}
    }

    //This call will force the parent process to wait for the child to die.  It may ensure
    //that all problems are processed.  Also ensure a clean teardown, (i.e. no zombie/orphaned 
    //processes)
	
    int status;
    waitpid(pid, &status, 0);
  }
	delete buff;
}
