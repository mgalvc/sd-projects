module LCD(
	input [31:0] dataa,
	output [31:0] result,
	output LED
);

	assign LED = dataa[0];

endmodule