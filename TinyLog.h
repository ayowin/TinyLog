
#ifndef __TINYLOG_H__
#define __TINYLOG_H__

#include <iostream>

class TinyLog
{
public:
	enum LEVEL{
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		FATAL
	};
	enum MODE {
		SINGLE_THREAD,
		MULTI_THREAD
	};

	static void debug(const char* format,...);
	static void info(const char* format, ...);
	static void warning(const char* format, ...);
	static void error(const char* format, ...);
	static void fatal(const char* format, ...);

	static void setStorageLevel(int level);
	static void setSingleMaxSize(int size);
	static void setStorageDir(const char* dir);
	static void setLogMode(int mode);

private:
	static int fileSize(const char* path);
	static void logConstruct(const int& level,
		const char* format,
		va_list args);
	static void singleThreadConstruct(const int& level,
		const char* format,
		va_list args);
	static void multiThreadConstruct(const int& level,
		const char* format,
		va_list args);

private:
	static int storageLevel;
	static int singleMaxSize;
	static std::string storageDir;
	static int logMode;
};

#endif