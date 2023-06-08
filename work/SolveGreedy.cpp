#include "SolveGreedy.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SolveGreedy::SolveGreedy(const CandySequence &candy_seq)
    : candy_seq_(candy_seq) {
}

Direction SolveGreedy::Solve(const Coord &last_pos, const BoxState &box) {
   int best_dir = -1;
   long long best_score = -1;

   rep(dir, 4) {
      BoxState n_box(box);
      n_box.Tilt(dir);

      auto score = n_box.CalcScore(candy_seq_);

      if (chmax(best_score, score)) {
         best_dir = dir;
      }
   }

   return best_dir;
}
