----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 21.04.2020 09:38:06
-- Design Name: 
-- Module Name: OEF2_LED_COUNTDOWN - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_misc.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
library UNISIM;
use UNISIM.VComponents.all;

entity OEF2_LED_COUNTDOWN is
Port (
LatchPin : out std_logic;
ClockPin : out std_logic;
TestOut : out std_logic;
DataPin : out std_logic
 );
end OEF2_LED_COUNTDOWN;

architecture Behavioral of OEF2_LED_COUNTDOWN is
    signal counter      : unsigned (27 downto 0);
    signal counter_1S   : std_logic;
    signal i_clk        : std_logic;
    signal buf_i_clk    : std_logic;
    TYPE state IS (nul, een, twee, drie, vier, vijf, zes, zeven, acht, negen);
    signal current_state : state := een;

function EncodeMatrix (matrix : std_logic_vector(15 downto 0))
return std_logic_vector is
    variable EncodedMatrix : std_logic_vector(15 downto 0) := x"0000";
    
    begin
    EncodedMatrix := EncodedMatrix OR ((matrix(8 downto 0) & "0000000") AND x"8000");
    EncodedMatrix := EncodedMatrix OR ((matrix(10 downto 0) & "00000") AND x"4000");
    EncodedMatrix := EncodedMatrix OR ((matrix(8 downto 0) & "0000000") AND x"2000");
    EncodedMatrix := EncodedMatrix OR (("000" & matrix(15 downto 3))AND x"1000");
    EncodedMatrix := EncodedMatrix OR ((matrix(8 downto 0) & "0000000")AND x"0800");
    EncodedMatrix := EncodedMatrix OR (matrix(15 downto 0)AND x"0400");
    EncodedMatrix := EncodedMatrix OR (("000" & matrix(15 downto 3)) AND x"0200");
    EncodedMatrix := EncodedMatrix OR ((matrix(14 downto 0) & "0") AND x"0100");

    EncodedMatrix := EncodedMatrix OR ((matrix(11 downto 0) & "0000")AND x"0080");
    EncodedMatrix := EncodedMatrix OR ((matrix(14 downto 0) & "0")AND x"0040");
    EncodedMatrix := EncodedMatrix OR ((matrix(12 downto 0) & "000")AND x"0020");
    EncodedMatrix := EncodedMatrix OR (("0000000" & matrix(15 downto 7))AND x"0010");
    EncodedMatrix := EncodedMatrix OR ((matrix(12 downto 0) & "000")AND x"0008");
    EncodedMatrix := EncodedMatrix OR (("00000000000" & matrix(15 downto 11))AND x"0004");
    EncodedMatrix := EncodedMatrix OR (("0000000000000" & matrix(15 downto 13))AND x"0002");
    EncodedMatrix := EncodedMatrix OR (("0" & matrix(15 downto 1)) AND x"0001");
    return EncodedMatrix;

end EncodeMatrix;

begin

STARTUPE2_inst : STARTUPE2
   generic map (
      PROG_USR => "FALSE",  
      SIM_CCLK_FREQ => 0.0  
   )
   port map (
      CFGCLK => open,      
      CFGMCLK => i_clk,     
      EOS => open,            
      PREQ => open,           
      CLK => '0',            
      GSR => '0',            
      GTS => '0',             
      KEYCLEARB => '0', 
      PACK => '0',           
      USRCCLKO => '0',                         
      USRCCLKTS => '0', 
      USRDONEO => '1',   
      USRDONETS => '0'
   );

		BUFG_i: component BUFG
        port map(
            I => i_clk ,
            O => buf_i_clk
        );
	
	-- buf_i_clk has around 65MHz
	
		
process(buf_i_clk)
	procedure WriteMatrix(shiftbuf : std_logic_vector(15 downto 0)) is
        variable i : integer := 0;
        variable iVector : std_logic_vector(15 downto 0) := (others => '0');
        variable result : std_logic_vector(15 downto 0 );
        variable x : std_logic;
    begin
        Latchpin <= '0';
            for I in 0 to 15 loop
            ClockPin <= '1';
            result := (iVector(i downto 0) & shiftbuf(15 downto i)); 
            
            if ((result(15 downto 0) AND x"0001") = x"0001") THEN
            DataPin <= '1';
            ELSE
            DataPin <= '0';
            END IF;  
                    
            ClockPin <= '0';
            end loop;
        ClockPin <= '1';
        LatchPin <= '1';
        LatchPin <= '0';
        ClockPin <= '0';
    end procedure;

	begin
	   if rising_edge(buf_i_clk) then 
	   counter_1S <= '0';
	           if counter < 65000000 then
	               counter <= counter + 1;
	           else            	           
	               counter_1S <= '1';
	               
	               counter <= (others => '0');
	          end if;
	   end if;
	   
if rising_edge(counter_1S) THEN
    case current_state IS
    
    WHEN negen =>
        current_state <= nul;
        TestOut <= '1';
        WriteMatrix(EncodeMatrix(x"FD3C"));
        WriteMatrix(EncodeMatrix(x"F324"));
        WriteMatrix(EncodeMatrix(x"CF24"));
        WriteMatrix(EncodeMatrix(x"BF3C"));
    WHEN nul =>
    TestOut <= '0';
        current_state <= een;
        WriteMatrix(EncodeMatrix(x"F720"));
        WriteMatrix(EncodeMatrix(x"FB10"));
        WriteMatrix(EncodeMatrix(x"F108"));
        WriteMatrix(EncodeMatrix(x"EF08"));
        WriteMatrix(EncodeMatrix(x"DF08"));
        WriteMatrix(EncodeMatrix(x"BF08"));
    WHEN een =>
        current_state <= twee;
        WriteMatrix(EncodeMatrix(x"FD18"));
        WriteMatrix(EncodeMatrix(x"F324"));
        WriteMatrix(EncodeMatrix(x"EF08"));
        WriteMatrix(EncodeMatrix(x"DF10"));
        WriteMatrix(EncodeMatrix(x"BF3C"));
    when twee =>
        current_state <= drie;
        WriteMatrix(EncodeMatrix(x"FE18"));
        WriteMatrix(EncodeMatrix(x"FD24"));
        WriteMatrix(EncodeMatrix(x"FB04"));
        WriteMatrix(EncodeMatrix(x"F718"));
        WriteMatrix(EncodeMatrix(x"CF04"));
        WriteMatrix(EncodeMatrix(x"DF24"));
        WriteMatrix(EncodeMatrix(x"BF18"));
    when drie =>
        current_state <= vier;
        WriteMatrix(EncodeMatrix(x"FD0C"));
        WriteMatrix(EncodeMatrix(x"FB14"));
        WriteMatrix(EncodeMatrix(x"F724"));
        WriteMatrix(EncodeMatrix(x"EF3C"));
        WriteMatrix(EncodeMatrix(x"9F04"));
    WHEN vier =>
        current_state <= vijf;
        WriteMatrix(EncodeMatrix(x"FD3C"));
        WriteMatrix(EncodeMatrix(x"FB20"));
        WriteMatrix(EncodeMatrix(x"F738"));
        WriteMatrix(EncodeMatrix(x"EF04"));
        WriteMatrix(EncodeMatrix(x"DF24"));
        WriteMatrix(EncodeMatrix(x"BF3C"));
     WHEN vijf =>
        current_state <= zes;
        WriteMatrix(EncodeMatrix(x"FD3C"));
        WriteMatrix(EncodeMatrix(x"FB20"));
        WriteMatrix(EncodeMatrix(x"F720"));
        WriteMatrix(EncodeMatrix(x"EF3C"));
        WriteMatrix(EncodeMatrix(x"DF24"));
        WriteMatrix(EncodeMatrix(x"BF3C")); 
     WHEN zes =>
        current_state <= zeven;
        WriteMatrix(EncodeMatrix(x"FD3E"));
        WriteMatrix(EncodeMatrix(x"FB04"));
        WriteMatrix(EncodeMatrix(x"F708"));
        WriteMatrix(EncodeMatrix(x"8F08"));  
     WHEN zeven =>
        current_state <= acht;
        WriteMatrix(EncodeMatrix(x"FE18"));
        WriteMatrix(EncodeMatrix(x"FD24"));
        WriteMatrix(EncodeMatrix(x"FB24"));
        WriteMatrix(EncodeMatrix(x"F73C"));
        WriteMatrix(EncodeMatrix(x"EF24"));
        WriteMatrix(EncodeMatrix(x"DF24"));
        WriteMatrix(EncodeMatrix(x"BF18"));
     WHEN acht =>
        current_state <= negen;
        WriteMatrix(EncodeMatrix(x"FD18"));
        WriteMatrix(EncodeMatrix(x"FB24"));
        WriteMatrix(EncodeMatrix(x"F724"));
        WriteMatrix(EncodeMatrix(x"EF1C"));
        WriteMatrix(EncodeMatrix(x"DF04"));
        WriteMatrix(EncodeMatrix(x"BF38")); 
end case;
end if;
end process;
end Behavioral;