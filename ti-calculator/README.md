<pre>

Ti-Calculator.

inspired Sinclair Scientific Calculator.
http://files.righto.com/calculator/sinclair_scientific_simulator.html

the code used a library "titanium bicycle for button".
https://klapautsiy.github.io/titanium-bicycle-for-button/

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

key: [C] -> nullify all
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

</pre>
