#include "../include/stds.h"

static char textBuffer[MAX_LINE_LENGTH];
static bool seed = false;

int32_t randomInt(int32_t min, int32_t max) {
  if (!seed) {
    srand((uint32_t) time(NULL));
    seed = true;
  }
  return (rand() % (max - min + 1)) + min;
}

float randomFloat(float min, float max) {
  if (!seed) {
    srand((uint32_t) time(NULL));
    seed = true;
  }

  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

int32_t clamp(int32_t value, int32_t min, int32_t max) {
  int newValue = value;
  if (value < min) {
    newValue = min;
  } else if (value > max) {
    newValue = max;
  }

  return newValue;
}

bool collision(int32_t x1, int32_t y1, int32_t w1, int32_t h1, int32_t x2, int32_t y2, int32_t w2, int32_t h2) {
  return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

void calcSlope(int x1, int y1, int x2, int y2, float* dx, float* dy) {
  int steps = MAX(abs(x1 - x2), abs(y1 - y2));

  if (steps == 0) {
    *dx = *dy = 0;
    return;
  }

  *dx = (x1 - x2);
  *dx /= steps;

  *dy = (y1 - y2);
  *dy /= steps;
}

float getAngle(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
  float angle = (float) (-90 + atan2(y1 - y2, x1 - x2) * (180 / PI));
  return angle >= 0 ? angle : 360 + angle;
}

int32_t getDistance(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
  int x = x2 - x1;
  int y = y2 - y1;

  return (int32_t) sqrt(x * x + y * y);
}

void print(const char* str, ...) {
  va_list args;
  memset(&textBuffer, '\0', sizeof(textBuffer));

  va_start(args, str);
  vsprintf(textBuffer, str, args);
  va_end(args);

  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, textBuffer);
}

float toRadians(float degrees) {
  return (float) (degrees * (PI / 180.0));
}