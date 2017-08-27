## multithreaded and singlethreaded codes for [Problem B. Trapezoid Counting](https://code.google.com/codejam/contest/12234486/dashboard#s=p1)

TaskB_brute is for small input.<br>
TaskB_largeinput.cpp  and TaskB_optimized.cpp both can handle large input.<br>
TaskB_largeinput.cpp is single threaded, where as TaskB_optimized.cpp is multithreaded.<br>
input.txt is worst case input (100 tests with n = 5000).<br>
On this input, TaskB_largeinput.cp runs in 2m32.678s.<br>
On this input, TaskB_optimized.cp runs in 0m25.675s.<br><br>
The official large input is far "smaller" than input.txt. So using TaskB_optimized.cpp is not required.