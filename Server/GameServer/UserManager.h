#pragma once
#include <mutex>

class User
{
	// TODO
};

class UserManager
{
public:
	static UserManager& Instance( )
	{
		static UserManager instance;
		return instance;
	}

	User* GetUser( int32 id )
	{
		lock_guard<mutex> guard{ mutex_ };
		// ¹º°¡¸¦ °®°í ¿È.
		return nullptr;
	}

	void ProcessSave( );

private:
	mutex mutex_;
};

