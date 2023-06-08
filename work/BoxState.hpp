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

// 傾ける方向
using Direction = int;

static constexpr Direction kDirLeft = 0;
static constexpr Direction kDirUp = 1;
static constexpr Direction kDirRight = 2;
static constexpr Direction kDirDown = 3;

// ボックス
static constexpr int H = 10;
static constexpr int W = 10;
static constexpr int kBoxSize = H * W;

class BoxState {
  public:
   BoxState();

   // 指定の方向に傾ける
   void Tilt(Direction dir);

   // 指定の空き場所にキャンディを追加する
   void AddCandy(CandyType candy, int open_index);

  protected:
   bool IsEmpty(int ind) const;
   CandyType GetCandy(int ind) const;

   void SetCandy(int ind, CandyType candy);

   void TiltLeft();
   int GetIndex(int h, int w) const;

   std::array<CandyType, kBoxSize> box_;
};
