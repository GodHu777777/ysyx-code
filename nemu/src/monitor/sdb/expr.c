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

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
// @hgh: to use "varibles"
#include "sdb.h"

static bool make_token(char *);

// @hgh: 

// return true when ch is an operator, ch is a token
bool is_operator(char ch);

// return true when the expression is surrounded by correct parentheses
bool check_parentheses(int p, int q);

// evaluate the expression from token p to q 
// NOTE!: tokens must not contain any spaces
int eval(int p, int q);

// size of tokens
int cnt = 0;

enum {
  TK_NOTYPE = 256, TK_EQ,TK_NEQ, TK_AND,TK_REF,TK_HEX_NUM,TK_REG,

  /* TODO: Add more token types */
  TK_NUM
};


static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  // regex   token_type
  // {"-[0-9]+", TK_NUM},  // negative number
  {"(0x)[0-9a-eA-E]+", TK_HEX_NUM}, // 0x1234
  {"[0-9]+", TK_NUM},   // number
  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"\\-", '-'},         // minus
  {"\\*", '*'},         // multiply
  {"\\/", '/'},         // divise
  {"\\(", '('},         // left parenthesis
  {"\\)", ')'},         // right parenthesis
  {"!=", TK_NEQ},       // not equal
  {"&&", TK_AND},       // and
  {"\\*", TK_REF},      // ref
  
  
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    // assert(0);
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }

  // // @hgh: debug
  // make_token("(((10 + 3))) * ((2 - 1))");
  // int ans = eval(0, cnt - 1);

  // make_token("(1+2)");
  // int ans = eval(0, cnt - 1);
  // cnt = 0;
  // Log("HGHGH: %d", ans);
}

typedef struct token {
  int type;
  char str[32];
} Token;

// @hgh: modify 32 to 65536 for gen_expr test
static Token tokens[65536] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  // // @:
  pmatch.rm_so = 0;
  // pmatch.rm_eo = strlen(e);

  nr_token = 0;

  

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    // @hgh: each i represents each 
    for (i = 0; i < NR_REGEX; i ++) {
      // assert(0);
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        // assert(0);
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        // printf("%.*s\n",substr_len, substr_start);
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case TK_NOTYPE: break;
          // to check if '*' is a multiplication or deref
          case '*': if(is_operator(tokens[cnt - 1].type) || tokens[cnt - 1].type == '(') tokens[cnt].type = TK_REF;break; 
          case TK_HEX_NUM:
            char* tmp_str = (char*)malloc(substr_len + 1);
            strncpy(tmp_str, substr_start, substr_len);
            int value_in_decimal = strtol(tmp_str, NULL, 16);
            sprintf(tmp_str, "%d", value_in_decimal);
            for(int j = 0; j <= strlen(tmp_str); j++) {
              tokens[cnt].str[j] = tmp_str[j]; // save string
              if(j == substr_len) tokens[cnt].str[j] ='\0'; // clear
            }
            
            free(tmp_str);
            break;
          case TK_NUM: 
            for(int j = 0; j <= substr_len; j++) {
              tokens[cnt].str[j] = substr_start[j]; // save string
              if(j == substr_len) tokens[cnt].str[j] ='\0'; // clear
            }
          
          default: tokens[cnt].type = rules[i].token_type;

          // printf("HGHGH: 0x%x, %c\n", cnt, tokens[cnt].type);
          cnt++;
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  // cnt = 0;
  return true;
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  // TODO();
  // save printed variables 
  variables[variable_count] = eval(0, cnt - 1);
  printf("$%d: %d\n", variable_count, variables[variable_count]);
  variable_count ++;

  // clear tokens
  cnt = 0;
  return 0;
}

bool is_operator(char ch) {
  if(ch == '+' || ch == '-' || ch == '*' || ch == '/') return true;
  return false;
}

bool check_parentheses(int p, int q) {
  if(tokens[p].type != '(' || tokens[q].type != ')') return false;
  int top = 0;
  for(int i = p + 1; i < q; i++) {
    if(tokens[i].type == '(') top++;
    if(tokens[i].type == ')') top--;
    if(top < 0) return false;
  }
  if(top == 0) return true;
  return false;
}

// calculate the value of expression in [p, q]
int eval(int p, int q) {
  if(p > q) {
    Log("%d %d", p, q);
    // return;
    assert(0);
  } 
  else if(p == q) {
    return atoi(tokens[p].str);
  }
  else if(check_parentheses(p, q) == true) {
    return eval(p + 1, q - 1);
  }
  else {
    // to find the latest operator 
    // and calculate the result of the two sides of the operator
    // denote + or - as 1; * or / as 2
    int priority = 2;
    int op = -1;

    // find the operator with the lowest priority
    // and saves its position in op
    for(int i = p; i <= q; i++) {
      /* you need to specify the parentheses are totally over
       if one opretor is in a parentheses 
       it is more prior than operator outside
      */
      if(tokens[i].type == '(') {
        int parent_count = 1;
        while(parent_count != 0 && i < cnt) {
          i++;
          if(tokens[i].type == '(') parent_count++;
          if(tokens[i].type == ')') parent_count--;
          // printf("pa_ch: %d\n", i);
        }
      }
      if(is_operator(tokens[i].type)) {
        Log("i: %d, token[i].type: %c", i, tokens[i].type);
        if(op == -1) { // first operator; do initialization
          op = i; 
          Log("BEGIN op: %d; i: %d", tokens[op].type, i);
          if(tokens[i].type == '+' || tokens[i].type == '-') priority = 1;
          else priority = 2;
        }
        else { // later operator
          // + or - always the lowest priority
          if(tokens[i].type == '+' || tokens[i].type == '-') {
            op = i;
            priority = 1;
          }
          // * or / is recorded only if the current operator is * or /
          else {
            if(priority == 2) {
              op = i;
            }
          }
        }

        Log("@@@@ %d, %c", op, tokens[op].type);
      }
      // Log("@@@@ QAQ %d, %d", op, i);
    }
    

    if(tokens[op].type == '+') return eval(p, op - 1) + eval(op + 1, q);
    if(tokens[op].type == '-') return eval(p, op - 1) - eval(op + 1, q); 
    if(tokens[op].type == '*') return eval(p, op - 1) * eval(op + 1, q);
    if(tokens[op].type == '/') return eval(p, op - 1) / eval(op + 1, q);

    Log("HGHGH: %d", op);
    // for compiler
    assert(0);   
    return 0;
  }
}
