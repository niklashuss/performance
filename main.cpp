#include <stdio.h>
#include <stdlib.h>
#include "example1.h"
#include "example2.h"

#include "time.h"


int main(int argument_count, char* arguments[]) {
    const u32 buffer_width = 3840 * 10;
    const u32 buffer_height = 2160;

    example_1(buffer_width, buffer_height);
    example_2(buffer_width, buffer_height);

    return 0;
}
