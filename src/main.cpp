#include <bits/stdc++.h>

#define SSTR_MAX_LENGTH 128 // Maximum length of a StaticString excluding the null terminator (default: 255)
#include "StaticString.h"

using namespace std;

void print_static_string(const StaticString &ss, const char *label)
{
    cout << label << ": \"" << sstr_to_cstr(&ss) << "\" (len=" << (int)ss.string_length << ")\n";
}

int main()
{
    StaticString s1, s2;

    // Initialization
    sstr_init(&s1);
    sstr_init(&s2);
    print_static_string(s1, "After init");

    // From C string
    sstr_from_cstr(&s1, "   Hello, World!   ");
    print_static_string(s1, "After sstr_from_cstr");

    // Trim
    sstr_trim(&s1);
    print_static_string(s1, "After sstr_trim");

    // Append character
    sstr_append(&s1, '!');
    print_static_string(s1, "After sstr_append('!')");

    // Append C string
    sstr_append_cstr(&s1, " Goodbye.");
    print_static_string(s1, "After sstr_append_cstr");

    // Copy
    sstr_copy(&s2, &s1);
    print_static_string(s2, "Copied to s2");

    // Equality check
    cout << "sstr_equals: " << (sstr_equals(&s1, &s2) ? "yes" : "no") << "\n";
    cout << "sstr_equals_cstr: " << (sstr_equals_cstr(&s1, sstr_to_cstr(&s2)) ? "yes" : "no") << "\n";

    // Replace character
    sstr_replace_char_from_index(&s1, 0, 'h');
    print_static_string(s1, "After sstr_replace_char at index 0");

    // Pop
    char popped = sstr_pop(&s1);
    cout << "Popped char: " << popped << "\n";
    print_static_string(s1, "After sstr_pop");

    // Uppercase
    sstr_to_uppercase(&s1);
    print_static_string(s1, "After sstr_to_uppercase");

    // Lowercase
    sstr_to_lowercase(&s1);
    print_static_string(s1, "After sstr_to_lowercase");

    // Reverse
    sstr_reverse(&s1);
    print_static_string(s1, "After sstr_reverse");

    getchar();

    return 0;
}