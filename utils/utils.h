char *int_to_string(int n);
int string_to_int(char *s);
int len_command(char **command);
int strings_compare(char *s1, const char *s2);
void cmd_exit(char **command);
char *string_copy(char *dest, char *src);
char *read_line(int fd);
char **string_split(char *str, char seperator);
