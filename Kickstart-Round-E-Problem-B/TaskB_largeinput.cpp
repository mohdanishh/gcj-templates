#include <bits/stdc++.h>

using namespace std;

int n;
map<long long, long long> counts;
map<long long, long long> numbersLessThanCur;
map<long long, long long> numbersGreaterThanCur;
vector<long long> a;

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

int _main(int argc, char *argv[]) {
   int t;
   cin >> t;
   for(int test = 1; test <= t; ++test){
      scanf("%d", &n);
      int x;
      init();
      set<long long> dist;
      for(int i = 0; i < n; ++i){
         scanf("%d", &x);
         a.push_back(x);
         dist.insert(x);
      }
      sort(a.begin(), a.end());
      build();
      
      /*for(int it : dist){
         cout << it << " " << numbersLessThanCur[it] << " " << numbersGreaterThanCur[it] << endl;
      }
      //return 0;
      */
      long long res = 0;
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
      printf("Case #%d: %lld\n", test, res);
      cerr << "Case #" << test << ": " << res << endl;
   }
   return 0;
}

//{
int correct(int argc, char *argv[]) {
   return 0;
}
int tests(int argc, char *argv[]) {
   return 0;
}
int main(int argc, char *argv[]) {
   if(argc >= 2 && argv[1][0] == '1') {
      correct(argc, argv);
   } else if(argc >= 2 && argv[1][0] == '2') {
      tests(argc, argv);
   } else {
      _main(argc, argv);
   }
   return 0;
}//}