#pragma once
/* mysql database increase del change search */
#include <mysql.h>
#include <string>
#include "public.h"


// database operation class
class Connection
{
public:
	// initialize database connection 
	Connection();
	
	// release connection
	~Connection();

	// connect database
	bool connect(string ip, unsigned short port, string user, string password,
		string dbname);

	//  insert、delete、update
	bool update(string sql);

	// select
	MYSQL_RES* query(string sql);
private:
	MYSQL* _conn; // 表示和MySQL Server的一条连接
};