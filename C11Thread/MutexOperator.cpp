/*
*
*  mutex������  ��������������ʾ
* lock()��unlock()  lock_guard()  lock()
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

	 // �������ݵ��߳�
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

	// �������ݵ��߳�
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
	// �̹߳�������
	std::list<std::string> CommandList;
	//��
	std::mutex mymutex;
};



// ��ʾ�������������ϵ�����������˳���෴

class DeadLock
{
public:

	 // �������ݵ��߳�
	void SendCommand(int UserCommand)
	{
		for (int i=0; i< 10; i++)
		{
			//my_mutex1.lock();
			std::lock(my_mutex1, my_mutex2);
			iNum.push_back(UserCommand);
			std::cout << "SendCommand thread ID :   " << UserCommand  << "  +  " << std::this_thread::get_id() << std::endl;
			my_mutex1.unlock();
			my_mutex2.unlock();	
		}
	
	}

	// �������ݵ��߳�
	void recvCommand()
	{
		for(int i=0; i< 10; i++)
		{
			//std::lock_guard<std::mutex> mylock(mymutex);
			//my_mutex1.lock();
			std::lock(my_mutex1, my_mutex2);
			std::lock_guard<std::mutex>mymutexTest0(my_mutex1, std::adopt_lock);
			std::lock_guard<std::mutex>mymutexTest1(my_mutex2, std::adopt_lock);
			if(!iNum.empty())
			{
				int GetNumber = iNum.front();
				std::cout << "GetCommand:  " <<  GetNumber << std::endl;
				std::cout << "\nrecvCommand thread ID :   " << std::this_thread::get_id() << std::endl;
			}
			//my_mutex1.unlock();
			//my_mutex2.unlock();
			
		}

	}

private:
	// �̹߳�������
	std::vector<int>iNum;  //��������
	std::mutex my_mutex1;
	std::mutex my_mutex2;
};



int main()
{
	std::string comm = "I love China!";
	// ���������̣߳�һ�����������ݣ�һ��д�빲������
	MyOperator myobj;
	std::thread mythread1(&MyOperator::SendCommand, &myobj, comm);
	std::thread mythread2(&MyOperator::recvCommand, &myobj);
	mythread1.join();
	mythread2.join();


	// ��������߳�
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

	// std::lock()��ʾ
	//  1�������������
	int inum = 100;
	// ���������̣߳�һ�����������ݣ�һ��д�빲������
	DeadLock myobj2;
	std::thread mythread5(&DeadLock::SendCommand, &myobj2, inum);
	std::thread mythread6(&DeadLock::recvCommand, &myobj2);
	mythread5.join();
	mythread6.join();



	system("pause");
	return 0;
}