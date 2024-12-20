#!/usr/bin/env python3

import sys

# Script that converts an image exported in C-format from
#
#   https://www.piskelapp.com
#
# to a data array that can be displayed on the OLED display ssd1306
#
# Usage: csto.py image.c

# Check input file
if len(sys.argv) < 2:
    sys.stderr.write("Too few arguments\n")
    exit(-1)

with open(sys.argv[1], "r") as file:

    start = False
    bit = []

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

            bit.append(tmp)

img_width = len(bit[0])
img_height = len(bit)

if img_height % 8 != 0:
    sys.stderr.write("The image height is not a multiple of 8, abort.")
    exit(-1)

byte_array =[]

for off in range(img_height // 8):
    tmp = []
    for k in range(img_width):
        n = 0
        for i in range(8):
            bit_value = bit[i + off*8][k]
            n = n | (bit_value << i)
        tmp.append(f"0x{n:02X}")
    byte_array.append(tmp)

print(f"uint8_t data[{img_width * img_height // 8}] = {{")
for i, item in enumerate(byte_array):
    print("  ", end="")
    if i != (len(byte_array) - 1):
        print(", ".join(item), end=",\n")
    else:
        print(", ".join(item), end="\n")
print("};")
