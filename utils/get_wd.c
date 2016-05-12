#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include <stdio.h>
#include <string.h>

/* NOTE: LEAKS 200KB every time you run pwd */
/* Does not work with from inside a mounted filesystem */

char *path_concat(char *path, char *newname);
char *get_wd_recurse(char *path, char *reverse_path, unsigned int search_inode);
char *get_wd();
int is_root(DIR *dir, unsigned int self_inode);
unsigned int get_self_inode(DIR *dir);

void pwd() {
  char *wd = get_wd();

  if (wd == NULL) return;

  write(1, wd, str_len(wd));
  write(1, "\n", 1);
}

char *get_wd() {
  char *path = malloc(sizeof(char) * 1);
  char *reverse_path = malloc(sizeof(char) * 3);
  DIR *dir = opendir(".");
  int self_inode = get_self_inode(dir);
  string_copy(path, "");
  string_copy(reverse_path, "..");
  return get_wd_recurse(path, reverse_path, self_inode);
}


char *get_wd_recurse(char *path, char *reverse_path, unsigned int search_inode) {
  DIR *dir = opendir(reverse_path);
  unsigned int self_inode = get_self_inode(dir);
  int root_boolean = is_root(dir, self_inode);
  struct dirent *dir_entry;
  dir_entry = readdir(dir);

   while (dir_entry != NULL) {
     if (dir_entry->d_ino == search_inode) {
       /* prepend name/ to path */
       path = path_concat(path, dir_entry->d_name);
       /* break recursion if no parent */
       if (root_boolean) {
         /* PROBABLY WORKS BUT COULD CAUSE BUG MAYBE */
         path = path_concat(path, "");
         return path;
       }

       reverse_path = path_concat(reverse_path, "..");
       return get_wd_recurse(path, reverse_path, self_inode);
     }
     dir_entry = readdir(dir);
  }
  return NULL;
}

/* returns 1 if dir is root, 0 otherwise */
int is_root(DIR *dir, unsigned int self_inode) {
  int ret = 1;
  struct dirent *dir_entry;
  if (!dir) return -1;
  dir_entry = readdir(dir);
  while (dir_entry != NULL) {
    if (strings_compare(dir_entry->d_name, "..") == 0) {
      if ((unsigned int) dir_entry->d_ino != self_inode)
        ret = 0;
    }
    dir_entry = readdir(dir);
  }
  rewinddir(dir);
  return ret;
}

/* returns the inode of this directory */
unsigned int get_self_inode(DIR *dir) {
  unsigned int ret = 0;
  struct dirent *dir_entry;
  dir_entry = readdir(dir);
   while (dir_entry != NULL) {
    if (strings_compare(dir_entry->d_name, ".") == 0) {
      ret = dir_entry->d_ino;
    }
    dir_entry = readdir(dir);
  }
  rewinddir(dir);
  return ret;
}

/*Don't use this unless you know what you are doing, it can damage things*/
char *path_concat(char *path, char *newname) {
  int size = str_len(newname) + str_len(path) + 2;
  char *temp = malloc(size * sizeof(char));
  string_copy(temp, newname);
  str_cat(temp, "/");
  str_cat(temp, path);
  free(path);
  path = temp;
  return path;
}
