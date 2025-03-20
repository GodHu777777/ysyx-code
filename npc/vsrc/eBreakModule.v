module eBreakModule(
    input [31:0] inst,
    output reg ebreak
);

// always @(posedge clk) begin
//     ebreak <= (inst == 32'h00100073);
// end

assign ebreak = (inst == 32'h00100073);


endmodule
