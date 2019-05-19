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
    .string "   Overflow!\n"

.text
   .globl main
    main:
      movl  $0, %edx  	 /*Регистр для текущего элемента массива*/
      movl  $array, %ebx /*Ссылка на массив*/
      movl  $len, %ecx
   
    for:
      movl  (%ebx), %edx  /*Загружаем текущий элемент массива в регистр*/
      cmpl  A, %edx
      jl    next          /*Если текущий элемент меньше A, заканчиваем итерацию цикла*/
      cmpl  B, %edx
      jg    next          /*Если текущий элемент больше B, заканчиваем итерацию цикла*/
      
      addl  %edx, Sum     /*Суммируем элемент с Sum*/
      jnc   next          /*Если нет переполнения - заканчиваем итерацию цикла*/

      pushl $msgOverflow  /*В случае переполнения отправляем сообщение в стек и идем на выход*/
      jmp exit

    next:
      addl $4, %ebx       /*Увеличиваем регистр на размер одного элемента массива*/
      loop  for           /*Выполняем цикл, уменьшая регистр ecx, пока он не станен равен 0*/

      pushl Sum
      pushl $printf_format
      jmp exit
      
    exit:
      call printf
      addl $8, %esp

      movl $0, Sum
      ret 


