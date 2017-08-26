#include <bits/stdc++.h>

using namespace std;

int main(){
   int t;
   cin >> t;
   for(int test = 1; test <= t; ++test){
      int a, b;
      scanf("%d%d", &a, &b);
      int res = 0;
      for(int i = 0; i <= a; ++i) ++res;
      for(int i = 0; i <= b; ++i) ++res;

      printf("Case #%d: %d\n", test, res);
   }
   return 0;
}
