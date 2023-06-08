#pragma once

#include <bits/stdc++.h>

#include "BoxState.hpp"

// 最も大きい連結成分がある方向に傾ける
class SolveGreedy {
  public:
   SolveGreedy(const CandySequence& candy_seq);

   Direction Solve(const Coord& last_pos, const BoxState& box);

  protected:
   BoxState box_;
   CandySequence candy_seq_;
};