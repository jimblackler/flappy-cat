#pragma once

#include "FlappyCatEntity.hpp"

template <typename T>
class FlappyCatStateNode : public FlappyCatEntity {
public:
    using entity_type = T;
    using initialize_modifier_type = std::function<void(entity_type&)>;
    using reset_modifier_type = std::function<void(entity_type&)>;
    using update_modifier_type = std::function<void(entity_type&, const FrameDuration&)>;
    using draw_modifier_type = std::function<void(const entity_type&, const Window&)>;

public:
    FlappyCatStateNode(const FlappyCatGameConstants& gameConstants);

public:
    void setInitializeModifier(initialize_modifier_type modifier);
    void setResetModifier(reset_modifier_type modifier);
    void setUpdateModifier(update_modifier_type modifier);
    void setDrawModifier(draw_modifier_type modifier);

public:
    void initialize() override;
    void reset() override;
    void update(const FrameDuration& frameDuration) override;
    void drawOn(const Window& window) const override;

private:
    initialize_modifier_type m_initializeModifier;
    reset_modifier_type mResetModifier;
    update_modifier_type mUpdateModifier;
    draw_modifier_type m_drawModifier;
};

// implementation

template <typename T>
void FlappyCatStateNode<T>::initialize()
{
    m_initializeModifier(*static_cast<entity_type*>(this));
}

template <typename T>
void FlappyCatStateNode<T>::reset()
{
    mResetModifier(*static_cast<entity_type*>(this));
}

template <typename T>
void FlappyCatStateNode<T>::update(const FrameDuration& frameDuration)
{
    mUpdateModifier(*static_cast<entity_type*>(this), frameDuration);
}

template <typename T>
void FlappyCatStateNode<T>::drawOn(const Window& window) const
{
    m_drawModifier(*static_cast<const entity_type*>(this), window);
}

template <typename T>
FlappyCatStateNode<T>::FlappyCatStateNode(const FlappyCatGameConstants& gameConstants)
    : FlappyCatEntity(gameConstants)
    , m_initializeModifier([](entity_type&) {})
    , mResetModifier([](entity_type&) {})
    , mUpdateModifier([](entity_type&, const FrameDuration&) {})
    , m_drawModifier([](const entity_type&, const Window&) {})
{
    //
}

template <typename T>
void FlappyCatStateNode<T>::setInitializeModifier(initialize_modifier_type modifier)
{
    m_initializeModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setResetModifier(reset_modifier_type modifier)
{
    mResetModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setUpdateModifier(update_modifier_type modifier)
{
    mUpdateModifier = modifier;
}

template <typename T>
void FlappyCatStateNode<T>::setDrawModifier(draw_modifier_type modifier)
{
    m_drawModifier = modifier;
}
