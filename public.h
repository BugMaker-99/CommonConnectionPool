#pragma once

#define LOG(info) \
	cout << __FILE__ << " : " << __LINE__ << " " << \
	__TIMESTAMP__ << " : " << info <<endl;

