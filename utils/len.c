int len_command(char **command) {
  int len = 0;
  while (*command != 0) {
    len++;
    command++;
  }
  return len;
}
