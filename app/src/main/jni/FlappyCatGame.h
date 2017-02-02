#ifndef FLAPPY_CAT_FLAPPYCATGAME_H
#define FLAPPY_CAT_FLAPPYCATGAME_H

// engine
#include <core/Clock.h>
#include <android/AndroidEvent.h>
#include <android/AndroidWindow.h>
#include <prototype/RectangleShape.h>
#include <prototype/CircleShape.h>

// self
#include "FlappyCatColorScheme.h"
#include "FlappyCatGameConstants.h"
#include "FlappyCatWall.h"
#include "FlappyCatChain.h"
#include "FlappyCatSpike.h"

// stl
#include <vector>
#include <memory>
#include <cmath>

class FlappyCatGame {
public:
  FlappyCatGame();

public:
  void processEvent(const AndroidEvent& event);
  void update(const FrameDuration& time);
  void render(const AndroidWindow&) const;

private:
  enum GameState : int32_t;

private:
  void initialize();
  void reset();


private:
  FlappyCatColorScheme mColorScheme;
  FlappyCatGameConstants mGameConstants;
  GameState mGameState;
  Position::position_type mPlateWidth;
  RectangleShape mFloor;

  FlappyCatChain<FlappyCatSpike> mFloorSpikes;

  FlappyCatChain<FlappyCatWall> mWalls;


  RectangleShape mBackgroundDirt;
  std::vector<RectangleShape> mBackgroundCity;
  std::vector<CircleShape>    mBackgroundSky;
  CircleShape mBall;
};

enum FlappyCatGame::GameState : int32_t {
  PressButtonState,
  PlayState,
  LoseState
};


#endif //FLAPPY_CAT_FLAPPYCATGAME_H
