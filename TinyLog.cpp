
#include "TinyLog.h"

#include <stdarg.h>
#include <mutex>
#include <string>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

int TinyLog::storageLevel = TinyLog::INFO; /* storage to file , default INFO */

int TinyLog::singleMaxSize = 10485760; /* unit£ºByte£¬default 10MB */

std::string TinyLog::storageDir = "./log"; /* storage to dir , default ./log */

void TinyLog::debug(const char* format, ...) 
{
	va_list args;
	va_start(args, format);

	logConstruct(TinyLog::DEBUG, format, args);

	va_end(args);
}

void TinyLog::info(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	logConstruct(TinyLog::INFO, format, args);
	
	va_end(args);
}

void TinyLog::warning(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	logConstruct(TinyLog::WARNING, format, args);

	va_end(args);
}

void TinyLog::error(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	logConstruct(TinyLog::ERROR, format, args);

	va_end(args);
}

void TinyLog::fatal(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	logConstruct(TinyLog::FATAL, format, args);

	va_end(args);
}

void TinyLog::setStorageLevel(int level)
{
	switch (level)
	{
	case TinyLog::DEBUG:
		storageLevel = TinyLog::DEBUG;
		break;
	case TinyLog::INFO:
		storageLevel = TinyLog::INFO;
		break;
	case TinyLog::WARNING:
		storageLevel = TinyLog::WARNING;
		break;
	case TinyLog::ERROR:
		storageLevel = TinyLog::ERROR;
		break;
	case TinyLog::FATAL:
		storageLevel = TinyLog::FATAL;
		break;
	default:
		break;
	}
}

void TinyLog::setSingleMaxSize(int size)
{
	singleMaxSize = size;
}

void TinyLog::setStorageDir(const char* dir)
{
	storageDir = dir;
}

void TinyLog::logConstruct(const int& level,
	const char* format,
	va_list args)
{
	const char* logLevel = NULL;
	switch (level)
	{
	case TinyLog::DEBUG:
		logLevel = "DEBUG";
		break;
	case TinyLog::INFO:
		logLevel = "INFO";
		break;
	case TinyLog::WARNING:
		logLevel = "WARNING";
		break;
	case TinyLog::ERROR:
		logLevel = "ERROR";
		break;
	case TinyLog::FATAL:
		logLevel = "FATAL";
		break;
	default:
		logLevel = "";
		break;
	}

	time_t tt = time(NULL);
	tm* t = localtime(&tt);

#ifdef _WIN32
	mkdir(storageDir.c_str());
#else
	mkdir(storageDir.c_str(), 0777);
#endif

	static std::mutex mutex;
	mutex.lock();

	static char content[2048] = { 0 };
	static char log[2098] = { 0 };
	memset(content, 0, sizeof(content));
	memset(log, 0, sizeof(log));

	vsprintf(content, format,args);
	sprintf(log,
		"[%s] [%d-%02d-%02d %02d:%02d:%02d] %s",
		logLevel,
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec,
		content);
	printf("%s", log);

	if(level >= storageLevel)
	{
		static std::string filename = storageDir + "/tiny.log";
		if (fileSize(filename.c_str()) > singleMaxSize)
		{
			std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			long long msTimestamp = now.count();
			std::string backupFilename = filename + "." + std::to_string(msTimestamp);
			rename(filename.c_str(), backupFilename.c_str());
		}
		else
		{
			static FILE *fp = NULL;
			fp = NULL;
			fp = fopen(filename.c_str(), "a+");
			if (fp != NULL)
			{
				fputs(log, fp);
				fclose(fp);
				fp = NULL;
			}
			else
			{
				printf("[TinyLog::logConstruct]: open or create log file failed,"
					"please check file permission.\n");
			}
		}
	}

	mutex.unlock();
}

int TinyLog::fileSize(const char *path)
{
	int size = -1;
	FILE *fp = fopen(path, "r");
	if (fp)
	{
		fseek(fp, 0L, SEEK_END);
		size = ftell(fp);
		fclose(fp);
	}
	return size;
}