#include<stdlib.h>
#include<string.h>

/**
 * Creates a copy of the given URL with its querystring sorted. The URL is
 * assumed to be valid and without any fragment. If the URL doesn't have a
 * querystring, a simple copy is returned.
 * 
 * A returned non-NULL URL must be freed by the caller.
 */
extern char
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

