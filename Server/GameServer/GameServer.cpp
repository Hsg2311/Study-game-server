#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <future>

int64 Colculate( )
{
	int64 sum = 0;

	for ( int32 i = 0; i < 100'000; ++i ) {
		sum += i;
	}

	return sum;
}

void PromiseWorker( std::promise<string>&& promise )
{
	promise.set_value( "Secret Message" );
}

void TaskWorker( std::packaged_task<int64( void )>&& task )
{
	task( );
}

int main()
{
	{
		// 동기(synchronous) 실행
		//int64 sum = Colculate( );
		//std::cout << sum << std::endl;
	}

	// std::future
	{
		// 1) deffered -> lazy evaluation : 지연해서 실행하세요
		// 2) async -> 별도의 쓰레드를 만들어서 실행하세요 / 중점적으로 사용됨
		// 3) deffered | async -> 둘 중 알아서 골라주세요

		// 언젠가 미래에 결과물을 뱉어줄거야!
		std::future<int64> future = std::async( std::launch::async, Colculate );

		// TODO
		//std::future_status status = future.wait_for( 1ms );	// 미리 결과물이 준비되었는지 확인
		//if ( status == future_status::ready ) {

		//}

		int64 sum = future.get( );	// 결과물이 이제서야 필요하다!

		// 참고 : 클래스의 멤버 함수도 실행 가능
		class Knight
		{
		public:
			int64 GetHP( ) { return 100; }
		};

		Knight knight;
		std::future<int64> future2 = std::async( std::launch::async, &Knight::GetHP, knight );	// knight.GetHP( );
	}

	// std::promise
	{
		// 미래(std::future)에 결과물을 반환해줄거라 약속(std::promise) 해줘!
		std::promise<string> promise;
		std::future<string> future = promise.get_future( );

		thread t{ PromiseWorker, std::move( promise ) };

		string message = future.get( );
		cout << message << endl;

		t.join( );
	}

	// std::packaged_task
	{
		std::packaged_task<int64( void )> task( Colculate );	// Colculate 함수의 시그니처와 일치해야 함
		std::future<int64> future = task.get_future( );

		thread t{ TaskWorker, std::move( task ) };

		int64 sum = future.get( );
		cout << sum << endl;

		t.join( );
	}

	// 결론)
	// mutex, condition_variable까지 가지 않고 단순한 애들을 처리할 수 있는 방법에 대해 알아보았다.
	// 특히, 한 번 발생하는 이벤트에 유용하다!
	// 1) async
	// 원하는 함수를 비동기적으로 실행 / 비동기와 멀티쓰레드는 다르다. deffered 같은 경우에는 실행 시점에 지연되는 것일 뿐이기 때문이다.
	// 2) promise
	// 결과물을 promise를 통해 future로 받아줌
	// 3) packaged_task
	// 원하는 함수의 실행 결과를 packaged_task를 틍해 future로 받아줌

}