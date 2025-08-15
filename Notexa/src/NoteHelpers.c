#include "Headers/Helpers/NoteHelper.h"

uint64_t note_next_id() {
    static uint64_t current_id = 0;
    return ++current_id;
}

