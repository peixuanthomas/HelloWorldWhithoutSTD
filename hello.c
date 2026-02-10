#ifdef _WIN32
typedef void* HANDLE;
typedef unsigned long DWORD;

__declspec(dllimport) HANDLE __stdcall GetStdHandle(DWORD nStdHandle);
__declspec(dllimport) int __stdcall WriteConsoleA(
    HANDLE hConsoleOutput,
    const void* lpBuffer,
    DWORD nNumberOfCharsToWrite,
    DWORD* lpNumberOfCharsWritten,
    void* lpReserved
);

#define STD_OUTPUT_HANDLE ((DWORD)-11)
#else
typedef unsigned long DWORD;
typedef unsigned long size_t;
typedef long ssize_t;
extern ssize_t write(int fd, const void* buf, size_t count);
#endif

int main() {
#if defined(_WIN32)
    const char* message = "hello world from windows\n";
#elif defined(__linux__)
    const char* message = "hello world from linux\n";
#elif defined(__APPLE__)
    const char* message = "hello world from OSX\n";
#else
    const char* message = "hello world from unknown\n";
#endif
    DWORD written;

    int length = 0;
    while (message[length] != '\0') {
        length++;
    }

#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    WriteConsoleA(console, message, length, &written, 0);
#else
    write(1, message, (size_t)length);
#endif

    return 0;
}
