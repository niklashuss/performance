#include <stdio.h>
#include <stdlib.h>
#include "time.h"

static void buffer_fill_0(u32* buffer, u32 width, u32 height, u32 color) {
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            buffer[x + y * width] = color;
        }
    }
}

static void buffer_fill_1(u32* buffer, u32 width, u32 height, u32 color) {
    for (u32 y = 0; y < height; y++) {
        const u32 line = y * width;
        for (u32 x = 0; x < width; x++) {
            buffer[x + line] = color;
        }
    }
}

static void buffer_fill_2(u32* buffer, u32 width, u32 height, u32 color) {
    u32 line = 0;
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            buffer[x + line] = color;
        }
        line += width;
    }
}

static void buffer_fill_3(u32* buffer, u32 width, u32 height, u32 color) {
    const u32 size = width * height;
    for (u32 i = 0; i < size; i++) {
        buffer[i] = color;
    }
}

static void warm_up_pages(u32* buffer, u32 width, u32 height) {
    const u32 size = width * height;
    for (u32 i = 0; i < size; i++) {
        buffer[i] = 0;
    }
}

void example_1(u32 buffer_width, u32 buffer_height) {
    // Change this to see the effect of non-alignment memory
    const u32 offset = 0;
    const u32 buffer_size = buffer_width * buffer_height * sizeof(u32) + offset;

    u8* buffer = (u8*)malloc(buffer_size);
    u8* buffer_offset = buffer + offset;

    // Need to get all the pages loaded.
    warm_up_pages((u32*)buffer_offset, buffer_width, buffer_height);

    printf("buffer pointer:   %p\n", buffer);
    printf("buffer + offset : %p\n", buffer_offset);
    printf("Allocated %lu Mb %lu\n", buffer_size / (1024 * 1024), buffer_size);
    {
        u64 start = time_in_microseconds();
        buffer_fill_0((u32*)buffer_offset, buffer_width, buffer_height, 0xff000000);
        u64 stop = time_in_microseconds();
        u64 took = stop - start;
        f64 in_mb = buffer_size / (1024.0 * 1024.0);
        f64 in_s = time_microseconds_to_seconds(took);
        f64 mb_s = in_mb / in_s;
        printf("Test 0 took: %llu microseconds, %0.2f Mb, %0.2f seconds, %0.2f Mb/s\n", took, in_mb, in_s, mb_s);
    }

    {
        u64 start = time_in_microseconds();
        buffer_fill_1((u32*)buffer_offset, buffer_width, buffer_height, 0x00ff0000);
        u64 stop = time_in_microseconds();
        u64 took = stop - start;
        f64 in_mb = buffer_size / (1024.0 * 1024.0);
        f64 in_s = time_microseconds_to_seconds(took);
        f64 mb_s = in_mb / in_s;
        printf("Test 1 took: %llu microseconds, %0.2f Mb, %0.2f seconds, %0.2f Mb/s\n", took, in_mb, in_s, mb_s);
    }

    {
        u64 start = time_in_microseconds();
        buffer_fill_2((u32*)buffer_offset, buffer_width, buffer_height, 0x0000ff00);
        u64 stop = time_in_microseconds();
        u64 took = stop - start;
        f64 in_mb = buffer_size / (1024.0 * 1024.0);
        f64 in_s = time_microseconds_to_seconds(took);
        f64 mb_s = in_mb / in_s;
        printf("Test 2 took: %llu microseconds, %0.2f Mb, %0.2f seconds, %0.2f Mb/s\n", took, in_mb, in_s, mb_s);
    }

    {
        u64 start = time_in_microseconds();
        buffer_fill_3((u32*)buffer_offset, buffer_width, buffer_height, 0x000000ff);
        u64 stop = time_in_microseconds();
        u64 diff = stop - start;
        f64 in_mb = buffer_size / (1024.0 * 1024.0);
        f64 in_s = time_microseconds_to_seconds(diff);
        f64 mb_s = in_mb / in_s;
        printf("Test 3 took: %llu microseconds, %0.2f Mb, %0.2f seconds, %0.2f Mb/s\n", diff, in_mb, in_s, mb_s);
    }
}
