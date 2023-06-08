#pragma once

#include <bits/stdc++.h>

#include "BoxState.hpp"

// 同一方向に傾ける
class SolveOneDir {
  public:
   SolveOneDir(const CandySequence& candy_seq);

   Direction Solve(const BoxState& box);

  protected:
   BoxState box_;
   CandySequence candy_seq_;
};