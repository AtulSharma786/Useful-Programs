#include <stdio.h> 
#include <dirent.h>
#include <windows.h>

void BailOut(char *msg)
{
  fprintf(stderr, "Exiting: %s\n", msg);
  exit(1);
}

int main(void) 
{ 
    // File name in which you are gonna add
    char filename[] = "";

    // directory path from where you watn to get list of files
    char dirname[] = "";
    
    // To store name of file
    char name_of_file[1000];

    // To store name of second last file as I have a.exe as last file and I don't want to add it in readme.md
    char previous_name_of_file[1000];

    char* link;

    struct dirent *de;  // Pointer for directory entry 
    FILE *ptr;
    ptr = fopen(filename, "a");
    
    // ************************************---For Fetching ClipBoard Data---**************************************

    HANDLE h;

    if (!OpenClipboard(NULL))
        BailOut("Can't open clipboard");
  
    h = GetClipboardData(CF_TEXT);

    link = (char *)h;

    CloseClipboard();

    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir(dirname); 
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" );
        return 0;
    } 
  
    while ((de = readdir(dr)) != NULL) 
    {   
        strcpy(previous_name_of_file, name_of_file);
        strcpy(name_of_file, de->d_name);
    }
    
    fprintf(ptr, "<br>[%s](%s)\n", previous_name_of_file, link); // It prints the text in the file where ptr points

    fclose(ptr);
    closedir(dr);     
    return 0; 
} 
