#pragma once
#include <mysql.h>
#include <ctime>
#include <iostream>

using namespace std;

/*
实现MySQL数据库的CURD
*/

class Connection {
public:
	// 初始化数据库连接
	Connection();
	
	// 释放数据库连接资源
	~Connection();

	// 连接数据库
	bool connect(
		string ip,
		unsigned short port,
		string username,
		string password,
		string dbname
	);

	// 更新操作 insert、delete、update
	bool update(string sql);

	// 查询操作 selete
	MYSQL_RES* query(string sql);

	// 刷新连接的起始空闲时间点
	void set_start_time() {
		_free_start_time = clock();
	}

	// 返回空闲状态存活的时间
	clock_t get_free_time() {
		return clock() - _free_start_time;
	}

private:
	MYSQL* _conn;                    // 表示和MySQL服务器的一条连接
	clock_t _free_start_time;        // 记录进入空闲状态后的起始时间
};