#pragma once

#include <bits/stdc++.h>

// キャンディ
using CandyType = int;

static constexpr CandyType kFruitEmpty = 0;  // 空白
static constexpr CandyType kFruitS = 1;      // イチゴ
static constexpr CandyType kFruitW = 2;      // スイカ
static constexpr CandyType kFruitP = 3;      // パンプキン

using CandySequence = std::vector<int>;  // キャンディをもらう順序
using CandyPosList = std::vector<int>;   // キャンディが入る空き場所

// ボックス
static constexpr int H = 10;
static constexpr int W = 10;
static constexpr int kBoxSize = H * W;

// 傾ける方向
using Direction = int;

static constexpr Direction kDirLeft = 0;
static constexpr Direction kDirUp = 1;
static constexpr Direction kDirRight = 2;
static constexpr Direction kDirDown = 3;

// Gridの移動方向の定義
using Coord = std::pair<int, int>;

static constexpr std::array<std::pair<long long, long long>, 4> dir_list = {
    std::make_pair(0, -1),  // 左
    std::make_pair(-1, 0),  // 上
    std::make_pair(0, 1),   // 右
    std::make_pair(1, 0),   // 下
};

class BoxState {
  public:
   BoxState();

   // 指定の方向に傾ける
   void Tilt(Direction dir);

   // 指定の空き場所にキャンディを追加する
   Coord AddCandy(CandyType candy, int open_index);

   // スコアを計算する
   long long CalcScore(const CandySequence& candy_seq) const;

   void Output() const;

   // 指定した位置のキャンディと同一の連結成分の個数を返す
   int GetSameCandyCCSize(const Coord& coord) const;

   // 指定した位置から指定した方向にある最も近いキャンディの位置とキャンディを返す
   std::pair<Coord, CandyType> GetCloseCandy(const Coord& coord, const Direction dir) const;

   CandyType GetCandy(int ind) const;

   CandyType GetCandy(const Coord& coord) const {
      return GetCandy(GetIndex(coord.first, coord.second));
   }

  protected:
   bool IsEmpty(int ind) const;
   bool InGrid(int h, int w) const;

   void SetCandy(int ind, CandyType candy);

   void TiltLeft();
   void TiltRight();
   void TiltUp();
   void TiltDown();

   int GetIndex(int h, int w) const;
   std::pair<int, int> GetPos(int ind) const;

   std::array<CandyType, kBoxSize> box_;
};
