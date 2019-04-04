# headerify
Convert any file into a C/C++ header file for embedding

## Building

```
mkdir build
cd build
cmake ..
make -j4

./src/headerify Test.txt
```

## Usage

Test.txt:
```
Hello, World!
```

```
./headerify Test.txt
```

Test.h
```C
#ifndef TEST_H
#define TEST_H

const char TEST_H[] = {
    0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x21
};

const size_t TEST_H_LENGTH = sizeof(TEST_H);
#endif TEST_H
```
