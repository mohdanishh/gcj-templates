#include <bits/stdc++.h>

using namespace std;

class Task{
public:

   void scan(int testcase){
      // scan the input corresponding 
      // to current test case;
   }

   void print(int testcase){
      printf("Case #%d: ", testcase);
      // print remaining output;
   }

   int run(int testcase){
      return 0;
   }
};

/*
 * Multithreading.
 * Runs approximately (total test cases / (num of threads = 8)) in parallel.
 * https://github.com/FallAndRise/gcj-templates
*/
mutex lck;
int testCases;
int nthreads = thread::hardware_concurrency();

vector<Task> tsk;
int tests_done = 0;
int executeTask(int test_start, int test_end, int tid){
   while(test_start <= test_end){
      tsk[test_start].run(test_start);
      lck.lock();
      ++tests_done;
      cerr << tests_done << "/" << testCases << " tests done" << "\r";
      lck.unlock();
      ++test_start;
   }
   return 0;
}

int main(int argc, char *argv[]) {
   cin >> testCases;
   tsk.resize(testCases + 5);
   for(int test = 1; test <= testCases; ++test){
      tsk[test].scan(test); 
   }
   int st = 1;
   if(nthreads == 0) nthreads = 4;
   int offset = testCases / nthreads;
   int remaining = testCases % nthreads;
   vector<future<int> > _threads;
   for(int th = 0; th < nthreads; ++th){
      _threads.push_back(async(launch::async, &executeTask, st, st + offset + (remaining ? 1 : 0) - 1, th + 1));
      st += (offset + (remaining ? 1 : 0));
      if(remaining) --remaining;
   }
   for(int th = 0; th < nthreads; ++th){
      _threads[th].wait();
   }
   cerr << endl;
   for(int test = 1; test <= testCases; ++test){
      tsk[test].print(test);
   }
   return 0;
}
