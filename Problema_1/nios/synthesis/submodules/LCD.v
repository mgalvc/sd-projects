module LCD (
	dataa,
	datab,
	clk,
	clk_en,
	reset,
	LCD_RS,
	LCD_DATA
);

	input [31:0] dataa;
	input [31:0] datab;
	input clk;
	input clk_en;
	input reset;
	
	output reg LCD_RS;
	output reg [7:0] LCD_DATA;

	always @ (posedge clk or posedge reset) begin
		#6 LCD_RS <= datab[0];
		#4 LCD_DATA[7:0] <= dataa[7:0];
	end

endmodule