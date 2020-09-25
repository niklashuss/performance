#include "example2.h"
#include "time.h"
#include <stdio.h>

Buffer::Buffer(u32 width, u32 height) : width(width), height(height) {
    u64 size = (u64)width * (u64)height;
    buffer = new u32[size];

    // We do not want to be hit by pages swapping in during the tests
    for (u32 i = 0; i < size; i++) {
        buffer[i] = 0;
    }
}

Buffer::~Buffer() {
    delete[] buffer;
}

void Buffer::fill_0(u32 color) {
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            buffer[x + y * width] = color;
        }
    }
}

void Buffer::fill_1(u32 color) {
    const u32 w = width;
    const u32 h = height;
    for (u32 y = 0; y < h; y++) {
        for (u32 x = 0; x < w; x++) {
            buffer[x + y * width] = color;
        }
    }
}

void Buffer::fill_2(u32 color) {
    const u32 w = width;
    const u32 h = height;
    for (u32 y = 0; y < h; y++) {
        const u32 line = y * w;
        for (u32 x = 0; x < w; x++) {
            buffer[x + line] = color;
        }
    }
}

void Buffer::fill_3(u32 color) {
    const u32 size = width * height;
    for (u32 i = 0; i < size; i++) {
        buffer[i] = color;
    }
}

void Buffer::fill_4(u32 color) {
    const u32 size = width * height;
    u32* buffer_local_ptr = buffer;
    for (u32 i = 0; i < size; i++) {
        buffer_local_ptr[i] = color;
    }
}

void example_2(u32 buffer_width, u32 buffer_height) {
    printf("Clearing buffers from a class object:\n");
    {
        Buffer buffer(buffer_width, buffer_height);
        u64 start = time_in_microseconds();
        buffer.fill_0(0xff000000);
        u64 stop = time_in_microseconds();
        u64 diff = stop - start;
        f64 took = time_microseconds_to_seconds(diff);
        printf("Test 0 took: %llu microseconds, %0.2f seconds\n", diff, took);
    }

    {
        Buffer buffer(buffer_width, buffer_height);
        u64 start = time_in_microseconds();
        buffer.fill_1(0xff000000);
        u64 stop = time_in_microseconds();
        u64 diff = stop - start;
        f64 took = time_microseconds_to_seconds(diff);
        printf("Test 1 took: %llu microseconds, %0.2f seconds\n", diff, took);
    }

    {
        Buffer buffer(buffer_width, buffer_height);
        u64 start = time_in_microseconds();
        buffer.fill_2(0xff000000);
        u64 stop = time_in_microseconds();
        u64 diff = stop - start;
        f64 took = time_microseconds_to_seconds(diff);
        printf("Test 2 took: %llu microseconds, %0.2f seconds\n", diff, took);
    }

    {
        Buffer buffer(buffer_width, buffer_height);
        u64 start = time_in_microseconds();
        buffer.fill_3(0xff000000);
        u64 stop = time_in_microseconds();
        u64 diff = stop - start;
        f64 took = time_microseconds_to_seconds(diff);
        printf("Test 3 took: %llu microseconds, %0.2f seconds\n", diff, took);
    }

    {
        Buffer buffer(buffer_width, buffer_height);
        u64 start = time_in_microseconds();
        buffer.fill_4(0xff000000);
        u64 stop = time_in_microseconds();
        u64 diff = stop - start;
        f64 took = time_microseconds_to_seconds(diff);
        printf("Test 4 took: %llu microseconds, %0.2f seconds\n", diff, took);
    }


}