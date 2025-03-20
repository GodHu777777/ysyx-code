
// used to modify reg value
// @hgh: 
// wen 1: write
// wen 0: read
// works like  ___
//       wen / ren
module RegisterFile #(ADDR_WIDTH = 5, DATA_WIDTH = 32) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input wen,
  output reg [DATA_WIDTH-1:0] regValue
);
  reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
  always @(posedge clk) begin
    if (wen) begin 
      rf[waddr] <= wdata; 
      $display("[RegFile]: Reg %x be written: %x", waddr, wdata);
      end

    else begin
      regValue <= rf[waddr];
      //                                               regValue
      $display("[RegFile]: Reg %x be read: %x", waddr, rf[waddr]);
      
    end 
    
    // $display("reg3: %x", rf[1]);

  end
endmodule
