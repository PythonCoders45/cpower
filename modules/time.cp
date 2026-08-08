// c^ Standard Library - Comprehensive Unified Time Module
class Time {

    // ==========================================
    // 1. HARDWARE TIME & EPOCH CLOCKS
    // ==========================================

    // Returns current Unix epoch time in seconds (UTC)
    public int time() {
        // Native bridge call to system clock
        return __native_get_epoch_seconds();
    }

    // Returns high-precision timestamp in milliseconds for performance tracking
    public int timeMs() {
        return __native_get_epoch_milliseconds();
    }

    // ==========================================
    // 2. DELAYS & THREAD SLEEP
    // ==========================================

    // Pauses execution for a specified number of milliseconds
    public void sleep(int ms) {
        if (ms > 0) {
            __native_sleep_ms(ms);
        }
    }

    // Pauses execution for a specified number of full seconds
    public void sleepSeconds(int seconds) {
        if (seconds > 0) {
            __native_sleep_ms(seconds * 1000);
        }
    }

    // ==========================================
    // 3. CONVERSIONS & UTILITIES
    // ==========================================

    public int secondsPerMinute() {
        return 60;
    }

    public int secondsPerHour() {
        return 3600;
    }

    public int secondsPerDay() {
        return 86400;
    }

    public int hoursToSeconds(int hours) {
        return hours * 3600;
    }

    public int daysToSeconds(int days) {
        return days * 86400;
    }

    // ==========================================
    // 4. TIMERS & ELAPSED TIME TRACKING
    // ==========================================

    // Calculates how much time is left in a countdown
    public int countdownRemaining(int startTime, int duration) {
        int currentTime = time();
        int elapsed = currentTime - startTime;
        int remaining = duration - elapsed;
        if (remaining < 0) {
            return 0;
        }
        return remaining;
    }

    // Checks if a designated timeout limit has been reached
    public bool isTimeoutReached(int startTime, int limitSeconds) {
        int currentTime = time();
        if ((currentTime - startTime) >= limitSeconds) {
            return true;
        }
        return false;
    }
}
