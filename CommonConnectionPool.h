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
ʵ�����ӳع���ģ��
*/

// ���ж���߳�ȥ�������ӳأ���д���̰߳�ȫ�ĵ���
class ConnectionPool {
public:
	// ��ȡ���ӳض���ʵ��
	static ConnectionPool* get_connection_pool();

	// ���ⲿ�ṩ�ӿڣ������ӳ��л�ȡ���õĿ�������
	// ͨ������ָ���Զ������ⲿ�����ӣ�����Ҫ�û��ֶ��ͷ�
	// ����Ҫ�ض�������ָ���ɾ����ʽ�������ӹ黹������
	shared_ptr<Connection> get_connection();     
private:
	static ConnectionPool pool;
	ConnectionPool();
	bool load_config();             // �������ļ��м�������
	void produce_conn_task();       // �����ڶ������߳��У����������µ�����
	void scan_conn_task();       // ɨ�賬������ʱ��_max_idle_time�����ӽ��л���

	string _ip;
	unsigned short _port;
	string _username;
	string _password;
	string _dbname;
	int _init_size;               // ���ӳصĳ�ʼ������
	int _max_size;                // ���ӳص����������
	int _max_idle_time;           // ���ӳ�������ʱ��
	int _connection_timeout;      // ���ӳػ�ȡ���ӵĳ�ʱʱ��
	
	queue<Connection*> _connection_queue;   // ���Ӷ���
	mutex _queue_mutex;          // ά�����Ӷ��е��̰߳�ȫ�Ļ�����
	atomic_int _connection_cnt;  // ���ӵ����������ᳬ��_max_size
	condition_variable cv;       // ���������������������������̺߳����������̵߳�ͨ��
};
