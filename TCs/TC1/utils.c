#include "utils.h"

RGB colorConverter(int hexValue) {
  RGB rgbColor;
  rgbColor.r = ((hexValue >> 16) & 0xFF) / 255.0;
  rgbColor.g = ((hexValue >> 8) & 0xFF) / 255.0;
  rgbColor.b = ((hexValue) & 0xFF) / 255.0;

  return rgbColor; 
}