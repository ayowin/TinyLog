
#include <iostream>
#include <thread>

#include "TinyLog.h"

/**
* @brief 获取毫秒时间戳
*/
long long millisecondTimestamp()
{
	std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	long long msTimestamp = now.count();
	return msTimestamp;
}

int main(int argc,char** argv) 
{
	long timestamp = millisecondTimestamp();

	//TinyLog::setSingleMaxSize(1024000);
	TinyLog::setStorageLevel(TinyLog::DEBUG);

	for (int i = 0;i < 20;i++) {
		std::thread* thread = new std::thread([=]() {
			for (int j = 0;j < 5000;j++) {
				switch (i%5)
				{
				case 0:
					TinyLog::debug("thread %d log %d\n",i,j);
					break;
				case 1:
					TinyLog::info("thread %d log %d\n", i, j);
					break;
				case 2:
					TinyLog::warning("thread %d log %d\n", i, j);
					break;
				case 3:
					TinyLog::error("thread %d log %d\n", i, j);
					break;
				case 4:
					TinyLog::fatal("thread %d log %d\n", i, j);
					break;
				default:
					break;
				}
			}
		});
		thread->detach();
	}

	getchar();
	timestamp = millisecondTimestamp() - timestamp;
	printf("consume: %d ms\n", timestamp);
	return 0;
}