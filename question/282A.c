#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int x = 0;
    for (int i = 0; i < n; i++) {
        char a[4]; // Assuming the input will be a string of length 3(imp)
        scanf("%s", a);
        if (a[0] == '+' || a[1] == '+' || a[2] == '+') {
            x += 1;
        } else {
            x -= 1;
        }
    }
    printf("%d\n", x);
    return 0;
}
