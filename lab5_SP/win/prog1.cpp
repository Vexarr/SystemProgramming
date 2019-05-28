#include <iostream>
#include <string>
#include <wchar.h>
#include <io.h>
#include <locale>
#include <fcntl.h>
#include <Windows.h>
#include <cstdio>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    wstring text;
    double part;
    double part_len;
    size_t str_len;
    wstring subString;
    double it = 0;

    wcout << L"Введите текст для биграммного частотного анализа: " << endl;
    getline(wcin, text);
    str_len = text.length();

    wcout << L"На сколько частей поделить текст: " << endl;
    wcin >> part;
    part_len = ceil(str_len / part);

    for (int i = 0; i < part; i++) {
        if (it + part_len > str_len)
            subString = text.substr(static_cast<unsigned int>(it),
                                    static_cast<unsigned int>(str_len - it));
        else
            subString = text.substr(static_cast<unsigned int>(it),
                                    static_cast<unsigned int>(part_len));
        it += part_len;

        wcout << L"Часть текста для анализа: " << subString << endl;
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        char OutString[500];
        sprintf(OutString, "\"C:\\Users\\Vexar\\Downloads\\win.exe\" \"%ls\"", subString.c_str());

        if (!CreateProcess(NULL,   // No module name (use command line)
                           (LPSTR) OutString,        // Command line
                           NULL,           // Process handle not inheritable
                           NULL,           // Thread handle not inheritable
                           FALSE,          // Set handle inheritance to FALSE
                           0,              // No creation flags
                           NULL,           // Use parent's environment block
                           NULL,           // Use parent's starting directory
                           &si,            // Pointer to STARTUPINFO structure
                           &pi)           // Pointer to PROCESS_INFORMATION structure
                ) {
            printf("CreateProcess failed (%d).\n", GetLastError());
            return 0;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

    }

    return 0;
}

