#include "MP3_Header.h" // Include the header file for MP3 tag definitions

int call_function(int val, mp3tag *mp3) // Function to call encoding functions based on the value
{
    switch (val) // Switch case to handle different values
    {
    case 1: // Case 1: Encode TIT2 and other tags
    {
        encode_user(strlen(mp3->user_data) + 1, "TIT2", mp3->user_data, mp3); // Encode user data for TIT2
        encode_TPE1(mp3); // Encode TPE1 tag
        encode_TALB(mp3); // Encode TALB tag
        encode_TYER(mp3); // Encode TYER tag
        encode_TCON(mp3); // Encode TCON tag
        encode_COMM(mp3); // Encode COMM tag
        encode_APIC(mp3); // Encode APIC tag
    }
    break;
    case 2: // Case 2: Encode TPE1 and other tags
    {
        encode_TIT2(mp3); // Encode TIT2 tag
        encode_user(strlen(mp3->user_data), "TPE1", mp3->user_data, mp3); // Encode user data for TPE1
        encode_TALB(mp3); // Encode TALB tag
        encode_TYER(mp3); // Encode TYER tag
        encode_TCON(mp3); // Encode TCON tag
        encode_COMM(mp3); // Encode COMM tag
        encode_APIC(mp3); // Encode APIC tag
    }
    break;
    case 3: // Case 3: Encode TALB and other tags
    {
        encode_TIT2(mp3); // Encode TIT2 tag
        encode_TPE1(mp3); // Encode TPE1 tag
        encode_user(strlen(mp3->user_data) + 1, "TALB", mp3->user_data, mp3); // Encode user data for TALB
        encode_TYER(mp3); // Encode TYER tag
        encode_TCON(mp3); // Encode TCON tag
        encode_COMM(mp3); // Encode COMM tag
        encode_APIC(mp3); // Encode APIC tag
    }
    break;
    case 4: // Case 4: Encode TYER and other tags
    {
        encode_TIT2(mp3); // Encode TIT2 tag
        encode_TPE1(mp3); // Encode TPE1 tag
        encode_TALB(mp3); // Encode TALB tag
        encode_user(strlen(mp3->user_data) + 1, "TYER", mp3->user_data, mp3); // Encode user data for TYER
        encode_TCON(mp3); // Encode TCON tag
        encode_COMM(mp3); // Encode COMM tag
        encode_APIC(mp3); // Encode APIC tag
    }
    break;
    case 5: // Case 5: Encode TCON and other tags
    {
        encode_TIT2(mp3); // Encode TIT2 tag
        encode_TPE1(mp3); // Encode TPE1 tag
        encode_TALB(mp3); // Encode TALB tag
        encode_TYER(mp3); // Encode TYER tag
        encode_user(strlen(mp3->user_data) + 1, "TCON", mp3->user_data, mp3); // Encode user data for TCON
        encode_COMM(mp3); // Encode COMM tag
        encode_APIC(mp3); // Encode APIC tag
    }
    break;
    case 6: // Case 6: Encode COMM and other tags
    {
        encode_TIT2(mp3); // Encode TIT2 tag
        encode_TPE1(mp3); // Encode TPE1 tag
        encode_TALB(mp3); // Encode TALB tag
        encode_TYER(mp3); // Encode TYER tag
        encode_TCON(mp3); // Encode TCON tag
        encode_user(strlen(mp3->user_data) + 1, "COMM", mp3->user_data, mp3); // Encode user data for COMM
        encode_APIC(mp3); // Encode APIC tag
    }
    break;
    case 7: // Case 7: Encode APIC and other tags
    {
        encode_TIT2(mp3); // Encode TIT2 tag
        encode_TPE1(mp3); // Encode TPE1 tag
        encode_TALB(mp3); // Encode TALB tag
        encode_TYER(mp3); // Encode TYER tag
        encode_TCON(mp3); // Encode TCON tag
        encode_COMM(mp3); // Encode COMM tag
        encode_user(strlen(mp3->user_data) + 1, "APIC", mp3->user_data, mp3); // Encode user data for APIC
    }
    break;
    default: // Default case: Return 1 for invalid value
        return 1;
    }
    return 0; // Return 0 on success
}

void encode_TIT2(mp3tag *mp3) // Function to encode TIT2 tag
{
    char data[] = "TIT2"; // Tag identifier
    int flag[3] = {0}; // Flags for the tag
    fwrite(data, 1, 4, mp3->temperary_file); // Write tag identifier
    int size1 = nibble_swap(mp3->title_content_size + 1); // Calculate size
    fwrite(&size1, 1, 4, mp3->temperary_file); // Write size
    fwrite(flag, 1, 3, mp3->temperary_file); // Write flags
    fwrite(mp3->title_content, 1, mp3->title_content_size, mp3->temperary_file); // Write content
}

void encode_TPE1(mp3tag *mp3) // Function to encode TPE1 tag
{
    char data[] = "TPE1"; // Tag identifier
    int flag[3] = {0}; // Flags for the tag
    fwrite(data, 1, 4, mp3->temperary_file); // Write tag identifier
    int size1 = nibble_swap(mp3->artist_content_size + 1); // Calculate size
    fwrite(&size1, 1, 4, mp3->temperary_file); // Write size
    fwrite(flag, 1, 3, mp3->temperary_file); // Write flags
    fwrite(mp3->artist_content, 1, mp3->artist_content_size, mp3->temperary_file); // Write content
}

void encode_TALB(mp3tag *mp3) // Function to encode TALB tag
{
    char data[] = "TALB"; // Tag identifier
    int flag[3] = {0}; // Flags for the tag
    fwrite(data, 1, 4, mp3->temperary_file); // Write tag identifier
    int size1 = nibble_swap(mp3->album_content_size + 1); // Calculate size
    fwrite(&size1, 1, 4, mp3->temperary_file); // Write size
    fwrite(flag, 1, 3, mp3->temperary_file); // Write flags
    fwrite(mp3->album_content, 1, mp3->album_content_size, mp3->temperary_file); // Write content
}

void encode_TYER(mp3tag *mp3) // Function to encode TYER tag
{
    char data[] = "TYER"; // Tag identifier
    int flag[3] = {0}; // Flags for the tag
    fwrite(data, 1, 4, mp3->temperary_file); // Write tag identifier
    int size1 = nibble_swap(mp3->year_content_size + 1); // Calculate size
    fwrite(&size1, 1, 4, mp3->temperary_file); // Write size
    fwrite(flag, 1, 3, mp3->temperary_file); // Write flags
    fwrite(mp3->year_content, 1, mp3->year_content_size, mp3->temperary_file); // Write content
}

void encode_TCON(mp3tag *mp3) // Function to encode TCON tag
{
    char data[] = "TCON"; // Tag identifier
    int flag[3] = {0}; // Flags for the tag
    fwrite(data, 1, 4, mp3->temperary_file); // Write tag identifier
    int size1 = nibble_swap(mp3->content_type_size + 1); // Calculate size
    fwrite(&size1, 1, 4, mp3->temperary_file); // Write size
    fwrite(flag, 1, 3, mp3->temperary_file); // Write flags
    fwrite(mp3->content_type, 1, mp3->content_type_size, mp3->temperary_file); // Write content
}

void encode_COMM(mp3tag *mp3) // Function to encode COMM tag
{
    char data[] = "COMM"; // Tag identifier
    int flag[3] = {0}; // Flags for the tag
    fwrite(data, 1, 4, mp3->temperary_file); // Write tag identifier
    int size1 = nibble_swap(mp3->composer_content_size + 1); // Calculate size
    fwrite(&size1, 1, 4, mp3->temperary_file); // Write size
    fwrite(flag, 1, 3, mp3->temperary_file); // Write flags
    fwrite(mp3->composer_content, 1, mp3->composer_content_size, mp3->temperary_file); // Write content
}

void encode_APIC(mp3tag *mp3) // Function to encode APIC tag
{
    char data[] = "APIC"; // Tag identifier
    int flag[3] = {0}; // Flags for the tag
    fwrite(data, 1, 4, mp3->temperary_file); // Write tag identifier
    int size1 = nibble_swap(mp3->image_content_size + 1); // Calculate size
    fwrite(&size1, 1, 4, mp3->temperary_file); // Write size
    fwrite(flag, 1, 3, mp3->temperary_file); // Write flags
    fwrite(mp3->image_content, 1, mp3->image_content_size, mp3->temperary_file); // Write content
}

void encode_user(int size, char *data, char *user, mp3tag *mp3) // Function to encode user-defined tag
{
    int flag[3] = {0}; // Flags for the tag
    fwrite(data, 1, 4, mp3->temperary_file); // Write tag identifier
    int size1 = nibble_swap(size + 1); // Calculate size
    fwrite(&size1, 1, 4, mp3->temperary_file); // Write size
    fwrite(flag, 1, 3, mp3->temperary_file); // Write flags
    fwrite(user, 1, size, mp3->temperary_file); // Write user data
}
