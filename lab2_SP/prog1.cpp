#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

void print_array(multiset<int> &multi_container) {
  multiset<int>::iterator multi_iter;
  multi_iter = multi_container.begin();

  for (int i = 1; multi_iter != multi_container.end(); ++i, ++multi_iter) {
    cout << *multi_iter << " ";
  }
  cout << endl << endl;
}

void array_fill(multiset<int> &multi_container) {
  int number;

  cout << "Введите 5 целых чисел: " << endl;
  for (int i = 0; i < 5; ++i) {
    cin >> number;
    multi_container.insert(number);
  } //Заполнение массива
  cout << endl;
  print_array(multi_container);
}

void delete_elem(multiset<int> &multi_container) {
  int del_num;

  cout << "Введите значение элемента, который будет удален\\ны: " << endl;
  cin >> del_num;
  multi_container.erase(del_num); //Удаление элемента
  print_array(multi_container);
}

void modify_elem(multiset<int> &multi_container) {
  int wrong_elem;
  int right_elem;
  multiset<int>::size_type num_wrong;

  cout << "Введите значение, которое нужно заменить: " << endl;
  cin >> wrong_elem;
  cout << "Введите значение, на которое нужно заменить предыдущее: " << endl;
  cin >> right_elem;

  num_wrong = multi_container.erase(wrong_elem);
  if (num_wrong > 0) { //Замена элемента
    vector<int> right_vect(num_wrong, right_elem);
    multi_container.insert(right_vect.begin(), right_vect.end());
  } else
    cout << "Отсутствует элемент с искомым значением." << wrong_elem << endl;
  print_array(multi_container);
}

void another_modify(multiset<int> &multi_container) {
  int count;
  int start_elem;
  multiset<int>::iterator begin_multi_iter;
  multiset<int>::iterator end_multi_iter;

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

void concat_arrays(multiset<int> &multi_container1,
                   multiset<int> &multi_container2) {
  multiset<int>::iterator begin_iter;
  multiset<int>::iterator end_iter;

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
  multiset<int> multi_container1;
  multiset<int> multi_container2;
  multiset<int>::iterator multi_iter;

  array_fill(multi_container1);
  //  delete_elem(multi_container1);
  //  modify_elem(multi_container1);
  array_fill(multi_container2);
  another_modify(multi_container1);
  concat_arrays(multi_container1, multi_container2);
  cout << endl;

  return 0;
}
