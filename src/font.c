#include "font.h"

const uint8_t font_20x32[][80] = {
  { 0x00, 0x00, 0xC0, 0xF0, 0xF8, 0xFC, 0xFC, 0x7E, 0x3E, 0x3E, 0x3E, 0x3E,
    0x7E, 0xFC, 0xFC, 0xF8, 0xF0, 0xC0, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF,
    0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
    0xFF, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F,
    0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x3F, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C,
    0x7E, 0x3F, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 0x00 },
  { 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
    0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F,
    0x07, 0x03, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C },
  { 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0x7E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
    0x3E, 0x3E, 0x7E, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 0x01, 0x01, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFF,
    0xFF, 0x7F, 0x3F, 0x1F, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE,
    0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7C, 0x7C, 0x7C, 0x7C,
    0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C },
  { 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
    0x3E, 0x7E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xF0, 0xF8, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C,
    0x7C, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0,
    0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0,
    0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0x7F, 0x3F, 0x1F, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x00, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7D, 0x7C, 0x7C, 0x7C, 0x7C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7C, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00 },
  { 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
    0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
    0xC0, 0x80, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
    0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C,
    0x7C, 0x7E, 0x7F, 0x7F, 0x3F, 0x1F, 0x0F, 0x07 },
  { 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0x7E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
    0x3E, 0x7E, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
    0xC0, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x0F,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
    0x0F, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C,
    0x7C, 0x7E, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x0F },
  { 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
    0x3E, 0x3E, 0x3E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFF,
    0xFF, 0xFF, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  { 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0x7E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
    0x3E, 0x7E, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 0xF0, 0x3F, 0x7F, 0xFF, 0xFF,
    0xFF, 0xF8, 0xF0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xF0, 0xF8, 0xFF,
    0xFF, 0xFF, 0x7F, 0x3F, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x1F, 0x3F, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8,
    0x0F, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C,
    0x7C, 0x7E, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x0F },
  { 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0x7E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
    0x3E, 0x7E, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 0xF0, 0x1F, 0x3F, 0x7F, 0xFF,
    0xFF, 0xFC, 0xF8, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8, 0xFC, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0E, 0x1E, 0x3E, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C,
    0x7C, 0x7E, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x0F }
};

const uint8_t font_8x16[][16]
    = { { 0xF8, 0xFC, 0x0E, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x7F, 0x7F, 0x03,
          0x03, 0x03, 0x03, 0x7F, 0x7F },
        { 0xFE, 0xFE, 0x86, 0x86, 0x86, 0xCE, 0xFC, 0x78, 0x7F, 0x7F, 0x61,
          0x61, 0x61, 0x73, 0x3F, 0x1E },
        { 0xF8, 0xFC, 0x1E, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x1F, 0x3F, 0x78,
          0x70, 0x60, 0x60, 0x60, 0x60 },
        { 0xFE, 0xFE, 0x06, 0x06, 0x0E, 0x1C, 0xF8, 0xF0, 0x7F, 0x7F, 0x60,
          0x60, 0x70, 0x38, 0x1F, 0x0F },
        { 0xFE, 0xFE, 0x86, 0x86, 0x86, 0x86, 0x06, 0x06, 0x7F, 0x7F, 0x61,
          0x61, 0x61, 0x61, 0x60, 0x60 },
        { 0xFE, 0xFE, 0xC6, 0xC6, 0xC6, 0x06, 0x06, 0x06, 0x7F, 0x7F, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0xFC, 0xFE, 0x0E, 0x06, 0x06, 0x06, 0x0E, 0x0C, 0x3F, 0x7F, 0x70,
          0x63, 0x63, 0x73, 0x7F, 0x3F },
        { 0xFE, 0xFE, 0x80, 0x80, 0x80, 0x80, 0xFE, 0xFE, 0x7F, 0x7F, 0x01,
          0x01, 0x01, 0x01, 0x7F, 0x7F },
        { 0x06, 0x06, 0x06, 0xFE, 0xFE, 0x06, 0x06, 0x06, 0x60, 0x60, 0x60,
          0x7F, 0x7F, 0x60, 0x60, 0x60 },
        { 0x06, 0x06, 0x06, 0x06, 0x06, 0xFE, 0xFE, 0x06, 0x18, 0x38, 0x70,
          0x60, 0x70, 0x3F, 0x1F, 0x00 },
        { 0xFE, 0xFE, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x06, 0x7F, 0x7F, 0x07,
          0x0E, 0x1C, 0x38, 0x70, 0x60 },
        { 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x60,
          0x60, 0x60, 0x60, 0x60, 0x60 },
        { 0xFE, 0xFE, 0x1C, 0x78, 0x78, 0x1C, 0xFE, 0xFE, 0x7F, 0x7F, 0x00,
          0x00, 0x00, 0x00, 0x7F, 0x7F },
        { 0xFE, 0xFE, 0x7C, 0xF0, 0xC0, 0x00, 0xFE, 0xFE, 0x7F, 0x7F, 0x00,
          0x01, 0x07, 0x1F, 0x7F, 0x7F },
        { 0xF0, 0xFC, 0x1E, 0x06, 0x06, 0x1E, 0xFC, 0xF0, 0x0F, 0x3F, 0x78,
          0x60, 0x60, 0x78, 0x3F, 0x0F },
        { 0xFE, 0xFE, 0xCE, 0x86, 0x86, 0xCE, 0xFE, 0xFC, 0x7F, 0x7F, 0x01,
          0x01, 0x01, 0x01, 0x01, 0x00 },
        { 0xF0, 0xFC, 0x1E, 0x06, 0x06, 0x1E, 0xFC, 0xF0, 0x0F, 0x3F, 0x78,
          0x60, 0x60, 0x38, 0x7F, 0x6F },
        { 0xFE, 0xFE, 0xCE, 0x86, 0x86, 0xCE, 0xFE, 0xFC, 0x7F, 0x7F, 0x07,
          0x0F, 0x1D, 0x39, 0x71, 0x60 },
        { 0xFC, 0xFE, 0xCE, 0x86, 0x86, 0x86, 0x86, 0x0C, 0x30, 0x61, 0x61,
          0x61, 0x61, 0x73, 0x7F, 0x3F },
        { 0x06, 0x06, 0x06, 0xFE, 0xFE, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00,
          0x7F, 0x7F, 0x00, 0x00, 0x00 },
        { 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x1F, 0x3F, 0x70,
          0x60, 0x60, 0x70, 0x3F, 0x1F },
        { 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x03, 0x0F, 0x3E,
          0x78, 0x78, 0x3E, 0x0F, 0x03 },
        { 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x1F, 0x3F, 0x78,
          0x1E, 0x1E, 0x78, 0x3F, 0x1F },
        { 0x06, 0x1E, 0x7C, 0xF0, 0xF0, 0x7C, 0x1E, 0x06, 0x70, 0x7C, 0x1F,
          0x07, 0x07, 0x1F, 0x7C, 0x70 },
        { 0x06, 0x1E, 0x78, 0xE0, 0xE0, 0x78, 0x1E, 0x06, 0x00, 0x00, 0x00,
          0x7F, 0x7F, 0x00, 0x00, 0x00 },
        { 0x06, 0x06, 0x86, 0x86, 0xE6, 0xF6, 0x3E, 0x1E, 0x78, 0x7E, 0x6F,
          0x63, 0x61, 0x60, 0x60, 0x60 } };
