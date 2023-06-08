#include <bits/stdc++.h>
#include <fstream>

#include "XorShift.hpp"
#include "Parameter.hpp"
#include "BoxState.hpp"
#include "SolveOneDir.hpp"

#include "debug.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)
template<class T> ostream& operator<<(ostream& os, vector<T>& vec){ rep(i, vec.size()) os << vec[i] << (i+1==(int)vec.size() ? "" : " "); return os;}
// clang-format on

using Problem = pair<CandySequence, CandyPosList>;

Problem LoadProblem();
int GetOpenInd(int turn, const CandyPosList& candy_pos_list);
void SendAnswer(Direction dir, vector<Direction>& answer_list);
char GetDirStr(Direction dir);
string GetAnswerStr(const vector<Direction>& answer_list);

int main() {
   auto [candy_seq, candy_pos_list] = LoadProblem();

   BoxState box;
   SolveOneDir solver(candy_seq);
   vector<Direction> answer_list;

   rep(turn, 100) {
      auto open_ind = GetOpenInd(turn, candy_pos_list);
      auto candy = candy_seq[turn];

      box.AddCandy(candy, open_ind);

      auto dir = solver.Solve(box);
      SendAnswer(dir, answer_list);
   }

   cerr << "Result=" << GetAnswerStr(answer_list) << " ";
   cerr << "Score=0"
        << " ";
   cerr << endl;

   return 0;
}

char GetDirStr(Direction dir) {
   const static array<char, 4> dir_char{'L', 'F', 'R', 'B'};
   return dir_char[dir];
}

void SendAnswer(Direction dir, vector<Direction>& answer_list) {
#ifdef LOCAL
   answer_list.emplace_back(dir);
#else
   cout << GetDirStr(dir) << endl;
#endif
}

int GetOpenInd(int turn, const CandyPosList& candy_pos_list) {
#ifdef LOCAL
   return candy_pos_list[turn];
#else
   int ind;
   cin >> ind;
   return ind;
#endif
}

string GetAnswerStr(const vector<Direction>& answer_list) {
   string ans;

   for (auto dir : answer_list) {
      ans += GetDirStr(dir);
   }
   return ans;
}

Problem LoadProblem() {
   CandySequence candy_seq;
   CandyPosList candy_pos_list;

#ifdef LOCAL
   string filename;
   cin >> filename;

   ifstream fin(filename, ios::in);

   rep(i, 100) {
      CandyType candy;
      fin >> candy;
      candy_seq.emplace_back(candy);
   }

   rep(i, 100) {
      int candy_pos;
      fin >> candy_pos;

      candy_pos_list.emplace_back(candy_pos);
   }
#else
   // ジャッジ実行時
   rep(i, 100) {
      CandyType candy;
      cin >> candy;
      candy_seq.emplace_back(candy);
   }
#endif

   return Problem(candy_seq, candy_pos_list);
}
