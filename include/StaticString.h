#ifndef STATICSTRING_H
#define STATICSTRING_H

#include <stdint.h>

#ifndef SSTR_MAX_LENGTH
#define SSTR_MAX_LENGTH ((uint8_t)(-1)) // Maximum length of a StaticString excluding the null terminator
#endif

#define IS_WHITESPACE(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')

typedef struct
{
    char static_string[SSTR_MAX_LENGTH + 1];
    uint32_t string_length;
} StaticString;

/**
 * @brief Initializes a StaticString structure.
 *
 * Sets the string length to 0 and null-terminates the internal character buffer.
 *
 * @param ss Pointer to the StaticString to initialize.
 *
 * @return void
 */
static inline void sstr_init(StaticString *ss)
{
    ss->string_length = 0;
    ss->static_string[0] = '\0';
}

/**
 * @brief Initializes a StaticString from a null-terminated C string.
 *
 * Copies characters from the given C string into the StaticString's internal buffer,
 * truncating if necessary to fit within the maximum allowed length.
 *
 * @param ss Pointer to the StaticString to initialize.
 * @param cstr Null-terminated C string to copy from.
 *
 * @return void
 */
static inline void sstr_from_cstr(StaticString *ss, const char *cstr)
{
    uint32_t i;
    for (i = 0; i < SSTR_MAX_LENGTH && cstr[i] != '\0'; i++)
    {
        ss->static_string[i] = cstr[i];
    }
    ss->static_string[i] = '\0';
    ss->string_length = i;
}

/**
 * @brief Clears the contents of a StaticString.
 *
 * Sets all characters in the internal buffer to null and resets the string length to 0.
 *
 * @param ss Pointer to the StaticString to clear.
 *
 * @return void
 */
static inline void sstr_clear(StaticString *ss)
{
    for (uint32_t i = 0; i <= SSTR_MAX_LENGTH; i++)
    {
        ss->static_string[i] = '\0';
    }
    ss->string_length = 0;
}

/**
 * @brief Appends a single character to the end of a StaticString.
 *
 * Adds the given character to the end of the string, null-terminates the result,
 * and updates the string length. If the string is already full, the character is not added.
 *
 * @param ss Pointer to the StaticString to modify.
 * @param character The character to append.
 *
 * @return uint32_t 1 if the character was appended, 0 if the string was full.
 */
static inline uint32_t sstr_append(StaticString *ss, const char character)
{
    if (ss->string_length < SSTR_MAX_LENGTH)
    {
        ss->static_string[ss->string_length] = character;
        ss->static_string[ss->string_length + 1] = '\0';
        ss->string_length++;
        return 1;
    }
    return 0;
}

/**
 * @brief Appends a null-terminated C string to a StaticString.
 *
 * Safely appends characters from the given C string to the end of the StaticString,
 * truncating if necessary to prevent buffer overflow. If the input string is NULL
 * or the StaticString is already full, the operation is skipped.
 *
 * @param ss Pointer to the StaticString to modify.
 * @param cstr Null-terminated C string to append.
 *
 * @return uint32_t The number of characters appended.
 */
static inline uint32_t sstr_append_cstr(StaticString *ss, const char *cstr)
{
    if (cstr == NULL || ss->string_length >= SSTR_MAX_LENGTH)
    {
        return 0;
    }

    uint32_t i = 0;
    for (i = 0; i < (SSTR_MAX_LENGTH - ss->string_length) && cstr[i] != '\0'; i++)
    {
        ss->static_string[ss->string_length + i] = cstr[i];
    }
    ss->static_string[ss->string_length + i] = '\0';
    ss->string_length += i;
    return i;
}

/**
 * @brief Replaces a character in a StaticString at a given index.
 *
 * If the index is within the bounds of the current string length, replaces
 * the character at that index with the given character.
 *
 * @param ss Pointer to the StaticString to modify.
 * @param index Zero-based index of the character to replace.
 * @param character The new character to write at the specified index.
 *
 * @return uint32_t 1 if the replacement was successful, 0 if the index was out of bounds.
 */
static inline uint32_t sstr_replace_char_from_index(StaticString *ss, uint32_t index, char character)
{
    if (index >= ss->string_length)
    {
        return 0;
    }

    ss->static_string[index] = character;
    return 1;
}

/**
 * @brief Replaces all occurrences of a character in a StaticString.
 *
 * Iterates through the StaticString and replaces every instance of the specified
 * old character with the new character.
 *
 * @param ss Pointer to the StaticString to modify.
 * @param old_char The character to search for.
 * @param new_char The character to replace with.
 *
 * @return uint32_t The number of characters replaced.
 */
static inline uint32_t sstr_replace_all_chars(StaticString *ss, char old_char, char new_char)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < ss->string_length; i++)
    {
        if (ss->static_string[i] == old_char)
        {
            ss->static_string[i] = new_char;
            count++;
        }
    }
    return count;
}

/**
 * @brief Trims trailing whitespace characters from a StaticString.
 *
 * Removes whitespace characters (as defined by IS_WHITESPACE) from the end of the
 * string, updating the string length and null-terminator accordingly.
 *
 * @param ss Pointer to the StaticString to modify.
 *
 * @return uint32_t The number of characters trimmed from the end.
 */
static inline uint32_t sstr_trim_trailing(StaticString *ss)
{
    uint32_t count = 0;
    while (ss->string_length > 0 && IS_WHITESPACE(ss->static_string[ss->string_length - 1]))
    {
        ss->string_length--;
        count++;
    }
    ss->static_string[ss->string_length] = '\0';
    return count;
}

/**
 * @brief Trims leading whitespace characters from a StaticString.
 *
 * Efficiently removes leading whitespace characters by finding the first
 * non-whitespace character and shifting the remainder of the string forward.
 *
 * @param ss Pointer to the StaticString to modify.
 *
 * @return uint32_t The number of characters removed from the beginning.
 */
static inline uint32_t sstr_trim_leading(StaticString *ss)
{
    uint32_t offset = 0;

    while (offset < ss->string_length && IS_WHITESPACE(ss->static_string[offset]))
    {
        offset++;
    }

    if (offset > 0)
    {
        for (uint32_t i = 0; i <= ss->string_length - offset; i++)
        {
            ss->static_string[i] = ss->static_string[i + offset];
        }
        ss->string_length -= offset;
    }

    return offset;
}

/**
 * @brief Trims both leading and trailing whitespace characters from a StaticString.
 *
 * Calls sstr_trim_leading() and sstr_trim_trailing() to remove whitespace characters
 * from both ends of the string, updating its length and content in-place.
 *
 * @param ss Pointer to the StaticString to modify.
 *
 * @return uint32_t The total number of characters removed.
 */
static inline uint32_t sstr_trim(StaticString *ss)
{
    uint32_t count = 0;
    count += sstr_trim_leading(ss);
    count += sstr_trim_trailing(ss);
    return count;
}

/**
 * @brief Removes all whitespace characters from a StaticString (optimized version).
 *
 * Uses a single pass with a write index to compact non-whitespace characters.
 *
 * @param ss Pointer to the StaticString to modify.
 *
 * @return void
 */
static inline void sstr_strip_all_whitespace(StaticString *ss)
{
    uint32_t write = 0;
    for (uint32_t read = 0; read < ss->string_length; read++)
    {
        if (!IS_WHITESPACE(ss->static_string[read]))
        {
            ss->static_string[write++] = ss->static_string[read];
        }
    }
    ss->static_string[write] = '\0';
    ss->string_length = write;
}

/**
 * @brief Compares two StaticString instances for equality.
 *
 * Checks whether both strings have the same length and identical characters.
 *
 * @param ss1 Pointer to the first StaticString.
 * @param ss2 Pointer to the second StaticString.
 *
 * @return uint32_t 1 if the strings are equal, 0 otherwise.
 */
static inline uint32_t sstr_equals(const StaticString *ss1, const StaticString *ss2)
{
    if (ss1->string_length != ss2->string_length)
        return 0;

    for (uint32_t i = 0; i < ss1->string_length; i++)
    {
        if (ss1->static_string[i] != ss2->static_string[i])
            return 0;
    }

    return 1;
}

/**
 * @brief Compares a StaticString with a null-terminated C string for equality.
 *
 * Checks whether the StaticString and the C string contain the same characters
 * and have the same length. If the C string is NULL, the function returns 0.
 *
 * @param ss Pointer to the StaticString.
 * @param cstr Pointer to the null-terminated C string.
 *
 * @return uint32_t 1 if the strings are equal, 0 otherwise.
 */
static inline uint32_t sstr_equals_cstr(const StaticString *ss, const char *cstr)
{
    if (cstr == NULL)
    {
        return 0;
    }

    uint32_t i = 0;

    while (i < ss->string_length && cstr[i] != '\0')
    {
        if (ss->static_string[i] != cstr[i])
        {
            return 0;
        }
        i++;
    }
    return (i == ss->string_length && cstr[i] == '\0');
}

/**
 * @brief Returns a pointer to the internal null-terminated C string.
 *
 * Provides read-only access to the internal character array of the StaticString.
 * The returned string is guaranteed to be null-terminated.
 *
 * @param ss Pointer to the StaticString.
 *
 * @return const char* Pointer to the null-terminated C string.
 */
static inline const char *sstr_to_cstr(const StaticString *ss)
{
    return ss->static_string;
}

/**
 * @brief Removes and returns the last character from the StaticString.
 *
 * If the StaticString is not empty, this function removes the last character,
 * updates the string length, and returns the removed character.
 * If the string is empty, it returns 0.
 *
 * @param ss Pointer to the StaticString.
 *
 * @return char The last character if available, otherwise 0.
 */
static inline char sstr_pop(StaticString *ss)
{
    char return_char = 0;
    if (ss->string_length > 0)
    {
        return_char = ss->static_string[ss->string_length - 1];
        ss->static_string[ss->string_length - 1] = '\0';
        ss->string_length--;
    }
    return return_char;
}

/**
 * @brief Truncates the StaticString to the specified length.
 *
 * Shortens the StaticString to the given length if the new length is less than
 * or equal to the current length. Ensures the string remains null-terminated.
 *
 * @param ss Pointer to the StaticString to truncate.
 * @param new_length The desired new length of the string.
 *
 * @return uint32_t 1 if the truncation was successful, 0 if new_length is greater than current length.
 */
static inline uint32_t sstr_truncate(StaticString *ss, uint32_t new_length)
{
    if (new_length > ss->string_length || new_length > SSTR_MAX_LENGTH)
    {
        return 0;
    }

    ss->string_length = new_length;
    ss->static_string[ss->string_length] = '\0';
    return 1;
}

/**
 * @brief Returns the current length of the StaticString.
 *
 * This function provides access to the length of the string,
 * excluding the null terminator.
 *
 * @param ss Pointer to the StaticString.
 *
 * @return uint32_t The number of characters in the string.
 */
static inline uint32_t sstr_length(const StaticString *ss)
{
    return ss->string_length;
}

/**
 * @brief Reverses the contents of the StaticString in place.
 *
 * Reverses the characters of the StaticString without allocating
 * additional memory. The operation is done in-place.
 *
 * @param ss Pointer to the StaticString to be reversed.
 */
static inline void sstr_reverse(StaticString *ss)
{
    if (ss->string_length == 0)
    {
        return;
    }
    uint32_t i = 0, j = ss->string_length - 1;
    while (i < j)
    {
        char temp = ss->static_string[i];
        ss->static_string[i] = ss->static_string[j];
        ss->static_string[j] = temp;
        i++;
        j--;
    }
}

/**
 * @brief Copies the contents of one StaticString to another.
 *
 * Performs a deep copy of the contents and string length from the source
 * StaticString (`ss2`) to the destination StaticString (`ss1`), including
 * null-termination. Returns void if the source StaticString (`ss2`) is too long.
 *
 * @param ss1 Pointer to the destination StaticString.
 * @param ss2 Pointer to the source StaticString.
 *
 * @return void
 */
static inline void sstr_copy(StaticString *ss1, const StaticString *ss2)
{
    if (ss2->string_length > SSTR_MAX_LENGTH)
    {
        return;
    }
    ss1->string_length = ss2->string_length;
    for (uint32_t i = 0; i < ss1->string_length; i++)
    {
        ss1->static_string[i] = ss2->static_string[i];
    }
    ss1->static_string[ss1->string_length] = '\0';
}

/**
 * @brief Converts all lowercase letters in the StaticString to uppercase.
 *
 * Iterates through the StaticString and converts each ASCII lowercase
 * character ('a' to 'z') to its uppercase equivalent ('A' to 'Z').
 *
 * @param ss Pointer to the StaticString to modify.
 * @return uint32_t The number of characters that were converted.
 */
static inline uint32_t sstr_to_uppercase(StaticString *ss)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < ss->string_length; i++)
    {
        if (ss->static_string[i] >= 'a' && ss->static_string[i] <= 'z')
        {
            ss->static_string[i] -= 'a' - 'A';
            count++;
        }
    }
    return count;
}

/**
 * @brief Converts all uppercase letters in the StaticString to lowercase.
 *
 * Iterates through the StaticString and converts each ASCII uppercase
 * character ('A' to 'Z') to its lowercase equivalent ('a' to 'z').
 *
 * @param ss Pointer to the StaticString to modify.
 * @return uint32_t The number of characters that were converted.
 */
static inline uint32_t sstr_to_lowercase(StaticString *ss)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < ss->string_length; i++)
    {
        if (ss->static_string[i] >= 'A' && ss->static_string[i] <= 'Z')
        {
            ss->static_string[i] += 'a' - 'A';
            count++;
        }
    }
    return count;
}
#endif