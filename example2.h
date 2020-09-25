#pragma once

#include "common.h"


class Buffer {
public:
    Buffer(u32 width, u32 height);
    virtual ~Buffer();

    void fill_0(u32 color);
    void fill_1(u32 color);
    void fill_2(u32 color);
    void fill_3(u32 color);
    void fill_4(u32 color);

private:
    u32* buffer = nullptr;
    u32 width;
    u32 height;
};


void example_2(u32 buffer_width, u32 buffer_height);
