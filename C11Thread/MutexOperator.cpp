/*
*
*  mutex的运用  互斥量和死锁演示
* lock()和unlock()  lock_guard()  lock()
*
**/

#include "iostream"
#include "list"
#include "stdlib.h"
#include "stdlib.h"
#include "mutex"
#include "thread"
#include "string"
#include "vector"


class MyOperator
{
public :
	MyOperator()
	{
	
	}

	~MyOperator()
	{
	
	}

	 // 发送数据的线程
	void SendCommand(std::string UserCommand)
	{
		for (int i=0; i< 10; i++)
		{
			mymutex.lock();
			CommandList.push_back(UserCommand);
			std::cout << "SendCommand thread ID :   " << UserCommand  << "  +  " << std::this_thread::get_id() << std::endl;
			mymutex.unlock();	
		}
	
	}

	// 接收数据的线程
	void recvCommand()
	{
		for(int i=0; i< 10; i++)
		{
			//std::lock_guard<std::mutex> mylock(mymutex);
			mymutex.lock();
			if(!CommandList.empty())
			{
				std::string  GetCommand = CommandList.front();
				CommandList.pop_front();
				std::cout << "GetCommand:  " <<  GetCommand << std::endl;
				std::cout << "\nrecvCommand thread ID :   " << std::this_thread::get_id() << std::endl;
			}
			mymutex.unlock();
			
		}

	}

private:
	// 线程共享数据
	std::list<std::string> CommandList;
	//锁
	std::mutex mymutex;
};



// 演示死锁：两个以上的锁，锁定的顺序相反

class DeadLock
{
public:
	void operator()()
	{
		std::cout << "DeadLock thread ID: " << std::this_thread::get_id() << std::endl;
	}

private:
	std::vector<int>iNum;  //共享数据
	std::mutex my_mutex1;
	std::mutex my_mutex2;
};

void DeadMutexDisplay()
{
	std::cout << "DeadMutexDisplay DeadLock thread ID: " << std::this_thread::get_id() << std::endl;
}


int main()
{
	std::string comm = "I love China!";
	// 创建两个线程，一个读共享数据，一个写入共享数据
	MyOperator myobj;
	std::thread mythread1(&MyOperator::SendCommand, &myobj, comm);
	std::thread mythread2(&MyOperator::recvCommand, &myobj);
	mythread1.join();
	mythread2.join();


	// 创建多个线程
	std::vector<std::thread>ThreadVec;
	for(int i=0; i< 4; i++)
	{
		ThreadVec.push_back(std::thread(&MyOperator::SendCommand, &myobj, std::to_string(i)));
	}
	for(auto iter =ThreadVec.begin(); iter != ThreadVec.end(); iter++)
	{
		iter->join();
	}

	auto mylambada = [] {
		std::cout << "\nmylambada" << std::endl;
	};
	std::thread mythread3(mylambada);
	mythread3.join();

	std::thread mythread4(DeadMutexDisplay);
	// 演示死锁

	system("pause");
	return 0;
}