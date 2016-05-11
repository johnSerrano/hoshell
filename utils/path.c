/*

    #include <stdlib.h>
    #include "utils.h"

    int attach_path(char *cmd) {
      char *ret;
      int index;
      int fd;
      function(ret, sizeof(ret)); /*no idea what this does yet*/

/* weir line...RM when testing...

      for (index=0; search_path[index] != NULL; index++) {
        strcpy(ret, search_path[index]);
        strncat(ret, cmd, strlen(cmd));
        if ((fd = open(ret, O_RDONLY)) > 0) {
          strncpy(cmd, ret, strlen(ret));
          close(fd);
          return 0;
        }
      }
      return 0;
    }

*/
