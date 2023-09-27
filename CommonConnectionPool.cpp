#include "pch.h"
#include "CommonConnectionPool.h"


ConnectionPool* ConnectionPool::getConnectionPool()
{
	static ConnectionPool pool; //lock and unlock
	return &pool; 
}

bool ConnectionPool::loadConfigFile()
{
	FILE* pf = fopen("mysql.ini", "r");
	if (pf == nullptr) {
		LOG("mysql.init file is not exist");
		return false;
	}
	while (!feof(pf))
	{
		char line[1024] = { 0 };
		fgets(line, 1024, pf);
		string str = line;
		int idx = str.find('=', 0);
		if (idx == -1)
		{
			continue;
		}
		int endinx = str.find('\n', idx);
		string key = str.substr(0, idx);
		string value = str.substr(idx + 1, endinx - idx - 1);

		if (key == "ip")
		{
			_ip = value;

		}
		else if (key == "port")
		{
			_port = atoi(value.c_str());
		}
		else if (key == "username")
		{
			_username = value;
		}
		else if (key == "password")
		{
			_password = value;
		}
		else if (key == "dbname")
		{
			_dbname = value;
		}
		else if (key == "initSize")
		{
			_initSize = atoi(value.c_str());
		}
		else if (key == "maxSize")
		{
			_maxSize = atoi(value.c_str());
		}
		else if (key == "maxIdletime") {
			_maxIdleTime = atoi(value.c_str());
		}
		else if (key == "connectionTimeOut")
		{
			_connectionTimeout = atoi(value.c_str());
		}

		cout << endl;

	}
}

// connection pool construction 
ConnectionPool::ConnectionPool()
{
	if (!loadConfigFile())
	{
		return;
	}

	for (int i = 0; i < _initSize;++i)
	{
		Connection* p = new Connection();
		p->connect(_ip, _port, _username, _password, _dbname);
		_connectionQue.push(p);
		_connectionCnt++;
	}

	// start a new thread
	thread produce(bind(&ConnectionPool::produceConnectionTask, this));

}

void ConnectionPool::produceConnectionTask()
{
	for (;;)
	{
		unique_lock<mutex> lock(_queueMutex);
		while (!_connectionQue.empty())
		{
			cv.wait(lock);

		}

		// if not reach the max connection, continue create new connections
		if (_connectionCnt < _maxSize)
		{
			Connection* p = new Connection();
			p->connect(_ip, _port, _username, _password, _dbname);
			_connectionQue.push(p);
			_connectionCnt++;

		}

		// notify consumer thread, can be connected
		cv.notify_all();
	}

}