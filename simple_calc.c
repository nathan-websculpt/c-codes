#include <stdio.h>
#include <float.h>

int main() {
	char operator;
	double operand_left_side, operand_right_side, rslt;

	int breaker = 1;

	while (breaker)
	{
		printf("Enter an operator (+, -, *, /): ");
		scanf("%c", &operator);

		printf("Enter two operands: ");
		scanf("%lf %lf", &operand_left_side, &operand_right_side);

		switch (operator) {
		case '+':
			rslt = operand_left_side + operand_right_side;
			break;
		case '-':
			rslt = operand_left_side - operand_right_side;
			break;
		case '*':
			rslt = operand_left_side * operand_right_side;
			break;
		case '/':
			rslt = operand_left_side / operand_right_side;
			break;
		case 'q':
			breaker = 0;
			break;
		default:
			printf("Error! Incorrect Operator Value\n");
			rslt = -DBL_MAX;
		}
		if (rslt != -DBL_MAX)
			printf("%.2lf\n\n", rslt);

		while (getchar() != '\n');
	}
    
	return 0;
}
