// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;

class Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    CData/*0:0*/ top__DOT__inst_exec_over;
    VL_IN8(PC_rst,0,0);
    VL_OUT8(ebreak,0,0);
    CData/*4:0*/ top__DOT__rf_addr;
    CData/*0:0*/ top__DOT__wen;
    CData/*2:0*/ top__DOT__u_addiModule__DOT__count;
    CData/*0:0*/ __Vtrigrprev__TOP__top__DOT__inst_exec_over;
    CData/*0:0*/ __Vtrigrprev__TOP__clk;
    CData/*0:0*/ __VactContinue;
    VL_IN(inst,31,0);
    VL_OUT(pc_out,31,0);
    IData/*31:0*/ top__DOT____Vcellinp__u_PC__din;
    IData/*31:0*/ top__DOT__rf_data;
    IData/*31:0*/ top__DOT__write_rf_data;
    IData/*31:0*/ top__DOT__u_addiModule__DOT__imm;
    IData/*31:0*/ top__DOT__u_addiModule__DOT__rs1;
    IData/*31:0*/ top__DOT__u_addiModule__DOT__alu_out;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<IData/*31:0*/, 32> top__DOT__u_RegisterFile__DOT__rf;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
