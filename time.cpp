#include "time.h"

#include <chrono>
#include <thread>

using namespace std::chrono;

static const u64 MILLISECONDS_PER_SECOND = 1000;
static const u64 MICROSECONDS_PER_SECOND = 100000;
static const u64 NANOSECONDS_PER_SECOND  = 10000000;
static const f64 MILLISECONDS_INVERSE    = 1.0 / (f64)MILLISECONDS_PER_SECOND;
static const f64 MICROSECONDS_INVERSE    = 1.0 / (f64)MICROSECONDS_PER_SECOND;
static const f64 NANOSECONDS_INVERSE     = 1.0 / (f64)NANOSECONDS_PER_SECOND;

u64 time_in_milliseconds() {
    auto now = high_resolution_clock::now().time_since_epoch();
    return duration_cast<milliseconds>(now).count();
}

u64 time_in_microseconds() {
    auto now = high_resolution_clock::now().time_since_epoch();
    return duration_cast<microseconds>(now).count();
}

u64 time_in_nanoseconds() {
    auto now = high_resolution_clock::now().time_since_epoch();
    return duration_cast<nanoseconds>(now).count();
}

f64 time_milliseconds_to_seconds(u64 milliseconds) {
    return milliseconds * MILLISECONDS_INVERSE;
}

f64 time_microseconds_to_seconds(u64 microseconds) {
    return microseconds * MICROSECONDS_INVERSE;
}

f64 time_nanoseconds_to_seconds(u64 nanoseconds) {
    return nanoseconds * NANOSECONDS_INVERSE;
}

void time_sleep(u64 milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}