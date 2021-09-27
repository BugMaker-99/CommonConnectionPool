#pragma once
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <memory>
#include <functional>
#include "Connection.h"

using namespace std;

/*
实现连接池功能模块
*/

// 会有多个线程去创建连接池，需写成线程安全的单例
class ConnectionPool {
public:
	// 获取连接池对象实例
	static ConnectionPool* get_connection_pool();

	// 给外部提供接口，从连接池中获取可用的空闲连接
	// 通过智能指针自动管理外部的连接，不需要用户手动释放
	// 还需要重定义智能指针的删除方式，把连接归还到队列
	shared_ptr<Connection> get_connection();     
private:
	static ConnectionPool pool;
	ConnectionPool();
	bool load_config();             // 从配置文件中加载数据
	void produce_conn_task();       // 运行在独立的线程中，负责生产新的连接
	void scan_conn_task();       // 扫描超过空闲时间_max_idle_time的连接进行回收

	string _ip;
	unsigned short _port;
	string _username;
	string _password;
	string _dbname;
	int _init_size;               // 连接池的初始连接量
	int _max_size;                // 连接池的最大连接量
	int _max_idle_time;           // 连接池最大空闲时间
	int _connection_timeout;      // 连接池获取连接的超时时间
	
	queue<Connection*> _connection_queue;   // 连接队列
	mutex _queue_mutex;          // 维护连接队列的线程安全的互斥锁
	atomic_int _connection_cnt;  // 连接的总数，不会超过_max_size
	condition_variable cv;       // 设置条件变量，用于连接生产线程和连接消费线程的通信
};
