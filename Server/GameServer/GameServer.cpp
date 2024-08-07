#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

vector<int32> v;

// Mutual Exlusive (상호배타적)
mutex m;

// RAII (Resource Acquisition Is Initialization)
// mutex의 lock, uulock을 생성자, 소멸자에서 처리하면 편리하다.
template<class T>
class LockGuard		// 표준에 std::lock_guard가 있음. LockGuard는 느낌을 파악하기 위함.
{
public:
	LockGuard( T& mutex )
		: mutex_( &mutex )
	{
		mutex_->lock( );
	}

	~LockGuard( )
	{
		mutex_->unlock( );
	}

private:
	T* mutex_;
};

void Push( )
{
	for ( int32 i = 0; i < 10000; ++i ) {
		// 자물쇠 잠그기
		LockGuard<std::mutex> lockGuard{ m };	// std::lock_guard<std::mutex> lockGuard{ m }; 와 같음.

		// std::unique_lock<std::mutex> uniqueLock{ m, std::defer_lock };
		// defer_lock : lock을 하지 않고 생성만 함. 나중에 lock을 하기 위함.
		// uniqueLock.lock( );	// lock을 하고 싶을 때 사용.
		// 소멸자에서 unlock을 하기 때문에 unlock을 하지 않아도 됨.

		//m.lock( );
		//m.lock( );	// 재귀 lock 허용하는 경우도 있음.

		v.push_back( i );

		if ( i == 5000 )
			break;

		// 자물쇠 풀기
		//m.unlock( );
		//m.unlock( );
	}
}

int main()
{
	std::thread t1{ Push };
	std::thread t2{ Push };

	t1.join( );
	t2.join( );

	cout << v.size( ) << endl;
}