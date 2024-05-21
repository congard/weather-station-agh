#include <cstddef>
#include "Font4x4.h"
constexpr static auto firstChar = 0x20;

constexpr static uint8_t font4x4[] = {
        0b0 , 0b0 , 0b0 , 0b0 ,  // space
        0b100 , 0b100 , 0b0 , 0b100 ,  // exclam
        0b1000 , 0b1000 , 0b0 , 0b0 ,  // quotedbl
        0b1111 , 0b110 , 0b1111 , 0b110 ,  // numbersign
        0b100 , 0b100 , 0b1100 , 0b100 ,  // dollar
        0b1010 , 0b0 , 0b100 , 0b1010 ,  // percent
        0b1100 , 0b1110 , 0b1000 , 0b1110 ,  // ampersand
        0b100 , 0b100 , 0b0 , 0b0 ,  // quotesingle
        0b10 , 0b100 , 0b100 , 0b10 ,  // parenleft
        0b100 , 0b10 , 0b10 , 0b100 ,  // parenright
        0b100 , 0b1100 , 0b100 , 0b1000 ,  // asterisk
        0b0 , 0b100 , 0b1100 , 0b100 ,  // plus
        0b0 , 0b0 , 0b0 , 0b100 ,  // comma
        0b0 , 0b1110 , 0b0 , 0b0 ,  // hyphen
        0b0 , 0b0 , 0b0 , 0b100 ,  // period
        0b10 , 0b0 , 0b100 , 0b1000 ,  // slash
        0b100 , 0b1010 , 0b1110 , 0b100 ,  // zero
        0b100 , 0b100 , 0b100 , 0b100 ,  // one
        0b1100 , 0b0 , 0b100 , 0b1100 ,  // two
        0b1100 , 0b100 , 0b0 , 0b1100 ,  // three
        0b1010 , 0b1010 , 0b1110 , 0b10 ,  // four
        0b1110 , 0b1100 , 0b10 , 0b1100 ,  // five
        0b1000 , 0b1100 , 0b1010 , 0b100 ,  // six
        0b1110 , 0b1010 , 0b10 , 0b10 ,  // seven
        0b100 , 0b1110 , 0b1010 , 0b100 ,  // eight
        0b100 , 0b1010 , 0b110 , 0b10 ,  // nine
        0b0 , 0b100 , 0b0 , 0b100 ,  // colon
        0b0 , 0b100 , 0b0 , 0b100 ,  // semicolon
        0b0 , 0b100 , 0b1000 , 0b100 ,  // less
        0b0 , 0b1110 , 0b0 , 0b1110 ,  // equal
        0b0 , 0b1100 , 0b0 , 0b1100 ,  // greater
        0b110 , 0b10 , 0b0 , 0b100 ,  // question
        0b100 , 0b1110 , 0b1000 , 0b100 ,  // at
        0b100 , 0b1010 , 0b1110 , 0b1010 ,  // A
        0b1100 , 0b1110 , 0b1010 , 0b1100 ,  // B
        0b100 , 0b1010 , 0b1000 , 0b110 ,  // C
        0b1100 , 0b1010 , 0b1010 , 0b1100 ,  // D
        0b1110 , 0b1100 , 0b1000 , 0b1110 ,  // E
        0b1110 , 0b1000 , 0b1100 , 0b1000 ,  // F
        0b110 , 0b1010 , 0b1010 , 0b110 ,  // G
        0b1010 , 0b1110 , 0b1010 , 0b1010 ,  // H
        0b1100 , 0b100 , 0b100 , 0b1100 ,  // I
        0b10 , 0b10 , 0b1010 , 0b100 ,  // J
        0b1010 , 0b1100 , 0b1100 , 0b1010 ,  // K
        0b1000 , 0b1000 , 0b1000 , 0b1110 ,  // L
        0b1110 , 0b1110 , 0b1010 , 0b1010 ,  // M
        0b1010 , 0b1110 , 0b1010 , 0b1010 ,  // N
        0b100 , 0b1010 , 0b1010 , 0b100 ,  // O
        0b1100 , 0b1010 , 0b1100 , 0b1000 ,  // P
        0b100 , 0b1010 , 0b1000 , 0b110 ,  // Q
        0b1100 , 0b1010 , 0b1100 , 0b1010 ,  // R
        0b110 , 0b1100 , 0b10 , 0b1100 ,  // S
        0b1100 , 0b100 , 0b100 , 0b100 ,  // T
        0b1010 , 0b1010 , 0b1010 , 0b100 ,  // U
        0b1010 , 0b1010 , 0b100 , 0b100 ,  // V
        0b1010 , 0b1010 , 0b1110 , 0b1010 ,  // W
        0b1010 , 0b100 , 0b100 , 0b1010 ,  // X
        0b1000 , 0b1100 , 0b100 , 0b100 ,  // Y
        0b1110 , 0b0 , 0b100 , 0b1110 ,  // Z
        0b110 , 0b100 , 0b100 , 0b110 ,  // bracketleft
        0b1000 , 0b100 , 0b0 , 0b10 ,  // backslash
        0b110 , 0b10 , 0b10 , 0b110 ,  // bracketright
        0b100 , 0b1000 , 0b0 , 0b0 ,  // asciicircum
        0b0 , 0b0 , 0b0 , 0b0 ,  // underscore
        0b100 , 0b10 , 0b0 , 0b0 ,  // grave
        0b0 , 0b110 , 0b1010 , 0b110 ,  // a
        0b1000 , 0b1100 , 0b1010 , 0b1100 ,  // b
        0b0 , 0b110 , 0b1000 , 0b110 ,  // c
        0b10 , 0b110 , 0b1010 , 0b110 ,  // d
        0b0 , 0b100 , 0b1110 , 0b110 ,  // e
        0b100 , 0b100 , 0b1100 , 0b100 ,  // f
        0b100 , 0b1100 , 0b0 , 0b1100 ,  // g
        0b1000 , 0b1100 , 0b1000 , 0b1000 ,  // h
        0b100 , 0b0 , 0b100 , 0b100 ,  // i
        0b10 , 0b0 , 0b10 , 0b10 ,  // j
        0b1000 , 0b1000 , 0b1100 , 0b1000 ,  // k
        0b100 , 0b100 , 0b100 , 0b10 ,  // l
        0b0 , 0b1100 , 0b1110 , 0b1010 ,  // m
        0b0 , 0b1100 , 0b1010 , 0b1010 ,  // n
        0b0 , 0b100 , 0b1010 , 0b100 ,  // o
        0b0 , 0b1100 , 0b1010 , 0b1100 ,  // p
        0b0 , 0b110 , 0b1010 , 0b110 ,  // q
        0b0 , 0b1000 , 0b1110 , 0b1000 ,  // r
        0b0 , 0b100 , 0b100 , 0b1100 ,  // s
        0b100 , 0b1100 , 0b100 , 0b100 ,  // t
        0b0 , 0b1010 , 0b1010 , 0b110 ,  // u
        0b0 , 0b1010 , 0b1010 , 0b100 ,  // v
        0b0 , 0b1010 , 0b1110 , 0b1010 ,  // w
        0b0 , 0b1010 , 0b100 , 0b1010 ,  // x
        0b0 , 0b1010 , 0b1010 , 0b110 ,  // y
        0b0 , 0b1100 , 0b100 , 0b1100 ,  // z
        0b10 , 0b110 , 0b10 , 0b1 ,  // braceleft
        0b100 , 0b100 , 0b100 , 0b100 ,  // bar
        0b100 , 0b100 , 0b100 , 0b1000   // braceright
};

// 1 byte per 1 row (1 row = 4 bits)
// = 4 bytes for 4 rows (height)
// = 4 bytes per 1 char

constexpr static auto charCount = sizeof(font4x4) / 4;

const uint8_t *Font4x4::getChar(char c) const {
    if (c < firstChar || c >= firstChar + charCount)
        return nullptr;
    return &font4x4[(static_cast<size_t>(c) - firstChar) * 4];
}

int Font4x4::width() const {
    return 8;
}

int Font4x4::height() const {
    return 4;
}