## Sphere Online Judge challenge
https://www.spoj.com/SHORTEN/problems/RPN/english/

Your task is to transform the expression with brackets into RPN form.

Priority: + - < * / < ^ < ( )

# Input
The first line of the standard input contains one integer t (t<101) which is the number of test cases.

In each of the next t lines there is a string consisted of two-argument operators: +, -, *, /, ^, brackets ( ) and letters a-z (operands).

# Output
For each test case print the expression in RPN form.

## Example

Input:
4
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))
((a-g)^l/c^h*(l^f-g^y)^i^j)


Output:
abc*+
ab+zx+*
at+bac++cd+^*
ag-l^ch^/lf^gy^-i^j^*
