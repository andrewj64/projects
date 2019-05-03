#include <unistd.h>
#include <iostream>
#include "MathObj.hpp"

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include <mqueue.h>
#include <ctime>
#define DEBUG 0

int main(int argc, char **argv)
{
	char *buff;
	std::srand(time(NULL));
	// open same queues from server
	mqd_t pQueue = mq_open(problemQueueName.c_str(), O_RDWR, 0666, NULL);
	//perror("Opening Problem: ");
	mqd_t aQueue = mq_open(answerQueueName.c_str(), O_RDWR, 0666, NULL);
	//perror("Opening Answer: ");
	mq_attr pAttr;
	mq_attr aAttr;
	mq_getattr(pQueue, &pAttr);
	mq_getattr(aQueue, &aAttr);
	buff = new char[aAttr.mq_msgsize];
	Problem p;
	Answer* a = (Answer*) buff;
	int loopCount;
	unsigned int prio;
	if(argc > 1)
	{
		sscanf(argv[argc - 1], "%d", &loopCount);
	}
	else
	{
		loopCount = 1;
		std::cout << "no command line arg. loop once" << std::endl;
	}
	for (int i = 0; i < loopCount; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			//make problem
			p.m_opcode = (Operation) (std::rand() % 4);
			p.m_op1 = (std::rand() % 10) + 1;
			p.m_op2 = (std::rand() % 10) + 1;

			// send problem to queue
			mq_send(pQueue, (char *) &p, sizeof(Problem), prio);
			//perror("Sending Problem: ");

			// receive answer from queue
			ssize_t received = mq_receive(aQueue, buff, aAttr.mq_msgsize, &prio);
			//perror("Receiving Answer: ");
			//std::cout << "Received " << received << " bytes" << std::endl;

			// calculate answer to check if message queue worked
			float ans;
			switch (p.m_opcode)
			{
				case eADD:
					ans = p.m_op1 + p.m_op2;
					break;
				case eSUB:
					ans = p.m_op1 - p.m_op2;
					break;
				case eMUL:
					ans = p.m_op1 * p.m_op2;
					break;
				case eDIV:
					ans = p.m_op1 / p.m_op2;
					break;
			}
			if(a->m_answer != ans)
			{
				std::cout << "qans != ans" << "\t(" << a->m_answer << ", " << ans << ")" << std::endl;	
			}
			//std::cout << "Answer: " << a->m_answer << std:: endl;
		}
	}
	delete buff;
	return 0;
}