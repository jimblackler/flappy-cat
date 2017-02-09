#ifndef FLAPPY_CAT_FLAPPYCATCLOUD_H
#define FLAPPY_CAT_FLAPPYCATCLOUD_H

// engine
#include <prototype/CircleShape.h>

// self
#include "FlappyCatEntity.h"

// stl
#include <vector>


class FlappyCatCloud : public FlappyCatEntity {
public:
  using entity_type = CircleShape;
  using modifier_type = std::function<void(entity_type&)>;

public:
  FlappyCatCloud(const FlappyCatGameConstants& gameConstants);

public:
  void setResetModifier(const modifier_type& modifier);

public:
  virtual void initialize() override;
  virtual void drawOn(const Window& window) const override;
  virtual const Position& position() const override;
  virtual void moveTo(const Position& position) override;
  virtual void reset() override;

public:
  Position mPosition;
  std::vector<entity_type> mCloudParts;
  modifier_type mResetModifier;
};


#endif //FLAPPY_CAT_FLAPPYCATCLOUD_H
