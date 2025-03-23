#include "MP3_Header.h" // Include the header file for MP3 tag operations

int main(int argc, char *argv[]) // Main function with command-line arguments
{
	mp3tag mp3; // Declare an mp3tag structure variable

	if (argc == 1) // Check if no arguments are passed
	{
		printf("For help please pass ./a.out --help\n"); // Print help message
		return 0; // Exit the program
	}

	if (argc >= 2) // Check if at least one argument is passed
	{
		if (strcmp(argv[1], "--help") == 0) // Check if the argument is "--help"
		{
			// Print usage instructions for viewing and editing MP3 tags
			printf("For Viewing the mp3 tag please pass ./a.out -v mp3_file_name\n");
			printf("For Editing the mp3 tag please pass ./a.out -e ( -a Artist / -t Title / -A Album / -y Year / -c Comment / -C Composer / -im Image ) input_content mp3_file_name\n");
			return 0; // Exit the program
		}
		else if (!strcmp(argv[1], "-v")) // Check if the argument is "-v" for viewing tags
		{
			if (argc == 3) // Check if exactly 3 arguments are passed
			{
				if (strcmp(strstr(argv[2], ".mp3"), ".mp3") == 0) // Validate the MP3 file extension
				{
					// Print header for MP3 tag reader
					printf("--------------------------------------------------------------------------------------\n");
					printf("                              MP3 Tag Reader and Editor for ID3v2\n");
					printf("--------------------------------------------------------------------------------------\n");

					mp3.source_name = argv[2]; // Assign the MP3 file name
					mp3.source_file = fopen(mp3.source_name, "r"); // Open the MP3 file in read mode

					if (mp3.source_file == NULL) // Check if the file failed to open
					{
						printf("Error in opening the file\n"); // Print error message
						return 1; // Exit with error
					}

					fseek(mp3.source_file, 10, SEEK_SET); // Skip the first 10 bytes of the file

					if (store_all_data(mp3.source_file, &mp3) == 0) // Store MP3 tag data
					{
						view_function(&mp3); // View the MP3 tag data
						// Print success message
						printf("--------------------------------------------------------------------------------------\n");
						printf("                          Viewing the mp3 tag is successful\n");
						printf("--------------------------------------------------------------------------------------\n");
					}
					else
					{
						printf("Error in reading the mp3 tag\n"); // Print error message
					}
				}
				else
				{
					printf("Please pass the valid mp3 file name\n"); // Print invalid file name message
				}
			}
			else
			{
				// Print usage instructions for viewing MP3 tags
				printf("For Viewing the mp3 tag please pass ./a.out -v mp3_file_name\n");
			}
		}
		else if (!strcmp(argv[1], "-e")) // Check if the argument is "-e" for editing tags
		{
			if (argc >= 3) // Check if at least 3 arguments are passed
			{
				if (strcmp(strstr(argv[argc - 1], ".mp3"), ".mp3") == 0) // Validate the MP3 file extension
				{
					// Print header for MP3 tag editor
					printf("--------------------------------------------------------------------------------------\n");
					printf("                       MP3 Tag Reader and Editor for ID3v2\n");
					printf("--------------------------------------------------------------------------------------\n");

					mp3.source_name = argv[argc - 1]; // Assign the MP3 file name
					mp3.temperary_name = "temp.mp3"; // Assign a temporary file name
					mp3.user_data = argv[argc - 2]; // Assign user input data

					mp3.source_file = fopen(mp3.source_name, "r"); // Open the MP3 file in read mode
					if (mp3.source_file == NULL) // Check if the file failed to open
					{
						printf("Error in opening the file\n"); // Print error message
						return 1; // Exit with error
					}

					mp3.temperary_file = fopen(mp3.temperary_name, "w"); // Open the temporary file in write mode
					if (mp3.temperary_file == NULL) // Check if the file failed to open
					{
						printf("Error in opening the file\n"); // Print error message
						return 1; // Exit with error
					}

					char data[10]; // Buffer to store the first 10 bytes of the file

					if (fread(data, 1, 10, mp3.source_file) != 10) // Read the first 10 bytes of the source file
					{
						printf("Error in reading the file\n"); // Print error message
						return 1; // Exit with error
					}

					if (fwrite(data, 1, 10, mp3.temperary_file) != 10) // Write the first 10 bytes to the temporary file
					{
						printf("Error in writing the file\n"); // Print error message
						return 1; // Exit with error
					}

					store_all_data(mp3.source_file, &mp3); // Store MP3 tag data
					view_function(&mp3); // View the MP3 tag data

					int ret; // Variable to store the operation type
					ret = check_operation(argv[2]); // Determine the operation type

					if (call_function(ret, &mp3) == 0) // Perform the editing operation
					{
						copy_remaining_data(mp3.source_file, mp3.temperary_file); // Copy remaining data to the temporary file
						fclose(mp3.source_file); // Close the source file
						fclose(mp3.temperary_file); // Close the temporary file
						remove(mp3.source_name); // Remove the original file
						rename(mp3.temperary_name, mp3.source_name); // Rename the temporary file to the original file name
						// Print success message
						printf("--------------------------------------------------------------------------------------\n");
						printf("                        Editing the mp3 tag is successful\n");
						printf("--------------------------------------------------------------------------------------\n");
					}
					else
					{
						// Print error message
						printf("--------------------------------------------------------------------------------------\n");
						printf("                        Error in editing the mp3 tag\n");
						printf("--------------------------------------------------------------------------------------\n");
					}
				}
				else
				{
					printf("Please pass the valid mp3 file name\n"); // Print invalid file name message
				}
			}
			else
			{
				// Print usage instructions for editing MP3 tags
				printf("For Editing the mp3 tag please pass ./a.out -e ( -a Artist / -t Title / -A Album / -y Year / -c Comment / -C Composer / -im Image ) input_content mp3_file_name\n");
			}
		}
		else
		{
			printf("Invalid option\n"); // Print invalid option message
		}
	}
}
