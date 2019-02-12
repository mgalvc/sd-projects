module Custom (
		input clk,
		input clk_en,
		input reset,
		input [31:0] dataa,
		input [31:0] datab,
		
		output reg ledCustom
);

	always @(posedge clk) begin
		if (clk_en) begin
			ledCustom <= dataa[0];
		end
	end
	
endmodule

