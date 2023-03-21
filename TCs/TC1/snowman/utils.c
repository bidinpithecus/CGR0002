#include "utils.h"

Rgb hexTo3f(int hexValue) {
  Rgb rgb;
  rgb.r = ((hexValue >> 16) & 0xFF) / 255.0;
  rgb.g = ((hexValue >> 8) & 0xFF) / 255.0;
  rgb.b = ((hexValue) & 0xFF) / 255.0;

  return rgb; 
}
