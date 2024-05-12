#include "BitmapRenderer.h"

BitmapRenderer::BitmapRenderer(BitmapView base)
    : m_base(base) {}

inline static void applyMask(uint8_t mask, uint8_t &seg, int flags) {
    if (flags & BitmapRenderer::Flag::Add) {
        seg |= mask;
    } else if (flags & BitmapRenderer::Flag::Exclude) {
        seg &= ~mask;
    }
}

void BitmapRenderer::setPixel(int x, int y, int flags) {
    int col = x % 8;
    uint8_t bitMask = 1 << (7 - col);
    auto &seg = m_base[y * (width() / 8) + x / 8];
    applyMask(bitMask, seg, flags);
}

template<typename T>
requires detail::MaskFactory<T>
void BitmapRenderer::drawRect(int sx, int sy, int _ex, int _ey, int flags, T &&maskFactory) {
    auto ex = std::min<int>(_ex, width());
    auto ey = std::min<int>(_ey, height());

    if (sx < 0 || sy < 0 || sx >= ex || sy >= ey || sx >= width() || sy >= height())
        return;

    // 1 segment = 8 bits (vertical)
    // segments are horizontal

    int startSeg = sx / 8;
    int endSeg = ex / 8;
    int segments = width() / 8;

    // offset relative to the initial segment
    // <=> sx % 8
    int segOffset = sx - startSeg * 8;

    // creates mask taking into account segOffset:
    // |yyyyyyyy|xxxxxxxx|
    // |prev seg|curr seg|
    // segOffset = 2
    // =>
    // |00yyyyyy|yyxxxxxx|
    // result => yyxxxxxx
    auto getMask = [=, &maskFactory](int srcSeg, int srcY) {
        using namespace detail;

        int dstSeg = srcSeg - startSeg;
        int dstY = srcY - sy;

        Mask prevSegMask = dstSeg == 0 ? 0 : maskFactory(dstSeg - 1, dstY);
        Mask segMask = maskFactory(dstSeg, dstY);

        DoubleMask mask = prevSegMask;
        mask <<= 8;
        mask |= segMask;
        mask >>= segOffset;

        return static_cast<Mask>(mask);
    };

    // fill the inner part: -xxx- (border '-' will be ignored)
    for (int segX = startSeg + 1; segX <= endSeg - 1; ++segX) {
        for (int y = sy; y < ey; ++y) {
            uint8_t mask = getMask(segX, y);
            auto &seg = m_base[y * segments + segX];
            applyMask(mask, seg, flags);
        }
    }

    // fill the border: x---x
    for (int y = sy; y < ey; ++y) {
        int leftStartX = startSeg * 8;
        int rightStartX = endSeg * 8;

        uint8_t baseLeftMask = getMask(startSeg, y);
        uint8_t baseRightMask = getMask(endSeg, y);

        // sx = 2, leftStartX = 0, sx >= leftStartX
        // 01000000 - 1 = 00111111
        // mask 00111111
        // x    01234567
        // rightMask: similar to the leftMask

        uint8_t leftMask = (1 << (8 - (sx - leftStartX))) - 1;
        uint8_t rightMask = ~((1 << (8 - (ex - rightStartX))) - 1); // exclusive

        auto &left = m_base[y * segments + startSeg];
        auto &right = m_base[y * segments + endSeg];

        if (startSeg == endSeg) {
            // left:     00011111
            // right:    11111100
            // combined: 00011100
            applyMask((~(leftMask ^ rightMask)) & baseLeftMask, left, flags);
        } else {
            applyMask(leftMask & baseLeftMask, left, flags);
            applyMask(rightMask & baseRightMask, right, flags);
        }
    }
}

void BitmapRenderer::drawRect(int sx, int sy, int ex, int ey, int flags) {
    drawRect(sx, sy, ex, ey, flags, [](int seg, int y) {
        return ~0;
    });
}

void BitmapRenderer::drawText(std::string_view text, int x, int y, const Font &font, int flags) {
    int posX = x;
    auto w = font.width();
    auto h = font.height();
    auto segPerRow = w / 8 + (w % 8 != 0);

    for (auto c : text) {
        auto data = font.getChar(c);

        drawRect(posX, y, posX + w, y + h, flags, [=](int seg, int y) {
            return data[y * segPerRow + seg];
        });

        posX += w;
    }
}
