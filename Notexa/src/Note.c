#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include "Headers/Note.h"
#include "Headers/Define.h"

Note note_new(){
    Note *note = malloc(sizeof(Note));

    if (!note) {
        return (Note){0};
    }

    note->id = note_next_id();
    note->created_at = time(NULL);
    note->updated_at = time(NULL);
    note->title[0] = '\0';
    note->content = NULL;
    note->is_event = false;

    return *note;
}

bool note_patch(Note *note, const char *title, const char *content, bool is_event) {
    if (!note_is_valid(note)) return false;

    strncpy(note->title, title, sizeof(note->title) - 1);
    note->title[sizeof(note->title) - 1] = '\0';

    free(note->content);
    note->content = strdup(content);
    note->is_event = is_event;

    return true;
}

Note note_free(Note *note){
    if (!note_is_valid(note))
        return (Note){0};

    free(note->content);
    free(note);
    return (Note){0};
}

bool note_is_valid(const Note *note) {
    if (!note) return false;

    return true;
}


