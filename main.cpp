#include <iostream>
#include "Connection.h"
#include "CommonConnectionPool.h"

using namespace std;

// 单线程，无连接池，5000次连接测试
void test1() {
	clock_t begin = clock();
	for (int i = 0; i < 5000; i++) {
		Connection conn;
		char sql[1024] = { 0 };
		sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
		conn.update(sql);
	}
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;
}

// 单线程，有连接池，5000次连接测试
void test2() {
	ConnectionPool* conn_pool = ConnectionPool::get_connection_pool();
	clock_t begin = clock();
	for (int i = 0; i < 5000; i++) {
		shared_ptr<Connection> conn_ptr = conn_pool->get_connection();
		char sql[1024] = { 0 };
		sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
		conn_ptr->update(sql);
	}
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;
}

// 四线程，无连接池，5000次连接测试
void test3() {
	clock_t begin = clock();
	thread t1([&]() {
		for (int i = 0; i < 1250; i++) {
			Connection conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql);
		}
	});
	thread t2([&]() {
		for (int i = 0; i < 1250; i++) {
			Connection conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql);
		}
	});
	thread t3([&]() {
		for (int i = 0; i < 1250; i++) {
			Connection conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql);
		}
	});
	thread t4([&]() {
		for (int i = 0; i < 1250; i++) {
			Connection conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
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
}

// 四线程，有连接池，5000次连接测试
void test4() {
	clock_t begin = clock();
	ConnectionPool* conn_pool = ConnectionPool::get_connection_pool();
	thread t1([&]() {
		shared_ptr<Connection> conn_ptr = conn_pool->get_connection();
		for (int i = 0; i < 1250; i++) {
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
			conn_ptr->update(sql);
		}
	});
	thread t2([&]() {
		shared_ptr<Connection> conn_ptr = conn_pool->get_connection();
		for (int i = 0; i < 1250; i++) {
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
			conn_ptr->update(sql);
		}
	});
	thread t3([&]() {
		shared_ptr<Connection> conn_ptr = conn_pool->get_connection();
		for (int i = 0; i < 1250; i++) {
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
			conn_ptr->update(sql);
		}
	});
	thread t4([&]() {
		shared_ptr<Connection> conn_ptr = conn_pool->get_connection();
		for (int i = 0; i < 1250; i++) {
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "shen", 20, "female");
			conn_ptr->update(sql);
		}
	});
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;
}

int main(){
	test3();

	return 0;
}
