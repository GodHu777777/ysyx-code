// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+41,"clk", false,-1);
    tracep->declBus(c+42,"inst", false,-1, 31,0);
    tracep->declBit(c+43,"PC_rst", false,-1);
    tracep->declBus(c+44,"pc_out", false,-1, 31,0);
    tracep->declBit(c+45,"ebreak", false,-1);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+41,"clk", false,-1);
    tracep->declBus(c+42,"inst", false,-1, 31,0);
    tracep->declBit(c+43,"PC_rst", false,-1);
    tracep->declBus(c+44,"pc_out", false,-1, 31,0);
    tracep->declBit(c+45,"ebreak", false,-1);
    tracep->declBit(c+46,"IDU_addi_en", false,-1);
    tracep->declBus(c+1,"rf_data", false,-1, 31,0);
    tracep->declBus(c+2,"rf_addr", false,-1, 4,0);
    tracep->declBit(c+3,"wen", false,-1);
    tracep->declBus(c+4,"write_rf_data", false,-1, 31,0);
    tracep->declBit(c+5,"inst_exec_over", false,-1);
    tracep->pushNamePrefix("u_IDU ");
    tracep->declBus(c+42,"inst", false,-1, 31,0);
    tracep->declBit(c+46,"IDU_addi_en", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_PC ");
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBit(c+43,"rst", false,-1);
    tracep->declBus(c+47,"din", false,-1, 31,0);
    tracep->declBus(c+44,"dout", false,-1, 31,0);
    tracep->declBit(c+48,"wen", false,-1);
    tracep->pushNamePrefix("i0 ");
    tracep->declBus(c+49,"WIDTH", false,-1, 31,0);
    tracep->declBus(c+50,"RESET_VAL", false,-1, 31,0);
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBit(c+43,"rst", false,-1);
    tracep->declBus(c+47,"din", false,-1, 31,0);
    tracep->declBus(c+44,"dout", false,-1, 31,0);
    tracep->declBit(c+48,"wen", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("u_RegisterFile ");
    tracep->declBus(c+51,"ADDR_WIDTH", false,-1, 31,0);
    tracep->declBus(c+49,"DATA_WIDTH", false,-1, 31,0);
    tracep->declBit(c+41,"clk", false,-1);
    tracep->declBus(c+4,"wdata", false,-1, 31,0);
    tracep->declBus(c+2,"waddr", false,-1, 4,0);
    tracep->declBit(c+3,"wen", false,-1);
    tracep->declBus(c+1,"regValue", false,-1, 31,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+6+i*1,"rf", true,(i+0), 31,0);
    }
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_addiModule ");
    tracep->declBus(c+42,"inst", false,-1, 31,0);
    tracep->declBit(c+46,"addi_en", false,-1);
    tracep->declBit(c+41,"clk", false,-1);
    tracep->declBus(c+1,"rf_data", false,-1, 31,0);
    tracep->declBus(c+2,"rf_addr", false,-1, 4,0);
    tracep->declBus(c+4,"write_rf_data", false,-1, 31,0);
    tracep->declBit(c+3,"wen", false,-1);
    tracep->declBit(c+5,"inst_exec_over", false,-1);
    tracep->declBus(c+38,"imm", false,-1, 31,0);
    tracep->declBus(c+39,"rs1", false,-1, 31,0);
    tracep->declBus(c+52,"alu_out", false,-1, 31,0);
    tracep->declBus(c+40,"count", false,-1, 2,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_eBreakModule ");
    tracep->declBus(c+42,"inst", false,-1, 31,0);
    tracep->declBit(c+45,"ebreak", false,-1);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSelf->top__DOT__rf_data),32);
    bufp->fullCData(oldp+2,(vlSelf->top__DOT__rf_addr),5);
    bufp->fullBit(oldp+3,(vlSelf->top__DOT__wen));
    bufp->fullIData(oldp+4,(vlSelf->top__DOT__write_rf_data),32);
    bufp->fullBit(oldp+5,(vlSelf->top__DOT__inst_exec_over));
    bufp->fullIData(oldp+6,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[0]),32);
    bufp->fullIData(oldp+7,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[1]),32);
    bufp->fullIData(oldp+8,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[2]),32);
    bufp->fullIData(oldp+9,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[3]),32);
    bufp->fullIData(oldp+10,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[4]),32);
    bufp->fullIData(oldp+11,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[5]),32);
    bufp->fullIData(oldp+12,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[6]),32);
    bufp->fullIData(oldp+13,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[7]),32);
    bufp->fullIData(oldp+14,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[8]),32);
    bufp->fullIData(oldp+15,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[9]),32);
    bufp->fullIData(oldp+16,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[10]),32);
    bufp->fullIData(oldp+17,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[11]),32);
    bufp->fullIData(oldp+18,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[12]),32);
    bufp->fullIData(oldp+19,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[13]),32);
    bufp->fullIData(oldp+20,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[14]),32);
    bufp->fullIData(oldp+21,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[15]),32);
    bufp->fullIData(oldp+22,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[16]),32);
    bufp->fullIData(oldp+23,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[17]),32);
    bufp->fullIData(oldp+24,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[18]),32);
    bufp->fullIData(oldp+25,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[19]),32);
    bufp->fullIData(oldp+26,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[20]),32);
    bufp->fullIData(oldp+27,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[21]),32);
    bufp->fullIData(oldp+28,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[22]),32);
    bufp->fullIData(oldp+29,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[23]),32);
    bufp->fullIData(oldp+30,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[24]),32);
    bufp->fullIData(oldp+31,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[25]),32);
    bufp->fullIData(oldp+32,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[26]),32);
    bufp->fullIData(oldp+33,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[27]),32);
    bufp->fullIData(oldp+34,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[28]),32);
    bufp->fullIData(oldp+35,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[29]),32);
    bufp->fullIData(oldp+36,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[30]),32);
    bufp->fullIData(oldp+37,(vlSelf->top__DOT__u_RegisterFile__DOT__rf[31]),32);
    bufp->fullIData(oldp+38,(vlSelf->top__DOT__u_addiModule__DOT__imm),32);
    bufp->fullIData(oldp+39,(vlSelf->top__DOT__u_addiModule__DOT__rs1),32);
    bufp->fullCData(oldp+40,(vlSelf->top__DOT__u_addiModule__DOT__count),3);
    bufp->fullBit(oldp+41,(vlSelf->clk));
    bufp->fullIData(oldp+42,(vlSelf->inst),32);
    bufp->fullBit(oldp+43,(vlSelf->PC_rst));
    bufp->fullIData(oldp+44,(vlSelf->pc_out),32);
    bufp->fullBit(oldp+45,(vlSelf->ebreak));
    bufp->fullBit(oldp+46,((IData)(((0x13U == (0x13U 
                                               & vlSelf->inst)) 
                                    & (~ (IData)((0U 
                                                  != 
                                                  (0x706cU 
                                                   & vlSelf->inst))))))));
    bufp->fullIData(oldp+47,(((IData)(4U) + vlSelf->pc_out)),32);
    bufp->fullBit(oldp+48,(1U));
    bufp->fullIData(oldp+49,(0x20U),32);
    bufp->fullIData(oldp+50,(0x80000000U),32);
    bufp->fullIData(oldp+51,(5U),32);
    bufp->fullIData(oldp+52,(vlSelf->top__DOT__u_addiModule__DOT__alu_out),32);
}
