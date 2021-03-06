#include <stdio.h>
#include <stdlib.h>	// for atof()

#define MAXOP	100 // max size of operand or operator
#define NUMBER	'0'

int getop(char []);
void push(double);
double pop(void);
void showInternals(int);

//reverse polish calculator
int main(){
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF) {
		showInternals(type);
		switch(type){
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if(op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '\n':
			printf("\tResult: %.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

#define MAXVAL	100 // maximum depth of val stack

int sp = 0;			// next free stack position
double val[MAXVAL];	// value stack

// push push f onto value stack
void push(double f){
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

//pop: pop and return top value from stack
double pop(void){
	if(sp > 0)
		return val[--sp];
	else {
		printf("pop error: stack empty.\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);
/*
// getop: get next operator or numeric operand
// separate inputs with either space or tab
int getop(char s[]){
	int i, c;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;	// ignore 
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	// not a number
	i = 0;
	if(isdigit(c))	// collect integer part
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')	// collect fractional part
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if( c != EOF)
		ungetch(c);
	return NUMBER;
}
*/
int getop(char s[]){
    int out;
    char c;
    float f;

    while((out = scanf("%c", &c)) != EOF){
        if((s[0] = c) != '\t' && c != ' ')
            break;
    }
    s[1] = '\0';
    if(out == EOF)
        return EOF;
    if(isdigit(c)){
        ungetc(c, stdin);
        scanf("%f", &f);
        sprintf(s, "%f", f);
        return NUMBER;
    }else{
        return c;
    }
}

#define BUFSIZE	100

char buf[BUFSIZE];	// buffer for ungetch
int bufp = 0;		// next free position in buf

int getch(void){	// get a (possibly pushed back) character
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){	// push character back on input
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void showInternals(int type)
{
	int i;
	printf("Operation: %c\tstack:\t", type == NUMBER ? ' ' : type);
	for(i = 0; i < sp; i++)
		printf("%lf, ", val[i]);
	printf("\n\n");
}
