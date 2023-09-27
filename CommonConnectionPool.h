#pragma once
/* connection pool function*/
#include <string>
#include <queue>
#include <mutex>
#include "Connection.h"
#include <atomic>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <memory>
#include <functional>

using namespace std;

class ConnectionPool
{
public:
	// GET CONNECTIONPOOL INSTANCE
	static ConnectionPool* getConnectionPool();
	// provide a interface, give a idle connection
	shared_ptr<Connection> getConnection();

private:
	ConnectionPool(); //singelton
	

	bool loadConfigFile(); //load configuration
	
	// run independent thread, it's for producing new connection
	void produceConnectionTask();
	
	
	string _ip;  //mysql id address
	unsigned short _port;  //port 3306
	string _username;     
	string _password;
	string _dbname; //database name
	int _initSize;    // initilize connection number
	int _maxSize;        // connection pool max number
	int _maxIdleTime;             // max idle time 
	int _connectionTimeout;           // max timeout 

	queue<Connection*> _connectionQue;    //queue store mysql connection 

	mutex _queueMutex; //maintain thread safety locker 

	atomic_int _connectionCnt; // record the connection number in queue   normal ++ not thread safe. atomic int is threading safety

	condition_variable cv; //set conditional variable, for connection produce thread and connection consumer thread communicate
};