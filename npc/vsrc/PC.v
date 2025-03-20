
// pc: 32bit width and reset at 0x80000000

module PC(
    input clk,
    input rst,
    input [31:0] din,
    output reg [31:0] dout,
    input wen
);

    Reg #(32, 32'h80000000) i0 (
        .clk(clk),
        .rst(rst),
        .din(din),
        .dout(dout),
        .wen(wen)
    );
    initial begin
        dout = 32'h80000000;
    end

always @(*) begin
    $display("PC: %x", dout);
end

always @(posedge clk) begin
    $display("PC: updated");
end
    

endmodule
