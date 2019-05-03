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
#include <string>
#include <errno.h>

int main()
{ 
    // allocate shm
     sem_unlink(problemNotFullSem.c_str());
    sem_unlink(problemNotEmptySem.c_str());
    sem_unlink(answerNotFullSem.c_str());
    sem_unlink(answerNotEmptySem.c_str());
    

    shm_unlink(problemMem.c_str());
    shm_unlink(answerMem.c_str());
   
    int prob = shm_open(problemMem.c_str(), O_CREAT | O_RDWR, 0666);
    //perror("prob");
    int ans = shm_open(answerMem.c_str(), O_CREAT | O_RDWR, 0666);
    //perror("ans");
    ftruncate(prob, (sizeof(Problem)*ARRAY_SIZE));
    ftruncate(ans, (sizeof(Answer)*ARRAY_SIZE));

    sem_t *probHasRoom;
    sem_t *probHasContent;
    probHasRoom = sem_open(problemNotFullSem.c_str(), O_CREAT | O_RDWR, 0666, ARRAY_SIZE);
    //perror("probHasRoom");
    probHasContent = sem_open(problemNotEmptySem.c_str(), O_CREAT | O_RDWR, 0666, 0);
    //perror("probHasContent");
    sem_t *ansHasRoom;
    sem_t *ansHasContent;
    ansHasRoom = sem_open(answerNotFullSem.c_str(), O_CREAT | O_RDWR, 0666, ARRAY_SIZE);
    //perror("ansHasRoom");
    ansHasContent = sem_open(answerNotEmptySem.c_str(), O_CREAT | O_RDWR, 0666, 0);
    //perror("ansHasContent");
    void *pHead = mmap(NULL, (sizeof(Problem)*ARRAY_SIZE), PROT_READ | PROT_WRITE, MAP_SHARED, prob, 0);
    void *aHead = mmap(NULL, (sizeof(Answer)*ARRAY_SIZE), PROT_READ | PROT_WRITE, MAP_SHARED, ans, 0);
    Problem *p = (Problem *) pHead;
    Answer *a = (Answer *) aHead;
    int offset = 0;
	////std::cout << "initialized" << std::endl;
    while(1)
    {
        // get problem from shm
        int sVal, retVal;
        retVal = sem_getvalue(probHasContent, &sVal);
        ////std::cout << "sVal = " << sVal << ". retVal= " << retVal << std::endl;
        sem_wait(probHasContent);
        //perror("probHasContent");
        // make answer
        sem_wait(ansHasRoom);
        //perror("ansHasContent");
        switch (p[offset].m_opcode)
		{
			case eADD:
				a[offset].m_answer = p[offset].m_op1 + p[offset].m_op2;
				break;
			case eSUB:
				a[offset].m_answer = p[offset].m_op1 - p[offset].m_op2;
				break;
			case eMUL:
				a[offset].m_answer = p[offset].m_op1 * p[offset].m_op2;
				break;
			case eDIV:
				a[offset].m_answer = p[offset].m_op1 / p[offset].m_op2;
				break;
		}
        offset = (offset + 1) % ARRAY_SIZE;
        //std::cout << "generated answer" << std::endl;
        sem_post(probHasRoom);
        //perror("sempost probHasRoom");
        sem_post(ansHasContent);
        
        // send answer back to client
    }
    return 0;
}
