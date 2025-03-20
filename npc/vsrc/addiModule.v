module addiModule(
    input [31:0] inst,
    input addi_en,
    input clk,
    input reg [31:0] rf_data, // link to regValue
    output reg [4:0] rf_addr, // link to waddr

    output reg [31:0] write_rf_data, // link to wdata
    output reg wen,
    output reg inst_exec_over
);

reg [31:0] imm;
reg [31:0] rs1;

reg [31:0] alu_out;


always @(inst) begin
    // $display("inst in addimod: %x, addi_en: ", inst, addi_en);
    if(addi_en) begin
        // $display("HELLO HEY");
    end
end

// always @(posedge addi_en) begin
//     $display("step into exec");

reg [2:0] count;

always @(posedge clk) begin
    
    if(addi_en)begin 
    case (count)
        3'b000: begin
            // set RegFile as read mode
            wen <= 0;
            rf_addr <= inst[19:15];   
            count <= 3'b001;
            imm <= { {20{inst[31]}}, inst[31:20] };
        end
        3'b001: begin     
            
            count <= 3'b010;
        end
        3'b010: begin
            // read rs1 and set RegFile as write mode
            rs1 <= rf_data;
            $display("inst: %xH, read data: %xH, imm: %xH", inst, rf_data, imm);
            count <= 3'b011;
            wen <= 1;
        end
        3'b011: begin
            // write result to rd
            rf_addr <= inst[11:7];
            write_rf_data <= rs1 + imm;
            // $display("Result: %x",  rs1 + imm);
            count <= 3'b100;
        end
        3'b100: begin
            // #5;
            inst_exec_over <= ~inst_exec_over;
            count <= 3'b101;
        end
        3'b101: begin
            inst_exec_over <= ~inst_exec_over;
            count <= 3'b000;
        end

        default: 
            count <= 3'b000;

endcase
    end

end

// always @(clk) begin
   
//     $display("inst in addimod: %x", inst);
//     if(addi_en) begin
//             $display("HELLO");
//         imm = { {20{inst[31]}}, inst[31:20] };
        
//         // read rs1 from RegisterFile
//         wen = 0;

//         rf_addr = inst[19:15];
//         rs1 = rf_data;

//         #1;

//         // add imm to rs1
//         alu_out = rs1 + imm;

        
//         $display("inst: %xH, res: %xH, imm: %xH", inst, alu_out, imm);

//         #1;

//         // write result to rd
//         wen = 1;
        
//         rf_addr = inst[11:7];
//         write_rf_data = alu_out;

//         #1;
//         inst_exec_over = ~inst_exec_over;

//         #1;
//         inst_exec_over = ~inst_exec_over;
        
//     end
// end



endmodule
