/* Author: Saifa Samia
 * CSC 3320 -- due: June 24th
 * Description: This C program implements a lyric jukebox where users can select
 * songs from a menu and view their lyrics displayed line by line with a
 * 1-second delay between lines. Each song's lyrics are sorted in sparate text
 * files located in the same directory as the program.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <unistd.h>

#define NUM_SONGS 5

typedef struct {
  char artist[50];   // Artist name holding up to 50 characters/bytes
  char songs[50];    // Song title
  char album[50];    // Album name
  char filename[50]; // Filename of text files containing lyrics
} Song;

void displayMenu(Song songs[]); // Function to display the menu
void displayLyrics(
    const char *filename); // Function to display the lyrics of a song

int main() {
  // Array of songs, containing information about each song
  Song songs[NUM_SONGS] = {
      {"One Direction", "One Thing", "Up All Night", "one_thing.txt"},
      {"Ed Sheeran", "Perfect", "Divide", "perfect.txt"},
      {"Eclipse", "Sudden Shower", "Lovely Runner", "sudden_shower.txt"},
      {"Car, the Garden", "Romantic Sunday", "Hometown Cha Cha Cha",
       "romantic_sunday.txt"},
      {"10cm", "Spring Snow", "Lovely Runner", "spring_snow.txt"},
  };

  int choice; // Variable to store user's menu choice

  // Display introductory message
  printf("Welcome to Saifa Samia's Lyric Jukebox!\n");
  printf("Please select a track from the list below:\n\n");

  while (1) {
    displayMenu(songs); // Display a menu of avaiable songs

    printf("\n0: Quit\n"); // Display quit option
    printf("\n:> ");       // User input prompt
    scanf("%d", &choice);  // Read user input for song selection

    if (choice == 0) {
      break; // Exit loop if user chooses to quit
    } else if (choice > 0 && choice <= NUM_SONGS) {
      printf("\nPlaying %s - %s - %s\n\n", songs[choice - 1].artist,
             songs[choice - 1].songs, songs[choice - 1].album);
      displayLyrics(
          songs[choice - 1].filename); // Display lyric of selected song
    } else {
      // Error message for invalid input
      printf("\nInvalid choice. Please try again.\n\n");
    }
  }

  printf("\nThank you for using the Lyric Jukebox!\n");
  return 0; // Return to indicate successful program execution
}

// Function to display the menu of songs
void displayMenu(Song songs[]) {
  printf(" %-23s  %-21s  %-22s\n", "Artist", "Song", "Album");
  printf("_____________________________________________________________________"
         "__\n");

  for (int i = 0; i < NUM_SONGS; i++) {
    // Print each song's details in formatted rows
    printf("%-1d: %-20s - %-20s - %-27s\n", i + 1, songs[i].artist,
           songs[i].songs, songs[i].album);
  }
}

// Function to display the lyrics of a song with a 1-second delay between lines
void displayLyrics(const char *filename) {
  // Open specified file for reading lyrics
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    // Error message if the file cannot be opened
    perror("Could not open file");
    return;
  }
  char line[256]; // Buffer to hold each line of the lyrics (256 bytes)
  while (fgets(line, sizeof(line), file)) {
    printf("%s", line); // Print each line of the lyrics
    fflush(stdout);     // Flush output to ensure lines are printed immediately
    sleep(1);           // Sleep for 1 second between lines
  }

  fclose(file);   // Close the file after reading all lines
  printf("\n\n"); // Print additional newlines after displaying lyrics
}