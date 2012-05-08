#include<stdlib.h>
#include<string.h>

/**
 * Creates a copy of the given URL with its querystring sorted. The URL is
 * assumed to be valid and without any fragment. If the URL doesn't have a
 * querystring, a simple copy is returned.
 * 
 * A returned non-NULL URL must be freed by the caller.
 */
char
* querysort(const char *url);

struct query_param {
  const char *value;
  short length;
};

typedef struct query_param param;

static void   sort_params(const char *url, const int position, char *sorted_url);
static int   count_params(const char *url, const int position);
static void search_params(const char *query_string, const int count, param params[]);
static int compare_params(const void *a, const void *b);
static void  apply_params(const param params[], const int count, char *sorted_url, int position);

char *
querysort(const char *url)
{
	char *sorted_url, *query_string;

	sorted_url = malloc(strlen(url) + 1);
	
	if (sorted_url == NULL) {
		return NULL;
	}
	
	strcpy(sorted_url, url);
	query_string = strchr(sorted_url, '?');

	if(query_string != NULL && query_string[1] != '\0') {
		int position = &query_string[1] - sorted_url;
		sort_params(url, position, sorted_url);
	}

	return sorted_url;
}

static void
sort_params(const char *url, const int position, char *sorted_url)
{
	int count = count_params(url, position);
	param params[count];
	search_params(&url[position], count, params);
	qsort(params, count, sizeof(param), compare_params);
	apply_params(params, count, sorted_url, position);
}

static int
count_params(const char *url, const int position)
{
	int count = 1;
	for (int i = position; url[i] != '\0'; i++) {
		count += (url[i] == '&');
	}
	return count;
}

static void
search_params(const char *query_string, const int count, param params[])
{
	int i = 0, p = 0;
	do {
		params[p].value = &query_string[i];
		params[p].length = 0;
		
		while (query_string[i] != '&' && query_string[i] != '\0') {
			params[p].length++;
			i++;
		}
		
		p++;
		i += (query_string[i] == '&');
	} while (query_string[i] != '\0');
}

static int
compare_params(const void *a, const void *b)
{
	const param *x = (const param *) a;
	const param *y = (const param *) b;
	
	int min_length = (x->length < y->length) ? x->length : y->length;
	int compare = strncmp(x->value, y->value, min_length);
	return (compare == 0) ? x->length - y->length : compare;
}

static void
apply_params(const param params[], const int count, char *sorted_url, int position)
{
	for (int p = 0; p < count; p++) {
		memcpy(&sorted_url[position], params[p].value, params[p].length);
		position += params[p].length;
		
		if (sorted_url[position] != '\0') {
			sorted_url[position++] = '&';
		}
	}
}

