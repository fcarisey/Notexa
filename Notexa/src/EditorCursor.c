#include "Headers/EditorCursor.h"

void editor_cursor_set_position(EditorCursor *cursor, EditorCursor new_position) {
    *cursor = new_position;
}

void editor_cursor_reset_position(EditorCursor *cursor) {
    *cursor = (EditorCursor){0, 0};
}
