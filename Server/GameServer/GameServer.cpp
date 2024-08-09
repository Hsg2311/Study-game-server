#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <Windows.h>

// 가시성)
// CPU의 각 코어마다 자신만의 캐시를 가지고 있다.
// 캐시에는 메모리의 일부분을 복사해 놓는다.
// 캐시에 복사된 데이터를 수정하면 메모리에 있는 데이터와 일치하지 않는다.
// Thread_1에서 y = 1이 실행된다 하더라도, Thread_2에서 r2 = y가 실행될 때의 y의 값이 1이 아닐 수 도 있다는 얘기다.
// 
// 코드 재배치)
// 컴파일러나 CPU는 코드를 재배치할 수 있다.
//
// 따라서 if ( r1 == 0 && r2 == 0 ) break; 이 조건문이 참이 되는 경우가 발생할 수 있다.

int32 x;
int32 y;
int32 r1;
int32 r2;

volatile bool ready;

void Thread_1( )
{
	while ( !ready );

	y = 1; // Store y
	r1 = x; // Load x
}

void Thread_2( )
{
	while ( !ready );

	x = 1; // Store x
	r2 = y; // Load y
}

int main( )
{
	int32 count = 0;

	while ( true ) {
		ready = false;
		count++;

		x = y = r1 = r2 = 0;

		thread t1{ Thread_1 };
		thread t2{ Thread_2 };

		ready = true;

		t1.join( );
		t2.join( );

		if ( r1 == 0 && r2 == 0 )
			break;
	}

	cout << count << " 번만에 빠져나옴" << endl;
}