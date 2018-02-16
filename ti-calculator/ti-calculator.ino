/*

Ti-Calculator.

inspired Sinclair Scientific Calculator.
http://files.righto.com/calculator/sinclair_scientific_simulator.html

the code
https://github.com/Klapautsiy/Ti-Calculator

the code used a library "titanium bicycle for button".
https://klapautsiy.github.io/titanium-bicycle-for-button/

MIT License.

Arduino board and LCD1602 HD44780 and matrix keypad 4x4.

LCD 1602
+----------------+
|Ti -1.234567e+12|
| +  0.000000e+00|
+----------------+

matrix keypad 4x4
key               index key
[7][8][9][+] <=> ( 0)( 1)( 2)( 3)
[4][5][6][-] <=> ( 4)( 5)( 6)( 7)
[1][2][3][*] <=> ( 8)( 9)(10)(11)
[0][C][!][/] <=> (12)(13)(14)(15)

IEEE Standard for Floating-Point Arithmetic (IEEE 754).
single-precision floating-point format.

key: [C] -> nullify result
key: [!] -> sign of mantissa and exponentials
key: [+] -> addition
key: [-] -> subtraction
key: [*] -> multiplication
key: [/] -> division

input: -1.234567e-12 key: [!][1][2][3][4][5][6][7][!][1][2]
input:  0.001        key: [0][0][0][1]
input: -55           key: [!][5][5][!][1]
input:  1000         key: [1][!][3]

Reverse Polish Notation (RPN).

examples:
1+2=    key: [1][+][2][+]
(-4)+8= key: [!][4][+][8][+]
2*(-5)= key: [2][+][!][5][*]
7*9-3=  key: [7][+][9][*][3][-]

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13, 14);

#include <Matrix.h>
Matrix keypad;

char  f_input[14];
float f_result = 0.0;
byte i = 1;
boolean end_input = 0;
char key = ' ';

void setup() {
lcd.begin(16, 2);
lcd.cursor();
create_matrix();
dtostre(0.0, f_input, 6, DTOSTR_ALWAYS_SIGN);
print_LCD();
}

void create_matrix() {
keypad.NO();
keypad.OKRO();
keypad.pullUp();
keypad.duration_bounce(20);
keypad.matrix_x(A0,A1,A2,A3);
keypad.matrix_y(A4,A5,A6,A7);
}

void loop() {
keypad.read();
calc();
}

void calc() {

if (keypad.event_click_Dn(12) == 1) {key = '0'; input(key);} // key '0' - (12)
if (keypad.event_click_Dn( 8) == 1) {key = '1'; input(key);} // key '1' - ( 8)
if (keypad.event_click_Dn( 9) == 1) {key = '2'; input(key);} // key '2' - ( 9)
if (keypad.event_click_Dn(10) == 1) {key = '3'; input(key);} // key '3' - (10)
if (keypad.event_click_Dn( 4) == 1) {key = '4'; input(key);} // key '4' - ( 4)
if (keypad.event_click_Dn( 5) == 1) {key = '5'; input(key);} // key '5' - ( 5)
if (keypad.event_click_Dn( 6) == 1) {key = '6'; input(key);} // key '6' - ( 6)
if (keypad.event_click_Dn( 0) == 1) {key = '7'; input(key);} // key '7' - ( 0)
if (keypad.event_click_Dn( 1) == 1) {key = '8'; input(key);} // key '8' - ( 1)
if (keypad.event_click_Dn( 2) == 1) {key = '9'; input(key);} // key '9' - ( 2)

// you can add function keys with a variable f_result.
if (keypad.event_click_Dn( 3) == 1) {key = '+'; func_key(); f_result += atof(f_input);} // key '+' - ( 3)
if (keypad.event_click_Dn( 7) == 1) {key = '-'; func_key(); f_result -= atof(f_input);} // key '-' - ( 7)
if (keypad.event_click_Dn(11) == 1) {key = '*'; func_key(); f_result *= atof(f_input);} // key '*' - (11)
if (keypad.event_click_Dn(15) == 1) {key = '/'; func_key(); f_result /= atof(f_input);} // key '/' - (15)

if (keypad.event_click_Dn(14) == 1) {key = '!';              // key '!' - (14)
if (i ==  1) {if (f_input[ 0] == '-') f_input[ 0] = ' '; else f_input[ 0] = '-';}
if (i == 10) {if (f_input[10] == '-') f_input[10] = '+'; else f_input[10] = '-';}
if (i >   1 && i < 10) i = 10;

}

if (keypad.event_click_Dn(13) == 1) {key = 'C'; f_result = 0.0;} // key 'c' - (13)

if (keypad.event_click_Dn() == 1) print_LCD();

}

void func_key() {
end_input = 1;
i = 1;
}

void clear_f_input() {
dtostre(0.0, f_input, 6, DTOSTR_ALWAYS_SIGN);
end_input = 0;
i = 1;
}

void input(char &a) {
if (end_input == 1) clear_f_input();
if (i == 10) i++;
if (i <  10) f_input[i] = a;
if (i == 11 || i == 12) {f_input[11] = f_input[12]; f_input[12] = a;}
if (i <  13)            i++;
if (i ==  2 || i ==  9) i++;
}

void print_LCD() {

lcd.clear();

lcd.setCursor(0, 0);
lcd.print("Ti");

lcd.setCursor(1, 1);
lcd.print(key);

lcd.setCursor(3, 0);
lcd.print(f_input);

char buf_f_result[14];
dtostre(f_result, buf_f_result, 6, DTOSTR_ALWAYS_SIGN);
lcd.setCursor(3, 1);
lcd.print(buf_f_result);

byte n = i;
if (i == 11) n = 12;
lcd.setCursor(3 + n, 0);

}

