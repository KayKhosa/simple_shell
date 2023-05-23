#include "shell.h"

char *_strdup(const char *str) {
    if (str == NULL)
        return NULL;
        
    size_t length = strlen(str);
    char *new_str = malloc((length + 1) * sizeof(char));
    if (new_str == NULL)
        return NULL;
        
    strcpy(new_str, str);
    return new_str;
}

char *concat_all(const char *name, const char *sep, const char *value) {
    if (name == NULL || sep == NULL || value == NULL)
        return NULL;
        
    size_t len_name = strlen(name);
    size_t len_sep = strlen(sep);
    size_t len_value = strlen(value);
    
    char *result = malloc((len_name + len_sep + len_value + 1) * sizeof(char));
    if (result == NULL)
        return NULL;
        
    strcpy(result, name);
    strcat(result, sep);
    strcat(result, value);
    
    return result;
}

size_t _strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

int _putchar(char c) {
    return putchar(c);
}

void _puts(const char *str) {
    size_t length = _strlen(str);
    for (size_t i = 0; i < length; i++)
        _putchar(str[i]);
}
