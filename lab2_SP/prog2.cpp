#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

void show_queue(queue<char> queue_container) {
  while (!queue_container.empty()) {
    cout << queue_container.front() << " ";
    queue_container.pop();
  }
  cout << endl;
}

void queue_fill(queue<char> &queue_container) {
  char item;

  cout << "Введите 5 элементов очереди: " << endl;
  for (int i = 0; i < 5; ++i) {
    cin >> item;
    queue_container.push(item);
  }
  cout << "Очередь: ";
  show_queue(queue_container);
}

void sort_queue(queue<char> &queue_container, bool great) {
  // Логика работы: Перекидываем очередь в вектор, сортируем вектор,
  // перекидываем отсортированные элементы из вектора в очередь.
  vector<char> q_vector;

  while (!queue_container.empty()) {
    q_vector.push_back(queue_container.front());
    queue_container.pop();
  }

  if (great == true) {
    sort(q_vector.begin(), q_vector.end(), greater<char>());
  } else {
    sort(q_vector.begin(), q_vector.end());
  }

  for (auto item : q_vector) {
    queue_container.push(item);
  }
  cout << "Отсортировано: ";
  show_queue(queue_container);
}

void send_elem(queue<char> &queue_container1, queue<char> &queue_container2,
               char elem) {
  // Логика работы: Прогоняем цикл, перекидывая элементы из фронтовой
  // части очереди в конец. Как только находим нужный элемент: удаляем его из
  // первого контейнера и перекидываем во второй.
  char find_elem;

  for (string::size_type i = 0; i < queue_container1.size(); i++) {
    find_elem = queue_container1.front();
    if (find_elem == elem) {
      queue_container2.push(find_elem);
      queue_container1.pop();
      continue;
    }
    queue_container1.pop();
    queue_container1.push(find_elem);
  }
}

void merge_two_queues(queue<char> &queue_container1,
                      queue<char> &queue_container2,
                      queue<char> &queue_container3) {
  // Переводим очереди в вектора, мержим два вектора в третий, восстанавливаем
  // из него очередь.
  vector<char> q_vector1;
  vector<char> q_vector2;
  vector<char> q_vector3;

  while (!queue_container1.empty()) {
    q_vector1.push_back(queue_container1.front());
    queue_container1.pop();
  }

  while (!queue_container2.empty()) {
    q_vector2.push_back(queue_container2.front());
    queue_container2.pop();
  }
  merge(q_vector1.begin(), q_vector1.end(), q_vector2.begin(), q_vector2.end(),
        back_inserter(q_vector3));
  for (auto item : q_vector3) {
    queue_container3.push(item);
  }
}

void find_elem(queue<char> queue_container, char elem) {
  // Переводим очередь в вектор и используем функцию find для поиска.
  vector<char> q_vector;
  vector<char>::iterator it;

  while (!queue_container.empty()) {
    q_vector.push_back(queue_container.front());
    queue_container.pop();
  }

  it = find(q_vector.begin(), q_vector.end(), elem);
  if (it != q_vector.end())
    cout << "Элемент найден" << std::endl;
  else
    cout << "Элемент не найден" << std::endl;
}

void count_elems(queue<char> queue_container, char elem) {
  // Переводим очередь в вектор и используем функцию count для подсчета.
  vector<char> q_vector;
  long elem_count;

  while (!queue_container.empty()) {
    q_vector.push_back(queue_container.front());
    queue_container.pop();
  }
  elem_count = count(q_vector.begin(), q_vector.end(), elem);
  cout << "Количество заданных элементов в очереди: " << elem_count << endl;
}

int main() {
  setlocale(LC_ALL, "Russian");
  queue<char> queue_container1;
  queue<char> queue_container2;
  queue<char> queue_container3;
  char elem;

  // Пункт 1
  queue_fill(queue_container1);
  // Пункт 2, 3
  cout << "Сортировка первого контейнера по убыванию... ";
  sort_queue(queue_container1, true);
  // Пункт 4, 5
  cout << "Введите значения элементов, которые нужно переместить (пробел, "
          "чтобы закончить): ";
  while (cin.peek() != ' ') {
    cin.get(elem);
    send_elem(queue_container1, queue_container2, elem);
  }
  // Пункт 6
  cout << "Второй контейнер: ";
  show_queue(queue_container2);
  // Пункт 7, 8
  cout << "Сортировка первого контейнера... ";
  sort_queue(queue_container1, false);
  cout << "Сортировка второго контейнера... ";
  sort_queue(queue_container2, false);
  // Пункт 9, 10
  merge_two_queues(queue_container1, queue_container2, queue_container3);
  cout << "Третий контейнер: ";
  show_queue(queue_container3);
  // Пункт 11
  cout << "Введите значение элемента, количество которых нужно подсчитать: ";
  cin >> elem;
  count_elems(queue_container3, elem);
  // Пункт 12
  cout << "Введите значение элемента, который надо найти: ";
  cin >> elem;
  find_elem(queue_container3, elem);

  return 0;
}
