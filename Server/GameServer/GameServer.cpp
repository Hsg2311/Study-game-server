#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>

mutex m;
queue<int32> q;
HANDLE handle;

void Producer( )
{
	while ( true ) {
		{
			unique_lock<mutex> lock{ m };
			q.push( 100 );
		}

		::SetEvent( handle );	// 커널 오브젝트의 Signal 상태를 true로 변경

		this_thread::sleep_for( 1000ms );
	}
}

void Consumer( )
{
	while ( true ) {
		::WaitForSingleObject( handle, INFINITE );	// 커널 오브젝트가 Signal(true) 상태면 진행, Non-Signal(false) 상태면 스레드가 잠듦. CPU 점유율을 낮추기 위해 사용
		// 다시 이 스레드가 실행이 되면, CreateEvent 함수의 bManualReset이 false(Auto)기 때문에
		// Signal 상태가 자동으로 Non-Signal 상태로 변경됨.

		unique_lock<mutex> lock{ m };
		
		if ( q.empty( ) == false ) {
			int32 data = q.front( );
			q.pop( );
			cout << data << endl;
		}
	}
}

int main()
{
	// 커널 오브젝트
	// Usage Count : 몇 개의 스레드가 이 오브젝트를 사용하고 있는지
	// Signal (파란불) / Non-Signal (빨간불) << bool
	// Auto / Manual << bool
	handle = ::CreateEvent( nullptr/*보안속성*/, false, false/*true : Signal, false : Non-Signal*/, nullptr );
	
	thread producer{ Producer };
	thread consumer{ Consumer };

	producer.join( );
	consumer.join( );

	::CloseHandle( handle );
}