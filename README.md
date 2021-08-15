# TinyLog

> 跨平台的C++日志库



[toc]

## 1 枚举说明

### 1.1 LEVEL

```cpp
enum LEVEL{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};
```

日志等级，分别为DEBUG、INFO、WARNING、ERROR、FATAL，即调试、信息、警告、错误、严重错误

### 1.2 MODE

```cpp
enum MODE {
    SINGLE_THREAD,
    MULTI_THREAD
};
```

日志模式，分别为SINGLE_THREAD、MULTI_THREAD，即单线程、多线程模式。



## 2 函数说明

### 2.1 debug/info/warning/error/fatal

```cpp
static void debug(const char* format,...);
static void info(const char* format, ...);
static void warning(const char* format, ...);
static void error(const char* format, ...);
static void fatal(const char* format, ...);
```

这几个函数与printf保持一致的使用方法，同printf使用即可。

### 2.2 setStorageLevel

```cpp
static void setStorageLevel(int level);
```

设置持久化等级，即持久化到文件的日志等级，大于等于level的日志等级将会持久化到文件中，level对应枚举LEVEL的值。

### 2.3 setSingleMaxSize

```cpp
static void setSingleMaxSize(int size);
```

设置单个日志文件的最大大小，当日志文件大小大于size值时，会新建另一个文件存储，默认值为10MB。

### 2.4 setStorageDir

```cpp
static void setStorageDir(const char* dir);
```

设置持久化的目录，日志文件的目录，默认值为./log。

### 2.5 setLogMode

```cpp
static void setLogMode(int mode);
```

设置日志运行模式，mode对应枚举MODE的值，默认值为MULTI_THREAD，即以多线程模式运行日志。

