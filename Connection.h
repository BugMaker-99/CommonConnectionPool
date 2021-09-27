#pragma once
#include <mysql.h>
#include <ctime>
#include <iostream>

using namespace std;

/*
ʵ��MySQL���ݿ��CURD
*/

class Connection {
public:
	// ��ʼ�����ݿ�����
	Connection();
	
	// �ͷ����ݿ�������Դ
	~Connection();

	// �������ݿ�
	bool connect(
		string ip,
		unsigned short port,
		string username,
		string password,
		string dbname
	);

	// ���²��� insert��delete��update
	bool update(string sql);

	// ��ѯ���� selete
	MYSQL_RES* query(string sql);

	// ˢ�����ӵ���ʼ����ʱ���
	void set_start_time() {
		_free_start_time = clock();
	}

	// ���ؿ���״̬����ʱ��
	clock_t get_free_time() {
		return clock() - _free_start_time;
	}

private:
	MYSQL* _conn;                    // ��ʾ��MySQL��������һ������
	clock_t _free_start_time;        // ��¼�������״̬�����ʼʱ��
};