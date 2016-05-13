#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

char *do_work(int, char*);
char *add_digit(char digit, char *str);

char *int_to_string(int n)
{
  char *str = malloc(sizeof(char)*1);
  *str = 0;

	if (n < 0) {
    str = add_digit('-', str);
	} else {
    n = 0-n;
  }
	if (n == 0) {
    str = add_digit('0', str);
	}
	else {
		str = do_work(n, str);
	}
  return str;
}

char *add_digit(char digit, char *str) {
  char *newdigit = malloc(2*sizeof(char));
  newdigit[0] = digit;
  newdigit[1] = 0;
  str = str_cat(str, newdigit);
  return str;
}

char *do_work(int n, char *str)
{
	int divisor = 1;
	int a = n;
	while (a < -9) {
		a /= 10;
		divisor *= 10;
	}

	while (n < 0) {
		int to_print = n / divisor;
		n -= to_print * divisor;
		divisor /= 10;
    to_print = 0-to_print;
	  str = add_digit('0' + to_print, str);

	}
  return str;
}
