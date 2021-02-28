#pragma once

// engine
#include <core/Color.hpp>

class HslColor {
public:
    typedef double value_type;

public:
    // hue        (0 - 360)
    // saturation (0 - 100)
    // luminace   (0 - 100)
    HslColor(value_type hue, value_type saturation, value_type luminance);

public:
    value_type hue() const;
    value_type saturation() const;
    value_type luminance() const;

    // TODO: create negative rotation too
    void rotateHue(value_type shift);
    void addSaturation(value_type shift);
    void addLuminance(value_type shift);

    void setHue(value_type hue);
    void setSaturation(value_type saturation);
    void setLuminance(value_type luminance);

public:
    Color toRgb();
    Color toRgb(uint8_t alpha);

private:
    value_type m_hue;
    value_type m_saturation;
    value_type m_luminance;
};
