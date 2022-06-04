#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Playlist {
    char *title;
    char *singer;
    struct Playlist *prev;
    struct Playlist *next;
} playlist;

void addSong(playlist **head_ref, char *new_title, char *new_singer);
void displayPlaylist(playlist *pl);
void displayReversePlaylist(playlist *pl);
void currentSong(playlist *pl);
void nextSong(playlist *pl);
void previousSong(playlist *pl);
void searchSong(playlist **pl, char *title);
void deleteSong(playlist **pl, char *title);
bool isEmpty(playlist **pl);
void ifOnlyOneSong(playlist **pl, char *title);
void deleteFirstSong(playlist **pl);
void deleteOneSong(playlist **pl, char *title);

int main() {
    playlist *album = NULL;
    addSong(&album, "Memories", "Maroon 5");
    addSong(&album, "With or Without You", "U2");
    addSong(&album, "Nothing Else Matters", "Metallica");
    addSong(&album, "Maki Madni", "The Derek Trucks Band");
    addSong(&album, "Summer of 69", "Bryan Adams");
    addSong(&album, "Another Brick in the Wall", "Pink Floyd");
    displayReversePlaylist(album);
    displayPlaylist(album);

    currentSong(album);
    nextSong(album);
    previousSong(album);
    searchSong(&album, "Ideal 30 days");
    searchSong(&album, "Maki Madni");
    deleteSong(&album, "Memories");
    displayPlaylist(album);

    return 0;
}

void addSong(playlist **head_ref, char *new_title, char *new_singer) {
    playlist *new_song = malloc(sizeof(playlist));
    if(new_song == NULL) {
        printf("No song can be added.");
        return;
    }
    playlist *last = *head_ref;
    new_song->title = new_title;
    new_song->singer = new_singer;
    new_song->next = NULL;          // new song will be the last song
    if(*head_ref == NULL) {         // if the album is empty
        new_song->prev = NULL;
        *head_ref = new_song;
        return;
    }
    while(last->next != NULL) {
        last = last->next;
    }
    last->next = new_song;
    new_song->prev = last;
}

void displayPlaylist(playlist *pl) {
    printf("Playlist:\n");
    if(pl == NULL) {
        printf("Playlist is Empty\n");
    }
    while(pl != NULL) {
        printf("%s, %s\n", pl->title, pl->singer);
        pl = pl->next;
    }
    printf("\n");
}

void displayReversePlaylist(playlist *pl) {
    playlist *last;
    printf("Playlist in Reverse:\n");
    if(pl == NULL) {
        printf("Playlist is Empty\n");
    }
    while(pl != NULL) {
        last = pl;
        pl = pl->next;
    }
    while(last != NULL) {
        printf("%s, %s\n", last->title, last->singer);
        last = last->prev;
    }
    printf("\n");
}

void currentSong(playlist *pl) {
    printf("Current Song:\n");
    if(pl == NULL) {
        printf("Playlist is Empty\n\n");
    } else {
        printf("%s, %s\n\n", pl->title, pl->singer);
    }
}

void nextSong(playlist *pl) {
    printf("Next Song:\n");
    if(pl == NULL) {
        printf("Playlist is Empty\n\n");
    } else {
        if(pl->next == NULL) {
            printf("End of Playlist\n\n");
        } else {
            printf("%s, %s\n\n", pl->next->title, pl->next->singer);
        }
    }
}

void previousSong(playlist *pl) {
    printf("Previous Song:\n");
    if(pl == NULL) {
        printf("Playlist is Empty\n\n");
    } else {
        if(pl->prev == NULL) {
            printf("End of Playlist\n\n");
        } else {
            printf("%s, %s\n\n", pl->prev->title, pl->prev->singer);
        }
    }
}

void searchSong(playlist **pl, char *title) {
    printf("Searched Song:\n");
    playlist *temp = *pl;
    if(temp == NULL) {
        printf("Playlist is Empty\n\n");
        return;
    }
    while(temp != NULL) {
        if(strcmp(temp->title, title) == 0) {
            printf("%s, %s\n\n", temp->title, temp->singer);
            return;
        } else {
            temp = temp->next;
        }
    }
    printf("%s, Does not exist\n\n", title);
}

bool isEmpty(playlist **pl) {
    printf("Song Deleted:\n");
    playlist *temp = *pl;
    if(temp == NULL) {
        printf("Playlist is Empty\n\n");
        return true;
    } else {
        return false;
    }
}

void ifOnlyOneSong(playlist **pl, char *title) {
    playlist *current = *pl;
    if(strcmp(current->title, title) == 0) {
        printf("%s, %s\n\n", current->title, current->singer);
        *pl = NULL;
        free(*pl);
    } else {
        printf("The song is not in the list.\n\n");
    }
}

void deleteFirstSong(playlist **pl) {
    playlist *current = *pl;
    playlist *temp = NULL;
    temp = current->next;
    temp->prev = NULL;
    *pl = temp;
    printf("%s, %s\n\n", current->title, current->singer);
    free(current);
}

void deleteOneSong(playlist **pl, char *title) {
    playlist *current = *pl;
    playlist *temp = NULL;
    while(current->next->next != NULL) {
        if (strcmp(current->next->title, title) == 0) {
            temp = current->next;
            current->next = temp->next;
            temp->prev = current->prev;
            printf("%s, %s\n\n", temp->title, temp->singer);
            free(temp);
            return;
        } else
            current = current->next;
    }
    if (strcmp(current->next->title, title) == 0) {
        printf("%s, %s\n\n", current->next->title, current->next->singer);
        current->next = NULL;
        free(current->next);
        return;
    }
}

void deleteSong(playlist **pl, char *title) {
    playlist *current = *pl;
    if(isEmpty(&current)) {
        return;
    }
    if((*pl)->prev == NULL && (*pl)->next == NULL) {
        ifOnlyOneSong(pl, title);
        return;
    }
    if(strcmp(current->title, title) == 0) {
        deleteFirstSong(pl);
        return;
    }
    deleteOneSong(pl, title);
}
