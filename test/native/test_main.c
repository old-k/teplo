#if defined(ARDUINO) && defined(UNIT_TEST)

#include <Arduino.h>
#include <unity.h>
#include "settings_test.h"

// setup connects serial, runs test cases (upcoming)
void setup() {
  delay(2000);
  //
  UNITY_BEGIN();

  RUN_TEST(settings_init_test);

  UNITY_END();
}

void loop() {
  // nothing to be done here.
}

#endif