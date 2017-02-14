// self
#include "FlappyCatGame.h"

// engine
#include <core/Log.h>
#include <physics/Collide.h>


FlappyCatGame::FlappyCatGame()
: mGameConstants()
, mGameState(PressButtonState)
, mPlateWidth(0.f)
, mFloor(mGameConstants)
, mWalls(mGameConstants)
, mBackgroundCity(mGameConstants)
, mBackgroundSky(mGameConstants)
, mHero(mGameConstants) {
  initialize();
  reset();
}

void FlappyCatGame::initialize() {

  mPlateWidth = mGameConstants.plateWidth();

  // floor
  mFloor.moveTo(Position(-mPlateWidth, -800.f));
  mFloor.resize(Position(mPlateWidth * 2.f, 0.f));

  mFloor.setResetModifier(
    [this](FlappyCatFloor& floor) {
      floor.setColor(mGameConstants.colorScheme().block(),
                     mGameConstants.colorScheme().dirt());
    }
  );

  // moving blocks
  mWalls.moveTo(Position(-mPlateWidth, 0.f));
  mWalls.resize(Position(mPlateWidth * 2.f, 0.f));
  mWalls.setStartOffset(Position(mPlateWidth * 4.f, 0.f));
  mWalls.setLinkSize(mGameConstants.blockSize());
  mWalls.setOffsetBetweenLinks(mGameConstants.blockSize() * 2.f);
  mWalls.setMovementDisplacement(Position(-10.f, 0.f));

  mWalls.setResetModifier(
    [this](FlappyCatWall& wall) {
      wall.setGapInterval(mGameConstants.gapInterval());
      wall.setGapDisplacement(mGameConstants.randomOffsetFrom(0.f, 200.f));
      wall.setColor(mGameConstants.colorScheme().block());
    }
  );

  mWalls.setUpdateModifier(
    [this](FlappyCatWall& wall) {

      float radius = mHero.radius();
      // TODO: implement proper origin in 'transformation' and remove this code
      // circle origin in bottom left so we shift by radius
      Position center = mHero.position() + Position(radius, radius);

      // TODO: This type of interface? if (collide(wall, mHero).or(wall, mFloor)){}
      if (wall.collideWithCircle(center, radius) || Collide::circleRect(center, radius,
                                                                        mFloor.boundingBox())) {
        mGameState = LoseState;
        Log::i(TAG, "Collide");
      }
    }
  );

  mWalls.setWrapAroundModifier(
    [this](FlappyCatWall& wall) {
      wall.setGapDisplacement(mGameConstants.randomOffsetFrom(0.f, 200.f));
    }
  );

  // city buildings
  mBackgroundCity.moveTo(Position(-mPlateWidth, -800.f));
  mBackgroundCity.resize(Position(mPlateWidth * 2.f, 0.f));
  mBackgroundCity.setLinkSize(mGameConstants.houseSize());
  mBackgroundCity.setMovementDisplacement(Position(-5.f, 0.f));

  mBackgroundCity.setResetModifier(
    [this](FlappyCatSpike& house) {
      Position varyingSize(mGameConstants.houseSize()
                           + Position(0.f, mGameConstants.randomOffsetFrom(0.f, 200.f)));
      house.resize(varyingSize);
      house.setColor(mGameConstants.colorScheme().house());
    }
  );

  mBackgroundCity.setWrapAroundModifier(
    [this](FlappyCatSpike& house) {
      Position varyingSize(mGameConstants.houseSize()
                           + Position(0.f, mGameConstants.randomOffsetFrom(0.f, 200.f)));
      house.resize(varyingSize);
    }
  );

  // sky with clouds
  mBackgroundSky.setResetModifier(
    [this](FlappyCatCloud::entity_type& cloud) {
      cloud.geometry().setRadius(mGameConstants.cloudRadius()
                               + mGameConstants.randomOffsetFrom(0.f, 100.f));

      Position pos(mGameConstants.randomOffsetFrom(0.f, 500.f, FlappyCatGameConstants::Sign::Both),
                   mGameConstants.randomOffsetFrom(0.f, 500.f, FlappyCatGameConstants::Sign::Both));

      cloud.transformation().setPosition(pos);
      cloud.setColor(mGameConstants.colorScheme().cloud());
    }
  );

  mHero.setUpdateModifier(
    [this](FlappyCatHero& hero, const FrameDuration& frameDuration) {


      hero.moveBy(hero.distance());
    }
  );

  mHero.setResetModifier(
    [this](FlappyCatHero& hero) {
      hero.setRadius(mGameConstants.heroRadius());
      hero.moveTo(Position(-300.f, 0.f));
      hero.setColor(mGameConstants.colorScheme().hero());
    }
  );

  // initialize all stuff
  mFloor.initialize();
  mWalls.initialize();
  mBackgroundCity.initialize();
  mBackgroundSky.initialize();
  mHero.initialize();
}

void FlappyCatGame::reset() {

  mGameState = PressButtonState;

  mGameConstants.reset();

  mHero.reset();
  mWalls.reset();
  mFloor.reset();
  mBackgroundCity.reset();
  mBackgroundSky.reset();

}

void FlappyCatGame::processEvent(const Event& event) {

  if (event.type() == AndroidEvent::EventType::TouchEventType) {

    mGameState = PlayState;

    // i'am falling with speed = v, acceleration = a, what must be 'v' and 'a' to pass distance 'd'?

    mHero.setAcceleration(Position(0.f, 600.f));
    mHero.setVelocity(Position(0.f, 200.f));
    //mHero.moveBy(Position(0.f, 200.f));
  }
}

void FlappyCatGame::update(const FrameDuration& time) {

  if (mGameState == PlayState) {

    mHero.update(time);
    mWalls.update(time);
  }

  // update background
  if (mGameState != LoseState) {

    mFloor.update(time);
    mBackgroundCity.update(time);
  }
}

void FlappyCatGame::render(const Window& window) const {

  window.clear(mGameConstants.colorScheme().background());

  mBackgroundSky.drawOn(window);
  mBackgroundCity.drawOn(window);
  mFloor.drawOn(window);
  mWalls.drawOn(window);
  mHero.drawOn(window);

  window.display();
}
