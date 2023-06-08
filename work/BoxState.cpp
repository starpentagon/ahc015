#include "BoxState.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

BoxState::BoxState() {
   rep(h, H) rep(w, W) {
      auto ind = GetIndex(h, w);
      box_[ind] = kFruitEmpty;
   }
}

int BoxState::GetIndex(int h, int w) const {
   assert(0 <= h && h < H);
   assert(0 <= w && w < W);
   int ind = h * W + w;

   return ind;
}

bool BoxState::IsEmpty(int ind) const {
   return box_[ind] == kFruitEmpty;
}

CandyType BoxState::GetCandy(int ind) const {
   return box_[ind];
}

void BoxState::SetCandy(int ind, CandyType candy) {
   assert(0 <= ind && ind < kBoxSize);
   box_[ind] = candy;
}

void BoxState::AddCandy(CandyType candy, int open_index) {
   int open_cnt = 0;

   rep(ind, kBoxSize) {
      if (IsEmpty(ind)) {
         open_cnt++;

         if (open_cnt == open_index) {
            SetCandy(ind, candy);
            return;
         }
      }
   }
}

void BoxState::Tilt(int dir) {
   if (dir == kDirLeft) {
      TiltLeft();
   } else if (dir == kDirUp) {
      assert(false);
   } else if (dir == kDirRight) {
      assert(false);
   } else {
      assert(false);
   }
}

void BoxState::TiltLeft() {
   rep(h, H) {
      vector<int> candy_list;

      rep(w, W) {
         auto ind = GetIndex(h, w);
         if (IsEmpty(ind)) continue;
         candy_list.emplace_back(GetCandy(ind));
      }

      rep(w, W) {
         auto ind = GetIndex(h, w);

         if (w < (int)candy_list.size()) {
            SetCandy(ind, candy_list[w]);
         } else {
            SetCandy(ind, kFruitEmpty);
         }
      }
   }
}
