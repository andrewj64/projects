#include "Head.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <memory>

#define HEADS 10
uint32_t array1[HEADS] = {0};
uint32_t array2[HEADS] = {0};


// Expectation: All values in array1 should equal 2*numIterations
// Verifies thread safety
void modArray1(int i)
{
	int temp = array1[i];
	usleep(1000);
	array1[i] = temp + 1;

	temp = array1[(i + 1) % HEADS];
	usleep(1000);
	array1[(i + 1) % HEADS] = temp + 1;
}

// Expectation: Stolchastic behavior in array2
// Verifies optimal concurrency
void modArray2(int i)
{
	for(int j = 0; j < HEADS; j++)
	{
		int temp = array2[j];
		usleep(1000);
		array2[j] = temp + 1;
	}
}

void test(std::function<void(int)> mod, uint32_t* array) {
	std::mutex mtx;
	std::vector<std::shared_ptr<Head> > headVec = Head::makePlatter(HEADS);

	//function to run as thread
	std::function<void(int i)> func = [&headVec, &mtx, mod](int i){
		for(int j = 0; j < 1000; j++)
		{
			mtx.lock();
			std::cout << "Iteration: " << j << std::endl;
			mtx.unlock();
			headVec[i]->execute([i, mod](){ mod(i); });
		}
	};

	std::vector<std::thread> tVec;
	for(int i = 0; i < HEADS; ++i)
	{
		tVec.emplace_back(func, i);
	}

	for(auto it = tVec.begin(); it != tVec.end(); ++it) {
		it->join();
	}

	for(int i = 0; i < HEADS; i++) {
		std::cout << "Idx: " << i << " Val: " << array[i] << std::endl;
	}
}

int main() {
	std::mutex mtx;

	std::vector<std::shared_ptr<std::thread>> threads;
	std::vector<std::shared_ptr<Head>> heads = Head::makePlatter(HEADS);

	std::thread grouper([&mtx]() {
		for (int i = 0; i < 2 * HEADS; ++i)	{
			{
				std::unique_lock<std::mutex> lock(mtx);
				std::cout
					<< "Time: " << i << " seconds" << std::endl;
			}
			sleep(1);
		}
		{
			std::unique_lock<std::mutex> lock(mtx);
			std::cout
				<< "Time: " << 2 * HEADS << " seconds" << std::endl;
		}
	});

	for (int i = 0; i < HEADS; ++i) {
		threads.push_back(std::make_shared<std::thread>([i, &heads, &mtx]() {
			heads[i]->execute([i, &mtx]() {
				{
					std::unique_lock<std::mutex> lock(mtx);
					std::cout << "\tHead " << i << std::endl;
				}
				sleep(2);
			});
		}));
	}

	for (int i = 0; i < HEADS; ++i) {
		threads[i]->join();
	}

	grouper.join();

    test(modArray1, array1);
	test(modArray2, array2);

	return 0;
}







