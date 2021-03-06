	component nios is
		port (
			buttons_connection_export : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			clk_clk                   : in  std_logic                    := 'X';             -- clk
			leds_connection_export    : out std_logic_vector(4 downto 0);                    -- export
			reset_reset_n             : in  std_logic                    := 'X';             -- reset_n
			data_export               : out std_logic_vector(7 downto 0);                    -- export
			rs_export                 : out std_logic;                                       -- export
			rw_export                 : out std_logic;                                       -- export
			en_export                 : out std_logic                                        -- export
		);
	end component nios;

	u0 : component nios
		port map (
			buttons_connection_export => CONNECTED_TO_buttons_connection_export, -- buttons_connection.export
			clk_clk                   => CONNECTED_TO_clk_clk,                   --                clk.clk
			leds_connection_export    => CONNECTED_TO_leds_connection_export,    --    leds_connection.export
			reset_reset_n             => CONNECTED_TO_reset_reset_n,             --              reset.reset_n
			data_export               => CONNECTED_TO_data_export,               --               data.export
			rs_export                 => CONNECTED_TO_rs_export,                 --                 rs.export
			rw_export                 => CONNECTED_TO_rw_export,                 --                 rw.export
			en_export                 => CONNECTED_TO_en_export                  --                 en.export
		);

