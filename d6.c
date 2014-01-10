#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>

static void sterge(const char * dir_name)
{
  DIR * d;
  d = opendir(dir_name);

  while(1){
    struct dirent * child;
    char * d_name;
    char * delete_path;
    /* "Readdir" ia fisierele din d. */
    child = readdir(d);
        /* Iesi daca nu mai sunt fisiere. */
    if(!child)
      break;

    d_name = child->d_name;
    /* Printeaza numele.
     * DELETE: cale, daca fisierul trebuie sters.
     * cale simpla daca fisierul nu trebuie sters
     */
     if(strstr(d_name,".out"))
     {
      char* file = malloc(strlen(dir_name) + strlen(d_name) + 2);
      printf("DELETE: %s/%s\n", dir_name, d_name);
      strcpy(file,dir_name);
      strcat(file,"/");
      strcat(file,d_name);
      remove(file);
      free(file);
    }
    else
      printf("%s/%s\n", dir_name, d_name);

    /* Vezi daca e subdirector pentru "d". */
    if(child->d_type & DT_DIR)
    { 
    /* Vezi daca nu e d sau parintele lui d. */

      if(strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0)
      {
        int path_length;
        char path[PATH_MAX];
    /* Concatenam in path fisierul la care s-a ajuns. */
        snprintf(path, PATH_MAX, "%s/%s", dir_name, d_name); 
    /* Chemam recursiv "sterge" pentru noua cale. */
        sterge(path);
      }
    }
  }
/* Inchide folder. */
  closedir(d);
}

int main(int argc, char const *argv[])
{
  char file[100];
  sterge(argv[1]);
  return 0;
}
