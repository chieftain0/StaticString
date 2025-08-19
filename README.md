# StaticString

A lightweight, fixed-size, statically-allocated string type for C/C++. Ideal for embedded and low-memory environments.

## Usage

Clone the repo:

```bash
git clone https://github.com/chieftain0/StaticString.git
```

or download the header file directly:

```bash
wget https://raw.githubusercontent.com/chieftain0/StaticString/main/include/StaticString.h -O StaticString.h
```

Copy the [header file](include/StaticString.h) into your project directory and include it in your source code:

```c
#include "StaticString.h"
```

## Example

[src/main.cpp](src/main.cpp) contains example usage that needs to be built with CMake:

### 1. Clone the repository

```bash
git clone https://github.com/chieftain0/StaticString.git
cd StaticString
```

### 2. Build with CMake

#### Linux / WSL

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

#### Windows (MinGW)

Make sure `\mingw64\bin` is in your `PATH` (before any conflicting toolchains).

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

#### Windows (MSVC / Visual Studio)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Features

### Core Initialization

```c
sstr_init(StaticString *sstr) 
sstr_from_cstr(StaticString *sstr, const char *cstr) 
sstr_clear(StaticString *sstr) 
```

### Append / Modify

```c
sstr_append(StaticString *sstr, char character)
sstr_append_cstr(StaticString *sstr, const char *cstr) 
sstr_replace_char_from_index(StaticString *sstr, uint32_t index, char character) 
sstr_replace_all_chars(StaticString *sstr, char old_char, char new_char) 
sstr_insert_char_at(StaticString *sstr, uint32_t index, char character) 
sstr_remove_at(StaticString *sstr, uint32_t index) 
sstr_remove_range(StaticString *sstr, uint32_t start, uint32_t end) 
sstr_substring(const StaticString *sstr_source, StaticString *sstr_dest, uint32_t start, uint32_t end) 
```

### Trim & Whitespaces

```c
sstr_trim_leading(StaticString *sstr)
sstr_trim_trailing(StaticString *sstr)
sstr_trim(StaticString *sstr)
sstr_strip_all_whitespace(StaticString *sstr)
```

### Compare / Check

```c
sstr_equals(const StaticString *sstr1, const StaticString *sstr2)
sstr_equals_cstr(const StaticString *sstr, const char*cstr)
```

### Read / Access

```c
sstr_to_cstr(const StaticString *sstr)
```

### Removal / Truncate

```c
sstr_pop(StaticString *sstr)
sstr_truncate(StaticString *sstr, uint32_t new_length)
```

### Utility

```c
sstr_length(const StaticString *sstr)
sstr_reverse(StaticString *sstr)
sstr_copy(StaticString *dest, const StaticString*src)
sstr_to_uppercase(StaticString *sstr)
sstr_to_lowercase(StaticString *sstr)
```

### Search

```c
sstr_contains(const StaticString *sstr, char ch)
sstr_first_index_of(const StaticString *sstr, char ch)
sstr_last_index_of(const StaticString *sstr, char ch)

```
