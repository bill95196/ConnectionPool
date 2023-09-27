# C++ MySQL Connection Pool

## Overview

The C++ MySQL Connection Pool is a robust and efficient solution designed to optimize database access, enhance performance, and reduce bottlenecks in high-traffic scenarios. This project leverages various technologies and concepts, including MySQL database programming, the Singleton design pattern, C++11 multithreading, thread synchronization, and more, to provide a reliable and scalable connection pool for MySQL database interactions.

## Project Structure

The project is organized into several key components:

- **ConnectionPool.cpp/ConnectionPool.h:** The core of the project, where the connection pool logic is implemented.
- **Connection.cpp/Connection.h:** Contains the database interaction code, including CRUD (Create, Read, Update, Delete) operations.

## Features

- **Singleton Design:** The connection pool is designed as a Singleton, ensuring that only one instance exists, optimizing resource utilization.

- **Thread-Safe Connection Management:** Idle connections are securely stored in a thread-safe Connection queue, using mutex locks to guarantee safe concurrent access.

- **Dynamic Connection Creation:** If the connection pool is empty, it dynamically creates new connections, adhering to a specified maximum limit (maxsize).

- **Idle Connection Management:** Connections idle for longer than maxIdleTime are released to maintain an optimal connection pool size, executed in a separate thread.

- **Connection Timeouts:** Implements connection timeouts, ensuring that connections are not held indefinitely. Connections exceeding maxIdleTime are released, retaining only the initial initsize connections.

- **Smart Pointer Management:** Utilizes shared_ptr for connection management, with custom lambda expressions to safely return connections to the pool.

- **Producer-Consumer Thread Model:** Follows a producer-consumer threading model, incorporating synchronization techniques such as mutexes and condition variables for inter-thread communication.

## Stress Testing

The project has undergone rigorous stress testing to evaluate its performance and stability under extreme conditions. Stress tests were conducted to measure the system's behavior and performance when subjected to high levels of concurrent data insertion operations. The results demonstrated the system's capacity to handle heavy workloads and the effectiveness of the connection pool in maintaining stability and performance under extreme conditions.

## Development Platform

The project was developed in C++ and is platform-independent, allowing for compilation and execution using the GNU Compiler Collection (GCC) on various platforms.

## Usage

1. Clone the repository.
2. Build the project using your preferred C++ compiler.
3. Incorporate the ConnectionPool and Connection classes into your application.
4. Configure the connection pool parameters as needed, such as maximum connection limit, initial pool size, and connection timeouts.
5. Utilize the connection pool to efficiently manage MySQL database connections in your application.

```cpp
// Example usage in your application

#include "pch.h"
#include <iostream>
using namespace std;
#include "Connection.h"
#include "CommonConnectionPool.h"

int main()
{
	Connection conn;
	conn.connect("127.0.0.1", 3306, "root", "8888", "chat");


	clock_t begin = clock();
	
	thread t1([]() {
		//ConnectionPool *cp = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i)
		{
			/*char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			shared_ptr<Connection> sp = cp->getConnection();
			sp->update(sql);*/
			Connection conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql);
		}
	});
	thread t2([]() {
		//ConnectionPool *cp = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i)
		{
			/*char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			shared_ptr<Connection> sp = cp->getConnection();
			sp->update(sql);*/
			Connection conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql);
		}
	});
	thread t3([]() {
		//ConnectionPool *cp = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i)
		{
			/*char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			shared_ptr<Connection> sp = cp->getConnection();
			sp->update(sql);*/
			Connection conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql);
		}
	});
	thread t4([]() {
		//ConnectionPool *cp = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i)
		{
			/*char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			shared_ptr<Connection> sp = cp->getConnection();
			sp->update(sql);*/
			Connection conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql);
		}
	});

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;
    return 0;
}
