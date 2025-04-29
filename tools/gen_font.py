#!/usr/bin/env python3

import sys
import os
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


def generate_c_array(number_bytes, array_name):

    array_dim = len(number_bytes)
    sub_array_dim = len(number_bytes[0])

    if array_dim == 1:
        c_array = f'const uint8_t {array_name}[{sub_array_dim}] ='
        c_array += " {\n"
    else:
        c_array = f'const uint8_t {array_name}[{array_dim}][{sub_array_dim}] ='
        c_array += " {\n"

    last = len(number_bytes) - 1
    for idx, number in enumerate(number_bytes):

        byte_as_c_array = "    { " if array_dim != 1 else ''
        byte_as_c_array += ", ".join(number)
        byte_as_c_array += " }" if array_dim != 1 else ''

        c_array += byte_as_c_array
        c_array += ',\n' if idx != last else '\n'

    c_array += '};'
    return c_array


if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        prog="gen_font.py",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description="""
Parse C files exported from Piskel and convert them to C arrays.

Examples:
    %(prog)s img.c
    %(prog)s in1.c in2.c
    %(prog)s letters.c numbers.c -o font.c
""")

    parser.add_argument("file", nargs='+', help="input C files.")
    parser.add_argument("-o", "--output", help="output file.", required=False)
    args = parser.parse_args()

    last = len(args.file) - 1
    output = ""
    for idx, file in enumerate(args.file):

        array_name = os.path.basename(file).split('.')[0]
        bit = read_file(file)
        byte = convert_bit_to_bytes(bit)
        array = generate_c_array(byte, array_name)

        output += array
        output += '' if idx == last else '\n\n'

    if args.output:
        with open(args.output, "w") as file:
            file.write(output)
    else:
        print(output)
