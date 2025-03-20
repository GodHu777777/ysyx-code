module top(
    input clk, // use c++ to set
    input [31:0] inst, // use c++
    input PC_rst, // use c++
    output reg [31:0] pc_out,
    output reg ebreak
);

eBreakModule u_eBreakModule(
    .inst   	(inst    ),
    .ebreak 	(ebreak  )
);


PC u_PC(
    .clk  	(inst_exec_over  ), // every time one inst over, turn it over
    .rst  	(PC_rst    ),
    .din  	(pc_out + 4   ),
    .dout 	(pc_out  ),
    .wen  	(1   )
);

reg IDU_addi_en;

IDU u_IDU(
    .inst        	(inst         ),
    .IDU_addi_en 	(IDU_addi_en  )
);


always @(*) begin
    
// $display("clk: %b", clk);
// $display("inst: %x", inst);
// $display("IDU_en: %b", IDU_addi_en);

// $display("inst_exec_over: %x", inst_exec_over);

end

reg [31:0] rf_data; // read from RegFile usage
reg [4:0] rf_addr;
reg wen; // whether to write in RegFile or read
reg [31:0] write_rf_data; // write into RegFile

RegisterFile u_RegisterFile(
    .clk      	(clk       ),
    .wdata    	(write_rf_data     ),
    .waddr    	(rf_addr     ),
    .wen      	(wen       ),
    .regValue 	(rf_data  )
);


reg inst_exec_over;

addiModule u_addiModule(
    .inst           	(inst            ),
    .addi_en        	(IDU_addi_en        ),
    .clk            	(clk             ),
    .rf_data        	(rf_data         ), // data read from RegFile
    .rf_addr        	(rf_addr         ), 
    .write_rf_data  	(write_rf_data   ),// data to write into RegFile
    .wen            	(wen             ),
    .inst_exec_over 	(inst_exec_over  ) // use this to drive pc
);





endmodule
