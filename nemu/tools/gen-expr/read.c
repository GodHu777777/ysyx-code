#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char *filename = "input";
    char line[256]; // 假设每行不超过255个字符，可以根据实际情况调整
    int number;
    char expression[256]; // 假设表达式部分也不超过255个字符

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1; // 表示程序出错
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        // 使用 sscanf 解析每一行
        if (sscanf(line, "%d %[^\n]", &number, expression) == 2) {
            // sscanf 返回成功解析的字段数量，这里期望解析到两个字段
            printf("Number: %d, Expression: %s\n", number, expression);
        } else {
            // 如果解析失败，可能是格式不符合预期或者空行等情况
            fprintf(stderr, "Warning: Could not parse line: %s", line);
            // 可以选择跳过当前行或者进行更详细的错误处理
        }
    }

    fclose(fp);
    return 0; // 表示程序正常结束
}