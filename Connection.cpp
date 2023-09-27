#include "pch.h"
#include "public.h"
#include "Connection.h"


// initialize database connection 
Connection::Connection()
{
	_conn = mysql_init(nullptr);
}

// release connection
Connection::~Connection()
{
	if (_conn != nullptr)
		mysql_close(_conn);
}
// connect database
bool Connection::connect(string ip, unsigned short port, string user, string password,
	string dbname)
{
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), user.c_str(),
		password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;
}
//  insert、delete、update
bool Connection::update(string sql)
{
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("Update failure:" + sql);
		return false;
	}
	return true;
}
//  select
MYSQL_RES* Connection::query(string sql)
{
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("Select failure:" + sql);
		return nullptr;
	}
	return mysql_use_result(_conn);
}