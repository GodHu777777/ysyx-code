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

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>

#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write

enum {
  TYPE_I, TYPE_U, TYPE_S, TYPE_J, TYPE_R, TYPE_B,
  TYPE_N, // none
};

#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)
#define immI() do { *imm = SEXT(BITS(i, 31, 20), 12); } while(0)
#define immU() do { *imm = SEXT(BITS(i, 31, 12), 20) << 12; } while(0)
#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
#define immJ() do { *imm = ((SEXT(BITS(i, 31, 31), 1) << 20) | (BITS(i, 30, 21) << 1) | (BITS(i, 20, 20) << 11) | (BITS(i, 19, 12) << 12)); } while(0)
// #define immB() do { *imm = ( (SEXT(BITS(i, 31, 31), 1) << 12) | (SEXT(BITS(i, 30, 25), 6) << 5) | (SEXT(BITS(i, 11, 8), 4) << 1) | (SEXT(BITS(i, 7, 7), 1)) << 11); Log("imm RAW: %x", *imm);} while(0)
#define immB() do { *imm = ( (SEXT(BITS(i, 31, 31), 1) << 12) | (BITS(i, 30, 25) << 5) | (BITS(i, 11, 8) << 1) | BITS(i, 7, 7) << 11); Log("imm B: %x", *imm);} while(0)
              // ( (1 << 13) - 1) & 
static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst;
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
  
  // printf("HALO: %lx\n", SEXT(BITS(0x1, 0, 0), 1));

  // set imm
  // *imm = BITS(i, 31, 20);
  // set rd
  *rd     = BITS(i, 11, 7);
  switch (type) {
    case TYPE_I: src1R();          immI(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_J:                   immJ(); break;
    case TYPE_R: src1R(); src2R();       ; break;
    case TYPE_B: src1R(); src2R(); immB(); break;
    
    case TYPE_N: break;
    default: panic("unsupported type = %d", type);
  }
}

// set dnpc
static int decode_exec(Decode *s) {
  // configure dnpc as snpc at first(snpc is the (physically) next instruction)
  s->dnpc = s->snpc;

#define INSTPAT_INST(s) ((s)->isa.inst)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  int rd = 0; \
  word_t src1 = 0, src2 = 0, imm = 0; \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}

  // declare a flag like thing, which you can jump back here 
  // by using ```goto *(__instpat_end);```
  INSTPAT_START(); // expand to { const void * __instpat_end = &&__instpat_end_;

    /*
    do {
          uint64_t key, mask, shift;

          pattern_decode(
              "??????? ????? ????? ??? ????? 00101 11",
              (sizeof("??????? ????? ????? ??? ????? 00101 11") - 1),
              &key, &mask, &shift
          );

          if ((((uint64_t)((s)->isa.inst) >> shift) & mask) == key) {
              {
                  int rd = 0;
                  word_t src1 = 0, src2 = 0, imm = 0;
                  
                  // first, manipulate operand according to instruction type
                  decode_operand(s, &rd, &src1, &src2, &imm, TYPE_U);

                  (cpu.gpr[check_reg_idx(rd)]) = s->pc + imm;
              };
              goto *(__instpat_end);
          }
      } while (0);

    */
   

  // src1: reg[rs1]  src2: reg[rs2]
  INSTPAT("??????? ????? ????? ??? ????? 00101 11", auipc  , U, R(rd) = s->pc + imm);
  INSTPAT("???? ???? ???? ???? ???? ????? 0110111", lui    , U, R(rd) = imm);

  INSTPAT("???? ???? ???? ????? 000 ????? 0010011", addi   , I, R(rd) = src1 + imm);
  INSTPAT("???? ???? ???? ????? 000 ????? 1100111", jalr   , I, s->dnpc = ((src1 + imm) & ~1); R(rd) = s->pc + 4);
  INSTPAT("???? ???? ???? ????? 011 ????? 0010011", sltiu  , I, R(rd) = src1 < imm);
  INSTPAT("000000 ?????? ????? 001 ????? 001 0011", slli   , I, R(rd) = src1 << imm);
  INSTPAT("???? ???? ???? ????? 111 ????? 0010011", andi   , I, R(rd) = src1 & imm);
  INSTPAT("??????? ????? ????? 100 ????? 00000 11", lbu    , I, R(rd) = SEXT(Mr(src1 + imm, 1), 16));
  INSTPAT("???? ???? ???? ????? 001 ????? 0000011", lh     , I, R(rd) = SEXT(Mr(src1 + imm, 2), 16));
  INSTPAT("???? ???? ???? ????? 010 ????? 0000011", lw     , I, R(rd) = Mr(src1 + imm, 4));
  INSTPAT("000000 ?????? ????? 101 ????? 001 0011", srli   , I, R(rd) = src1 >> imm);
  INSTPAT("010000 ?????? ????? 101 ????? 001 0011", srai   , I, R(rd) = (int32_t)src1 >> imm);
  INSTPAT("???? ???? ???? ????? 100 ????? 0010011", xori   , I, R(rd) = src1 ^ imm);
  

  INSTPAT("??????? ????? ????? 000 ???? ? 1100011", beq    , B, s->dnpc += (src1 == src2) ? (imm - 4) : 0);
  INSTPAT("??????? ????? ????? 001 ???? ? 1100011", bne    , B, s->dnpc += (src1 != src2) ? (imm - 4) : 0);
  // INSTPAT("??????? ????? ????? 101 ???? ? 1100011", bge    , B, s->dnpc += ((int32_t)(src1 - src2) >= 0) ? (imm - 4) : 0;Log("minusRes: %d # src1: %x, src2: %x, imm: %x", (int32_t)(src1 - src2) >= 0, src1, src2, imm));
  INSTPAT("??????? ????? ????? 101 ???? ? 1100011", bge    , B, s->dnpc += ( (int32_t)(src1) >= (int32_t)(src2) ) ? (imm - 4) : 0);
  INSTPAT("??????? ????? ????? 100 ???? ? 1100011", blt    , B, s->dnpc += ( (int32_t)(src1) < (int32_t)(src2) ) ? (imm - 4) : 0);
  INSTPAT("??????? ????? ????? 111 ???? ? 1100011", bgeu   , B, s->dnpc += ( (src1) >= (src2) ) ? (imm - 4) : 0);
  INSTPAT("??????? ????? ????? 110 ???? ? 1100011", bltu   , B, s->dnpc += ( (src1) < (src2) ) ? (imm - 4) : 0);

  INSTPAT("0000000 ????? ????? 000 ????? 011 0011", add    , R, R(rd) = src1 + src2);
  INSTPAT("0100000 ????? ????? 000 ????? 011 0011", sub    , R, R(rd) = src1 - src2);
  INSTPAT("0000001 ????? ????? 000 ????? 011 0011", mul    , R, R(rd) = (int32_t)src1 * (int32_t)src2);
  INSTPAT("0000001 ????? ????? 001 ????? 011 0011", mulh   , R, R(rd) = (int32_t)( (SEXT(src1, 32) * SEXT(src2, 32)) >> 32 ));
  INSTPAT("0000001 ????? ????? 100 ????? 011 0011", div    , R, R(rd) = (int32_t)src1 / (int32_t)src2);
  INSTPAT("0000001 ????? ????? 101 ????? 011 0011", divu   , R, R(rd) = src1 / src2);
  INSTPAT("0000001 ????? ????? 110 ????? 011 0011", rem    , R, R(rd) = src1 % src2);
  INSTPAT("0000001 ????? ????? 111 ????? 011 0011", remu   , R, R(rd) = src1 % src2);
  INSTPAT("0000000 ????? ????? 010 ????? 011 0011", slt    , R, R(rd) = (int32_t)src1 < (int32_t)src2);
  INSTPAT("0000000 ????? ????? 011 ????? 011 0011", sltu   , R, R(rd) = src1 < src2);
  INSTPAT("0000000 ????? ????? 100 ????? 011 0011", xor    , R, R(rd) = src1 ^ src2);
  INSTPAT("0000000 ????? ????? 110 ????? 011 0011", or     , R, R(rd) = src1 | src2);
  INSTPAT("0100000 ????? ????? 101 ????? 011 0011", sra    , R, R(rd) = (int32_t)src1 >> src2);
  INSTPAT("0000000 ????? ????? 101 ????? 011 0011", srl    , R, R(rd) = src1 >> src2);

  INSTPAT("??????? ????? ????? 000 ????? 01000 11", sb     , S, Mw(src1 + imm, 1, src2));
  INSTPAT("??????? ????? ????? 010 ????? 01000 11", sw     , S, Mw(src1 + imm, 4, src2));
  //                                                              Dynamic NEXT pc, it is already "NEXT", so should minus 4
  INSTPAT("???? ???? ???? ???? ???? ????? 1101111", jal    , J, R(rd) = s->pc + 4;s->dnpc += imm - 4; Log("imm J: %x",imm)); 

  INSTPAT("0000000 00001 00000 000 00000 11100 11", ebreak , N, NEMUTRAP(s->pc, R(10))); // R(10) is $a0
  INSTPAT("??????? ????? ????? ??? ????? ????? ??", inv    , N, INV(s->pc)); // for undefined instruction

  
  
  INSTPAT_END();// expand to __instpat_end_: ; }

  R(0) = 0; // reset $zero to 0

  return 0;
}

int isa_exec_once(Decode *s) {
  // instruction fetch
  // @: set snpc as (physically) next instruction
  s->isa.inst = inst_fetch(&s->snpc, 4);
  return decode_exec(s);
}
