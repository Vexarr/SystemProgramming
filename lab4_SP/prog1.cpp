#include <iostream>
#include <array>

using namespace std;

array<long int, 9> my_array = {6, 180, -5, 11, 3, 109, 45, -23, 4};
int arr_len = my_array.size();
long int sum = 0;
long int A = 10;
long int B = 200;
int ch = 0;

int main()
{
	asm volatile
	(
		"movl  $0, %edx\n\t"
		"movl  $my_array, %ebx\n\t"
		"movl  arr_len, %ecx\n\t"

	"for_loop:\n\t"
		"movl  (%ebx), %edx\n\t"
		"cmpl  A, %edx\n\t"
		"jl    next\n\t"
		"cmpl  B, %edx\n\t"
		"jg    next\n\t"

		"addl  %edx, sum\n\t"
		"jnc   next\n\t"
		"addl  $1, ch\n\t"

	"next:\n\t"
		"addl  $8, %ebx\n\t"
		"loop  for_loop\n\t"
	);
        
    if (ch == 0){
    	cout << "Result: " << sum << endl;
    }
    else
    	cout << "Overflow!" << endl;

    return 0;
}
