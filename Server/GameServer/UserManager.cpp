#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

void UserManager::ProcessSave( )
{
	// userLock
	//lock_guard<mutex> guard{ mutex_ };

	// accountLock
	//Account* account = AccountManager::Instance( ).GetAccount( 100 );

	// �ذ� ���
	// ProcessSave�� ProcessLogin �Լ����� ������ lock�� ��� ������ �����ϰ� �����ش�.

	// accountLock
	Account* account = AccountManager::Instance( ).GetAccount( 100 );

	// userLock
	lock_guard<mutex> guard{ mutex_ };


	// TODO
}