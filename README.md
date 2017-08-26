# gcj-templates
Multithreading C++ templates for Google-Codejam and Facebook-Hackercup.<br>
You can use [multi_thread_template.cpp](https://github.com/FallAndRise/gcj-templates/blob/master/multi_thread_template.cpp) as a blackbox. But if you want the details, you can go through this tutorial.

## Introduction
You can use [multi_thread_template.cpp](https://github.com/FallAndRise/gcj-templates/blob/master/multi_thread_template.cpp) to run your solution in parallel. 
Let's say there are 96 test cases in a file. Now, this program splits these 96 test cases into 8 buckets of size 12. In other words, this program runs the solution in 8 threads in parallel, each thread handles 12 disjoint testcases.<br>
//details about why multithreading. To be added.

## Usage
Just write your solution in `Task class`.
It has 3 member functions.
- `void scan(int testCase)`
  - `testCase` is the current testcase it is processing.
  - Scan the input for a testcase.
- `int main(int testCase)`
  - `testCase` is the current testcase it is processing.
  - Your main solution should go here. You need not scan or print anything in this function.
- `void print(int testCase)`
  - `testCase` is the current testcase it is processing.
  - Print the final output.

As a whole, complete the `Task class` as if you have a single testcase. See the example section for further details.<br>
Note: Declare all the variables in the class itself. Make sure you are not using any shared variables.
## Example
Let's consider a simple problem in which for each testcase, you are given two numbers `a` and `b` and you need to print it's sum as output. Let's suppose the testcases are 5\*10<sup>4</sup>. So `void scan(int testCase)` should scan two numbers `a` and `b`.
```C++
void scan(int testcase){
    scanf("%d%d", &a, &b);
}
```
`int main(int testCase)` should compute the sum of `a` and `b` and stores it's result in `res`. In this problem, let's compute sum in  O(a + b). So
```C++
int main(int testcase){
    for(int i = 0; i <= a; ++i) ++res;
    for(int i = 0; i <= b; ++i) ++res;
    return 0;
}
```
`void print(int testCase)` Print the `res` as output. So
```C++
void print(int testcase){
    printf("Case #%d: ", testcase); //Following codejam output format.
    printf("%d\n", res);
}
```
Declare variables `a`, `b`, `res` inside the class. You can find the complete code [here](https://github.com/FallAndRise/gcj-templates/blob/master/multi_thread_aplusb.cpp).<br>
That's it! To compile and run, just use
```bash
g++ -std=c++11 -pthread <filename.cpp> -o source
./source < input.txt > output.txt
```
## Performance analysis
First let's analyze the complexity of the code in case of single and multi threaded solutions. In case of single threaded, all the `testCases` are run on one thread which gives the complexity of O(testCases \* (a + b)). Which is around 5\*10<sup>10</sup> operations. But in case of multi threaded, assuming 8 threads, it gives O(testCases/8 \* (a + b)). Which is around 625\*10<sup>7</sup> or 6\*10<sup>9</sup> operations -- Almost 8 times faster.

Now Let's compare the performance between [singlethreaded](https://github.com/FallAndRise/gcj-templates/blob/master/single.cpp) and [multithreaded](https://github.com/FallAndRise/gcj-templates/blob/master/multi_thread_aplusb.cpp) solutions. To do that, just run 
```bash
bash run.sh
```
to run the codes. It compiles the codes, generate testcases and then runs two programs with the generated testcases and finally compares the difference between their outputs. If there is no error, it should produce output something like this(tested on i7-7700 CPU, 3.6GHz x 8).
```bash
Running single threaded

real	1m29.698s
user	1m29.696s
sys	0m0.000s
Running multi threaded
Thread #1 begins
Thread #2 begins
Thread #3 begins
Thread #5 begins
Thread #4 begins
Thread #6 begins
Thread #7 begins
Thread #8 begins
Thread #8 ends
Thread #2 ends
Thread #4 ends
Thread #3 ends
Thread #6 ends
Thread #1 ends
Thread #5 ends
Thread #7 ends

real	0m15.127s
user	1m59.040s
sys	0m0.012s
```
Observe that non-parallel solution took nearly 1.5 minutes to run. Where as multithreaded solution with 8 threads completed in just 15 seconds. You can ignore user time(It is basically amount of cpu time for executing the process and it includes sum of time taken for all threads. You can learn more about it [here](https://stackoverflow.com/questions/556405/what-do-real-user-and-sys-mean-in-the-output-of-time1))

## Tips
- Since we are declaring all the variables in stack, there might be a chance of stack overflow. To prevent that, on linux, you could do some thing like this `ulimit -s unlimited` before running the solution. You can even edit .bashrc file accordingly so that you need not run this command everytime.
- Since each testcase is an object, suppose if we declare a static array of length 10<sup>5</sup> in each object and there are 100 test cases. But in the actual tests, there are very few tests with length such big. So here we end up using lot of unnecessary memory. So it is better to use vectors, etc; to allocate memory as per required.
- Try to use number of threads which are atmost maximum allowed. By default, number of threads is same as maximum threads.

## References
- To be added.
