#!/usr/bin/env python3

import sys

# Script that converts an image exported in C-format from
#
#   https://www.piskelapp.com
#
# to a data array that can be displayed on the OLED display ssd1306
#
# Usage: csto.py image.c

def read_file(file_path):
    with open(file_path, "r") as file:

        start = False
        font_bits = { 0 : [], 1 : [], 2 : [], 3 : [], 4 : [], 5 : [], 6 : [], 7 : [], 8 : [], 9 : [] }
        i = 0

        for line in file:
            line = line.replace("0xff000000", "1").strip()
            line = line.replace("0x00000000", "0")

            if line == "{":
                start = True
                continue

            if line == "}":
                break

            if start:
                tmp = []

                for n in line.replace(" ", "").split(","):
                    if n.isnumeric():
                        tmp.append(int(n))

                # If array is empty
                if not tmp:
                    i += 1
                    continue;
                else:
                    font_bits[i].append(tmp)

    return font_bits

def convert_bit_to_bytes(font_bits):

    font_bytes = { 0 : [], 1 : [], 2 : [], 3 : [], 4 : [], 5 : [], 6 : [], 7 : [], 8 : [], 9 : [] }

    img_width = len(font_bits[0][0])
    img_height = len(font_bits[0])

    if img_height % 8 != 0:
        sys.stderr.write("The image height is not a multiple of 8, abort.\n")
        exit(-1)

    for font in font_bits:
        for off in range(img_height // 8):
            tmp = []
            for k in range(img_width):
                n = 0
                for i in range(8):
                    bit_value = font_bit[font][i + off*8][k]
                    n = n | (bit_value << i)
                font_bytes[font].append(f"0x{n:02X}")


    return font_bytes

def generate_font_c_file(out_file_path, font_byte):

    with open(out_file_path, "w") as file:
        file.write('#include "font.h"\n')
        file.write('\n')
        file.write('const uint8_t font_24x32[][80] = {\n')

        for i in range(10):

            byte_as_c_array = "{ "
            byte_as_c_array += ", ".join(font_byte[i])
            byte_as_c_array += " }"

            file.write(byte_as_c_array)
            file.write(',\n' if i != 9 else '\n')

        file.write('};\n')

if __name__ == "__main__":

    font_bit = read_file(sys.argv[1])
    font_byte = convert_bit_to_bytes(font_bit)
    generate_font_c_file(sys.argv[2], font_byte)
