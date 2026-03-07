![Banner](https://i.imgur.com/lvNKVsT.png)
![C](https://img.shields.io/badge/language-C-blue)
![Standard](https://img.shields.io/badge/ISO-C99-green)
![MIT](https://img.shields.io/badge/license-MIT-yellow)


# Header-Only | Zero-Dependency | Strict ISO C99 Dynamic Vector Library

**Dynavec** is a header-only, zero‑dependency dynamic vector library written in **strict ISO C99**, portable across **all C99-compatible platforms**, including desktops, microcontrollers, and embedded systems.

---

## Features

- Strict ISO C99 compliance  
- No external dependencies  
- High portability and predictable and safe memory behavior  
- Simple integration into existing C projects

---

## Supported Vector Types

- **`IVec`**  : `int`  
- **`CVec`**  : `char`  
- **`DVec`**  : `double`  
- **`UIVec`** : `unsigned int`  

Methods follow the pattern: `{type-prefix}vec_{method_name}();`  

---

## API Layers

Dynavec provides two layers controlled via macros:

```c
#define DYNAVEC_IMPLEMENTATION      // Core API (safe)
#define DYNAVEC_ENABLE_ADVANCED     // Advanced API (performance)
```

- **Core API**: validates pointers, checks bounds, returns error codes  
- **Advanced API**: high-performance access without checks

---

## Key Methods

| Category             | Methods (All Types)                       |
|---------------------|-------------------------------------------|
| Initialization       | `ivec_init()`, `cvec_init()`, `dvec_init()`, `uivec_init()` |
| Size & Capacity      | `*_size()`, `*_capacity()`                |
| Safe Access          | `*_sget()`                                |
| Insertion            | `*_push()`                                |
| Removal              | `*_pop()`                                 |
| Assignment           | `*_assign()`                              |
| Memory Management    | `*_clear()`, `*_free()`                   |
| Advanced Access      | `*_get()`, `*_begin()`, `*_end()`        |
| Debug / Integrity    | `*_corrupt_check()`                       |

---

## Generic Return Codes

| Code                 | Value | Description                                |
|----------------------|-------|--------------------------------------------|
| `OOB_ACCESS`         | -1    | Attempted access outside vector bounds     |
| `SUCCESS`            | 0     | Operation completed successfully           |
| `INVALID_PTR_PASSED` | 1     | NULL pointer passed to function            |
| `VEC_TOO_SMALL`      | 2     | Vector is too small for the operation     |
| `AT_MAX_CAPACITY`    | 3     | Vector has reached its maximum allowed size|
| `REALLOC_FAILED`     | 4     | Memory reallocation failed                 |
| `ASSIGN_FAILED`      | 5     | Failed to assign values from provided list|
| `INTERNAL_CORRUPTION`| 6     | Vector integrity check failed              ||

--- 

## Quick Example

```c
#define DYNAVEC_IMPLEMENTATION
#include "dynavec.h"
#include <stdio.h>

int main() {
    IVec* vec = ivec_init();

    ivec_assign(vec, 5, (int[]){0,1,2,3,4});
    ivec_push(vec, 5);
    ivec_push(vec, 6);

    for(size_t i = 0; i < ivec_size(vec); i++) {
        int value;
        ivec_sget(vec, i, &value);
        printf("%d\n", value);
    }

    ivec_free(&vec);
    return 0;
}
```

---

## Polite Warning

Since Dynavec uses dynamic memory allocation, **always call `{type-prefix}vec_free()`** at the end of your program:

```c
int ivec_free(IVec** vec);
int cvec_free(CVec** vec);
int dvec_free(DVec** vec);
int uivec_free(UIVec** vec);
```

---

## Portability

Dynavec is **strict ISO C99 compliant** and runs on **any platform with a C99-compatible compiler**, including desktops, Linux systems, Raspberry Pi, and embedded microcontrollers.

---

## Compilation

Single-header, no build system required:

```bash
cc main.c -o program
```

---

## License

MIT License, Erdem Araç ©2026


