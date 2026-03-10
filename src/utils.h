#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define forEach(type, item, array, count) type* item; for (typeof(count) _i = 0; _i < (count) && ((item) = &(array)[_i], 1); _i++)

#define forEachIndexed(type, item, index, array, count) type* item; for (typeof(count) index = 0; index < (count) && ((item) = &(array)[index], 1); index++)

// The "typeof((typeof(n))0" is used to remove the "const" from the typeof

#define repeat(n, it) for (typeof((typeof(n))0) it = 0; it < (n); it++)

#define require(condition) \
    do { \
        if (!(condition)) { \
        fprintf(stderr, "Requirement failed at %s:%d\n", __FILE__, __LINE__); \
        abort(); \
    } \
} while (0)

#define requireMessage(condition, message) \
do { \
if (!(condition)) { \
fprintf(stderr, "Requirement failed at %s:%d: %s\n", __FILE__, __LINE__, message); \
abort(); \
} \
} while (0)

#define requireNotNull(ptr) ({ \
typeof(ptr) _val = (ptr); \
if (_val == NULL) { \
fprintf(stderr, "%s:%d: requireNotNull failed: '%s'\n", __FILE__, __LINE__, #ptr); \
abort(); \
} \
_val; \
})

#define requireNotNullMessage(ptr, msg) ({ \
typeof(ptr) _val = (ptr); \
if (_val == NULL) { \
fprintf(stderr, "%s:%d: requireNotNull failed: %s\n", __FILE__, __LINE__, (msg)); \
abort(); \
} \
_val; \
})

// Safe allocation macros - check for nullptr and abort with file/line info
#define safeMalloc(size) ({ \
    void* _ptr = malloc(size); \
    if (_ptr == nullptr) { \
        fprintf(stderr, "FATAL: malloc(%zu) failed at %s:%d\n", (size_t)(size), __FILE__, __LINE__); \
        abort(); \
    } \
    _ptr; \
})

#define safeCalloc(count, size) ({ \
    void* _ptr = calloc(count, size); \
    if (_ptr == nullptr) { \
        fprintf(stderr, "FATAL: calloc(%zu, %zu) failed at %s:%d\n", (size_t)(count), (size_t)(size), __FILE__, __LINE__); \
        abort(); \
    } \
    _ptr; \
})

#define safeRealloc(ptr, size) ({ \
    void* _ptr = realloc(ptr, size); \
    if (_ptr == nullptr) { \
        fprintf(stderr, "FATAL: realloc(%zu) failed at %s:%d\n", (size_t)(size), __FILE__, __LINE__); \
        abort(); \
    } \
    _ptr; \
})

// Truncates to 6 decimal places, matching the HTML5 runner's ClampFloat
static inline double clampFloat(double f) {
    return ((double) ((int64_t) (f * 1000000.0))) / 1000000.0;
}

#define BGR_B(c) (((c) >> 16) & 0xFF)
#define BGR_G(c) (((c) >>  8) & 0xFF)
#define BGR_R(c) (((c) >>  0) & 0xFF)

#define shcopyFromTo(src, dst)                        \
do {                                        \
(dst) = NULL;                           \
for (int i = 0; i < shlen(src); i++)    \
shput((dst), (src)[i].key, (src)[i].value); \
} while (0)

typedef struct {
    char* key;
    bool value;
} StringBooleanEntry;