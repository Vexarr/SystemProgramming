.data
printf_format:
    .string "Result: %d\n"

A:
    .long 10
B:
    .long 200

array:
    .long 6, 180, -5, 11, 3, 109, 45, -23, 4

.set len, (.-array)/4

Sum:
    .long 0

msgOverflow:
    .string "Buffer overflow!\n"

.text
   .globl main
   main:
      movl  $0, %edx  	 /*Текущий элемент массива*/
      movl  $array, %ebx /*Ссылка на массив*/
      movl  $len, %ecx
   
   for:
      movl  (%ebx), %edx  /*Скидываем текущий элемент массива в регистр*/
      cmpl  A, %edx
      jl    next          /*Если текущий элемент меньше A, скипаем код дальше*/
      cmpl  B, %edx
      jg    next          /*Если текущий элемент больше B, также скипаем код*/
      
      addl  %edx, Sum
      jnc   next
      pushl msgOverflow
      jmp exit

   next:
      addl $4, %ebx
      loop  for

      pushl Sum
      jmp exit
     
   
    exit:
      pushl $printf_format
      call printf
      addl $8, %esp

      movl $0, Sum
      ret 


