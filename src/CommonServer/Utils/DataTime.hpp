//
// Common date-time aliases used throughout the system
//
// Created by Michael Lewis on 10/7/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_DATATIME_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_DATATIME_HPP

#include <chrono>

namespace BeaconTech
{
    // Nanoseconds since the UNIX epoch.
    using UnixNanos = std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<uint64_t, std::nano>>;

    // Measure distance between points in time
    using TimePoint = std::chrono::steady_clock::time_point;

} // namespace BeaconTech

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_DATATIME_HPP