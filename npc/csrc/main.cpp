#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h" // 使用VCD格式的头文件

unsigned long long insts[1000] = { 0x00108113, 0x00210193, 0x00100073};
unsigned pmem_read(unsigned long long addr) {
  assert(addr - 0x80000000 < 1000);
  // printf("#DEBUG addr: %x, inst: %x \n", addr, insts[(addr - 0x80000000) / 4]);
  return insts[(addr - 0x80000000) / 4];
}


int main(int argc, char** argv) {
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vtop* top = new Vtop{contextp};

    // 波形初始化
    Verilated::traceEverOn(true);       // 启用波形跟踪
    VerilatedVcdC* tfp = new VerilatedVcdC; // 使用VCD格式
    top->trace(tfp, 99);                // 跟踪99层层次结构
    tfp->open("wave.vcd");              // 使用.vcd文件

    int t = 0;
    
    top->PC_rst = 0;

    while (!contextp->gotFinish()) {

      if(top->ebreak) break;
      printf("TIME: %d ## ", contextp->time());

      contextp->timeInc(1);          // 先增加时间
        
        top->clk = ~top->clk;
        
        // printf("pc: %x, clk: %b\n", top->pc_out, top->clk);
        if(t > 4) top->inst = pmem_read(top->pc_out);
        
        t++;
        top->eval();
        tfp->dump(contextp->time());   // 写入波形

        if(t > 40) break;
    }

    printf("Time: %llu, PC_rst: %d, clk: %d, inst: %x\n", contextp->time(), top->PC_rst, top->clk, top->inst);
    top->final();
    tfp->close();
    delete tfp;
    delete top;
    delete contextp;
    return 0;
}
