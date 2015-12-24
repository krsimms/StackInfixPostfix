#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <string.h>
#include <ctype.h>

#define MAX 50
#define EMPTY -1


//Construct the Stack that is to be manipulated by the code
struct stack
{
	int data[MAX];// Variable for the data to be entered by the user
    int top;// Variable for top of stack
};//End of stack contruction
 

// Determine if a stack is empty
void emptystack(struct stack* s)
{
    s->top=EMPTY;
}//End of Empty Determin-er


//Checks to see when stack is empty
int isempty(struct stack *s)
{
    return (s->top == EMPTY) ? 1 : 0;
}//End of stack "checker"


//Stack push function
void push(struct stack* s,int item)
{
    //Prevents stack from reaching beyond what it can handle
	if(s->top == (MAX-1))
    {
        printf("\nSTACK FULL");
    }
    else
    {
        ++s->top;
        s->data[s->top]=item;
    }
}//End of stack function
 

//Stack pop function
char pop(struct stack* s)
{
    char ret=(char)EMPTY;
    if(!isempty(s))
    {
        ret= s->data[s->top];
        --s->top;
    }
    return ret;
}//End of pop function


//Display stack data variable(s)
void display(struct stack s)
{
    while(s.top != EMPTY)
    {
        printf("\n%d",s.data[s.top]);
        s.top--;
    }
}//End of display function


//Determines what operators can be used in accordence to the code
char isoperator(char e)
{
   //If statement that prevents user from entering any other operator
	if(e == '+' || e == '-' || e == '*' || e == '/' || e == '%')
        return 1;
    else
        return 0;
}//END of operator determin-er function

 
//Determines the priority of the operators in relation to each other 
char priority(char e)
{
    int pri = 0;
	
	//Determines how it evaluates the data
    if(e == '*' || e == '/' || e =='%')
        pri = 2;
    else
    {
        if(e == '+' || e == '-')
            pri = 1;
    }
    return pri;

}//End of priority Determin-er 
 

//Changes Infix notation into prefix notation
void infix2postfix(char* infix, char * postfix, int insertspace)
{
    char *i,*p; //Varibles for the infix and postfix of the stack
    struct stack X; // Variable for the precontructed stack
    char n1;//Variable
    emptystack(&X);//Points to what stack is empty
    i = &infix[0]; //Determines the use of the "i variable"
    p = &postfix[0]; //Determines the use of the "p variable"

	//While loop for the infix
    while(*i)
    {
        while(*i == ' ' || *i == '\t')
        {
            i++;
        }
 
		//If statement that checks for digits and spaces
	       if( isdigit(*i) || isalpha(*i) )
        {
			//While loop for the digits
            while( isdigit(*i) || isalpha(*i))
            {
                *p = *i;
                p++;
                i++;
            }//End of digit while loop
            
			//If statement that checks for spaces
            if(insertspace)
            {
                *p = ' ';
                p++;
            }
            //End of space code

        }//End of If statement digit checker
 
		   //Checks for Left Parenthesis in the infix entered by the user
        if( *i == '(' )
        {
            push(&X,*i);
            i++;
        }//End of Left Parenthesis code
 
		 //Checks for Right Parenthesis in the infix entered by the user
        if( *i == ')')
        {
            n1 = pop(&X);
            while( n1 != '(' )
            {
                *p = n1;
                p++;

                //Checks for spaces in postfix
                if(insertspace)
				{
                    *p = ' ';
                    p++;
                }//End of postfix space code
          
                n1 = pop(&X);
            }
            i++;
        }//End of Right Parenthesis code
 
		//If statement for the operator
        if( isoperator(*i) )
        {
			//If statement that Ccecks for operator
            if(isempty(&X))
                push(&X,*i);
            else
            {
                n1 = pop(&X);

				//While loop for the priority of the operators
                while(priority(n1) >= priority(*i))
                {
                    *p = n1;
                    p++;
                    //If statement that checks for empty spaces
                    if(insertspace)
                    {
                        *p = ' ';
                        p++;
                    }//End of space code

                    n1 = pop(&X);
                }//End of While loop

                push(&X,n1);
                push(&X,*i);
            }////End of if statement that Ccecks for operator
            i++;
        }//End of operator if statement
    }//End of while loop for the infix

	//While statement for empty stacks
    while(!isempty(&X))
    {
        n1 = pop(&X);
        *p = n1;
        p++;

        //If statement that checks for empty spaces
        if(insertspace)
        {
            *p = ' ';
            p++;
        }
        //End of spae code

    }//End of while statement

	*p = '\0';

}//End of infix conversion function


//Evaluates the stack
int evaluate(char *postfix)
{
    char *p;//Variable for postfix
    struct stack X;//Variable for stack
    int op1,op2,result;//Variable for operator and results
 
    emptystack(&X);
    p = &postfix[0];
 
	//While loop for readin the postfix
    while(*p != '\0')
    {
       //Removes tabs and spaces when reading the postfix
        while(*p == ' ' || *p == '\t')
        {
            p++;
        }//End of tab removal while loop

      // Checks if is digit when reading the postfix
        if(isdigit(*p))
        {
            push(&X,*p - 48);
        }//End of if statement

        else
        {
           // Checks to see if it is an operator when reading the postfix
            op1 = pop(&X);
            op2 = pop(&X);
 
			//Switch for the postfix when determining how to evaluate itself
				switch(*p)
            {
				//Case for additional addition symbol
                case '+':
                    result = op2 + op1;
                    break;
 
					//Case for additional subtraction symbol
                case '-':
                    result = op2 - op1;
                    break;
 
					//Case for additional division symbol
                case '/':
                    result = op2 / op1;
                    break;
 
					//Case for additional multiplication symbol
                case '*':
                    result = op2 * op1;
                    break;
 
					//Case for additional division symbol
                case '%':
                    result = op2 % op1;
                    break;
 
                default:
                    return result;//Returns results of evaluation
            }//End of switch

            push(&X,result);//Determines push
        }//End of else statement

        p++;
    }//End of postfix reading while loop
    
	result = pop(&X);//Determines what reprsents the result variable
    return result;//Returns results of evaluation

}//End of evaluation function

//Main function
int main()
{
    char in[50] = { 0 },post[50] = { 0 };//Variable for infix and postfix
 
    strcpy(&post[0],"");//Copies postfix string into the rray
    printf("Enter Infix Expression: ");//Alerts user to enter their infix   

	fgets(in, sizeof(in), stdin);//Get infix string from stream
		in[strlen(in) - 1] = '\0';//Gets length of infix string
	infix2postfix(&in[0],&post[0],1);//Preforms infix conversion
    printf("Postfix Expression is: %s\n",&post[0]);//Prints postfix of entered infix
	
	fgets(in, sizeof(in), stdin);//Get infix string from stream
        post[strlen(post) - 1] = '\0';//Gets length of post string
    printf(" %s EQUALS %d\n",post,evaluate(&post[0]));//Prints infix evaluation	

	std::getchar();//Allows for user to read program before it closes

    
	return 0;//Ends program

	
}//End of main function
