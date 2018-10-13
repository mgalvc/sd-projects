module LCD (
	dataa,
	datab,
	clk,
	clk_en,
	reset,
	lcd_rs,
	lcd_rw,
	lcd_en,
	lcd_data
);

	input wire [7:0] dataa;
	input wire datab;
	input clk, clk_en, reset;
	output reg lcd_rs, lcd_rw, lcd_en;
	output reg [7:0] lcd_data;
	
	initial begin
		lcd_rw = 0;
		lcd_en = 1;
	end
	
	always @ (posedge clk) begin
		lcd_data <= dataa;
		lcd_rs <= datab;
	end
  
endmodule

