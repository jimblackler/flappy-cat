// engine
#include "View.hpp"

View::View()
    : Transformation()
    , m_origin(0.f, 0.f)
    , mSize(0.f, 0.f)
    , mScale(1.f, 1.f)
    , m_angle(0.f)
{
    //
}

void View::setOrigin(const Position& origin)
{

    m_origin = origin;
}

const Position& View::origin() const
{

    return m_origin;
}

void View::setPosition(const Position& position)
{

    mSize = position;
}

const Position& View::position() const
{

    return mSize;
}

void View::setScale(const Position& factor)
{

    mScale = factor;
}

const Position& View::scale() const
{

    return mScale;
}

void View::setRotation(float angle)
{

    m_angle = angle;
}

float View::rotation() const
{

    return m_angle;
}
