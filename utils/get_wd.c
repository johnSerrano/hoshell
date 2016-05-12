#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

char *path_concat(char *path, char *newname);
char *get_wd_recurse(char *path, char *reverse_path, unsigned int search_inode);
char *get_wd();

void pwd() {
  char *wd = get_wd();

  /* TODO failing because wd is returning null */

  write(1, wd, str_len(wd));
}

char *get_wd() {
  char *path = "";
  char *reverse_path = "..";
  DIR *dir = opendir(".");
  struct dirent *dir_ent = readdir(dir);
  return get_wd_recurse(path, reverse_path, dir_ent->d_ino);
}


char *get_wd_recurse(char *path, char *reverse_path, unsigned int search_inode) {
  DIR *dir = opendir(reverse_path);
  struct dirent *dir_entry = readdir(dir);
  int parent_exists_boolean = 0;
  unsigned int self_inode;

  while (dir_entry != NULL) {
    if (strings_compare(dir_entry->d_name, "..") == 0) {
      parent_exists_boolean = 1;
    } else if (strings_compare(dir_entry->d_name, ".") == 0) {
      self_inode = dir_entry->d_ino;
    }
    if (dir_entry->d_ino == search_inode) {
      /* prepend name/ to path */
      path = path_concat(path, dir_entry->d_name);
      /* break recursion if no parent */
      if (!parent_exists_boolean) {
        /* PROBABLY WORKS BUT COULD CAUSE BUG MAYBE */
        path = path_concat(path, "");
        return path;
      }

      reverse_path = path_concat(reverse_path, "../");
      return get_wd_recurse(path, reverse_path, self_inode);
    }
    dir_entry = readdir(dir);
  }
  return NULL;
}

/*Don't use this unless you know what you are doing, it can damage things*/
char *path_concat(char *path, char *newname) {
  int size = str_len(newname) + str_len(path) + 2;
  char *temp = malloc(size * sizeof(char));
  string_copy(temp, newname);
  str_cat(temp, "/");
  str_cat(temp, path);
  /* free(path);*/
  path = temp;
  return path;
}
