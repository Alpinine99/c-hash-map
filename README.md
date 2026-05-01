# C Hash Map Implementation

A simple and efficient hash table implementation in C, providing key-value storage with string keys and values.

## Features

- **Separate Chaining**: Uses linked lists to handle hash collisions
- **djb2 Hash Function**: Fast and reliable string hashing algorithm
- **Dynamic Memory Management**: Automatic allocation and deallocation of memory
- **String Key-Value Pairs**: Supports string keys and values
- **Thread-Unsafe**: Designed for single-threaded applications

## Building the Project

### Prerequisites

- GCC compiler
- Make build system

### Build Instructions

1. Clone or navigate to the project directory
2. Run `make` to build the project:

```bash
make
```

This will create the executable `bin/hashmap` and compile object files in the `build/` directory.

### Clean Build

To clean the build artifacts:

```bash
make clean
```

## Running the Example

After building, run the example program:

```bash
./bin/hashmap
```

This will demonstrate basic hash table operations including setting, getting, updating, and deleting key-value pairs.

## API Reference

### Data Structures

- `HashTable`: Opaque structure representing the hash table

### Functions

#### `HashTable *dict_create(size_t size)`

Creates a new hash table with the specified number of buckets.

**Parameters:**
- `size`: Number of buckets in the hash table (recommended: prime numbers for better distribution)

**Returns:** Pointer to the newly created hash table, or NULL on allocation failure

#### `void dict_set(HashTable *table, const char *key, const char *value)`

Inserts or updates a key-value pair in the hash table.

**Parameters:**
- `table`: Pointer to the hash table
- `key`: String key (will be duplicated)
- `value`: String value (will be duplicated)

**Note:** If the key already exists, the value is updated. Memory for the old value is freed.

#### `char *dict_get(HashTable *table, const char *key)`

Retrieves the value associated with a key.

**Parameters:**
- `table`: Pointer to the hash table
- `key`: String key to look up

**Returns:** Pointer to the value string, or NULL if key not found

#### `void dict_delete(HashTable *table, const char *key)`

Removes a key-value pair from the hash table.

**Parameters:**
- `table`: Pointer to the hash table
- `key`: String key to delete

**Note:** Frees memory associated with the key and value.

#### `void dict_free(HashTable *table)`

Destroys the hash table and frees all associated memory.

**Parameters:**
- `table`: Pointer to the hash table to destroy

## Implementation Details

### Hash Function

The implementation uses the djb2 hash function, a simple and effective string hashing algorithm:

```c
static size_t djb2_hash(const char* key, size_t size) {
    size_t hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash % size;
}
```

### Collision Resolution

Collisions are resolved using separate chaining with linked lists. Each bucket contains a linked list of `HashEntry` structures.

### Memory Management

- Keys and values are duplicated using `strdup()` when stored
- Memory is properly freed in `dict_free()` and `dict_delete()`
- Uses `malloc()`, `calloc()`, and `free()` for dynamic allocation

### Thread Safety

This implementation is not thread-safe. Concurrent access to the hash table from multiple threads may lead to data corruption or crashes.

## Example Usage

```c
#include <dict.h>

int main() {
    // Create a hash table with 100 buckets
    HashTable *dict = dict_create(100);

    // Set some key-value pairs
    dict_set(dict, "name", "John Doe");
    dict_set(dict, "age", "30");
    dict_set(dict, "city", "New York");

    // Retrieve values
    char *name = dict_get(dict, "name");
    char *age = dict_get(dict, "age");

    printf("Name: %s, Age: %s\n", name, age);

    // Update a value
    dict_set(dict, "age", "31");

    // Delete a key-value pair
    dict_delete(dict, "city");

    // Clean up
    dict_free(dict);

    return 0;
}
```

## Performance Characteristics

- **Average Case**: O(1) for insert, lookup, and delete operations
- **Worst Case**: O(n) when all keys hash to the same bucket
- **Space Complexity**: O(n) where n is the number of key-value pairs

## Limitations

- Only supports string keys and values
- Not thread-safe
- No support for custom hash functions or key comparison functions
- Fixed number of buckets (no automatic resizing)

## Contributing

Feel free to submit issues, feature requests, or pull requests to improve this implementation.

## License

This project is open source. Please check the license file for details.