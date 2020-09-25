#pragma once

#include "common.h"

u64 time_in_milliseconds();
u64 time_in_microseconds();
u64 time_in_nanoseconds();

f64 time_milliseconds_to_seconds(u64 milliseconds);
f64 time_microseconds_to_seconds(u64 microseconds);
f64 time_nanoseconds_to_seconds(u64 nanoseconds);

void time_sleep(u64 milliseconds);