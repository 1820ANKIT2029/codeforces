#include <stdio.h>

int main() {
    char problem_input[100]; // Assuming a maximum input length of 100 characters
    scanf("%s", problem_input);
    int problem_no = problem_input[0] - '0';
    int output = 0;

    for (int i = 0; i < problem_no; i++) {
        printf("a");
        if (((problem_input[2 + (4 * i)] - '0') + (problem_input[3 + (4 * i)] - '0') + (problem_input[4 + (4 * i)] - '0')) >= 2) {
            output += 1;
        }
    }

    printf("%d\n", output);
    return 0;
}
