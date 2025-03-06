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

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO; // head and free_, these 2 nodes are set as default -1
  struct watchpoint *next;

  /* TODO: Add more members if necessary */

  // bool is_free;
  char* wp_expr;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

WP* new_wp();
void free_wp(WP *wp);

void debug_func_wp();

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    // wp_pool[i].is_free = 1; // init as free state
  }
  /* after for loop, 
    it be like 0->1->2->3->...->n-1->NULL
  */ 

  head = NULL;
  free_ = wp_pool;

  /*
  after here, 
    it be like :
    head -> NULL
    free_ ->  0->1->2->3->...->n-1->NULL
  */
}

/* TODO: Implement the functionality of watchpoint */

// idea: use the first element in free_ linklist, 
// and save it as first element in head linklist
WP* new_wp() {
  // for(int i = 0; i < NR_WP; i++) {
  //   if(wp_pool[i].is_free == 1) {
  //     return &wp_pool[i];
  //   }
  // }

  WP* wp1 = free_; // Definition: WP *free_ = NULL, free_ is already an address

  if(free_->next != NULL) {
    // use wp1 to cache the first node after head
    wp1 = head->next;
    head->next = free_->next;
    head->next->next = wp1;

    // delete the newed node from free_ linklist
    free_->next = free_->next->next;
  }
  
  return head->next;
  // no availiable watchpoint node
  assert(0);
} 

void free_wp(WP *wp) {
  // wp is already a node in head linklist
  // first you need to iterate the head list 
  // to find where it is

  WP* wp1 = head;
  while(wp1->next != NULL) {
    if(wp1->next->NO == wp->NO) {
      // step into here means the wp found
      // i.e. wp1 is the node before wp 
      
      // delete wp node from head
      wp1->next = wp1->next->next;

      // add wp into free_ and as the first node
      wp->next = free_->next->next;
      free_->next = wp;
    }
  }
}

void print_linklist(WP* wp) {
  while (wp != NULL)
  {
    printf("->%d", wp->NO);
    wp = wp->next;
  }
  printf("\n");
}

void debug_func_wp() {
  print_linklist(head);
  print_linklist(free_);

  WP* wp1 = new_wp();
  print_linklist(head);
  print_linklist(free_);

  printf("%d", wp1->NO);
}