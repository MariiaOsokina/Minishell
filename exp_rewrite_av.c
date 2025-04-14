int main() {
    // Original array of string literals (not malloc'ed)
    char *original[] = {"hello", "world", "example"};
    int size = sizeof(original) / sizeof(original[0]);

    // Rewrite array to use malloc'd copies
    rewrite_array(original, size);

    // Now all strings in original[] are dynamically allocated
    for (int i = 0; i < size; ++i) {
        printf("%s\n", original[i]);
        free(original[i]);  // Remember to free each string
    }

    return 0;
}


void rewrite_array(char **array, int size) {
    char *new_str;
    for (int i = 0; i < size; ++i) {
        // Make a copy of the string using strdup
        new_str = ft_strdup(array[i]);
        if (!new_str) {
            fprintf(stderr, "Memory allocation failed for string %d\n", i);
            exit(EXIT_FAILURE);
        }
        array[i] = new_str;
    }
}