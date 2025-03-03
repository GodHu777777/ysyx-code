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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

#define MAX_DEPTH 15

int choose(int n) {
  return rand() % n;
}

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"#include <signal.h>\n"
"#include <stdlib.h>\n"

"void handle_sigfpe(int sig) {\n"
// "    printf(\"Division by zero error!\\n\");\n"
"    printf(\"\");\n"
"    exit(1); // \n"
"}"


"int main() { \n"
"  signal(SIGFPE, handle_sigfpe);\n"
"  unsigned result = %s; \n"
"  char *s = \"%s\";\n"
"  printf(\"%%u %%s \\n\", result, s); \n"
"  return 0; \n"
"}\n";

int buffer_length = 0;


void gen_num() {
  int random_number = choose(1 << 5);
  char str_number[20]; // 定义一个足够大的字符数组
  sprintf(str_number, "%d", random_number);
  strcat(buf, str_number);
}

static void gen_rand_op() {
  char ops[] = {'+', '-', '*', '/'};
  strncat(buf, &ops[choose(sizeof(ops) / sizeof(ops[0]))], 1);

}

static void gen_rand_expr(int depth) {
  if(depth > MAX_DEPTH) {
    gen_num();
    return;
  }

  // generate random space
  if(choose(2)) strcat(buf, " ");
  
  switch (choose(3)) {
    case 0: gen_num(); break;
    case 1: strcat(buf, "("); gen_rand_expr(depth + 1); strcat(buf, ")"); break;
    default: gen_rand_expr(depth + 1); gen_rand_op(); gen_rand_expr(depth + 1); break;
  }

  // generate random space
  if(choose(2)) strcat(buf, " ");
  
}


int main(int argc, char *argv[]) {

  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    buf[0] = '\0'; // clear buf before generating new expression
    gen_rand_expr(0);


    // save buf into code_buf 
    sprintf(code_buf, code_format, buf, buf);

    FILE *fp = fopen("./.code.c", "w");
    assert(fp != NULL);

    // write code_buf into ./.code.c
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc ./.code.c -o ./.expr && ./.expr");
    if (ret != 0) continue;

    fp = popen("./.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    // printf("%s\n",  buf);
  }
  return 0;
}
