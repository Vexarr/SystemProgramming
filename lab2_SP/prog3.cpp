#include <iostream>

using namespace std;

template <typename T> class MyTest {
public:
  MyTest(T value1, T value2) {
    this->value1 = value1;
    this->value2 = value2;
  }

  void class_func() {
    cout << "Результат классовой функции: " << value1 * value2 << endl;
  }

private:
  T value1;
  T value2;
};

template <typename T> T test_func1(T obj1, T obj2) { return obj1 + obj2; }
template <typename T1, typename T2> void test_func2(T1 obj1, T2 obj2) {
  cout << "Результат работы второй тестовой функции: " << obj1 + obj2 << endl;
}

int main() {
  setlocale(LC_ALL, "Russian");
  int obj1 = 5;
  int obj2 = 44;
  int result1;
  char obj3 = 1;
  double obj4 = 9.1;
  double obj5 = 8.5;
  double result2;

  result1 = test_func1(obj1, obj2);
  cout << "Результат работы первой тестовой функции с int переменными: "
       << result1 << endl;

  result2 = test_func1(obj4, obj5);
  cout << "Результат работы первой тестовой функции с double переменными: "
       << result2 << endl;

  test_func2(obj1, obj3);

  MyTest<int> val(obj1, obj2);
  val.class_func();

  return 0;
}
