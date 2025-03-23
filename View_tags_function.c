#include "MP3_Header.h" // Include the header file containing the mp3tag structure and function declarations

int view_function(mp3tag *mp3) // Function to display MP3 tag information
{
    printf("Artist : %s\n", mp3->artist_content); // Print the artist's name
    printf("Title : %s\n", mp3->title_content); // Print the title of the song
    printf("Album : %s\n", mp3->album_content); // Print the album name
    printf("Year : %s\n", mp3->year_content); // Print the year of release
    printf("Content Type : %s\n", mp3->content_type); // Print the content type (genre)
    printf("Composer : %s\n", mp3->composer_content); // Print the composer's name
    printf("Image : %s\n", mp3->image_content); // Print the image content (e.g., album art)
    return 0; // Return 0 to indicate successful execution
}
