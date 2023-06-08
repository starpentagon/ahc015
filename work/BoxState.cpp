#include "BoxState.hpp"

using namespace std;

// clang-format off
#define rep(i, n) for (int i = 0; (i) < (int)(n); (i)++)

template<class T> bool chmax(T &a, const T &b) {if(a<b) {a=b; return true;} return false; }
template<class T> bool chmin(T &a, const T &b) {if(a>b) {a=b; return true;} return false; }
// clang-format on

// UnionFindで素集合を管理するクラス
// ノードIDは1-indexed
class UnionFind {
  public:
   UnionFind(const size_t N);

   // node_1とnode_2が所属する集合を結合する(Union by size)
   // 計算量: O(almost 1)
   void Unite(size_t node_1, size_t node_2);

   // node_1とnode_2が同じ集合に入っているか
   // 計算量: O(almost 1)
   bool IsSameGroup(size_t node_1, size_t node_2) const;

   // nodeが所属する集合のサイズを返す
   // 計算量: O(almost 1)
   size_t size(size_t node) const;

   // 各グループを返す(親ノードの番号 -> 子のリスト)
   map<size_t, vector<size_t>> EnumGroup() const;

   // nodeの親のnode_idを返す
   size_t root(size_t node) const;

  private:
   // ノードの数
   size_t N_;

   // parent_node_id_[i]: 親ノードのノードID, rootの場合はparent_node_id_[i] ==
   // iになる
   mutable vector<size_t> parent_node_id_;

   // tree_size_[i]: ルートノードiに含まれる集合のサイズ
   vector<size_t> tree_size_;
};

UnionFind::UnionFind(const size_t N)
    : N_(N), parent_node_id_(N + 1), tree_size_(N + 1, 1) {
   // 全ノードをrootで初期化する
   for (size_t i = 0; i <= N; i++) {
      parent_node_id_[i] = i;
   }
}

size_t UnionFind::root(size_t node) const {
   assert(1 <= node && node <= N_);

   // ルートノード以外のノードを記録し直接、親ノードをルートノードにつなぎ変える(経路圧縮)
   vector<size_t> internal_nodes;

   while (parent_node_id_[node] != node) {
      internal_nodes.push_back(node);
      node = parent_node_id_[node];
   }

   for (auto n : internal_nodes) {
      parent_node_id_[n] = node;
   }

   return node;
}

bool UnionFind::IsSameGroup(size_t node_1, size_t node_2) const {
   auto parent_1 = root(node_1);
   auto parent_2 = root(node_2);

   return parent_1 == parent_2;
}

void UnionFind::Unite(size_t node_1, size_t node_2) {
   if (IsSameGroup(node_1, node_2)) {
      // すでに同じ木の場合は何もしない
      return;
   }

   // サイズの小さい方を大きいにつなぐ
   auto size_1 = size(node_1);
   auto size_2 = size(node_2);

   size_t union_from = node_1, union_to = node_2;

   if (size_1 > size_2) {
      union_from = node_2;
      union_to = node_1;
   }
   auto parent_from = root(union_from);
   auto parent_to = root(union_to);

   parent_node_id_[parent_from] = parent_to;
   tree_size_[parent_to] = tree_size_[parent_to] + tree_size_[parent_from];
}

size_t UnionFind::size(size_t node) const {
   auto parent = root(node);
   return tree_size_[parent];
}

map<size_t, vector<size_t>> UnionFind::EnumGroup() const {
   map<size_t, vector<size_t>> group;

   for (size_t i = 1; i <= N_; i++) {
      auto parent = root(i);
      group[parent].push_back(i);
   }

   return group;
}

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

pair<int, int> BoxState::GetPos(int ind) const {
   int h = ind / W;
   int w = ind % W;

   return {h, w};
}

bool BoxState::InGrid(int h, int w) const {
   if (0 <= h && h < H && 0 <= w && w < W) return true;
   return false;
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

Coord BoxState::AddCandy(CandyType candy, int open_index) {
   int open_cnt = 0;

   rep(ind, kBoxSize) {
      if (IsEmpty(ind)) {
         open_cnt++;

         if (open_cnt == open_index) {
            SetCandy(ind, candy);
            return GetPos(ind);
         }
      }
   }

   assert(false);
   return Coord(-1, -1);
}

void BoxState::Tilt(int dir) {
   if (dir == kDirLeft) {
      TiltLeft();
   } else if (dir == kDirUp) {
      TiltUp();
   } else if (dir == kDirRight) {
      TiltRight();
   } else {
      TiltDown();
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

void BoxState::TiltUp() {
   rep(w, W) {
      vector<int> candy_list;

      rep(h, H) {
         auto ind = GetIndex(h, w);
         if (IsEmpty(ind)) continue;
         candy_list.emplace_back(GetCandy(ind));
      }

      rep(h, H) {
         auto ind = GetIndex(h, w);

         if (h < (int)candy_list.size()) {
            SetCandy(ind, candy_list[h]);
         } else {
            SetCandy(ind, kFruitEmpty);
         }
      }
   }
}

void BoxState::TiltRight() {
   rep(h, H) {
      vector<int> candy_list;

      rep(w, W) {
         auto ind = GetIndex(h, W - w - 1);
         if (IsEmpty(ind)) continue;
         candy_list.emplace_back(GetCandy(ind));
      }

      rep(w, W) {
         auto ind = GetIndex(h, W - w - 1);

         if (w < (int)candy_list.size()) {
            SetCandy(ind, candy_list[w]);
         } else {
            SetCandy(ind, kFruitEmpty);
         }
      }
   }
}

void BoxState::TiltDown() {
   rep(w, W) {
      vector<int> candy_list;

      rep(h, H) {
         auto ind = GetIndex(H - h - 1, w);
         if (IsEmpty(ind)) continue;
         candy_list.emplace_back(GetCandy(ind));
      }

      rep(h, H) {
         auto ind = GetIndex(H - h - 1, w);

         if (h < (int)candy_list.size()) {
            SetCandy(ind, candy_list[h]);
         } else {
            SetCandy(ind, kFruitEmpty);
         }
      }
   }
}

long long BoxState::CalcScore(const CandySequence &candy_seq) const {
   UnionFind uf(kBoxSize);

   rep(h, H) rep(w, W) {
      auto c_ind = GetIndex(h, w);
      auto c_candy = GetCandy(c_ind);

      for (auto [dh, dw] : dir_list) {
         int nh = h + dh;
         int nw = w + dw;

         if (!InGrid(nh, nw)) continue;

         auto n_ind = GetIndex(nh, nw);
         auto n_candy = GetCandy(n_ind);

         if (c_candy != kFruitEmpty && c_candy == n_candy) {
            uf.Unite(c_ind + 1, n_ind + 1);
         }
      }
   }

   long long score = 0;
   auto cc_group = uf.EnumGroup();

   for (const auto &[p, cc_vec] : cc_group) {
      if (p == 0) continue;

      int ind = p - 1;
      if (GetCandy(ind) == kFruitEmpty) continue;
      score += cc_vec.size() * cc_vec.size();
   }

   score *= 1000000;

   long long denom = 0;

   array<int, 4> candy_cnt{0};

   for (auto candy : candy_seq) {
      candy_cnt[candy]++;
   }

   for (int i = 1; i <= 3; i++) {
      denom += candy_cnt[i] * candy_cnt[i];
   }

   score = (long long)round((double)score / denom);
   return score;
}

void BoxState::Output() const {
   rep(h, H) {
      rep(w, W) {
         cerr << GetCandy(GetIndex(h, w));
      }

      cerr << endl;
   }
}

int BoxState::GetSameCandyCCSize(const Coord &coord) const {
   int cc_size = 0;

   auto ind = GetIndex(coord.first, coord.second);
   auto candy = GetCandy(ind);
   bitset<kBoxSize> visited;

   queue<int> que;
   que.emplace(ind);

   while (!que.empty()) {
      auto c_ind = que.front();
      que.pop();

      if (visited[c_ind]) continue;
      visited[c_ind] = true;
      cc_size++;

      auto [h, w] = GetPos(c_ind);

      for (auto [dh, dw] : dir_list) {
         int nh = h + dh;
         int nw = w + dw;

         if (!InGrid(nh, nw)) continue;

         auto n_ind = GetIndex(nh, nw);
         if (visited[n_ind]) continue;
         if (GetCandy(n_ind) != candy) continue;

         que.emplace(n_ind);
      }
   }

   return cc_size;
}

pair<Coord, CandyType> BoxState::GetCloseCandy(const Coord &coord, const Direction dir) const {
   auto [h, w] = coord;
   auto [dh, dw] = dir_list[dir];

   for (int d = 1; d <= max(H, W); d++) {
      int nh = h + dh * d;
      int nw = w + dw * d;

      if (!InGrid(nh, nw)) {
         // 盤外
         return {Coord(h + dh * (d - 1), w + dw * (d - 1)), kFruitEmpty};
      }

      auto ind = GetIndex(nh, nw);
      auto candy = GetCandy(ind);

      if (candy != kFruitEmpty) {
         return {Coord(nh, nw), kFruitEmpty};
      }
   }

   assert(false);
   return {Coord(-1, -1), kFruitEmpty};
}
