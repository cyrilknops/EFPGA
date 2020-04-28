----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06.01.2018 14:53:52
-- Design Name: 
-- Module Name: Leds - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Leds is
generic(
    clock_frequency: integer := 50_000_000 -- Hertz
);
    Port ( clk_in : in STD_LOGIC;
            -- om states opnieuw te doen
           runstates : in STD_LOGIC_VECTOR (3 downto 0);
           led_out : out STD_LOGIC;
           -- leds declaraties
           states : in STD_LOGIC_VECTOR (3 downto 0);
           Led0 : in STD_LOGIC_VECTOR (23 downto 0);
           Led1 : in std_logic_vector (23 downto 0);
           Led2 : in std_logic_vector (23 downto 0);
           Led3 : in std_logic_vector (23 downto 0);
           Led4 : in std_logic_vector (23 downto 0);
           Led5 : in std_logic_vector (23 downto 0);
           Led6 : in std_logic_vector (23 downto 0);
           Led7 : in std_logic_vector (23 downto 0);
           Led8 : in std_logic_vector (23 downto 0);
           Led9 : in std_logic_vector (23 downto 0);
           Led10 : in std_logic_vector (23 downto 0);
           Led11 : in std_logic_vector (23 downto 0);
           Led12 : in std_logic_vector (23 downto 0);
           Led13 : in std_logic_vector (23 downto 0);
           Led14 : in std_logic_vector (23 downto 0);
           Led15 : in std_logic_vector (23 downto 0);
           Led16 : in std_logic_vector (23 downto 0);
           Led17 : in std_logic_vector (23 downto 0);
           Led18 : in std_logic_vector (23 downto 0);
           Led19 : in std_logic_vector (23 downto 0);
           Led20 : in std_logic_vector (23 downto 0);
           Led21 : in std_logic_vector (23 downto 0);
           Led22 : in std_logic_vector (23 downto 0);
           Led23 : in std_logic_vector (23 downto 0);
           Led24 : in std_logic_vector (23 downto 0);
           Led25 : in std_logic_vector (23 downto 0);
           Led26 : in std_logic_vector (23 downto 0);
           Led27 : in std_logic_vector (23 downto 0);
           Led28 : in std_logic_vector (23 downto 0);
           Led29 : in std_logic_vector (23 downto 0);
           Led30 : in std_logic_vector (23 downto 0);
           Led31 : in std_logic_vector (23 downto 0);
           Led32 : in std_logic_vector (23 downto 0);
           Led33 : in std_logic_vector (23 downto 0);
           Led34 : in std_logic_vector (23 downto 0);
           Led35 : in std_logic_vector (23 downto 0);
           Led36 : in std_logic_vector (23 downto 0);
           Led37 : in std_logic_vector (23 downto 0);
           Led38 : in std_logic_vector (23 downto 0);
           Led39 : in std_logic_vector (23 downto 0);
           Led40 : in std_logic_vector (23 downto 0);
           Led41 : in std_logic_vector (23 downto 0);
           Led42 : in std_logic_vector (23 downto 0);
           Led43 : in std_logic_vector (23 downto 0);
           Led44 : in std_logic_vector (23 downto 0);
           Led45 : in std_logic_vector (23 downto 0);
           Led46 : in std_logic_vector (23 downto 0);
           Led47 : in std_logic_vector (23 downto 0);
           Led48 : in std_logic_vector (23 downto 0);
           Led49 : in std_logic_vector (23 downto 0);
           Led50 : in std_logic_vector (23 downto 0);
           Led51 : in std_logic_vector (23 downto 0);
           Led52 : in std_logic_vector (23 downto 0);
           Led53 : in std_logic_vector (23 downto 0);
           Led54 : in std_logic_vector (23 downto 0);
           Led55 : in std_logic_vector (23 downto 0);
           Led56 : in std_logic_vector (23 downto 0);
           Led57 : in std_logic_vector (23 downto 0);
           Led58 : in std_logic_vector (23 downto 0);
           Led59 : in std_logic_vector (23 downto 0);
           Led60 : in std_logic_vector (23 downto 0);
           Led61 : in std_logic_vector (23 downto 0);
           Led62 : in std_logic_vector (23 downto 0);
           Led63 : in std_logic_vector (23 downto 0));
end Leds;

architecture Behavioral of Leds is

    constant T0_h   :   integer := 17;
    constant T0_l   :   integer := 38;
    constant T1_h   :   integer := 35;
    constant T1_l   :   integer := 28;
    constant Reset  :   integer := 2500;
    
    type LED_matrix is array(0 to 63) of std_logic_vector(23 downto 0);
    type st_machine is (loading_state, sending_state, send_bit_state,reset_state);

begin
    process
        variable    state               : st_machine := loading_state;

        
        
        variable    GRB                 : std_logic_vector (23 downto 0)    := x"000000";
        variable    delay_high_cntr     : integer := 0;
        variable    delay_low_cntr      : integer := 0;
        variable    index               : integer := 0;
        variable    bit_cntr            : integer := 0;
        variable    LEDS                : LED_matrix;

begin

		   LEDS(0) :=  Led0;  --  LED  0
           LEDS(1) :=  Led1;  --  LED  1
           LEDS(2) :=  Led2;  --  LED  2
           LEDS(3) :=  Led3;  --  LED  3
           LEDS(4) :=  Led4;  --  LED  4
           LEDS(5) :=  Led5;  --  LED  5
           LEDS(6) :=  Led6;  --  LED  6
           LEDS(7) :=  Led7;  --  LED  7
           LEDS(8) :=  Led8;  --  LED  8
           LEDS(9) :=  Led9;  --  LED  9
           LEDS(10) := Led10;  -- LED  10
           LEDS(11) := Led11;  -- LED  11
           LEDS(12) := Led12;  -- LED  12
           LEDS(13) := Led13;  -- LED  13
           LEDS(14) := Led14;  -- LED  14
           LEDS(15) := Led15;  -- LED  15
           LEDS(16) := Led16;  -- LED  16
           LEDS(17) := Led17;  -- LED  17
           LEDS(18) := Led18;  -- LED  18
           LEDS(19) := Led19;  -- LED  19
           LEDS(20) := Led20;  -- LED  20
           LEDS(21) := Led21;  -- LED  21
           LEDS(22) := Led22;  -- LED  22
           LEDS(23) := Led23;  -- LED  23
           LEDS(24) := Led24;  -- LED  24
           LEDS(25) := Led25;  -- LED  25
           LEDS(26) := Led26;  -- LED  26
           LEDS(27) := Led27;  -- LED  27
           LEDS(28) := Led28;  -- LED  28
           LEDS(29) := Led29;  -- LED  29
           LEDS(30) := Led30;  -- LED  30
           LEDS(31) := Led31;  -- LED  31
           LEDS(32) := Led32;  -- LED  32
           LEDS(33) := Led33;  -- LED  33
           LEDS(34) := Led34;  -- LED  34
           LEDS(35) := Led35;  -- LED  35
           LEDS(36) := Led36;  -- LED  36
           LEDS(37) := Led37;  -- LED  37
           LEDS(38) := Led38;  -- LED  38
           LEDS(39) := Led39;  -- LED  39
           LEDS(40) := Led40;  -- LED  40
           LEDS(41) := Led41;  -- LED  41
           LEDS(42) := Led42;  -- LED  42
           LEDS(43) := Led43;  -- LED  43
           LEDS(44) := Led44;  -- LED  44
           LEDS(45) := Led45;  -- LED  45
           LEDS(46) := Led46;  -- LED  46
           LEDS(47) := Led47;  -- LED  47
           LEDS(48) := Led48;  -- LED  48
           LEDS(49) := Led49;  -- LED  49
           LEDS(50) := Led50;  -- LED  50
           LEDS(51) := Led51;  -- LED  51
           LEDS(52) := Led52;  -- LED  52
           LEDS(53) := Led53;  -- LED  53
           LEDS(54) := Led54;  -- LED  54
           LEDS(55) := Led55;  -- LED  55
           LEDS(56) := Led56;  -- LED  56
           LEDS(57) := Led57;  -- LED  57
           LEDS(58) := Led58;  -- LED  58
           LEDS(59) := Led59;  -- LED  59
           LEDS(60) := Led60;  -- LED  60
           LEDS(61) := Led61;  -- LED  61
           LEDS(62) := Led62;  -- LED  62
           LEDS(63) := Led63;  -- LED  63

     wait until rising_edge(clk_in);
     if (runstates = "0001") then
    
         case state is
             when loading_state  =>
                                     GRB         := LEDS(index);
                                     bit_cntr    := 24;
                                     state       := sending_state;
             when sending_state  =>
                                     if( bit_cntr  > 0) then
                                         bit_cntr    := bit_cntr -1;
                                         if GRB(bit_cntr) ='1' then
                                             delay_high_cntr := T1_h;
                                             delay_low_cntr  := T1_l;
                                         else
                                             delay_high_cntr := T0_h;
                                             delay_low_cntr  := T0_l;
                                         end if;
                                         state   := send_bit_state;
                                     else
                                         if( index < 63) then
                                             index   := index + 1;
                                             state   := loading_state;
                                         else
                                             delay_low_cntr := Reset;
                                             state          := reset_state;
                                         end if;
                                     end if;
             when send_bit_state =>
                                     if (delay_high_cntr > 0) then
                                         led_out <= '1';
                                         delay_high_cntr := delay_high_cntr - 1;
                                     elsif (delay_low_cntr > 0) then
                                         led_out <= '0';
                                         delay_low_cntr := delay_low_cntr - 1;
                                     else
                                         state := sending_state;
                                     end if;
             when reset_state    =>
                                     if (delay_low_cntr > 0) then
                                         led_out <= '0';
                                         delay_low_cntr := delay_low_cntr - 1;
                                     else
                                         index := 0;
                                     end if;
             when others         =>
                                     NULL;
         end case;
     else
         state := loading_state;
     end if;
  end process;
 end Behavioral;
