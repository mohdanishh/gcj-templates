#include <bits/stdc++.h>

using namespace std;

class Task{
public:

   int a, b;
   int res;

   void scan(int testcase){
      // scan the input corresponding 
      // to current test case;
      scanf("%d%d", &a, &b);
   }

   void print(int testcase){
      printf("Case #%d: ", testcase);
      // print remaining output;
      printf("%d\n", res);
   }

   int run(int testcase){
      for(int i = 0; i <= a; ++i) ++res;
      for(int i = 0; i <= b; ++i) ++res;
      return 0;
   }
};

/*
 * Multithreading.
 * Runs approximately (total test cases / (num of threads = 8)) in parallel.
 * I think I am trying to kill a fly with a cannon.
 * github.com/FallAndRise/gcj-templates
*/
mutex lck;
int testCases;
int nthreads = thread::hardware_concurrency();

vector<Task> tsk;

int executeTask(int test_start, int test_end, int tid){
   lck.lock();
   cerr << "Thread #" << tid << " begins" << endl;
   lck.unlock();
   while(test_start <= test_end){
      tsk[test_start].run(test_start);
      ++test_start;
   }
   lck.lock();
   cerr << "Thread #" << tid << " ends" << endl;
   lck.unlock();
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
   for(int test = 1; test <= testCases; ++test){
      tsk[test].print(test);
   }
   return 0;
}
