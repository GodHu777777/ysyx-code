module IDU (
    input [31:0] inst,
    // output reg [11:0] imm,
    // output reg [4:0] rs1,
    // output reg [4:0] rd,
    output reg IDU_addi_en 
);

// assign rs1 = inst[19:15];
// assign rd = inst[11:7];

assign IDU_addi_en = ~( inst[14] | inst[13] | inst[12] | inst[6] | inst[5] | inst[3] | inst[2] ) & (inst[4] & inst[1] & inst[0]);




endmodule
