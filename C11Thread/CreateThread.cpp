/*
���ִ����̵߳ķ���
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
	// 1) ���������߳�
	thread myobj(mythread1);
	myobj.join();  // �������̣߳��ȴ����߳�ִ�����
	// myobj.detach();// �������̣߳���̨�ӹ�
	cout << "main 1 runninng stop! \n" << endl;

	// �ഴ������
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

	 // lambada �����߳�
	auto mylambada = [] {
		cout << "mylambada" << endl;
	};
	thread mythread3(mylambada);
	mythread3.join();

	system("pause");
	return 0;
}