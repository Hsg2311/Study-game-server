#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

class SpinLock
{
public:
	void lock( )
	{
		// CAS (Compare-And-Swap)
		
		bool expected = false;
		bool desired = true;

		// CAS 의사 코드
		/*
		if ( locked_ == expected ) {
			expected = locked_;
			locked_ = desired;
			return true;
		}
		else {
			expected = locked_;
			return false;
		}
		*/
		// 위의 의사 코드가 아래의 atomic 타입의 compare_exchange_strong 함수로 대체되면서
		// atomic한 동작이 이루어짐.

		while ( locked_.compare_exchange_strong( expected, desired ) == false ) {
			expected = false;
		}
	}

	void unlock( )
	{
		//locked_ = false;
		locked_.store( false );
	}

private:
	atomic<bool> locked_ = false;
};

int32 sum = 0;
mutex m;
SpinLock spinLock;

void Add( )
{
	for ( int32 i = 0; i < 10'0000; ++i ) {
		lock_guard<SpinLock> guard{ spinLock };
		++sum;
	}
}

void Sub( )
{
	for ( int32 i = 0; i < 10'0000; ++i ) {
		lock_guard<SpinLock> guard{ spinLock };
		--sum;
	}
}

int main()
{
	thread t1{ Add };
	thread t2{ Sub };

	t1.join( );
	t2.join( );

	cout << sum << endl;
}