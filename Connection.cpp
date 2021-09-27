#include <iostream>
#include "connection.h"
#include "public.h"

using namespace std;

Connection::Connection() {
	// ��ʼ�����ݿ�����
	// ʵ������malloc��һ��MYSQL�ṹ���С��ָ��
	_conn = mysql_init(nullptr);
}

Connection::~Connection() {
	// �ͷ����ݿ�������Դ
	if (_conn != nullptr) {
		mysql_close(_conn);
	}
}

bool Connection::connect(string ip, unsigned short port, string username, 
	string password, string dbname) {
	// �������ݿ�
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), username.c_str(),
		password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;
}

bool Connection::update(string sql) {
	// ���²��� insert��delete��update
	if (mysql_query(_conn, sql.c_str())) {
		LOG("����ʧ�ܣ�" + sql);
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(string sql) {
	// ��ѯ���� selete
	// mysql_query()����0˵���ɹ�����0ʧ��
	if (mysql_query(_conn, sql.c_str())) {
		LOG("��ѯʧ�ܣ�" + sql);
		return nullptr;
	}
	return mysql_use_result(_conn);
}
