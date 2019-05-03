#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

void print_array(multiset<char> &multi_container) {
  multiset<char>::iterator multi_iter;
  multi_iter = multi_container.begin();

  for (int i = 1; multi_iter != multi_container.end(); ++i, ++multi_iter) {
    cout << *multi_iter << " ";
  }
  cout << endl << endl;
}

void array_fill(multiset<char> &multi_container) {
  char item;

  cout << "Введите 5 элементов массива: " << endl;
  for (int i = 0; i < 5; ++i) {
    cin >> item;
    multi_container.insert(item);
  } //Заполнение массива
  cout << endl;
  print_array(multi_container);
}

void delete_elem(multiset<char> &multi_container) {
  char del_item;

  cout << "Введите значение элемента, который будет удален\\ны: " << endl;
  cin >> del_item;
  multi_container.erase(del_item); //Удаление элемента
  print_array(multi_container);
}

void modify_elem(multiset<char> &multi_container) {
  char wrong_elem;
  char right_elem;
  multiset<char>::size_type num_wrong;

  cout << "Введите значение, которое нужно заменить: " << endl;
  cin >> wrong_elem;
  cout << "Введите значение, на которое нужно заменить предыдущее: " << endl;
  cin >> right_elem;

  num_wrong = multi_container.erase(wrong_elem);
  if (num_wrong > 0) { //Замена элемента
    vector<char> right_vect(num_wrong, right_elem);
    multi_container.insert(right_vect.begin(), right_vect.end());
  } else
    cout << "Отсутствует элемент с искомым значением." << wrong_elem << endl;
  print_array(multi_container);
}

void another_modify(multiset<char> &multi_container) {
  int count;
  char start_elem;
  multiset<char>::iterator begin_multi_iter;
  multiset<char>::iterator end_multi_iter;

  cout << "Введите значение элемента, с которого начнется удаление: " << endl;
  cin >> start_elem;
  cout << "Введите количество удаляемых элементов: " << endl;
  cin >> count;

  begin_multi_iter = multi_container.find(start_elem);
  end_multi_iter = begin_multi_iter;
  begin_multi_iter++;
  for (int i = 0; i <= count; i++) {
    end_multi_iter++;
    if (end_multi_iter == multi_container.end())
      break;
  }
  multi_container.erase(begin_multi_iter, end_multi_iter);
  print_array(multi_container);
}

void concat_arrays(multiset<char> &multi_container1,
                   multiset<char> &multi_container2) {
  multiset<char>::iterator begin_iter;
  multiset<char>::iterator end_iter;

  begin_iter = multi_container2.begin();
  end_iter = multi_container2.end();
  for (int i = 1; begin_iter != end_iter; i++, begin_iter++) {
    multi_container1.insert(*begin_iter);
  }
  cout << "Итоговый первый массив: " << endl;
  print_array(multi_container1);
  cout << "Итоговый второй массив: " << endl;
  print_array(multi_container2);
}

int main() {
  setlocale(LC_ALL, "Russian");
  multiset<char> multi_container1;
  multiset<char> multi_container2;
  multiset<char>::iterator multi_iter;
  // Пункт 1, 2
  array_fill(multi_container1);
  // Пункт 3, 4
  delete_elem(multi_container1);
  modify_elem(multi_container1);
  // Пункт 5
  array_fill(multi_container2);
  // Пункт 6
  another_modify(multi_container1);
  // Пункт 7
  concat_arrays(multi_container1, multi_container2);
  cout << endl;

  return 0;
}
