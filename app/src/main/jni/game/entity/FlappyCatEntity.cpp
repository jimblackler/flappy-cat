#include "FlappyCatEntity.hpp"
#include <core/Log.hpp>

FlappyCatEntity::FlappyCatEntity(const FlappyCatGameConstants& gameConstants)
    : m_gameConstants(gameConstants)
    , mPosition()
    , mSize()
    , m_angle(0.f)
{
    //
}

FlappyCatEntity::~FlappyCatEntity() = default;

void FlappyCatEntity::syncChildren()
{
    // intentionally left blank
}

void FlappyCatEntity::moveBy(const Position& offset)
{
    moveTo(position() + offset);
}

void FlappyCatEntity::moveTo(const Position& position)
{
    mPosition = position;
    syncChildren();
}

void FlappyCatEntity::resize(const Position& size)
{
    mSize = size;
    syncChildren();
}

void FlappyCatEntity::rotateTo(float angle)
{
    m_angle = angle;
    syncChildren();
}

const FlappyCatGameConstants& FlappyCatEntity::gameConstants() const
{
    return m_gameConstants;
}

const Position& FlappyCatEntity::position() const
{
    return mPosition;
}

const Position& FlappyCatEntity::size() const
{
    return mSize;
}

float FlappyCatEntity::rotation() const
{
    return m_angle;
}
