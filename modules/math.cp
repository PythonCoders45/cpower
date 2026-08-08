// c^ Standard Library - Comprehensive Unified Math Module with Statistics
class Math {

    // ==========================================
    // 1. CONSTANTS (Scaled by 100,000)
    // ==========================================
    public int getPi() {
        return 314159; // 3.14159
    }

    public int getE() {
        return 271828; // 2.71828
    }

    // ==========================================
    // 2. ABSOLUTE & COMPARISON
    // ==========================================
    public int abs(int value) {
        if (value < 0) {
            return value * -1;
        }
        return value;
    }

    public int max(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }

    public int min(int a, int b) {
        if (a < b) {
            return a;
        }
        return b;
    }

    // ==========================================
    // 3. POWERS & ROOTS
    // ==========================================
    public int pow(int base, int exp) {
        int result = 1;
        int i = 0;
        while (i < exp) {
            result = result * base;
            i = i + 1;
        }
        return result;
    }

    public int sqrt(int n) {
        if (n < 0) {
            return 0; 
        }
        if (n == 0 || n == 1) {
            return n;
        }
        
        int i = 1;
        int result = 1;
        while (result <= n) {
            i = i + 1;
            result = i * i;
        }
        return i - 1;
    }

    // ==========================================
    // 4. NUMBER PROPERTIES & FACTORIAL
    // ==========================================
    public bool isEven(int n) {
        int remainder = n - ((n / 2) * 2);
        if (remainder == 0) {
            return true;
        }
        return false;
    }

    public bool isOdd(int n) {
        if (isEven(n) == true) {
            return false;
        }
        return true;
    }

    public int factorial(int n) {
        if (n <= 1) {
            return 1;
        }
        int result = 1;
        int i = 2;
        while (i <= n) {
            result = result * i;
            i = i + 1;
        }
        return result;
    }

    // ==========================================
    // 5. TRIGONOMETRY (Taylor Series Approximations)
    // ==========================================
    public int radians(int degrees) {
        return (degrees * 314159) / 180;
    }

    public int sin(int x) {
        int twoPi = 628318;
        while (x > twoPi) {
            x = x - twoPi;
        }
        while (x < 0) {
            x = x + twoPi;
        }

        int x2 = (x * x) / 100000;
        int x3 = (x2 * x) / 100000;
        int x5 = (x3 * x2) / 100000;
        int x7 = (x5 * x2) / 100000;

        int term1 = x;
        int term2 = x3 / 6;
        int term3 = x5 / 120;
        int term4 = x7 / 5040;

        return term1 - term2 + term3 - term4;
    }

    public int cos(int x) {
        int halfPi = 157079;
        return sin(x + halfPi);
    }

    public int tan(int x) {
        int s = sin(x);
        int c = cos(x);
        if (c == 0) {
            return 0; 
        }
        return (s * 100000) / c;
    }

    // ==========================================
    // 6. STATISTICS (Mean, Median, Mode)
    // ==========================================
    public int mean(int sum, int count) {
        if (count == 0) {
            return 0;
        }
        return (sum * 100000) / count;
    }

    public int medianOfThree(int a, int b, int c) {
        if ((a > b && a < c) || (a < b && a > c)) {
            return a;
        } else if ((b > a && b < c) || (b < a && b > c)) {
            return b;
        } else {
            return c;
        }
    }

    public int simpleMode(int a, int b) {
        return a; 
    }
}
