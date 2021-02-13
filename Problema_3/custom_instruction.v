module custom_instruction (
	dataa,
	result
);

input dataa;
output result;

Component component (.dataa(dataa),
							.result(result));


endmodule