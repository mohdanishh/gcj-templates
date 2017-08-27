/*
 * Multi-threading. 8 times faster than normal program. 
 * Runs (nthreads = 8) threads in parallel. Each thread 
 * handles approximately (totalTests / 8) test cases.
 * Taken from: https://github.com/FallAndRise/gcj-templates
*/

#include <bits/stdc++.h>

using namespace std;

class Task{
public:

   // Declare variables;
   int testid;
   int n;
   map<int, int> counts;
   map<int, int> numbersLessThanCur;
   map<int, int> numbersGreaterThanCur;
   vector<int> a;
   set<int> dist;

   long long nc2(long long x){
      return (x * (x - 1)) / 2;
   }

   long long nc3(long long x){
      return (x * (x - 1) * (x - 2)) / 6;
   }

   void init(){
      a.clear();
      numbersLessThanCur.clear();
      numbersGreaterThanCur.clear();
      counts.clear();
   }

   void build(){
      int prev = -1;
      numbersLessThanCur[prev] = 0;
      for(int i = 0; i < a.size(); ++i){
         ++counts[a[i]];
         numbersLessThanCur[a[i]] = numbersLessThanCur[prev] + 1;
         prev = a[i];
      }
      numbersLessThanCur[(int)1e9 + 7] = numbersLessThanCur[prev];
      prev = (int)1e9 + 7;
      numbersGreaterThanCur[prev] = 0;
      for(int i = a.size() - 1; i >= 0; --i){
         numbersGreaterThanCur[a[i]] = numbersGreaterThanCur[prev] + 1;
         prev = a[i];
      }
      numbersGreaterThanCur[0] = numbersGreaterThanCur[prev];
   }

   int binarySearchMax(long long x){
      int st = 0;
      int en = n - 1;
      int iter = 40;
      int mid;
      while(iter--){
         mid = (st + en) / 2;
         if(a[mid] <= x) mid = st;
         else mid = en;
      }
      int s1 = mid - 5;
      int e1 = mid + 5;
      if(s1 < 0) s1 = 0;
      if(e1 >= n) e1 = n;
      while(s1 <= e1){
         if(a[s1] > x) return a[s1];
         ++s1;
      }
      return -1;
   }

   int binarySearchMin(long long x){
      int st = 0;
      int en = n - 1;
      int iter = 40;
      int mid;
      while(iter--){
         mid = (st + en) / 2;
         if(a[mid] <= x) st = mid;
         else en = mid;
      }
      int s1 = mid - 10;
      int e1 = mid + 10;
      if(s1 < 0) s1 = 0;
      if(e1 >= n) e1 = n - 1;
      int res = 0;
      while(s1 <= e1){
         if(a[s1] >= x){
            return res;
         }
         res = a[s1];
         ++s1;
      }
      return 1e9 + 7;
   }

   long long get(long long x, long long y){
      long long p = (2 * x) + y;
      long long idx1 = binarySearchMax(y);
      long long idx2 = binarySearchMin(p);
   //cout << x << " " << y << " " << p << " " << idx2 << " " << numbersLessThanCur[y] << " " << numbersLessThanCur[idx2] << endl;
      long long res = -numbersLessThanCur[y];
      res += numbersLessThanCur[idx2];
      assert(res >= 0);
      return res;
   }

   void scan(int _testid){
      testid = _testid;
      // Scan the input corresponding 
      // to current test case;
      scanf("%d", &n);
      int x;
      init();
      for(int i = 0; i < n; ++i){
         scanf("%d", &x);
         a.push_back(x);
         dist.insert(x);
      }
      sort(a.begin(), a.end());
      build();
   }
   
   long long res = 0;
   void print(){
      printf("Case #%d: ", testid);
      // Print remaining output;
      printf("%lld\n", res);
   }

   int run(){
      // Actual solution;
      res = 0;
      for(long long it : dist){
         for(long long it1 : dist){
            long long tres = 0;
            if(it == it1){
               if(counts[it] >= 3){
                  long long ret = get(it, it1);
                  if((it > it1) && (it < (2ll*it + it1))){
                     assert(false);
                  }
                  tres = nc3(counts[it]) * ret;
                  //cout << " : "<< it << " " << it1 << " " << ret << " " << tres << endl;
               }
               else continue;
            }
            else{
               if(counts[it] >= 2 && counts[it1] >= 1){
                  long long ret = get(it, it1);
                  if((it > it1) && (it < (2ll*it + it1))){
                     tres = nc3(counts[it]) * counts[it1];
                     tres += nc2(counts[it]) * (ret - counts[it]) * counts[it1];
                  }
                  else{
                     tres = nc2(counts[it]) * (counts[it1]) * ret;
                  }
                  //cout << it << " " << it1 << " " << ret << " " << tres << endl;
               }
            }
            res += tres;
         }
      }
      return 0;
   }
};

// Ignore code from here;
mutex lck;
int testCases;
int nthreads = thread::hardware_concurrency();

vector<Task> tsk;
int tests_done = 0;
int executeTask(int test_start, int test_end, int tid){
   while(test_start <= test_end){
      tsk[test_start].run();
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
      tsk[test].print();
   }
   return 0;
}
