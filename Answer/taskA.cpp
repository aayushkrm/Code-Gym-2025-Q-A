#include <cstdio> 

int main() {
    int w;

    if (scanf("%d", &w) != 1) { 

        return 1; 
    }


    if (w >= 0 && w % 5 == 0) {

        double weight_per_side = (double)w / 2.0;

        printf("%.2f\n", weight_per_side); 
    } else {

        printf("-1\n");
    }

    return 0;
}
