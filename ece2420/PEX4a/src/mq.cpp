#include <unistd.h>	
#include <iostream>

#include <fcntl.h> 		/* For O_* constants */
#include <sys/stat.h>	/* For mode constants */
#include <mqueue.h>	
#include <errno.h>
#include <string.h>
#include <mqueue.h>
#include "MathObj.hpp"

int main ()
{
	char buff[8192];
	//open q
	//while()
	//get msg
	//make answer
	//send answer back to client
	mq_unlink(problemQueueName.c_str());
	mq_unlink(answerQueueName.c_str());
	mqd_t pQueue = mq_open(problemQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
	//perror("Opening Problem: ");
	mqd_t aQueue = mq_open(answerQueueName.c_str(), O_CREAT | O_RDWR, 0666, NULL);
	//perror("Opening Answer: ");
	mq_attr pAttr;
	mq_attr aAttr;
	mq_getattr(pQueue, &pAttr);
	mq_getattr(aQueue, &pAttr);
	Problem* p = (Problem*) buff;
	Answer a;
	unsigned int prio = 1;

	
	while(1)
	{
		// receive problem
		ssize_t received = mq_receive(pQueue, buff, pAttr.mq_msgsize, &prio);
		//std::cout << "Received " << received << " bytes" << std::endl;
		// make answer
		switch (p->m_opcode)
		{
			case eADD:
				a.m_answer = p->m_op1 + p->m_op2;
				break;
			case eSUB:
				a.m_answer = p->m_op1 - p->m_op2;
				break;
			case eMUL:
				a.m_answer = p->m_op1 * p->m_op2;
				break;
			case eDIV:
				a.m_answer = p->m_op1 / p->m_op2;
				break;
		}
		// send answer to client
		mq_send(aQueue, (char *) &a, sizeof(Answer), prio); 
	}
	

	
	
	
	return 0;
}