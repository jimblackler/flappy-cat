#ifndef FLAPPY_CAT_FLAPPYCATGAME_H
#define FLAPPY_CAT_FLAPPYCATGAME_H

// engine
#include <core/Clock.h>
#include <core/Event.h>
#include <core/Window.h>
#include <prototype/RectangleShape.h>

// self
#include "FlappyCatGameConstants.h"
#include "FlappyCatWall.h"
#include "FlappyCatChain.h"
#include "FlappyCatSpike.h"
#include "FlappyCatHero.h"
#include "FlappyCatCloud.h"
#include "FlappyCatFloor.h"

// stl
#include <vector>
#include <memory>
#include <cmath>

class FlappyCatGame {
public:
  FlappyCatGame();

public:
  void processEvent(const Event& event);
  void update(const FrameDuration& time);
  void render(const Window&) const;
  Position cameraSize() const;

private:
  enum GameState : int32_t;

private:
  void initialize();
  void reset();


private:
  FlappyCatGameConstants mGameConstants;
  GameState mGameState;
  FlappyCatFloor mFloor;
  FlappyCatChain<FlappyCatWall> mWalls;
  FlappyCatChain<FlappyCatSpike> mBackgroundCity;
  FlappyCatCloud mBackgroundSky;
  FlappyCatHero mHero;
};

enum FlappyCatGame::GameState : int32_t {
  PressButtonState,
  PlayState,
  LoseState,
  OnTheFloorState
};

#endif //FLAPPY_CAT_FLAPPYCATGAME_H
