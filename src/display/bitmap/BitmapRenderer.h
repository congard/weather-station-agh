#ifndef WEATHERSTATION_BITMAPRENDERER_H
#define WEATHERSTATION_BITMAPRENDERER_H

#include "BitmapView.h"
#include "Font.h"

#include <string_view>

namespace ws {
namespace detail {
using Mask = uint8_t;
using DoubleMask = uint16_t;

template<typename T>
concept MaskFactory = std::is_invocable_r_v<Mask, T, int, int>;
}

class BitmapRenderer {
public:
    enum Flag {
        Add = 0b01,
        Exclude = 0b10
    };

public:
    explicit BitmapRenderer(BitmapView base);

    void setPixel(int x, int y, int flags = Flag::Add);

    void drawRect(int sx, int sy, int ex, int ey, int flags = Flag::Add);

    void drawText(std::string_view text, int x, int y, const Font &font, int flags = Flag::Add);

    inline auto width() const {
        return m_base.width();
    }

    inline auto height() const {
        return m_base.height();
    }

    inline auto data() const {
        return m_base.data();
    }

    inline static constexpr auto getBufferSize(int width, int height) {
        return (width / 8 + (width % 8 != 0)) * height;
    }

private:
    /**
     * Draws rect using the mask provided by `maskFactory`.
     * @tparam T The mask factory type.
     * @param sx Start x
     * @param sy Start y
     * @param ex End x
     * @param ey End y
     * @param maskFactory The mask factory. Signature: <code>detail::Mask(int seg, int y)</code>
     *                    Note: `seg` and `y` are in content's coordinate system, not in
     *                    the current bitmap's coordinate system.
     *                    I.e. `seg` is in range [0, widthInSegments), `y` is in range [0, height).
     * @param flags Additional flags.
     */
    template<typename T>
    requires detail::MaskFactory<T>
    void drawRect(int sx, int sy, int ex, int ey, int flags, T &&maskFactory);

private:
    BitmapView m_base;
};
}

#endif //WEATHERSTATION_BITMAPRENDERER_H
