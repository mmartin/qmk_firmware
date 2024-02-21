#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#include "features/achordion.h"

enum TapDance {
    TD_CAPS,
};

enum Layers {
    _BASE = 0,
    _NAV,
    _NUM,
    _FUN,
    _DANGER,
};

bool is_left(keyrecord_t *record);
bool is_thumb(keyrecord_t *record);

#endif
