#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

void UserManager::ProcessSave( )
{
	// userLock
	//lock_guard<mutex> guard{ mutex_ };

	// accountLock
	//Account* account = AccountManager::Instance( ).GetAccount( 100 );

	// 해결 방법
	// ProcessSave와 ProcessLogin 함수에서 각각의 lock을 얻는 순서를 동일하게 맞춰준다.

	// accountLock
	Account* account = AccountManager::Instance( ).GetAccount( 100 );

	// userLock
	lock_guard<mutex> guard{ mutex_ };


	// TODO
}