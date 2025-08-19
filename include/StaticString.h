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
 * @param sstr Pointer to the StaticString to initialize.
 *
 * @return void
 */
inline void sstr_init(StaticString *sstr)
{
    sstr->string_length = 0;
    sstr->static_string[0] = '\0';
}

/**
 * @brief Initializes a StaticString from a null-terminated C string.
 *
 * Copies characters from the given C string into the StaticString's internal buffer,
 * truncating if necessary to fit within the maximum allowed length.
 *
 * @param sstr Pointer to the StaticString to initialize.
 * @param cstr Null-terminated C string to copy from.
 *
 * @return void
 */
inline void sstr_from_cstr(StaticString *sstr, const char *cstr)
{
    uint32_t i;
    for (i = 0; i < SSTR_MAX_LENGTH && cstr[i] != '\0'; i++)
    {
        sstr->static_string[i] = cstr[i];
    }
    sstr->static_string[i] = '\0';
    sstr->string_length = i;
}

/**
 * @brief Clears the contents of a StaticString.
 *
 * Sets all characters in the internal buffer to null and resets the string length to 0.
 *
 * @param sstr Pointer to the StaticString to clear.
 *
 * @return void
 */
inline void sstr_clear(StaticString *sstr)
{
    for (uint32_t i = 0; i <= SSTR_MAX_LENGTH; i++)
    {
        sstr->static_string[i] = '\0';
    }
    sstr->string_length = 0;
}

/**
 * @brief Appends a single character to the end of a StaticString.
 *
 * Adds the given character to the end of the string, null-terminates the result,
 * and updates the string length. If the string is already full, the character is not added.
 *
 * @param sstr Pointer to the StaticString to modify.
 * @param character The character to append.
 *
 * @return uint32_t 1 if the character was appended, 0 if the string was full.
 */
inline uint32_t sstr_append(StaticString *sstr, const char character)
{
    if (sstr->string_length < SSTR_MAX_LENGTH)
    {
        sstr->static_string[sstr->string_length] = character;
        sstr->static_string[sstr->string_length + 1] = '\0';
        sstr->string_length++;
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
 * @param sstr Pointer to the StaticString to modify.
 * @param cstr Null-terminated C string to append.
 *
 * @return uint32_t The number of characters appended.
 */
inline uint32_t sstr_append_cstr(StaticString *sstr, const char *cstr)
{
    if (cstr == NULL || sstr->string_length >= SSTR_MAX_LENGTH)
    {
        return 0;
    }

    uint32_t i = 0;
    for (i = 0; i < (SSTR_MAX_LENGTH - sstr->string_length) && cstr[i] != '\0'; i++)
    {
        sstr->static_string[sstr->string_length + i] = cstr[i];
    }
    sstr->static_string[sstr->string_length + i] = '\0';
    sstr->string_length += i;
    return i;
}

/**
 * @brief Replaces a character in a StaticString at a given index.
 *
 * If the index is within the bounds of the current string length, replaces
 * the character at that index with the given character.
 *
 * @param sstr Pointer to the StaticString to modify.
 * @param index Zero-based index of the character to replace.
 * @param character The new character to write at the specified index.
 *
 * @return uint32_t 1 if the replacement was successful, 0 if the index was out of bounds.
 */
inline uint32_t sstr_replace_char_from_index(StaticString *sstr, uint32_t index, char character)
{
    if (index >= sstr->string_length)
    {
        return 0;
    }

    sstr->static_string[index] = character;
    return 1;
}

/**
 * @brief Replaces all occurrences of a character in a StaticString.
 *
 * Iterates through the StaticString and replaces every instance of the specified
 * old character with the new character.
 *
 * @param sstr Pointer to the StaticString to modify.
 * @param old_char The character to search for.
 * @param new_char The character to replace with.
 *
 * @return uint32_t The number of characters replaced.
 */
inline uint32_t sstr_replace_all_chars(StaticString *sstr, char old_char, char new_char)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < sstr->string_length; i++)
    {
        if (sstr->static_string[i] == old_char)
        {
            sstr->static_string[i] = new_char;
            count++;
        }
    }
    return count;
}

/**
 * @brief Inserts a single character into a StaticString at a given index.
 *
 * Shifts all characters at and after the given index to the right by one position
 * and inserts the given character at the specified index. If the index is greater
 * than the current string length, the character is not inserted.
 *
 * @param sstr Pointer to the StaticString to modify.
 * @param index Zero-based index where the character should be inserted.
 * @param character The character to insert.
 *
 * @return uint32_t The new length of the string, or 0 if the index was out of bounds.
 */
inline uint32_t sstr_insert_char_at(StaticString *sstr, uint32_t index, char character)
{
    if (index > sstr->string_length || sstr->string_length >= SSTR_MAX_LENGTH)
    {
        return 0;
    }

    for (uint32_t i = sstr->string_length; i > index; --i)
    {
        sstr->static_string[i] = sstr->static_string[i - 1];
    }

    sstr->static_string[index] = character;
    sstr->string_length++;
    sstr->static_string[sstr->string_length] = '\0';

    return sstr->string_length;
}

/**
 * @brief Removes a single character from a StaticString at a given index.
 *
 * Shifts all characters at and after the given index to the left by one position
 * and removes the character at the specified index. If the index is greater
 * than the current string length, the function does not modify the string.
 *
 * @param sstr Pointer to the StaticString to modify.
 * @param index Zero-based index of the character to remove.
 *
 * @return uint32_t The new length of the string.
 */
inline uint32_t sstr_remove_at(StaticString *sstr, uint32_t index)
{
    if (index >= sstr->string_length)
    {
        return sstr->string_length;
    }

    for (int i = index; i < sstr->string_length - 1; i++)
    {
        sstr->static_string[i] = sstr->static_string[i + 1];
    }
    sstr->static_string[sstr->string_length - 1] = '\0';
    sstr->string_length--;
    return sstr->string_length;
}

/**
 * @brief Removes a range of characters from a StaticString.
 *
 * Shifts all characters at and after the given start index to the left by the
 * given range length and removes the characters at the specified range.
 * If the start index is greater than the current string length, the function
 * does not modify the string.
 *
 * @param sstr Pointer to the StaticString to modify.
 * @param start Zero-based index of the first character to remove.
 * @param end Zero-based index of the last character to remove.
 *
 * @return uint32_t The new length of the string.
 */
inline uint32_t sstr_remove_range(StaticString *sstr, uint32_t start, uint32_t end)
{
    if (start >= sstr->string_length || end >= sstr->string_length || start > end)
    {
        return sstr->string_length;
    }

    for (uint32_t i = end + 1; i < sstr->string_length; i++)
    {
        sstr->static_string[i - (end - start + 1)] = sstr->static_string[i];
    }

    sstr->string_length = sstr->string_length - (end - start + 1);
    sstr->static_string[sstr->string_length] = '\0';

    return sstr->string_length;
}

/**
 * @brief Copies a substring from one StaticString to another.
 *
 * Copies a range of characters from the source StaticString to the destination
 * StaticString. The range is specified by the start and end indices, which
 * are zero-based and inclusive. The function returns 1 if the operation is
 * successful, or 0 if the start index is greater than the current string
 * length, the end index is greater than the current string length, or the
 * start index is greater than the end index.
 *
 * @param sstr_source Pointer to the source StaticString.
 * @param sstr_dest Pointer to the destination StaticString.
 * @param start Zero-based index of the first character to copy.
 * @param end Zero-based index of the last character to copy.
 *
 * @return uint8_t 1 if the operation is successful, 0 if the indices are invalid.
 */
inline uint8_t sstr_substring(const StaticString *sstr_source, StaticString *sstr_dest, uint32_t start, uint32_t end)
{
    if (start >= sstr_source->string_length || end >= sstr_source->string_length || start > end)
    {
        return 0;
    }

    sstr_dest->string_length = end - start + 1;
    for (uint32_t i = 0; i < sstr_dest->string_length; i++)
    {
        sstr_dest->static_string[i] = sstr_source->static_string[start + i];
    }
    sstr_dest->static_string[sstr_dest->string_length] = '\0';
    return 1;
}

/**
 * @brief Trims trailing whitespace characters from a StaticString.
 *
 * Removes whitespace characters (as defined by IS_WHITESPACE) from the end of the
 * string, updating the string length and null-terminator accordingly.
 *
 * @param sstr Pointer to the StaticString to modify.
 *
 * @return uint32_t The number of characters trimmed from the end.
 */
inline uint32_t sstr_trim_trailing(StaticString *sstr)
{
    uint32_t count = 0;
    while (sstr->string_length > 0 && IS_WHITESPACE(sstr->static_string[sstr->string_length - 1]))
    {
        sstr->string_length--;
        count++;
    }
    sstr->static_string[sstr->string_length] = '\0';
    return count;
}

/**
 * @brief Trims leading whitespace characters from a StaticString.
 *
 * Efficiently removes leading whitespace characters by finding the first
 * non-whitespace character and shifting the remainder of the string forward.
 *
 * @param sstr Pointer to the StaticString to modify.
 *
 * @return uint32_t The number of characters removed from the beginning.
 */
inline uint32_t sstr_trim_leading(StaticString *sstr)
{
    uint32_t offset = 0;

    while (offset < sstr->string_length && IS_WHITESPACE(sstr->static_string[offset]))
    {
        offset++;
    }

    if (offset > 0)
    {
        for (uint32_t i = 0; i <= sstr->string_length - offset; i++)
        {
            sstr->static_string[i] = sstr->static_string[i + offset];
        }
        sstr->string_length -= offset;
    }

    return offset;
}

/**
 * @brief Trims both leading and trailing whitespace characters from a StaticString.
 *
 * Calls sstr_trim_leading() and sstr_trim_trailing() to remove whitespace characters
 * from both ends of the string, updating its length and content in-place.
 *
 * @param sstr Pointer to the StaticString to modify.
 *
 * @return uint32_t The total number of characters removed.
 */
inline uint32_t sstr_trim(StaticString *sstr)
{
    uint32_t count = 0;
    count += sstr_trim_leading(sstr);
    count += sstr_trim_trailing(sstr);
    return count;
}

/**
 * @brief Removes all whitespace characters from a StaticString (optimized version).
 *
 * Uses a single pass with a write index to compact non-whitespace characters.
 *
 * @param sstr Pointer to the StaticString to modify.
 *
 * @return void
 */
inline void sstr_strip_all_whitespace(StaticString *sstr)
{
    uint32_t write = 0;
    for (uint32_t read = 0; read < sstr->string_length; read++)
    {
        if (!IS_WHITESPACE(sstr->static_string[read]))
        {
            sstr->static_string[write++] = sstr->static_string[read];
        }
    }
    sstr->static_string[write] = '\0';
    sstr->string_length = write;
}

/**
 * @brief Compares two StaticString instances for equality.
 *
 * Checks whether both strings have the same length and identical characters.
 *
 * @param sstr1 Pointer to the first StaticString.
 * @param sstr2 Pointer to the second StaticString.
 *
 * @return uint32_t 1 if the strings are equal, 0 otherwise.
 */
inline uint32_t sstr_equals(const StaticString *sstr1, const StaticString *sstr2)
{
    if (sstr1->string_length != sstr2->string_length)
        return 0;

    for (uint32_t i = 0; i < sstr1->string_length; i++)
    {
        if (sstr1->static_string[i] != sstr2->static_string[i])
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
 * @param sstr Pointer to the StaticString.
 * @param cstr Pointer to the null-terminated C string.
 *
 * @return uint32_t 1 if the strings are equal, 0 otherwise.
 */
inline uint32_t sstr_equals_cstr(const StaticString *sstr, const char *cstr)
{
    if (cstr == NULL)
    {
        return 0;
    }

    uint32_t i = 0;

    while (i < sstr->string_length && cstr[i] != '\0')
    {
        if (sstr->static_string[i] != cstr[i])
        {
            return 0;
        }
        i++;
    }
    return (i == sstr->string_length && cstr[i] == '\0');
}

/**
 * @brief Returns a pointer to the internal null-terminated C string.
 *
 * Provides read-only access to the internal character array of the StaticString.
 * The returned string is guaranteed to be null-terminated.
 *
 * @param sstr Pointer to the StaticString.
 *
 * @return const char* Pointer to the null-terminated C string.
 */
inline const char *sstr_to_cstr(const StaticString *sstr)
{
    return sstr->static_string;
}

/**
 * @brief Removes and returns the last character from the StaticString.
 *
 * If the StaticString is not empty, this function removes the last character,
 * updates the string length, and returns the removed character.
 * If the string is empty, it returns 0.
 *
 * @param sstr Pointer to the StaticString.
 *
 * @return char The last character if available, otherwise 0.
 */
inline char sstr_pop(StaticString *sstr)
{
    char return_char = 0;
    if (sstr->string_length > 0)
    {
        return_char = sstr->static_string[sstr->string_length - 1];
        sstr->static_string[sstr->string_length - 1] = '\0';
        sstr->string_length--;
    }
    return return_char;
}

/**
 * @brief Truncates the StaticString to the specified length.
 *
 * Shortens the StaticString to the given length if the new length is less than
 * or equal to the current length. Ensures the string remains null-terminated.
 *
 * @param sstr Pointer to the StaticString to truncate.
 * @param new_length The desired new length of the string.
 *
 * @return uint32_t 1 if the truncation was successful, 0 if new_length is greater than current length.
 */
inline uint32_t sstr_truncate(StaticString *sstr, uint32_t new_length)
{
    if (new_length > sstr->string_length || new_length > SSTR_MAX_LENGTH)
    {
        return 0;
    }

    sstr->string_length = new_length;
    sstr->static_string[sstr->string_length] = '\0';
    return 1;
}

/**
 * @brief Returns the current length of the StaticString.
 *
 * This function provides access to the length of the string,
 * excluding the null terminator.
 *
 * @param sstr Pointer to the StaticString.
 *
 * @return uint32_t The number of characters in the string.
 */
inline uint32_t sstr_length(const StaticString *sstr)
{
    return sstr->string_length;
}

/**
 * @brief Reverses the contents of the StaticString in place.
 *
 * Reverses the characters of the StaticString without allocating
 * additional memory. The operation is done in-place.
 *
 * @param sstr Pointer to the StaticString to be reversed.
 */
inline void sstr_reverse(StaticString *sstr)
{
    if (sstr->string_length == 0)
    {
        return;
    }
    uint32_t i = 0, j = sstr->string_length - 1;
    while (i < j)
    {
        char temp = sstr->static_string[i];
        sstr->static_string[i] = sstr->static_string[j];
        sstr->static_string[j] = temp;
        i++;
        j--;
    }
}

/**
 * @brief Copies the contents of one StaticString to another.
 *
 * Performs a deep copy of the contents and string length from the source
 * StaticString (`sstr2`) to the destination StaticString (`sstr1`), including
 * null-termination. Returns void if the source StaticString (`sstr2`) is too long.
 *
 * @param sstr1 Pointer to the destination StaticString.
 * @param sstr2 Pointer to the source StaticString.
 *
 * @return void
 */
inline void sstr_copy(StaticString *sstr1, const StaticString *sstr2)
{
    if (sstr2->string_length > SSTR_MAX_LENGTH)
    {
        return;
    }
    sstr1->string_length = sstr2->string_length;
    for (uint32_t i = 0; i < sstr1->string_length; i++)
    {
        sstr1->static_string[i] = sstr2->static_string[i];
    }
    sstr1->static_string[sstr1->string_length] = '\0';
}

/**
 * @brief Converts all lowercase letters in the StaticString to uppercase.
 *
 * Iterates through the StaticString and converts each ASCII lowercase
 * character ('a' to 'z') to its uppercase equivalent ('A' to 'Z').
 *
 * @param sstr Pointer to the StaticString to modify.
 *
 * @return uint32_t The number of characters that were converted.
 */
inline uint32_t sstr_to_uppercase(StaticString *sstr)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < sstr->string_length; i++)
    {
        if (sstr->static_string[i] >= 'a' && sstr->static_string[i] <= 'z')
        {
            sstr->static_string[i] -= 'a' - 'A';
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
 * @param sstr Pointer to the StaticString to modify.
 *
 * @return uint32_t The number of characters that were converted.
 */
inline uint32_t sstr_to_lowercase(StaticString *sstr)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < sstr->string_length; i++)
    {
        if (sstr->static_string[i] >= 'A' && sstr->static_string[i] <= 'Z')
        {
            sstr->static_string[i] += 'a' - 'A';
            count++;
        }
    }
    return count;
}

/**
 * @brief Returns the number of times a character appears in a StaticString.
 *
 * Iterates through the StaticString and counts the number of occurrences of
 * the specified character.
 *
 * @param sstr Pointer to the StaticString.
 * @param ch The character to search for.
 *
 * @return uint32_t The number of times the character appears in the string.
 */
inline uint32_t sstr_contains(const StaticString *sstr, char ch)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < sstr->string_length; i++)
    {
        if (sstr->static_string[i] == ch)
        {
            count++;
        }
    }
    return count;
}

/**
 * @brief Finds the first occurrence of a character in a StaticString.
 *
 * Searches the StaticString for the specified character and returns the
 * zero-based index of its first occurrence. If the character is not found,
 * the function returns -1.
 *
 * @param sstr Pointer to the StaticString to search.
 * @param ch The character to find.
 *
 * @return int The index of the first occurrence of the character, or -1 if not found.
 */
inline int sstr_first_index_of(const StaticString *sstr, char ch)
{
    for (uint32_t i = 0; i < sstr->string_length; i++)
    {
        if (sstr->static_string[i] == ch)
        {
            return (int)i;
        }
    }
    return -1;
}

/**
 * @brief Finds the last occurrence of a character in a StaticString.
 *
 * Searches the StaticString in reverse order for the specified character
 * and returns the zero-based index of its last occurrence. If the character
 * is not found, the function returns -1.
 *
 * @param sstr Pointer to the StaticString to search.
 * @param ch The character to find.
 *
 * @return int The index of the last occurrence of the character, or -1 if not found.
 */
inline int sstr_last_index_of(const StaticString *sstr, char ch)
{
    for (uint32_t i = sstr->string_length - 1; i >= 0; i--)
    {
        if (sstr->static_string[i] == ch)
        {
            return (int)i;
        }
    }
    return -1;
}

#endif