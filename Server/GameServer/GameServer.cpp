#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>

mutex m;
queue<int32> q;

// 참고) CV는 User-Level Object (커널 오브젝트 X )
condition_variable cv;

void Producer( )
{
	while ( true ) {
		// 1) Lock을 걸고
		// 2) 공유 변수 값을 수정
		// 3) Lock을 풀고
		// 4) 조건변수를 통해 다른 쓰레드에게 통지

		{
			unique_lock<mutex> lock{ m };
			q.push( 100 );
		}

		cv.notify_one( );	// wait 중인 쓰레드가 있으면 딱 1개를 깨운다.

		//this_thread::sleep_for( 1000ms );
	}
}

void Consumer( )
{
	while ( true ) {
		unique_lock<mutex> lock{ m };
		cv.wait( lock, []( ) { return q.empty( ) == false; } );		// lock이 걸려 있으면 따로 다시 걸지는 않음.
		// 1) Lock을 걸고
		// 2) 조건 확인
		// - 만족 O => 빠져 나와서 이어서 코드를 진행
		// - 만족 X => Lock을 풀어주고 대기 상태

		// 그런데 notify_one을 했으면 항상 조건식을 만족하는 거 아닐까?
		// Spurious Wakeup : 조건이 만족하지 않았는데도 깨어나는 현상 (가짜 기상?)이 발생할 수 있음
		// notify_one할 때 lock을 걸고 있는 것이 아니기 때문
		
		{
			int32 data = q.front( );
			q.pop( );
			cout << q.size( ) << endl;
		}
	}
}

int main()
{
	thread producer{ Producer };
	thread consumer{ Consumer };

	producer.join( );
	consumer.join( );
}