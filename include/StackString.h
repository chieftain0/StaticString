#ifndef STACKSTRING_H
#define STACKSTRING_H

#include <stdint.h>

#define SS_MAX_DATA_TYPE uint8_t
#define SS_MAX_LENGTH ((SS_MAX_DATA_TYPE)(-1))
#define IS_WHITESPACE(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')

typedef struct
{
    char stack_string[SS_MAX_LENGTH + 1];
    SS_MAX_DATA_TYPE string_length;
} StackString;

// Initialization

/**
 * @brief Initializes a StackString.
 *
 * @param ss A pointer to the StackString to initialize.
 *
 * @details Initializes a StackString by setting the string length to 0 and
 *          setting the first character of the underlying string to '\0'.
 *          This function should be called before any other operation is
 *          performed on the StackString.
 */
static inline void ss_init(StackString *ss)
{
    ss->string_length = 0;
    ss->stack_string[0] = '\0';
}

/**
 * @brief Copies a C string into a StackString.
 *
 * @param ss A pointer to the StackString to copy into.
 * @param cstr A pointer to the C string to copy from.
 *
 * @details Copies a C string into a StackString until either the end of the
 *          C string is reached or the end of the StackString is reached.
 *          The copied string is null-terminated. The string length is set
 *          to the length of the copied string.
 */
static inline void ss_from_cstr(StackString *ss, const char *cstr)
{
    SS_MAX_DATA_TYPE i;
    for (i = 0; i < SS_MAX_LENGTH && cstr[i] != '\0'; i++)
    {
        ss->stack_string[i] = cstr[i];
    }
    ss->stack_string[i] = '\0';
    ss->string_length = i;
}

/**
 * @brief Clears a StackString.
 *
 * @param ss A pointer to the StackString to clear.
 *
 * @details Sets all characters in the StackString to '\0' and resets the
 *          string length to 0. This effectively empties the StackString.
 */

static inline void ss_clear(StackString *ss)
{
    for (SS_MAX_DATA_TYPE i = 0; i < SS_MAX_LENGTH; i++)
    {
        ss->stack_string[i] = '\0';
    }
    ss->string_length = 0;
}

// Append / Modify

/**
 * @brief Appends a character to the end of a StackString.
 *
 * @param ss A pointer to the StackString to append to.
 * @param character The character to append.
 *
 * @details If the StackString is not full, appends the given character to the end
 *          of the StackString. Increments the string length. Otherwise, does
 *          nothing.
 */
static inline void ss_append(StackString *ss, const char character)
{
    if (ss->string_length < SS_MAX_LENGTH)
    {
        ss->stack_string[ss->string_length] = character;
        ss->stack_string[ss->string_length + 1] = '\0';
        ss->string_length++;
    }
}

/**
 * @brief Appends a C string to the end of a StackString if it fits.
 *
 * @param ss A pointer to the StackString to append to.
 * @param cstr The C string to append.
 *
 * @details If the C string fits into the remaining space in the StackString,
 *          appends the given C string to the end of the StackString. Increments
 *          the string length by the length of the appended string.
 *          Otherwise, does nothing.
 */
static inline void ss_append_cstr(StackString *ss, const char *cstr)
{
    SS_MAX_DATA_TYPE i;
    for (i = 0; i < SS_MAX_LENGTH - ss->string_length && cstr[i] != '\0'; i++)
    {
        ss->stack_string[ss->string_length + i] = cstr[i];
    }
    ss->stack_string[ss->string_length + i] = '\0';
    ss->string_length += i;
}

/**
 * @brief Replaces a character at a given index in a StackString.
 *
 * @param ss A pointer to the StackString to modify.
 * @param index The index of the character to replace.
 * @param character The character to replace with.
 *
 * @details If the given index is within the bounds of the StackString, replaces
 *          the character at that index with the given character. Returns 1
 *          if the replacement was successful, and 0 if the index is out of
 *          bounds.
 */
static inline SS_MAX_DATA_TYPE ss_replace_char_from_index(StackString *ss, SS_MAX_DATA_TYPE index, char character)
{
    if (index >= ss->string_length)
    {
        return 0;
    }

    ss->stack_string[index] = character;
    return 1;
}

/**
 * @brief Replaces all occurrences of a character in a StackString.
 *
 * @param ss A pointer to the StackString to modify.
 * @param old_char The character to replace.
 * @param new_char The character to replace with.
 *
 * @details Replaces all occurrences of the given old character with the given
 *          new character. Returns the count of replacements made.
 */
static inline SS_MAX_DATA_TYPE ss_replace_all_chars(StackString *ss, char old_char, char new_char)
{
    SS_MAX_DATA_TYPE count = 0;
    for (SS_MAX_DATA_TYPE i = 0; i < ss->string_length; i++)
    {
        if (ss->stack_string[i] == old_char)
        {
            ss->stack_string[i] = new_char;
            count++;
        }
    }
    return count;
}

// Trim & Whitespace

/**
 * @brief Removes trailing whitespace from a StackString.
 *
 * @param ss A pointer to the StackString to modify.
 *
 * @details Removes all trailing whitespace from the StackString. Returns the
 *          count of whitespace removed.
 */
static inline SS_MAX_DATA_TYPE ss_trim_trailing(StackString *ss)
{
    SS_MAX_DATA_TYPE count = 0;
    while (ss->string_length > 0 && ss->stack_string[ss->string_length - 1] == ' ')
    {
        ss->string_length--;
        count++;
    }
    ss->stack_string[ss->string_length] = '\0';
    return count;
}

/**
 * @brief Removes leading whitespace from a StackString.
 *
 * @param ss A pointer to the StackString to modify.
 *
 * @details Removes all leading whitespace from the StackString. Returns the
 *          count of whitespace removed.
 */
static inline SS_MAX_DATA_TYPE ss_trim_leading(StackString *ss)
{
    SS_MAX_DATA_TYPE count = 0;
    while (ss->string_length > 0 && IS_WHITESPACE(ss->stack_string[0]))
    {
        for (SS_MAX_DATA_TYPE i = 0; i < ss->string_length; i++)
        {
            ss->stack_string[i] = ss->stack_string[i + 1];
        }
        ss->stack_string[ss->string_length - 1] = '\0';
        ss->string_length--;
        count++;
    }
    return count;
}

/**
 * @brief Removes both leading and trailing whitespace from a StackString.
 *
 * @param ss A pointer to the StackString to modify.
 *
 * @details Utilizes ss_trim_leading and ss_trim_trailing to remove all leading
 *          and trailing whitespace from the StackString. Returns the total count
 *          of whitespace characters removed.
 */
static inline SS_MAX_DATA_TYPE ss_trim(StackString *ss)
{
    SS_MAX_DATA_TYPE count = 0;
    count += ss_trim_leading(ss);
    count += ss_trim_trailing(ss);
    return count;
}

/**
 * @brief Removes all whitespace from a StackString.
 *
 * @param ss A pointer to the StackString to modify.
 *
 * @details Iterates through the StackString and removes all whitespace characters,
 *          effectively condensing the string by shifting non-whitespace characters
 *          to the left. The string length is adjusted accordingly.
 */
static inline void ss_strip_all_whitespace(StackString *ss)
{
    for (SS_MAX_DATA_TYPE i = 0; i < ss->string_length; i++)
    {
        if (IS_WHITESPACE(ss->stack_string[i]))
        {
            for (SS_MAX_DATA_TYPE j = i; j < ss->string_length - 1; j++)
            {
                ss->stack_string[j] = ss->stack_string[j + 1];
            }
            ss->stack_string[ss->string_length - 1] = '\0';
            ss->string_length--;
            i--;
        }
    }
}

// Compare / Check

/**
 * @brief Compares two StackStrings for equality.
 *
 * @param ss1 A pointer to the first StackString to compare.
 * @param ss2 A pointer to the second StackString to compare.
 *
 * @details Checks if two StackStrings are equal by comparing their
 *          string lengths and then comparing each character in the
 *          strings. Returns 1 if the strings are equal and 0 if they
 *          are not.
 */
static inline SS_MAX_DATA_TYPE ss_equals(const StackString *ss1, const StackString *ss2)
{
    if (ss1->string_length != ss2->string_length)
        return 0;

    for (SS_MAX_DATA_TYPE i = 0; i < ss1->string_length; i++)
    {
        if (ss1->stack_string[i] != ss2->stack_string[i])
            return 0;
    }

    return 1;
}

/**
 * @brief Compares a StackString to a C string for equality.
 *
 * @param ss A pointer to the StackString to compare.
 * @param cstr A pointer to the C string to compare.
 *
 * @details Checks if a StackString is equal to a C string by comparing their
 *          string lengths and then comparing each character in the
 *          strings. Returns 1 if the strings are equal and 0 if they
 *          are not.
 */
static inline SS_MAX_DATA_TYPE ss_equals_cstr(const StackString *ss, const char *cstr)
{
    SS_MAX_DATA_TYPE i = 0;

    while (i < ss->string_length && cstr[i] != '\0')
    {
        if (ss->stack_string[i] != cstr[i])
        {
            return 0;
        }
        i++;
    }
    return (i == ss->string_length && cstr[i] == '\0');
}

// Read / Access

/**
 * @brief Returns a pointer to the C string contained in the StackString.
 *
 * @param ss A pointer to the StackString to get the C string from.
 *
 * @details Returns a pointer to the C string contained in the StackString.
 *          This function does not perform a copy of the string, it simply
 *          returns a pointer to the original string. The returned pointer
 *          is valid until the StackString is modified.
 *
 * @return A pointer to the C string contained in the StackString.
 */
static inline const char *ss_to_cstr(const StackString *ss)
{
    return ss->stack_string;
}

// Removal / Truncate

/**
 * @brief Removes the last character of a StackString and returns it.
 *
 * @param ss A pointer to the StackString to remove a character from.
 *
 * @details Removes the last character of a StackString, returns the removed
 *          character, and reduces the string length by 1. If the StackString
 *          is empty, does not modify the StackString and returns 0.
 *
 * @return The removed character, or 0 if the StackString is empty.
 */
static inline char ss_pop(StackString *ss)
{
    char return_char = 0;
    if (ss->string_length > 0)
    {
        return_char = ss->stack_string[ss->string_length - 1];
        ss->stack_string[ss->string_length - 1] = '\0';
        ss->string_length--;
    }
    return return_char;
}
/**
 * @brief Truncates a StackString to a given length.
 *
 * @param ss A pointer to the StackString to truncate.
 * @param new_length The new length of the StackString.
 *
 * @details If the given new length is less than or equal to the current length
 *          of the StackString, truncates the StackString to the given length.
 *          If the given new length is greater than the current length of the
 *          StackString, does not modify the StackString and returns 0.
 *
 * @return 1 if the StackString was truncated, 0 if the StackString was not
 *         modified.
 */
static inline SS_MAX_DATA_TYPE ss_truncate(StackString *ss, SS_MAX_DATA_TYPE new_length)
{
    if (new_length > ss->string_length)
    {
        return 0;
    }

    ss->string_length = new_length;
    ss->stack_string[ss->string_length] = '\0';
    return 1;
}

// Utility

/**
 * @brief Gets the length of a StackString.
 *
 * @param ss A pointer to the StackString to get the length of.
 *
 * @details Returns the length of the StackString, which is the number of
 *          characters in the string before the null terminator.
 *
 * @return The length of the StackString.
 */
static inline SS_MAX_DATA_TYPE ss_length(const StackString *ss)
{
    return ss->string_length;
}

static inline void ss_reverse(StackString *ss)
{
    // TODO
}

/**
 * @brief Copies the contents of one StackString into another.
 *
 * @param ss1 A pointer to the StackString to copy into.
 * @param ss2 A pointer to the StackString to copy from.
 *
 * @details Copies the contents of one StackString into another if the length of
 *          the source StackString is less than or equal to the maximum length
 *          of the destination StackString. Otherwise, does not modify the
 *          destination StackString.
 */
static inline void ss_copy(StackString *ss1, const StackString *ss2)
{
    if (ss2->string_length > SS_MAX_LENGTH)
    {
        return;
    }
    ss1->string_length = ss2->string_length;
    for (SS_MAX_DATA_TYPE i = 0; i < ss1->string_length; i++)
    {
        ss1->stack_string[i] = ss2->stack_string[i];
    }
    ss1->stack_string[ss1->string_length] = '\0';
    return;
}

/**
 * @brief Converts all lowercase characters in a StackString to uppercase.
 *
 * @param ss A pointer to the StackString to convert.
 *
 * @details Converts all lowercase characters in a StackString to uppercase
 *          by subtracting the difference between the lowercase and uppercase
 *          character values. Returns the count of characters converted.
 *
 * @return The count of characters converted.
 */
static inline SS_MAX_DATA_TYPE ss_to_uppercase(StackString *ss)
{
    SS_MAX_DATA_TYPE count = 0;
    for (SS_MAX_DATA_TYPE i = 0; i < ss->string_length; i++)
    {
        if (ss->stack_string[i] >= 'a' && ss->stack_string[i] <= 'z')
        {
            ss->stack_string[i] -= 'a' - 'A';
            count++;
        }
    }
    return count;
}

/**
 * @brief Converts all uppercase characters in a StackString to lowercase.
 *
 * @param ss A pointer to the StackString to convert.
 *
 * @details Converts all uppercase characters in a StackString to lowercase
 *          by adding the difference between the lowercase and uppercase
 *          character values. Returns the count of characters converted.
 *
 * @return The count of characters converted.
 */
static inline SS_MAX_DATA_TYPE ss_to_lowercase(StackString *ss)
{
    SS_MAX_DATA_TYPE count = 0;
    for (SS_MAX_DATA_TYPE i = 0; i < ss->string_length; i++)
    {
        if (ss->stack_string[i] >= 'A' && ss->stack_string[i] <= 'Z')
        {
            ss->stack_string[i] += 'a' - 'A';
            count++;
        }
    }
    return count;
}
#endif