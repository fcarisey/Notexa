#pragma once

#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#include "Helpers/NoteHelper.h"

typedef struct {
    uint64_t id;          // unique
    time_t   created_at;
    time_t   updated_at;
    char     title[256];
    char    *content;     // dynamique
    bool     is_event;
} Note;

Note note_new();

bool note_patch(Note *note, const char *title, const char *content, bool is_event);

Note note_free(Note *note);

bool note_is_valid(const Note *note);