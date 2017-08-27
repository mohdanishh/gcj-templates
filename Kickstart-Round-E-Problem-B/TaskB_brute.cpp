#include <bits/stdc++.h>

using namespace std;

int n;

bool check(int a, int b, int c, int d){
   vector<int> p;
   p.push_back(a);
   p.push_back(b);
   p.push_back(c);
   p.push_back(d);
   sort(p.begin(), p.end());
   do{
      if(p[0] != p[1]) continue;
      int b1 = p[2];
      int b2 = p[3];
      double hyp = p[0];
      double base = (double)abs(b1 - b2) / (2.0);
      double len = (hyp * hyp) - (base * base);
      if(len > 0 && (b1 != b2)){
         return true;
      }
   }while(next_permutation(p.begin(), p.end()));
   return false;
}

int _main(int argc, char *argv[]) {
   int t;
   cin >> t;
   for(int test = 1; test <= t; ++test){
      scanf("%d", &n);
      int x;
      vector<int> a;
      for(int i = 0; i < n; ++i){
         scanf("%d", &x);
         a.push_back(x);
      }
      int res = 0;
      for(int i = 0; i < n; ++i){
         for(int j = i + 1; j < n; ++j){
            for(int k = j + 1; k < n; ++k){
               for(int l = k + 1; l < n; ++l){
                  //set<int> s;
                  //s.insert(a[i]);
                  //s.insert(a[j]);
                  //s.insert(a[k]);
                  //s.insert(a[l]);
                  //if(s.size() >= 2 && s.size() <= 3){
                   if(check(a[i], a[j], a[k], a[l])) {
                     ++res;
                  }
                  //}
               }
            }
         }
      }
      printf("Case #%d: %d\n", test, res);
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