#include <stdio.h>
#include "Headers/Note.h"
#include "Headers/Editor.h"
#include "Headers/Define.h"

int main() {
    Note note = note_new();
    note_patch(&note, "Sample Title", "This is a sample content.\n Miaouuuu !", false);
    
    printf("%s\n %s\n", note.title, note.content);

    Editor editor = editor_new(&note);

    editor_open(&editor);
    editor_close(&editor);

    printf("%s\n %s\n", note.title, note.content);

    return 0;
}
