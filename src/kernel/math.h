#define pi 3.14159265358979323846  /* pi */
#define cos(x) sin(x + pi/2)

double sin(double x) {
    double result = 0.0;
    double term = x;
    double sign = 1.0;
    int i = 1;
    while (i <= 10) {
        result += term;
        sign *= -1.0;
        term *= (x * x) / ((2 * i) * (2 * i + 1));
        i++;
    }
    return result;
}

int abs(int x) {
    if (x < 0)
        return -x;
    else
        return x;
}