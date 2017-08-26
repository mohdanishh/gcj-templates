#include <bits/stdc++.h>

using namespace std;

class Task{
public:

   int n, K, a1, b1, c;
   int d, e1, e2, f;
   long long a[205];
   long long b[205];
   long long arr[205][205];
   long long dp[205][205];
   long long res;

   void scan(int testcase){
      // scan the input corresponding 
      // to current test case;
      cin >> n >> K >> a1 >> b1;
      cin >> c >> d >> e1 >> e2 >> f;
   }

   void print(int testcase){
      printf("Case #%d: ", testcase);
      // print remaining output;
      printf("%lld\n", res);
   }

   void generate(int testcase){
      int x, y;
      x = a1;
      a[1] = x;
      y = b1;
      b[1] = y;
      int r = 0;
      int s = 0;
      for(int i = 2; i <= n; ++i){
         int tx = x;
         int ty = y;
         int tr = r;
         int ts = s;
         x = (c* 1ll *tx + d* 1ll *ty + e1) % f;
         y = (d* 1ll *tx + c* 1ll *ty + e2) % f;
         r = (c* 1ll *tr + d* 1ll *ts + e1) % 2;
         s = (d* 1ll *tr + c* 1ll *ts + e2) % 2;
         a[i] = (r ? -1 : 1) * 1ll * x;
         b[i] = (s ? -1 : 1) * 1ll * y;
      }
      for(int i = 0; i <= n; ++i){
         for(int j = 0; j <= n; ++j){
            dp[i][j] = 0;
         }
      }
      for(int i = 1; i <= n; ++i){
         for(int j = 1; j <= n; ++j){
            arr[i][j] = a[i] * 1ll * b[j];
         }
      }
   }

   void build(){
      for(int i = 1; i <= n; ++i){
         for(int j = 1; j <= n; ++j){
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
            dp[i][j] += arr[i][j];
         }
      }
   }

   long long get(int i, int j, int k, int l){
      long long tres = dp[k][l] - dp[k][j - 1] - dp[i - 1][l] + dp[i - 1][j - 1];
      return tres;
   }

   int run(int testcase){
      generate(testcase);
      build();
      priority_queue <long long, vector<long long>, greater<long long> > pq;
      long long sum;
      res = 0;
      int len = 0;
      for(int i = 1; i <= n; ++i){
         for(int j = 1; j <= n; ++j){
            for(int k = i; k <= n; ++k){
               for(int l = j; l <= n; ++l){
                  sum = get(i, j, k, l);
                  if(pq.size() < K){
                     pq.push(sum);
                  }
                  else{
                     if(pq.top() <= sum){
                        pq.pop();
                        pq.push(sum);
                     }
                  }
               }
            }
         }
      }
      assert(pq.size() == K);
      res = pq.top();
      return 0;
   }
};

/*
 * Multithreading.
 * Runs approximately (total test cases / (num of threads = 8)) in parallel.
 * github.com/FallAndRise/gcj-templates
*/
mutex lck;
int testCases;
int nthreads = thread::hardware_concurrency();

vector<Task> tsk;

int executeTask(int test_start, int test_end, int tid){
   while(test_start <= test_end){
      tsk[test_start].run(test_start);
      lck.lock();
      cerr << "Test #" << test_start << " done" << endl;
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
   if(nthreads == 0) nthreads = 1;
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
