#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// Function to display a manual for a Linux command
void show_manual(const char *command) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "man %s", command);
    printf("Do you want to see the manual for '%s'? (y/n): ", command);
    char response;
    scanf(" %c", &response);
    if (response == 'y' || response == 'Y') {
        system(cmd);
    }
}

// Function to handle zip files
void handle_zip_file(const char *filename) {
    printf("Detected a zip file: %s\n", filename);
    printf("Do you want to unzip it? (y/n): ");
    char response[64];
    gets(response);

    if (response[0] == 'y' || response[0] == 'Y') {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "unzip %s", filename);
        system(cmd);
    }
}


// Function to handle media files
void handle_media_file(const char *filename) {
    printf("Opening media file: %s\n", filename);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "xdg-open %s", filename);
    if(system(cmd) == -1){
        perror("Error opening media file");
    }
}

// Function to display file content in the terminal
void display_file_content(const char *filename) {
    printf("Displaying content of: %s\n", filename);
    FILE *file = fopen(filename, "r");
    if (!file) {
       perror("Error opening file");
        return;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

// Detect file type based on extension
void detect_and_handle_file(const char *filename) {
    const char *ext = strrchr(filename, '.');
    if (!ext) {
        printf("Unknown file type: %s\n", filename);
        return;
    }

    if (strcmp(ext, ".zip") == 0) {
        handle_zip_file(filename);
    } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".png") == 0 ||
               strcmp(ext, ".mp4") == 0 || strcmp(ext, ".mp3") == 0) {
        handle_media_file(filename);
    } else {
        display_file_content(filename);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file|command>\n", argv[0]);
        return 1;
    }

    struct stat statbuf;
    if (stat(argv[1], &statbuf) == 0) {
        if (S_ISREG(statbuf.st_mode)) {
            detect_and_handle_file(argv[1]);
        } else {
            printf("Not a regular file: %s\n", argv[1]);
        }
    } else {
        // Handle as a command if the file does not exist
        printf("Detected a Linux command: %s\n", argv[1]);
        show_manual(argv[1]);
    }

    return 0;
}
