#include <cstdio>

int main() {
    int w; // Variable to store the input weight

    // Read the integer weight from standard input
    if (scanf("%d", &w) != 1) {
        // If input reading fails, exit with an error code
        return 1;
    }

    // Check if the weight is non-negative and divisible by 5
    if (w >= 0 && w % 5 == 0) {
        // Calculate the weight for each side
        double weight_per_side = (double)w / 2.0;
        // Print the result formatted to two decimal places
        printf("%.2f\n", weight_per_side);
    } else {
        // If the conditions are not met, print -1
        printf("-1\n");
    }

    return 0; // Exit successfully
}
