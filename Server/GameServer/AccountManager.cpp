#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

void AccountManager::ProcessLogin( )
{
	// accountLock
	lock_guard<mutex> guard{ mutex_ };

	// userLock
	User* user = UserManager::Instance( ).GetUser( 100 );

	// TODO
}