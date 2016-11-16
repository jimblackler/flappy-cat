// self
#include "CircleShape.h"

CircleShape::CircleShape(const Position& position, float radius, std::size_t resolution)
: Shape()
, mTransform(position)
, mGeometry(radius, resolution)
, mRender() {
  mGeometry.onUpdate().connect(std::bind(&CircleShape::update, this));
  update();
}

CircleGeometry& CircleShape::geometry() {
  return mGeometry;
}

FlatTransform& CircleShape::transform() {
  return mTransform;
}

VertexBasedRender& CircleShape::render() {
  return mRender;
}

const CircleGeometry& CircleShape::geometry() const {
  return mGeometry;
}

const FlatTransform& CircleShape::transform() const {
  return mTransform;
}

const VertexBasedRender& CircleShape::render() const {
  return mRender;
}

void CircleShape::update() {
  render().update(*this);
}















