#ifndef MP3_HEADER_H // Include guard to prevent multiple inclusions of this header file
#define MP3_HEADER_H

#include <stdio.h> // Standard I/O library
#include <stdlib.h> // Standard library for memory allocation, process control, etc.
#include <string.h> // String manipulation functions
#include <unistd.h> // POSIX API for access to the operating system

// Structure to hold MP3 tag information
typedef struct
{
	char *source_name; // Name of the source file
	char *temperary_name; // Name of the temporary file

	FILE *source_file; // File pointer for the source file
	FILE *temperary_file; // File pointer for the temporary file

	char *user_data; // User-defined data
	int user_data_size; // Size of the user-defined data

	char *artist_content; // Artist metadata content
	int artist_content_size; // Size of the artist metadata content

	char *title_content; // Title metadata content
	int title_content_size; // Size of the title metadata content

	char *album_content; // Album metadata content
	int album_content_size; // Size of the album metadata content

	char *year_content; // Year metadata content
	int year_content_size; // Size of the year metadata content

	char *content_type; // Content type metadata
	int content_type_size; // Size of the content type metadata

	char *composer_content; // Composer metadata content
	int composer_content_size; // Size of the composer metadata content

	char *image_content; // Image metadata content
	int image_content_size; // Size of the image metadata content
} mp3tag;

// Function declarations for MP3 tag operations
int call_function(int val, mp3tag *mp3); // Calls a specific function based on the value
void encode_TPE1(mp3tag *mp3); // Encodes the artist metadata
void encode_TIT2(mp3tag *mp3); // Encodes the title metadata
void encode_TALB(mp3tag *mp3); // Encodes the album metadata
void encode_TYER(mp3tag *mp3); // Encodes the year metadata
void encode_TCON(mp3tag *mp3); // Encodes the content type metadata
void encode_COMM(mp3tag *mp3); // Encodes the comment metadata
void encode_APIC(mp3tag *mp3); // Encodes the image metadata
void encode_user(int size, char *data, char *user, mp3tag *mp3); // Encodes user-defined data

// Utility function declarations
int get_size(FILE *fptr); // Gets the size of the file
int nibble_swap(int size); // Swaps nibbles in a given size
int skip_byte(int size, FILE *fptr); // Skips a specific number of bytes in the file
void get_contant(int size, char *data, FILE *fptr); // Reads content of a specific size from the file
void copy_remaining_data(FILE *, FILE *); // Copies remaining data from one file to another
int store_all_data(FILE *fptr, mp3tag *mp3); // Stores all metadata from the file into the mp3tag structure
int check_operation(char *str); // Checks the operation to be performed based on the input string

int view_function(mp3tag *mp3); // Displays the MP3 tag information

#endif // End of include guard
