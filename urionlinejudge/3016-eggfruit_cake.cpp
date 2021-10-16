#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
enum {
  P = 'P',
  E = 'E'
};

string cake;
int N, B;

void solve(){
  N = cake.size();
  cin >> B;
  int e_start = 0;
  ull total = 0;
  int last_e_pos = -1;
  int last_p_pos = 0;

  // Find first E
  for(int i=B-1; i>=0; i--){
    if(cake[i] == E){
      last_e_pos = i;
      break;
    }
  }

  for(int i=0; i<N; i++){
    int iters = B;
    int s = i;
    if(cake[(i+B-1) % N] == E)
      last_e_pos = i+B-1;

    //else if(cake[i] == E)
    //  last_e_pos = i;
    bool has_e_slow = false;
    bool has_e = (i <= last_e_pos) && (last_e_pos <= (i+B-1));

    //fprintf(stderr, "(i=%d) , last e pos %d\n", i ,last_e_pos);
  /*
    while(iters--){
      if(cake[s%N] == E){
        has_e_slow = true;
        break;
      }
      s++;
    }

    fprintf(stderr, "Does substring starting from i=%d have e? fast: %d, slow: %d, last_e_pos: %d, ", i, has_e, has_e_slow, last_e_pos);
    if(has_e_slow != has_e){
      cerr << "CULPRIT CASE: " << cake << endl;
      throw runtime_error("bool diff");
    }
*/
    if(has_e){
      ull add = B;
      
      if(cake[(i+B-1)%N] == P){
        ull p = (i+B-1)%N;
        add -= ((i+B-1))-last_e_pos;
        //fprintf(stderr, " Decreasing %lld ", last_e_pos - p - 1);
      }
      total += add;
      //fprintf(stderr, "adding %lld", add);
    }
    //fprintf(stderr, " (total %lld)", total);
    cerr << endl;


    if(cake[(i+B-1) % N] == P)
      last_p_pos = i+B-1;

    /*
EEEPPPPPPPPPP EEEPPPPPPPPPP
E
 E
  E
EE
 EE
EEE
 EEP
  EP
  EPP
         PPE
          PE
          PEE
    */

  }

  cout << total << endl;
}

int main(){
  int c = 1;
  while(getline(cin, cake)){
    if(cake[0] == 'x') break;
    if(cake[0] != P && cake[0] != E) continue;
    cerr << "NEW CASE " <<c<<" --------------------------------" << endl;
    solve();
    c++;
  }
}

// PEE PEE
// PPE PPE
// PEEEEP PEE
// PE
//  E
//  EE
//   E
//   EE
//    E
//    EE
//     EP
//

/*

EEEPPPPPPPPPP EEEPPPPPPPPPP
          PP  E
           P  E
           P  EE
              E
               E
                E
              EE
               EE
              EEE
               EEP
                EP
                EPP

*/