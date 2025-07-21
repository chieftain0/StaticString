#ifndef STACKSTRING_H
#define STACKSTRING_H

#include <stdint.h>

#ifndef SS_SIZE_TYPE
#define SS_SIZE_TYPE uint8_t
#endif
typedef SS_SIZE_TYPE ss_size_t;

#define SS_MAX_LENGTH ((ss_size_t)(-1))
#define IS_WHITESPACE(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')

typedef struct
{
    char stack_string[SS_MAX_LENGTH + 1];
    ss_size_t string_length;
} StackString;

static inline void ss_init(StackString *ss)
{
    ss->string_length = 0;
    ss->stack_string[0] = '\0';
}

static inline void ss_from_cstr(StackString *ss, const char *cstr)
{
    ss_size_t i;
    for (i = 0; i < SS_MAX_LENGTH && cstr[i] != '\0'; i++)
    {
        ss->stack_string[i] = cstr[i];
    }
    ss->stack_string[i] = '\0';
    ss->string_length = i;
}

static inline void ss_clear(StackString *ss)
{
    for (ss_size_t i = 0; i < SS_MAX_LENGTH; i++)
    {
        ss->stack_string[i] = '\0';
    }
    ss->string_length = 0;
}

static inline void ss_append(StackString *ss, const char character)
{
    if (ss->string_length < SS_MAX_LENGTH)
    {
        ss->stack_string[ss->string_length] = character;
        ss->stack_string[ss->string_length + 1] = '\0';
        ss->string_length++;
    }
}

static inline void ss_append_cstr(StackString *ss, const char *cstr)
{
    ss_size_t i;
    for (i = 0; i < SS_MAX_LENGTH - ss->string_length && cstr[i] != '\0'; i++)
    {
        ss->stack_string[ss->string_length + i] = cstr[i];
    }
    ss->stack_string[ss->string_length + i] = '\0';
    ss->string_length += i;
}

static inline ss_size_t ss_replace_char_from_index(StackString *ss, ss_size_t index, char character)
{
    if (index >= ss->string_length)
    {
        return 0;
    }

    ss->stack_string[index] = character;
    return 1;
}

static inline ss_size_t ss_replace_all_chars(StackString *ss, char old_char, char new_char)
{
    ss_size_t count = 0;
    for (ss_size_t i = 0; i < ss->string_length; i++)
    {
        if (ss->stack_string[i] == old_char)
        {
            ss->stack_string[i] = new_char;
            count++;
        }
    }
    return count;
}

static inline ss_size_t ss_trim_trailing(StackString *ss)
{
    ss_size_t count = 0;
    while (ss->string_length > 0 && ss->stack_string[ss->string_length - 1] == ' ')
    {
        ss->string_length--;
        count++;
    }
    ss->stack_string[ss->string_length] = '\0';
    return count;
}

static inline ss_size_t ss_trim_leading(StackString *ss)
{
    ss_size_t count = 0;
    while (ss->string_length > 0 && IS_WHITESPACE(ss->stack_string[0]))
    {
        for (ss_size_t i = 0; i < ss->string_length; i++)
        {
            ss->stack_string[i] = ss->stack_string[i + 1];
        }
        ss->stack_string[ss->string_length - 1] = '\0';
        ss->string_length--;
        count++;
    }
    return count;
}

static inline ss_size_t ss_trim(StackString *ss)
{
    ss_size_t count = 0;
    count += ss_trim_leading(ss);
    count += ss_trim_trailing(ss);
    return count;
}

static inline void ss_strip_all_whitespace(StackString *ss)
{
    for (ss_size_t i = 0; i < ss->string_length; i++)
    {
        if (IS_WHITESPACE(ss->stack_string[i]))
        {
            for (ss_size_t j = i; j < ss->string_length - 1; j++)
            {
                ss->stack_string[j] = ss->stack_string[j + 1];
            }
            ss->stack_string[ss->string_length - 1] = '\0';
            ss->string_length--;
            i--;
        }
    }
}

static inline ss_size_t ss_equals(const StackString *ss1, const StackString *ss2)
{
    if (ss1->string_length != ss2->string_length)
        return 0;

    for (ss_size_t i = 0; i < ss1->string_length; i++)
    {
        if (ss1->stack_string[i] != ss2->stack_string[i])
            return 0;
    }

    return 1;
}

static inline ss_size_t ss_equals_cstr(const StackString *ss, const char *cstr)
{
    ss_size_t i = 0;

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

static inline const char *ss_to_cstr(const StackString *ss)
{
    return ss->stack_string;
}

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

static inline ss_size_t ss_truncate(StackString *ss, ss_size_t new_length)
{
    if (new_length > ss->string_length)
    {
        return 0;
    }

    ss->string_length = new_length;
    ss->stack_string[ss->string_length] = '\0';
    return 1;
}

static inline ss_size_t ss_length(const StackString *ss)
{
    return ss->string_length;
}

static inline void ss_reverse(StackString *ss)
{
    // TODO
    SS_SIZE_TYPE i = 0, j = ss->string_length - 1;
    while (i < j)
    {
        char temp = ss->stack_string[i];
        ss->stack_string[i] = ss->stack_string[j];
        ss->stack_string[j] = temp;
        i++;
        j--;
    }
}

static inline void ss_copy(StackString *ss1, const StackString *ss2)
{
    if (ss2->string_length > SS_MAX_LENGTH)
    {
        return;
    }
    ss1->string_length = ss2->string_length;
    for (ss_size_t i = 0; i < ss1->string_length; i++)
    {
        ss1->stack_string[i] = ss2->stack_string[i];
    }
    ss1->stack_string[ss1->string_length] = '\0';
    return;
}

static inline ss_size_t ss_to_uppercase(StackString *ss)
{
    ss_size_t count = 0;
    for (ss_size_t i = 0; i < ss->string_length; i++)
    {
        if (ss->stack_string[i] >= 'a' && ss->stack_string[i] <= 'z')
        {
            ss->stack_string[i] -= 'a' - 'A';
            count++;
        }
    }
    return count;
}

static inline ss_size_t ss_to_lowercase(StackString *ss)
{
    ss_size_t count = 0;
    for (ss_size_t i = 0; i < ss->string_length; i++)
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