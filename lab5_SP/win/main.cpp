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
#include <fcntl.h>

//#pragma execution_character_set("utf-8")

using namespace std;

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
            temp_str = source_text.substr(static_cast<unsigned long long int>(i),
                                          static_cast<unsigned long long int>(2));

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

int wmain(int argc, wchar_t *argv[]) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Russian");
    map<wstring, pair<int, double>> container;
    bigram_generator(container);

    bigram_counter(wstring(argv[1]), container);

    return 0;
}