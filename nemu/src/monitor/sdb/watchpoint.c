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
  int wp_value;
  bool disp;
} WP;

static WP wp_pool[NR_WP] = {};

static WP head_sentinel = {
  .NO = -1,
  .next = NULL,
  .wp_expr = NULL 
};

static WP free_sentinel = {
  .NO = -1,
  .next = NULL,
  .wp_expr = NULL 
};

static WP *head = &head_sentinel, *free_ = &free_sentinel;


WP* new_wp();
void free_wp(int no);

// e here is expression to be watched
void create_watchpoint(char* e);

bool scan_watchpoints();

void debug_func_wp();

void init_wp_pool() {
  head = &head_sentinel;
  free_ = &free_sentinel;
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    wp_pool[i].disp = 1;
    // wp_pool[i].is_free = 1; // init as free state
  }
  /* after for loop, 
    it be like 0->1->2->3->...->n-1->NULL
  */ 

  // use head and free_ as sentinel
  // head->NO = -1; 
  head->next = NULL;
  // free_->NO = -1; 
  free_->next = wp_pool;

  /*
  after here, 
    it be like :
    head -> NULL 
    
    free_ -> 0-> 1->2->3->...->n-1->NULL
  */
}

/* TODO: Implement the functionality of watchpoint */

// idea: use the first element in free_ linklist, 
// and save it as first element in head linklist
// March 7: save to end of head list
WP* new_wp() {

  // no availiable watchpoint node
  if(free_->next == NULL) assert(0);

  // WP* wp1 = free_->next;

  // wp2 point to the current last node in head list
  WP* wp2 = head;
  while(wp2->next != NULL) {
    wp2 = wp2->next;
  }
  wp2->next = free_->next;
  free_->next = free_->next->next;
  wp2->next->next = NULL;
  // free_->next = free_->next->next;
  // wp1->next = head->next;
  // head->next = wp1;

  // return wp1;
  return wp2->next;
} 



void free_wp(int no) {
  // wp is already a node in head linklist
  // first you need to iterate the head list 
  // to find where it is

  WP* wp1 = head;
  WP* wp = head;
  bool is_found = 0;
  // loop to find the node before target wp
  while(wp1->next != NULL) {
    if(wp1->next->NO == no) {
      // Step0: use wp to cache the node to be delete
      // step into here means the wp found
      // i.e. wp1 is the node before wp 
      wp = wp1->next;

      // Step1: let node before target point to node after target
      // delete wp node from head
      wp1->next = wp1->next->next;

      // Step2: target node points to first of free_ list
      wp->next = free_->next;
      
      // Step3: free_ point to target
      free_->next = wp;


      // add wp into free_ and as the first node
      // wp->next = free_->next;
      // free_ = wp;

      is_found = 1;
      break;
    }

    wp1 = wp1->next;
  }

  if(!is_found) assert(0); // not founded
}


// show current watchpoints
void print_watchpoints() {
  if(head->next == NULL) {
    printf("No watchpoints.\n");
    return;
  }else {
    printf("NUM Disp  What\n");
  }

  WP* wp1 = head->next;
  while (wp1 != NULL)
  {
    char* my_disp = wp1->disp ? "keep" : "del";

    printf("%-3d %-4s  %s\n", wp1->NO, my_disp, wp1->wp_expr);
    wp1 = wp1->next;
  }
  
}

void print_linklist(WP* wp) {
  wp = wp->next;
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

  // WP* wp0 = create_watchpoint("1 + 2");
  // WP* wp1 = create_watchpoint("$t0");
  // free_wp(wp1);
  // WP* wp2 = create_watchpoint("$t0");
  // WP* wp3 = create_watchpoint("$t0");

  create_watchpoint("1 + 2");
  create_watchpoint("$t0");
  
  create_watchpoint("$t0");
  // create_watchpoint("$t0");
  // create_watchpoint("$t0");
  
  
  printf("HEAD: ");print_linklist(head);
  printf("free_: ");print_linklist(free_);
  
  printf("HEAD after freed: ");print_linklist(head);
  printf("free_ after freed: ");print_linklist(free_);

  // free_wp(wp3);
  printf("HEAD after freed: ");print_linklist(head);
  printf("free_ after freed: ");print_linklist(free_);

  
  // printf("%d", wp0->NO);
  // printf("%s", head->next->next->wp_expr);
  // printf("%d", wp2->NO);
  // printf("%d", wp3->NO);
  
}

// api for other files who want to create wp
void create_watchpoint(char* e) {
  WP* wp1 = new_wp();
  wp1->wp_expr = e; 
  wp1->wp_value = expr(e, NULL);
  // return wp1;
}

void delete_watchpoint(int no) {
  free_wp(no);
}

// return 1 when expr modified
bool scan_watchpoints() {

  WP* wp1 = head;

  // check all nodes in head list
  while(wp1 != NULL) {
    if(wp1 == head) {wp1=wp1->next; continue;}

    uint32_t cur_value = expr(wp1->wp_expr, NULL);
    if(cur_value != wp1->wp_value) {
      // assert(0);

      printf("[watchpoint]: encounter wp%d of \"%s\"\n", wp1->NO, wp1->wp_expr);
      return 1;
    }
    wp1 = wp1->next; 
  } 

  return 0;
}