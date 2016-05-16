#include <stdlib.h>

/*
 * Function that splits strings into array of strings depending on
 * seperator.
 * TODO: split into multiple functions
 */
char **string_split(char *str, char seperator)
{
	char **ret;
	char *ret_ptr;
	char *ptr;
	char *fast;
	int count = 0;
	int word_count = 0;

	ptr = str;
	while (*ptr != 0) {
		while (*ptr == seperator)
			ptr++;
		if (*ptr == 0)
			break;
		while (*ptr != seperator && *ptr != 0)
			ptr++;
		count++;
	}

	/* empty string after split */
	if (count == 0) {
		ret = malloc(sizeof(char *)*1);
		ret[0] = NULL;
		return ret;
	}

	ret = malloc(sizeof(char *) * (count+2));
	ptr = str;

	while (*ptr != 0) {
		while (*ptr == seperator)
			ptr++;
		count = 0;
		fast = ptr;

		while (*fast != seperator && *fast != 0) {
			count++;
			fast++;
		}

		ret[word_count] = malloc(sizeof(char) * (count + 1));
		ret_ptr = ret[word_count];

		while (*ptr != seperator && *ptr != 0) {
			*ret_ptr = *ptr;
			ret_ptr++;
			ptr++;
		}

		while (*ptr == seperator)
			ptr++;
		*ret_ptr = 0;
		word_count++;
	}
	ret[word_count] = 0;

	return ret;
}
