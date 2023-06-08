#include "SolveOneDir.hpp"

using namespace std;

SolveOneDir::SolveOneDir(const CandySequence& candy_seq)
    : candy_seq_(candy_seq) {
}

Direction SolveOneDir::Solve(const BoxState& box) {
   box_ = box;
   return kDirDown;
}
