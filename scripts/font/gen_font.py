#!/usr/bin/env python3

import sys
import argparse


def read_file(file_path):
    with open(file_path, "r") as file:

        start = False
        font_bits = []
        char_bits = []

        for line in file:
            line = line.replace("0xff000000", "1").strip()
            line = line.replace("0x00000000", "0")

            if line == "{":
                start = True
                continue

            if line == "}":
                break

            if start:
                line_bit = []

                for n in line.replace(" ", "").split(","):
                    if n.isnumeric():
                        line_bit.append(int(n))

                if not line_bit:
                    font_bits.append(char_bits)
                    char_bits = []
                    continue
                else:
                    char_bits.append(line_bit)

    font_bits.append(char_bits)

    return font_bits


def convert_bit_to_bytes(font_bits):

    font_bytes = []
    char_bytes = []

    img_width = len(font_bits[0][0])
    img_height = len(font_bits[0])

    if img_height % 8 != 0:
        sys.stderr.write("The image height is not a multiple of 8, abort.\n")
        exit(-1)

    for char in font_bits:
        for off in range(img_height // 8):
            for k in range(img_width):
                n = 0
                for i in range(8):
                    bit_value = char[i + off*8][k]
                    n = n | (bit_value << i)
                char_bytes.append(f"0x{n:02X}")

        font_bytes.append(char_bytes)
        char_bytes = []

    return font_bytes


def output(output_filepath, number_bytes, letter_bytes):

    with open(output_filepath, "w") as file:
        file.write('#include "font.h"\n')
        file.write('\n')

        # Write number font
        file.write('const uint8_t font_20x32[][80] = {\n')
        last_element_index = len(number_bytes) - 1
        for index, number in enumerate(number_bytes):

            byte_as_c_array = "{ "
            byte_as_c_array += ", ".join(number)
            byte_as_c_array += " }"

            file.write(byte_as_c_array)
            file.write(',\n' if index != last_element_index else '\n')

        file.write('};\n\n')

        # Write letter font
        file.write('const uint8_t font_8x16[][16] = {\n')
        last_element_index = len(letter_bytes) - 1
        for index, letter in enumerate(letter_bytes):

            byte_as_c_array = "{ "
            byte_as_c_array += ", ".join(letter)
            byte_as_c_array += " }"

            file.write(byte_as_c_array)
            file.write(',\n' if index != last_element_index else '\n')

        file.write('};\n')


if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        prog="gen_font.py",
        description="""
Generate `font.c` from font designed with Piskel and exported as C file.
Used to display numbers and letter on SSD1306 Oled display."""
    )
    parser.add_argument("-n", "--number-font",
                        help="C file generated with Piskel with numbers",
                        required=True)
    parser.add_argument("-l", "--letter-font",
                        help="C file generated with Piskel with letters",
                        required=True)
    parser.add_argument("-o", "--output",
                        help="Output file with number and letter font",
                        required=True)
    args = parser.parse_args()
    args = vars(args)

    number_filepath = args["number_font"]
    letter_filepath = args["letter_font"]
    output_filepath = args["output"]

    number_font_bit = read_file(number_filepath)
    letter_font_bit = read_file(letter_filepath)

    number_font_byte = convert_bit_to_bytes(number_font_bit)
    letter_font_byte = convert_bit_to_bytes(letter_font_bit)

    output(output_filepath, number_font_byte, letter_font_byte)
