#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include "Headers/Note.h"
#include "Headers/Editor.h"

Editor editor_new(Note *note){
    Editor editor;
    editor.note = note;
    editor.cursor = (EditorCursor){0, 0};
    return editor;
}

void editor_enable_raw_mode() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hIn, &mode);
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hIn, mode);
}

void editor_disable_raw_mode() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hIn, &mode);
    mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hIn, mode);
}

void editor_open(Editor *editor) {
    editor_cursor_reset_position(&editor->cursor);

     // Clear console before raw mode
    printf("\033[2J\033[H");  // ANSI: clear screen + move cursor to top-left
    fflush(stdout);

    editor_enable_raw_mode();

    printf("Tape des touches (ESC pour quitter)\n");
    
    editor_init_cursor(editor);

    size_t lignes_count = 1;
    size_t *lignes = calloc(lignes_count, sizeof(size_t));

    int ch;
    while ((ch = _getch()) != 27) { // 27 = ESC

        // Handle special keys
        if (ch == 224 || ch == 0){
            switch (ch = _getch())
            {
                case 72: //Up
                    if (editor->cursor.y > 1){
                        editor->cursor.y--;
                        if (editor->cursor.x > lignes[editor->cursor.y - 1]) {
                            editor->cursor.x = lignes[editor->cursor.y - 1];
                        }
                    }
                            
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
                    break;
                case 80: //Down
                    if (editor->cursor.y < lignes_count) {
                        editor->cursor.y++;

                        if (editor->cursor.x > lignes[editor->cursor.y - 1]) {
                            editor->cursor.x = lignes[editor->cursor.y - 1];
                        }
                    }
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
                    break;
                case 75: //Left
                    if (editor->cursor.x > 0)
                        editor->cursor.x--;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
                    break;
                case 77: //Right
                    if (editor->cursor.x < lignes[editor->cursor.y - 1])
                        editor->cursor.x++;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
                    break;
                default:
                    break;
            }
            continue;
            // printf("default: %c: [%d]\n", ch, ch);
        }

        switch (ch)
        {
            case 19: // Ctrl + S
                // Save the note
                break;
            case 8:
                editor_backspace(editor, lignes);
                break;
            case 13: // Enter
                editor_enter(editor, lignes, &lignes_count);
                break;
            default:
                printf("%c", ch);
                editor->cursor.x++;

                lignes[editor->cursor.y - 1] = editor->cursor.x;
                
                break;
        }

        // Debug
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){100, 0});
        printf("Cursor position: (%lld, %lld)\n", editor->cursor.x, editor->cursor.y);

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){100, editor->cursor.y});
        printf("%lld: %lld \n", editor->cursor.y, lignes[editor->cursor.y - 1]);

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
    }
}

void editor_backspace(Editor *editor, size_t *lignes) {
    if (editor->cursor.x > 0) {
        printf("\b \b"); // Move back, print space, move back again
        editor->cursor.x--;
        lignes[editor->cursor.y - 1] = editor->cursor.x;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
    }else if (editor->cursor.y > 1) {
        // If at the beginning of a line, move to the end of the previous line
        editor->cursor.y--;
        editor->cursor.x = lignes[editor->cursor.y - 1];
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
    }
}

void editor_enter(Editor *editor, size_t *lignes, size_t *lignes_count){
    printf("\n");

    (*lignes_count)++;
    lignes = realloc(lignes, sizeof(size_t) * (*lignes_count));
    (lignes)[*lignes_count - 1] = 0;

    if (*lignes_count > 1 && editor->cursor.x > (lignes)[*lignes_count - 1]) {
        editor->cursor.x = (lignes)[*lignes_count - 1];
    }

    editor->cursor.y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
}

void editor_init_cursor(Editor *editor) {
    editor->cursor.x = 0;
    editor->cursor.y = 1;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){editor->cursor.x, editor->cursor.y});
}

void editor_close(Editor *editor) {
    editor_cursor_reset_position(&editor->cursor);
    editor_disable_raw_mode();
}
