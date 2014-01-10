#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
/* "readdir" etc. are defined here. */
#include <dirent.h>
/* limits.h defines "PATH_MAX". */
#include <limits.h>

/* List the files in "dir_name". */

static void
list_dir (const char * dir_name)
{
    DIR * d;

    /* Open the directory specified by "dir_name". */

    d = opendir (dir_name);

    /* Check it was opened. */
    while (1) {
        struct dirent * entry;
        const char * d_name;
        const char * delete_path;
        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
        
        if(strstr(d_name,".out"))
        {
            char* folder = malloc(strlen(dir_name) + strlen(d_name) + 2);
            printf ("DELETE:%s/%s\n", dir_name, d_name);
            strcpy(folder,dir_name);
            strcat(folder,"/");
            strcat(folder,d_name);
            remove(folder);
            free(folder);
        }
        else
            printf ("%s/%s\n", dir_name, d_name);
        /* See if "entry" is a subdirectory of "d". */

        if (entry->d_type & DT_DIR) {

            /* Check that the directory is not "d" or d's parent. */

            if (strcmp (d_name, "..") != 0 &&
                strcmp (d_name, ".") != 0) {
                int path_length;
            char path[PATH_MAX];
            path_length = snprintf (path, PATH_MAX,
                "%s/%s", dir_name, d_name);
            printf ("%s\n", path);
/* Recursively call "list_dir" with the new path. */
            list_dir (path);
        }
    }
}
    /* After going through all the entries, close the directory. */
closedir(d);
}

int main ()
{
    char file[100];

    scanf("%s",&file);
    list_dir (".");
    return 0;
}