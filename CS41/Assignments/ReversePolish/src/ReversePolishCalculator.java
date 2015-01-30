/**
 * @author Mike Zrimsek
 * @version 01.28.2015
 */

public class ReversePolishCalculator
{
	private LinkedStack<String> stack;
	private String[] formulaTokens;
	
	public ReversePolishCalculator(String formula)
	{
		stack = new LinkedStack<String>();
		if(!isValidFormula())
			return;
		formulaTokens = formula.split(" ");
		for (String s : formulaTokens)
		{
			if (isOperator(s)) s = doOperation(s, stack.pop(), stack.pop());
			if (!s.equals("=")) stack.push(s);
		}
	}
	
	public String doOperation(String op, String num2, String num1)
	{
		double n1 = Double.valueOf(num1);
		double n2 = Double.valueOf(num2);
		double val = 0;
		if (op.equals("+"))
			val = n1 + n2;
		else if (op.equals("-"))
			val = n1 - n2;
		else if (op.equals("*"))
			val = n1 * n2;
		else
		{
			if (n2 == 0)
			{
				System.out.println("Error: Divide by zero");
				return "NAN";
			}
			val = n1 / n2;
		}
		return val + "";
	}
	
	// FIXME add real stuff to this function
	private boolean isValidFormula()
	{
		return true;
		// check on token instead of formula???
	}
	
	private boolean isOperator(String s)
	{
		return s.equals("+") || s.equals("-") || s.equals("*") || s.equals("/");
	}
	
	public String toString()
	{
		return stack.toString();
	}
}
