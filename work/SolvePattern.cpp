#include "SolvePattern.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

SolvePattern::SolvePattern(const CandySequence &candy_seq)
    : candy_seq_(candy_seq) {
   array<int, 4> candy_cnt;

   for (auto candy : candy_seq) {
      candy_cnt[candy]++;
   }

   using P = pair<int, CandyType>;
   vector<P> p_list;

   for (int i = 1; i <= 3; i++) {
      p_list.emplace_back(candy_cnt[i], i);
   }

   sort(p_list.rbegin(), p_list.rend());

   right_candy_ = p_list[0].second;
   up_candy_ = p_list[1].second;
   down_candy_ = p_list[2].second;
}

Direction SolvePattern::Solve(const Coord &last_pos, const BoxState &box) {
   auto candy = box.GetCandy(last_pos);

   if (right_candy_ == candy) {
      return kDirRight;
   } else if (up_candy_ == candy) {
      return kDirLeft;
   } else {
      return kDirDown;
   }
}
