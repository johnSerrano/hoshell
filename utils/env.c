int print_env(char** envp) {
  char** env;
  for (env = envp; *env != 0; env++)
  {
    char* thisEnv = *env;
    printf("%s\n", thisEnv);
  }
  return(0);
}
