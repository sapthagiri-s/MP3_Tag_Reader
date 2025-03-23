# MP3 Tag Reader and Editor

This project is a command-line tool for reading and editing ID3v2 tags in MP3 files. It allows users to view and modify metadata such as the title, artist, album, year, genre, composer, and album art.

## Features

- **View MP3 Tags**: Display metadata information from an MP3 file.
- **Edit MP3 Tags**: Modify metadata fields such as title, artist, album, year, genre, composer, and album art.
- **ID3v2 Support**: Works with MP3 files using the ID3v2 tagging standard.

## Usage

### Viewing MP3 Tags

To view the metadata of an MP3 file, use the following command:

```bash
./a.out -v <mp3_file_name>
```

Example:

```bash
./a.out -v song.mp3
```

### Editing MP3 Tags

To edit the metadata of an MP3 file, use the following command:

```bash
./a.out -e <option> <input_content> <mp3_file_name>
```

#### Options for Editing

- `-t`: Edit the title of the song.
- `-a`: Edit the artist's name.
- `-A`: Edit the album name.
- `-y`: Edit the year of release.
- `-c`: Edit the comment field.
- `-C`: Edit the composer's name.
- `-im`: Edit the album art (image).

Example:

```bash
./a.out -e -t "New Title" song.mp3
```

### Help

To display help information, use the following command:

```bash
./a.out --help
```

## File Structure

- **Main.c**: Contains the main function and handles command-line arguments.
- **Common_functions.c**: Implements utility functions for reading, writing, and processing MP3 tags.
- **Edit_tags_function.c**: Contains functions for encoding and modifying MP3 tags.
- **View_tags_function.c**: Implements the functionality to display MP3 tag information.
- **MP3_header.h**: Header file defining the `mp3tag` structure and function prototypes.

## Compilation

To compile the project, use the following command:

```bash
gcc Main.c Common_functions.c Edit_tags_function.c View_tags_function.c -o a.out
```

## Notes

- Ensure that the MP3 file provided as input has a valid ID3v2 tag.
- The tool creates a temporary file during editing operations and replaces the original file upon successful completion.

## License

This project is provided as-is without any warranty. Use it at your own risk.
