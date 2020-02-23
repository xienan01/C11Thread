#include   <windows.h>  
#include   <stdio.h>  
#include   <process.h>  

#ifdef __unix__
#include <pthread.h>
#include <stdlib.h>
#endif

unsigned   Counter;

unsigned   __stdcall   SecondThreadFunc(void* pArguments)
{
    printf("In   second   thread...\n");

    while (Counter < 1000000)
    {
        Counter++;
    }
    printf(" second  thread pid = %d\n", GetCurrentThreadId());
    _endthreadex(0);
    return   0;
}


DWORD WINAPI ThirdThreadFunc(LPVOID p)
{
    while (Counter < 1000000)
    {
        Counter++;
    }
    printf(" third  thread pid = %d\n", GetCurrentThreadId()); 
    return 0;
}


static void* pthread(void* arg)
{
    printf("linux pthread start!\n");
    return NULL;
}

int   main()
{
    HANDLE   hThread;
    unsigned  threadID;
    printf(" first  thread pid = %d\n", GetCurrentThreadId());
    hThread = (HANDLE)_beginthreadex(NULL, 0, &SecondThreadFunc, NULL, 0, &threadID);   //NULL表示无传递参数
    printf("Creating   first   thread...\n");
    WaitForSingleObject(hThread, INFINITE); 
    CloseHandle(hThread);

    HANDLE   Thread;
    DWORD   ThreadID;
    Thread = CreateThread(NULL, 0, &ThirdThreadFunc, NULL, 0, &ThreadID);
    printf("Counter   should   be   1000000;   it   is->   %d\n", Counter);


#ifdef  __unix__
	pthread_t tidp;
	/* 创建线程pthread */
	if ((pthread_create(&tidp, NULL, pthread, NULL)) == -1)
	{
		printf("create error!\n");
		return 1;
	}
    // 等待线程释放
	if (pthread_join(tidp, NULL))
	{
		printf("thread is not exit...\n");
		return -2;
	}
#endif 

}
