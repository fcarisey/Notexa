#pragma once

#include "Note.h"
#include "EditorCursor.h"

typedef struct {
    Note *note;
    EditorCursor cursor;
} Editor;

Editor editor_new(Note *note);
void editor_init_cursor(Editor *editor);
void editor_enable_raw_mode();
void editor_disable_raw_mode();
void editor_open(Editor *editor);
void editor_close(Editor *editor);

void editor_enter(Editor *editor, size_t *lignes, size_t *lignes_count);
void editor_backspace(Editor *editor, size_t *lignes);
