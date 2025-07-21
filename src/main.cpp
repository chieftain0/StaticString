#include <bits/stdc++.h>

#define SS_SIZE_TYPE uint8_t // decides how many characters can be stored (default: uint16_t)
#include "StackString.h"

using namespace std;

void print_stack_string(const StackString &ss, const char *label)
{
    cout << label << ": \"" << ss_to_cstr(&ss) << "\" (len=" << (int)ss.string_length << ")\n";
}

int main()
{
    StackString s1, s2;

    // Initialization
    ss_init(&s1);
    ss_init(&s2);
    print_stack_string(s1, "After init");

    // From C string
    ss_from_cstr(&s1, "   Hello, World!   ");
    print_stack_string(s1, "After ss_from_cstr");

    // Trim
    ss_trim(&s1);
    print_stack_string(s1, "After ss_trim");

    // Append character
    ss_append(&s1, '!');
    print_stack_string(s1, "After ss_append('!')");

    // Append C string
    ss_append_cstr(&s1, " Goodbye.");
    print_stack_string(s1, "After ss_append_cstr");

    // Copy
    ss_copy(&s2, &s1);
    print_stack_string(s2, "Copied to s2");

    // Equality check
    cout << "ss_equals: " << (ss_equals(&s1, &s2) ? "yes" : "no") << "\n";
    cout << "ss_equals_cstr: " << (ss_equals_cstr(&s1, ss_to_cstr(&s2)) ? "yes" : "no") << "\n";

    // Replace character
    ss_replace_char_from_index(&s1, 0, 'h');
    print_stack_string(s1, "After ss_replace_char at index 0");

    // Pop
    char popped = ss_pop(&s1);
    cout << "Popped char: " << popped << "\n";
    print_stack_string(s1, "After ss_pop");

    // Uppercase
    ss_to_uppercase(&s1);
    print_stack_string(s1, "After ss_to_uppercase");

    // Lowercase
    ss_to_lowercase(&s1);
    print_stack_string(s1, "After ss_to_lowercase");

    // Reverse
    ss_reverse(&s1);
    print_stack_string(s1, "After ss_reverse");

    getchar();

    return 0;
}