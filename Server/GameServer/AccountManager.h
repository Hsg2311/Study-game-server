#pragma once
#include <mutex>

class Account
{
	// TODO
};

class AccountManager
{
public:
	static AccountManager& Instance( )
	{
		static AccountManager instance;
		return instance;
	}

	Account* GetAccount( int32 id )
	{
		lock_guard<mutex> guard{ mutex_ };
		// ¹º°¡¸¦ °®°í ¿È.
		return nullptr;
	}

	void ProcessLogin( );

private:
	mutex mutex_;
	//map<int32, Account*> accounts_;
};
