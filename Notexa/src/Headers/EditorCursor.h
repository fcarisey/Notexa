#pragma once

#include <stddef.h>

typedef struct {
    size_t x;
    size_t y;
} EditorCursor;

void editor_cursor_set_position(EditorCursor *cursor, EditorCursor new_position);
void editor_cursor_reset_position(EditorCursor *cursor);