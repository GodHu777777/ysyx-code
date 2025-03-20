// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->ebreak = (0x100073U == vlSelf->inst);
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Body
    VL_WRITEF("PC: updated\n");
    vlSelf->pc_out = ((IData)(vlSelf->PC_rst) ? 0x80000000U
                       : vlSelf->top__DOT____Vcellinp__u_PC__din);
    VL_WRITEF("PC: %x\n",32,vlSelf->pc_out);
    vlSelf->top__DOT____Vcellinp__u_PC__din = ((IData)(4U) 
                                               + vlSelf->pc_out);
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    // Init
    CData/*4:0*/ __Vdlyvdim0__top__DOT__u_RegisterFile__DOT__rf__v0;
    __Vdlyvdim0__top__DOT__u_RegisterFile__DOT__rf__v0 = 0;
    IData/*31:0*/ __Vdlyvval__top__DOT__u_RegisterFile__DOT__rf__v0;
    __Vdlyvval__top__DOT__u_RegisterFile__DOT__rf__v0 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_RegisterFile__DOT__rf__v0;
    __Vdlyvset__top__DOT__u_RegisterFile__DOT__rf__v0 = 0;
    IData/*31:0*/ __Vdly__top__DOT__rf_data;
    __Vdly__top__DOT__rf_data = 0;
    CData/*2:0*/ __Vdly__top__DOT__u_addiModule__DOT__count;
    __Vdly__top__DOT__u_addiModule__DOT__count = 0;
    CData/*0:0*/ __Vdly__top__DOT__inst_exec_over;
    __Vdly__top__DOT__inst_exec_over = 0;
    // Body
    __Vdly__top__DOT__inst_exec_over = vlSelf->top__DOT__inst_exec_over;
    __Vdly__top__DOT__u_addiModule__DOT__count = vlSelf->top__DOT__u_addiModule__DOT__count;
    __Vdly__top__DOT__rf_data = vlSelf->top__DOT__rf_data;
    __Vdlyvset__top__DOT__u_RegisterFile__DOT__rf__v0 = 0U;
    if (vlSelf->top__DOT__wen) {
        VL_WRITEF("[RegFile]: Reg %x be written: %x\n",
                  5,vlSelf->top__DOT__rf_addr,32,vlSelf->top__DOT__write_rf_data);
        __Vdlyvval__top__DOT__u_RegisterFile__DOT__rf__v0 
            = vlSelf->top__DOT__write_rf_data;
        __Vdlyvset__top__DOT__u_RegisterFile__DOT__rf__v0 = 1U;
        __Vdlyvdim0__top__DOT__u_RegisterFile__DOT__rf__v0 
            = vlSelf->top__DOT__rf_addr;
    } else {
        __Vdly__top__DOT__rf_data = vlSelf->top__DOT__u_RegisterFile__DOT__rf
            [vlSelf->top__DOT__rf_addr];
        VL_WRITEF("[RegFile]: Reg %x be read: %x\n",
                  5,vlSelf->top__DOT__rf_addr,32,vlSelf->top__DOT__u_RegisterFile__DOT__rf
                  [vlSelf->top__DOT__rf_addr]);
    }
    if (__Vdlyvset__top__DOT__u_RegisterFile__DOT__rf__v0) {
        vlSelf->top__DOT__u_RegisterFile__DOT__rf[__Vdlyvdim0__top__DOT__u_RegisterFile__DOT__rf__v0] 
            = __Vdlyvval__top__DOT__u_RegisterFile__DOT__rf__v0;
    }
    if ((IData)(((0x13U == (0x13U & vlSelf->inst)) 
                 & (~ (IData)((0U != (0x706cU & vlSelf->inst))))))) {
        if ((4U & (IData)(vlSelf->top__DOT__u_addiModule__DOT__count))) {
            if ((2U & (IData)(vlSelf->top__DOT__u_addiModule__DOT__count))) {
                __Vdly__top__DOT__u_addiModule__DOT__count = 0U;
            } else if ((1U & (IData)(vlSelf->top__DOT__u_addiModule__DOT__count))) {
                __Vdly__top__DOT__inst_exec_over = 
                    (1U & (~ (IData)(vlSelf->top__DOT__inst_exec_over)));
                __Vdly__top__DOT__u_addiModule__DOT__count = 0U;
            } else {
                __Vdly__top__DOT__inst_exec_over = 
                    (1U & (~ (IData)(vlSelf->top__DOT__inst_exec_over)));
                __Vdly__top__DOT__u_addiModule__DOT__count = 5U;
            }
        } else if ((2U & (IData)(vlSelf->top__DOT__u_addiModule__DOT__count))) {
            if (VL_LIKELY((1U & (IData)(vlSelf->top__DOT__u_addiModule__DOT__count)))) {
                vlSelf->top__DOT__rf_addr = (0x1fU 
                                             & (vlSelf->inst 
                                                >> 7U));
                vlSelf->top__DOT__write_rf_data = (vlSelf->top__DOT__u_addiModule__DOT__rs1 
                                                   + vlSelf->top__DOT__u_addiModule__DOT__imm);
                __Vdly__top__DOT__u_addiModule__DOT__count = 4U;
            } else {
                VL_WRITEF("inst: %xH, read data: %xH, imm: %xH\n",
                          32,vlSelf->inst,32,vlSelf->top__DOT__rf_data,
                          32,vlSelf->top__DOT__u_addiModule__DOT__imm);
                vlSelf->top__DOT__u_addiModule__DOT__rs1 
                    = vlSelf->top__DOT__rf_data;
                __Vdly__top__DOT__u_addiModule__DOT__count = 3U;
                vlSelf->top__DOT__wen = 1U;
            }
        } else if ((1U & (IData)(vlSelf->top__DOT__u_addiModule__DOT__count))) {
            __Vdly__top__DOT__u_addiModule__DOT__count = 2U;
        } else {
            vlSelf->top__DOT__wen = 0U;
            vlSelf->top__DOT__rf_addr = (0x1fU & (vlSelf->inst 
                                                  >> 0xfU));
            __Vdly__top__DOT__u_addiModule__DOT__count = 1U;
            vlSelf->top__DOT__u_addiModule__DOT__imm 
                = (((- (IData)((vlSelf->inst >> 0x1fU))) 
                    << 0xcU) | (vlSelf->inst >> 0x14U));
        }
    }
    vlSelf->top__DOT__rf_data = __Vdly__top__DOT__rf_data;
    vlSelf->top__DOT__u_addiModule__DOT__count = __Vdly__top__DOT__u_addiModule__DOT__count;
    vlSelf->top__DOT__inst_exec_over = __Vdly__top__DOT__inst_exec_over;
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<2> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vtop___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("vsrc/top.v", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vtop___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("vsrc/top.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("vsrc/top.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->PC_rst & 0xfeU))) {
        Verilated::overWidthError("PC_rst");}
}
#endif  // VL_DEBUG
