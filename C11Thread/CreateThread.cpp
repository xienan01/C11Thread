/*
三种创建线程的方法
*/


#include "iostream"
#include "thread"
using namespace std;

void mythread1 ()
{
	int sum =0;
	cout << " mythread is begining! " << endl;
	for(int i=0; i <10; i++)
	{
		sum += i;
	}
	cout << "sum: " << sum << endl;
}

class MythreadClass
{
public:
	
	void operator()()
	{
		cout << "You are thread2!" << endl;
	}

	MythreadClass();

	MythreadClass(int i):iNum(i)
	{
		cout << "iNum: " << iNum << endl;
	}

	MythreadClass(const MythreadClass& mythread)
	{
		cout << " MythreadClass() running end!" << endl;
	}

	~MythreadClass()
	{
		cout << " ~MythreadClass() running end!" << endl;
	}
	
private:
	int iNum;
};

int min()
{
	// 1) 函数创建线程
	thread myobj(mythread1);
	myobj.join();  // 阻塞主线程，等待子线程执行完成
	// myobj.detach();// 分离子线程，后台接管
	cout << "main 1 runninng stop! \n" << endl;

	// 类创建对象
	/*MythreadClass mythread();
	thread mythread2(mythread);
	mythread2.join();
	if(mythread2.joinable())
	{
		cout << "mythread2 is joined!" << endl;
	}
	else
	{
		cout << "mythread2 is not joined!" << endl;
		cout << "mythread2 is not joined!" << endl;
	}*/

	 // lambada 创建线程
	auto mylambada = [] {
		cout << "mylambada" << endl;
	};
	thread mythread3(mylambada);
	mythread3.join();

	system("pause");
	return 0;
}