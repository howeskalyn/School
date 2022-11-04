package com.perscholas.java_basics;

public class CoreJavaVariables {
	
	public static void main(String[] args) {
		
		// #1
		int x = 4;
		int y = 5;
		int sum = x + y;
		System.out.println(x + " + " + y + " = " + sum);
		
		// #2
		double a = 5.0;
		double b = 6.0;
		double dSum = a + b;
		System.out.println(a + " + " + b + " = " + dSum);
		
		// #3
		int c = 3;
		double d = 9;
		double dSum2 = c + d; // sum must be a double
		System.out.println(c + " + " + d + " = " + dSum2);
		
		// #4
		int largerNum = 10;
		int smallerNum = 8;
		int quotient = largerNum / smallerNum;
		System.out.println(largerNum + " / " + smallerNum + " = " + quotient);
		// largerNum = 10.0 - cannot change larger number to a decimal if initalized as an int.
		// double dLargerNum = 10.0;
		//quotient = dLargerNum / smallerNum - type mismatch, can't store a double in an int
		
		// #5
		double dSmallerNum = 2;
		double dLargerNum = 16;
		double dQuotient = dLargerNum / dSmallerNum;
		System.out.println(dLargerNum + " / " + dSmallerNum + " = " + dQuotient);
		int iQuotient = (int) (dLargerNum / dSmallerNum);
		System.out.println(dLargerNum + " / " + dSmallerNum + " = " + iQuotient);
		
		// #6
		x = 5;
		y = 6;
		double q = y/x; // must be a double for the casting two lines down
		System.out.println(q);
		q = (double) y;
		System.out.println(q);
		
		// #7
		final double PI = 3.1415926;
		double r = 6;
		double circumference = 2 * PI * r; 
		System.out.println("The circumference of a circle with radius " + r + " is: " + circumference + "\n");
		
		// #8
		double coffee = 3.45;
		double espresso = 4.25;
		double tea = 2.50;
		double subtotal = 0, totalSale = 0;
		
		subtotal = (3 * coffee) + (4 * espresso) + (2 * tea);
		System.out.println("Your subtotal is: " + subtotal);
		
		final double SALES_TAX = 0.06;
		totalSale = subtotal + (subtotal * SALES_TAX);
		System.out.printf("Your total with tax is: %.2f", totalSale);
		
	
	}

}
