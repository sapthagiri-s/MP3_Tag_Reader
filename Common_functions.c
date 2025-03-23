#include "MP3_Header.h" // Include the header file for MP3 tag reader

int get_size(FILE *fptr) // Function to get the size of a tag
{
    int size = 0; // Initialize size to 0
    fread(&size, 1, 4, fptr); // Read 4 bytes from the file into size
    size = nibble_swap(size); // Swap the nibbles of the size
    return size; // Return the swapped size
}

void get_contant(int size, char *data, FILE *fptr) // Function to get the content of a tag
{
    fread(data, size, 1, fptr); // Read the tag content from the file
}

int skip_byte(int size, FILE *fptr) // Function to skip bytes in the file
{
    fseek(fptr, size, SEEK_CUR); // Move the file pointer forward by size bytes
}

int nibble_swap(int size) // Function to swap the nibbles of an integer
{
    int temp = 0; // Temporary variable to store the swapped value
    temp = ((size & 0x000000FF) << 24) | // Swap the least significant byte to the most significant byte
           ((size & 0x0000FF00) << 8) |  // Swap the second least significant byte
           ((size & 0x00FF0000) >> 8) |  // Swap the second most significant byte
           ((size & 0xFF000000) >> 24);  // Swap the most significant byte to the least significant byte
    return temp; // Return the swapped value
}

int store_all_data(FILE *fptr, mp3tag *mp3) // Function to store all MP3 tag data
{
    int i = 0; // Loop counter
    char *Tag = (char *)malloc(4); // Allocate memory for the tag name
    for (i = 0; i < 7; i++) // Loop through the tags
    {
        fread(Tag, 4, 1, fptr); // Read the tag name from the file
        if (strcmp(Tag, "TPE1") == 0) // Check if the tag is "TPE1" (artist)
        {
            mp3->artist_content_size = (get_size(fptr) - 1); // Get the size of the artist content
            fseek(fptr, 3, SEEK_CUR); // Skip 3 bytes
            mp3->artist_content = (char *)malloc(mp3->artist_content_size); // Allocate memory for the artist content
            get_contant(mp3->artist_content_size, mp3->artist_content, fptr); // Get the artist content
        }
        else if (strcmp(Tag, "TIT2") == 0) // Check if the tag is "TIT2" (title)
        {
            mp3->title_content_size = (get_size(fptr) - 1); // Get the size of the title content
            fseek(fptr, 3, SEEK_CUR); // Skip 3 bytes
            mp3->title_content = (char *)malloc(mp3->title_content_size); // Allocate memory for the title content
            get_contant(mp3->title_content_size, mp3->title_content, fptr); // Get the title content
        }
        else if (strcmp(Tag, "TALB") == 0) // Check if the tag is "TALB" (album)
        {
            mp3->album_content_size = (get_size(fptr) - 1); // Get the size of the album content
            fseek(fptr, 3, SEEK_CUR); // Skip 3 bytes
            mp3->album_content = (char *)malloc(mp3->album_content_size); // Allocate memory for the album content
            get_contant(mp3->album_content_size, mp3->album_content, fptr); // Get the album content
        }
        else if (strcmp(Tag, "TYER") == 0) // Check if the tag is "TYER" (year)
        {
            mp3->year_content_size = (get_size(fptr) - 1); // Get the size of the year content
            fseek(fptr, 3, SEEK_CUR); // Skip 3 bytes
            mp3->year_content = (char *)malloc(mp3->year_content_size); // Allocate memory for the year content
            get_contant(mp3->year_content_size, mp3->year_content, fptr); // Get the year content
        }
        else if (strcmp(Tag, "TCON") == 0) // Check if the tag is "TCON" (content type)
        {
            mp3->content_type_size = (get_size(fptr) - 1); // Get the size of the content type
            fseek(fptr, 3, SEEK_CUR); // Skip 3 bytes
            mp3->content_type = (char *)malloc(mp3->content_type_size); // Allocate memory for the content type
            get_contant(mp3->content_type_size, mp3->content_type, fptr); // Get the content type
        }
        else if (strcmp(Tag, "COMM") == 0) // Check if the tag is "COMM" (composer)
        {
            mp3->composer_content_size = (get_size(fptr) - 1); // Get the size of the composer content
            fseek(fptr, 3, SEEK_CUR); // Skip 3 bytes
            mp3->composer_content = (char *)malloc(mp3->composer_content_size); // Allocate memory for the composer content
            get_contant(mp3->composer_content_size, mp3->composer_content, fptr); // Get the composer content
        }
        else if (strcmp(Tag, "APIC") == 0) // Check if the tag is "APIC" (image)
        {
            mp3->image_content_size = (get_size(fptr) - 1); // Get the size of the image content
            fseek(fptr, 3, SEEK_CUR); // Skip 3 bytes
            mp3->image_content = (char *)malloc(mp3->image_content_size); // Allocate memory for the image content
            get_contant(mp3->image_content_size, mp3->image_content, fptr); // Get the image content
        }
    }
    if (i == 7) // Check if all tags were processed
    {
        return 0; // Return 0 if successful
    }
    else
    {
        return 1; // Return 1 if not all tags were processed
    }
}

void copy_remaining_data(FILE *fptr, FILE *fptr1) // Function to copy remaining data from one file to another
{
    char ch; // Variable to store a single character
    while (fread(&ch, 1, 1, fptr) != 0) // Read one character at a time from the source file
    {
        fwrite(&ch, 1, 1, fptr1); // Write the character to the destination file
    }
}

int check_operation(char *str) // Function to check the operation based on the input string
{
    if (!strcmp(str, "-t")) // Check if the operation is "-t" (title)
        return 1; // Return 1 for title
    else if (!strcmp(str, "-a")) // Check if the operation is "-a" (artist)
        return 2; // Return 2 for artist
    else if (!strcmp(str, "-A")) // Check if the operation is "-A" (album)
        return 3; // Return 3 for album
    else if (!strcmp(str, "-y")) // Check if the operation is "-y" (year)
        return 4; // Return 4 for year
    else if (!strcmp(str, "-c")) // Check if the operation is "-c" (content type)
        return 5; // Return 5 for content type
    else if (!strcmp(str, "-C")) // Check if the operation is "-C" (composer)
        return 6; // Return 6 for composer
    else if (!strcmp(str, "-im")) // Check if the operation is "-im" (image)
        return 7; // Return 7 for image
}