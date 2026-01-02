
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

#include "../utils/memory.h"


char *find_and_replace(char *src, char *search, char *replace) {

    if (!src || !search || !replace)
        return NULL;
    
    if (strcmp(src, "") == 0)
        return strdup(src);

    int count = 0;
    char *tmp = src;
    
    if (count == 0) {
        return (char*) strdup(src);
    }
   
    /* We must assign the result of strstr() to 'tmp' to jump to the match.
     *
     * WHY THIS MATTERS:
     * If we don't update 'tmp' to the match position, the instruction 'tmp += len'
     * only advances from the OLD position.
     *
     * Example: searching "foo" (len 3) inside ".......foo"
     * 1. strstr finds "foo" far ahead.
     * 2. We blindly add 3 bytes to our current start position.
     * 3. We land on the dots ("..."), effectively NOT skipping "foo".
     * 4. Next loop: strstr finds the EXACT SAME "foo" again.
     */
    while ((tmp = strstr(tmp, search)) != NULL) {
        count++;
        /*Start count AFTER the word which we found. */
        tmp += strlen(search); 
    }  

    /*calculate the new string */
    int search_len = strlen(search);
    int replace_len = strlen(replace);
    /*orginal length, differences of replaced string and the old searched string
     * and null terminator */
    int new_len = strlen(src) + (count * (replace_len - search_len)) + 1;

    /*new string components */
    char *result = xmalloc(new_len);

    char *p_res = result; /*pointer to write in the new str */
    char *p_src = src;
    char *next_occ; /*pointer to next occurences */

    while ((next_occ = strstr(p_src, search))) {
        /*we copy the part before the occ */
        int len_segment = next_occ - p_src;
        memcpy(p_res, p_src, len_segment);
        p_res += len_segment;

        /*replace */
        memcpy(p_res, replace, replace_len);
        p_res += replace_len;

        /* update the src for the next search */
        p_src = next_occ + search_len;
    }
    strcpy(p_res, p_src);

    return result;
}

