	nios u0 (
		.buttons_connection_export            (<connected-to-buttons_connection_export>),            // buttons_connection.export
		.clk_clk                              (<connected-to-clk_clk>),                              //                clk.clk
		.data_export                          (<connected-to-data_export>),                          //               data.export
		.en_export                            (<connected-to-en_export>),                            //                 en.export
		.leds_connection_export               (<connected-to-leds_connection_export>),               //    leds_connection.export
		.rs_export                            (<connected-to-rs_export>),                            //                 rs.export
		.rw_export                            (<connected-to-rw_export>),                            //                 rw.export
		.uart_rxd                             (<connected-to-uart_rxd>),                             //               uart.rxd
		.uart_txd                             (<connected-to-uart_txd>),                             //                   .txd
		.arbiter_conduit_writeresponsevalid_n (<connected-to-arbiter_conduit_writeresponsevalid_n>), //    arbiter_conduit.writeresponsevalid_n
		.arbiter_conduit_beginbursttransfer   (<connected-to-arbiter_conduit_beginbursttransfer>)    //                   .beginbursttransfer
	);

