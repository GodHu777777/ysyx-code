/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <common.h>
#include "/home/ghhu/Desktop/study/ysyx-workbench/nemu/src/monitor/sdb/sdb.h"
void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

    // ----------------- expr test
    FILE *fp;
    char *filename = "/home/ghhu/Desktop/study/ysyx-workbench/nemu/src/input";
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

        expr(expression, NULL);
        // printf("");
        assert(variables[variable_count - 1] == number);
    }

    fclose(fp);
    // -----------------




  /* Start engine. */
  engine_start();


  

  return is_exit_status_bad();
}
