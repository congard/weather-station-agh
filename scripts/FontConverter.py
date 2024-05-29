import sys
import subprocess
import os
from fontTools.misc.py23 import unichr
from fontTools.ttLib import TTFont
from PIL import Image
import numpy as np

def image_to_hex_sequence(image_path, size: int, threshold = 128):
    image = Image.open(image_path)
    width, height = image.size
    left, top, right, bottom = 0, 0, min(size, width), size

    cropped_image = image.crop((left, top, right, bottom)).convert('L')
    image_array = np.array(cropped_image)
    bit_sequence = (image_array<threshold).astype(int)

    hex_sequence = []
    for row in bit_sequence:
        binary_str = ''.join(map(str, row))
        hex_value = int(binary_str, 2)
        hex_sequence.append(hex_value)

    return hex_sequence

TEXTS_DIR = "texts"
IMAGES_DIR = "images"

TTF_PATH = sys.argv[1]
FONT_SIZE = sys.argv[2]
TTF_NAME, TTF_EXT = os.path.splitext(os.path.basename(TTF_PATH))

ttf = TTFont(TTF_PATH, 0, verbose=0, allowVID=0, ignoreDecompileErrors=True, fontNumber=-1)

for d in [TEXTS_DIR, IMAGES_DIR]:
    if not os.path.isdir(d):
        os.mkdir(d)

for x in ttf["cmap"].tables:
    for y in x.cmap.items():
        char_unicode = y[0]
        if 32 <= char_unicode <= 32+96:
            char_utf8 = unichr(char_unicode).encode('utf_8')
            char_name = y[1]
            with open(os.path.join(TEXTS_DIR, char_name + '.txt'), 'w') as f:
                f.write(char_utf8.decode('utf-8'))
            f.close()

            filename = char_name + '.txt'
            input_txt = TEXTS_DIR + "/" + filename
            output_png = IMAGES_DIR + "/" + char_name + ".png"
            subprocess.call(
                ["convert", "-font", TTF_PATH, "-pointsize", FONT_SIZE, "-background", "white", "label:@" + input_txt,
                 output_png])

            hex_sequence = image_to_hex_sequence(output_png, int(FONT_SIZE))
            for num in hex_sequence:
                print(hex(num), ", ", end="")
            print(f" // {char_name}")
ttf.close()

