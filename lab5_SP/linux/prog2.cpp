#include <QString>
#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <pthread.h>
#include <string>
#include <vector>

using namespace std;

typedef struct {
  map<QString, pair<int, double>> container;
  QString subString;
} params;

void bigram_generator(map<QString, pair<int, double>> &container) {
  //  QString alphabet = "abcdefghijklmnopqrstuvwxyz";
  QString alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
  int str_len;

  str_len = alphabet.length();
  for (int i = 0; i < str_len; i++) {
    for (int j = 0; j < str_len; j++) {
      container.insert(make_pair(
          QString("%1%2").arg(alphabet[i]).arg(alphabet[j]), make_pair(0, 0)));
    }
  }
}

void frequancy_sort(map<QString, pair<int, double>> &container) {
  vector<pair<QString, pair<int, double>>> vec(container.begin(),
                                               container.end());
  double another_sum = 0;

  sort(vec.begin(), vec.end(),
       [](const pair<QString, pair<int, double>> &l,
          const pair<QString, pair<int, double>> &r) {
         if (l.second != r.second)
           return l.second > r.second;

         return l.first > r.first;
       });

  for (auto const &pair : vec) {
    if (pair.second.second != 0.0) {
      cout << pair.first.toUtf8().constData() << ": " << pair.second.second
           << "%" << endl;
      another_sum += pair.second.second;
    }
  }

  cout << "Проверка суммы в %: " << another_sum << endl << endl;
}

void *bigram_counter(void *thread_data) {
  params *data = (params *)thread_data;
  double sum = 0;

  for (auto elem : data->container) {
    int ch = 0;
    ch = data->subString.count(elem.first);

    if (ch != 0) {
      sum += ch;
      data->container[elem.first].first = ch;
    }
  }

  for (auto elem : data->container) {
    if (elem.second.first != 0 and sum != 0.0) {
      data->container[elem.first].second = elem.second.first / sum * 100;
    }
  }

  cout << "Часть текста для анализа: " << data->subString.toUtf8().constData()
       << endl;

  frequancy_sort(data->container);
  pthread_exit(NULL);
}

int main() {
  setlocale(LC_ALL, "Russian");
  string source_text;
  QString convert_text;
  QString subString;
  int it = 0;
  double str_len;
  double part_len;
  int part;
  map<QString, pair<int, double>> container;

  bigram_generator(container);

  cout << "Введите текст для биграммного частотного анализа: " << endl;
  getline(cin, source_text);
  convert_text = QString::fromStdString(source_text).toLower();
  str_len = convert_text.length();

  cout << "На сколько частей поделить текст: " << endl;
  cin >> part;
  part_len = ceil(str_len / part);

  pthread_t threads[part];
  params threadData[part];

  for (int i = 0; i < part; i++) {
    if (it + part_len > str_len)
      subString = convert_text.mid(it, static_cast<int>(str_len - it));
    else
      subString = convert_text.mid(it, static_cast<int>(part_len));
    it += part_len;

    threadData[i].subString = subString;
    threadData[i].container = container;
    cout << "Поток: " << i << endl;
    pthread_create(&threads[i], NULL, bigram_counter, &threadData[i]);
  }

  for (int i = 0; i < part; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
