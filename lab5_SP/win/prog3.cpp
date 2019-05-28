#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <wchar.h>
#include <vector>
#include <process.h>
#include <cwchar>
#include <codecvt>
#include <locale>
#include <io.h>
#include <Windows.h>
#include <fcntl.h>
#include <cstdio>

using namespace std;

const int part = 3;
HANDLE ghMutex;

typedef struct {
    map<wstring, pair<int, double>> container;
    wstring subString;
} params;

void bigram_generator(map<wstring, pair<int, double>> &container) {
    //  wchar_t *alphabet = "abcdefghijklmnopqrstuvwxyz";
    wstring alphabet[] = {L"а", L"б", L"в", L"г", L"д", L"е", L"ё", L"ж", L"з", L"и", L"й", L"к", L"л", L"м", L"н",
                          L"о", L"п", L"р", L"с", L"т", L"у", L"ф", L"х", L"ц", L"ч", L"ш", L"щ", L"ъ", L"ы", L"ь",
                          L"э", L"ю", L"я"};
    size_t str_len;

    str_len = (sizeof(alphabet) / sizeof(*alphabet));

    for (int i = 0; i < str_len; i++) {
        for (int j = 0; j < str_len; j++) {
            container.insert(make_pair(
                    alphabet[i] + alphabet[j], make_pair(0, 0)));
        }
    }
}


void frequancy_sort(map<wstring, pair<int, double>> &container) {
    vector<pair<wstring, pair<int, double>>> vec(container.begin(),
                                                 container.end());
    double another_sum = 0;

    sort(vec.begin(), vec.end(),
         [](const pair<wstring, pair<int, double>> &l,
            const pair<wstring, pair<int, double>> &r) {
             if (l.second != r.second)
                 return l.second > r.second;

             return l.first > r.first;
         });

    for (auto const &pair : vec) {
        if (pair.second.second != 0.0) {
            wcout << pair.first << ": " << pair.second.second
                  << "%" << endl;
            another_sum += pair.second.second;
        }
    }

    wcout << L"Проверка суммы в %: " << another_sum << endl << endl;
}

void bigram_counter(wstring source_text, map<wstring, pair<int, double>> container) {
    double sum = 0;
    wstring temp_str;
    int ch;

    for (auto const &elem : container) {
        ch = 0;

        for (size_t i = 0; i < source_text.length(); i++) {
            temp_str = source_text.substr(static_cast<unsigned int>(i),
                                          static_cast<unsigned int>(2));

            if (temp_str.compare(elem.first) == 0) { ch = ch + 1; }
        }
        if (ch != 0) {
            sum += ch;
            container[elem.first].first = ch;
        }
    }

    for (auto &elem : container) {
        if (elem.second.first != 0 && sum != 0.0) {
            container[elem.first].second = elem.second.first / sum * 100;
        }
    }

    frequancy_sort(container);
}

DWORD WINAPI ThreadFunc(void *thread_data) {
    WaitForSingleObject(ghMutex, INFINITE);
    params *data = (params *) thread_data;
    bigram_counter(data->subString, data->container);

    DWORD dwResult = 0;
    ReleaseMutex(ghMutex);
    return dwResult;
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    wstring text;
    double part_len;
    size_t str_len;
    wstring subString;
    double it = 0;
    map<wstring, pair<int, double>> container;

    ghMutex = CreateMutex(
            NULL,              // default security attributes
            FALSE,             // initially not owned
            NULL);             // unnamed mutex

    if (ghMutex == NULL)
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return 1;
    }

    bigram_generator(container);

    wcout << L"Введите текст для биграммного частотного анализа: " << endl;
    getline(wcin, text);
    str_len = text.length();

//    wcout << L"На сколько частей поделить текст: " << endl;

    part_len = ceil(str_len / part);

    DWORD dwThreadId[part];
    HANDLE hThread[part];
    params threadData[part];

    for (int i = 0; i < part; i++) {
        if (it + part_len > str_len)
            subString = text.substr(static_cast<unsigned int>(it),
                                    static_cast<unsigned int>(str_len - it));
        else
            subString = text.substr(static_cast<unsigned int>(it),
                                    static_cast<unsigned int>(part_len));
        it += part_len;

        wcout << L"Часть текста для анализа: " << subString << endl;

        threadData[i].subString = subString;
        threadData[i].container = container;

        hThread[i] = CreateThread(NULL, 0, ThreadFunc, &threadData[i], 0, &dwThreadId[i]);
        if (!hThread) printf("main process: thread %d not execute!", i);
    }
    WaitForMultipleObjects(part, hThread, TRUE, INFINITE);

    for(int i=0; i < part; i++ )
        CloseHandle(hThread[i]);

    CloseHandle(ghMutex);

    return 0;
}
