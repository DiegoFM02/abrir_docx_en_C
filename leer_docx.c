#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

void extract_docx_content(const char *filename) {
    struct zip *zipfile = zip_open(filename, 0, NULL);
    if (!zipfile) {
        fprintf(stderr, "No se pudo abrir el archivo .docx\n");
        return;
    }

    struct zip_stat st;
    if (zip_stat(zipfile, "word/document.xml", 0, &st) == 0) {
        // Leer el contenido de word/document.xml
        char *contents = malloc(st.size + 1);
        struct zip_file *file = zip_fopen(zipfile, "word/document.xml", 0);
        if (file) {
            zip_fread(file, contents, st.size);
            contents[st.size] = '\0';
            printf("Contenido del archivo Word:\n%s\n", contents);
            zip_fclose(file);
        } else {
            fprintf(stderr, "No se pudo leer el contenido de document.xml\n");
        }
        free(contents);
    } else {
        fprintf(stderr, "No se encontró el archivo document.xml en el .docx\n");
    }

    zip_close(zipfile);
}

int main() {
    const char *filename = "archivo.docx";
    printf("Leyendo el archivo Word: %s\n", filename);
    extract_docx_content(filename);
    return 0;
}
