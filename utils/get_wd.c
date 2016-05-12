#include <stat.h>

char *get_wd() {
  int curr_inode;
  char *path;
  char *temp;
  struct stat wd = stat(open('.'));
  close('.');

  curr_inode = wd->st_ino;

  /*read .. and find dir with same inode as us.
    prepend that to path. Rinse and repeat.
    break when no .. (root).
  */

}
