#pragma once

#include <bits/stdc++.h>

#include "BoxState.hpp"

// キャンディごとに置く場所を決め打つ
class SolvePattern {
  public:
   SolvePattern(const CandySequence& candy_seq);

   Direction Solve(const Coord& last_pos, const BoxState& box);

  protected:
   CandyType right_candy_;
   CandyType up_candy_;
   CandyType down_candy_;

   BoxState box_;
   CandySequence candy_seq_;
};