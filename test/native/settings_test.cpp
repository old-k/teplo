#include "settings_test.h"
#include "Settings.hpp"
#include <unity.h>

void settings_init_test() {
    const SettingsManager* v = &SettingsManager::instance();
    TEST_ASSERT(v != NULL);
}
