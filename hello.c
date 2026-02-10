#ifdef _WIN32
// 手动声明需要的类型和常量
typedef void* HANDLE;
typedef unsigned long DWORD;

// 手动声明Windows API函数
__declspec(dllimport) HANDLE __stdcall GetStdHandle(DWORD nStdHandle);
__declspec(dllimport) int __stdcall WriteConsoleA(
    HANDLE hConsoleOutput,
    const void* lpBuffer,
    DWORD nNumberOfCharsToWrite,
    DWORD* lpNumberOfCharsWritten,
    void* lpReserved
);

// 定义常量
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#else
// 非Windows：手动声明 write 所需类型与函数
typedef unsigned long DWORD;
typedef unsigned long size_t;
typedef long ssize_t;
extern ssize_t write(int fd, const void* buf, size_t count);
#endif

int main() {
    const char* message = "Hello World!\n";
    DWORD written;

    // 计算字符串长度
    int length = 0;
    while (message[length] != '\0') {
        length++;
    }

#ifdef _WIN32
    // 获取标准输出句柄
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // 写入控制台
    WriteConsoleA(console, message, length, &written, 0);
#else
    // 写入标准输出
    write(1, message, (size_t)length);
#endif

    return 0;
}
