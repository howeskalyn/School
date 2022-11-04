package com.teksystems;

import java.util.Scanner;

public class Day1 {

	private static final double PI = 3.14159;

	public static void main(String[] args) {

		// Example (slide 7):
		double radius = 20, area;
		area = radius * radius * PI;
		System.out.println("The area of a circle with radius " + radius + " is " + area + "\n");

		// Primitive data types (slide 20):
		byte num = 113;
		System.out.println(num);

		short snum = 150;
		System.out.println(snum);

		long lnum = -12332252626L;
		System.out.println(lnum);

		double dnum = -42937727.9d;
		System.out.println(dnum);

		float fnum = 19.98f;
		System.out.println(fnum);

		boolean b = false;
		System.out.println(b);

		char ch = 'Z';
		// char ch = '\u0061'; // a
		System.out.println(ch + "\n");
		
		// Character literals (slide 28):
		System.out.println("This will print on\r\ntwo lines.");
		System.out.println("She said \"Hello\" to me!");
		System.out.println("This will print two back-slashes: \\\\");
		System.out.println();

		// String literals (slide 30):
		String test = "pop";
		System.out.println(test);
		test = test.concat("corn");
		System.out.println(test + "\n");
		
		// Scanner example (slide 37):
		Scanner input = new Scanner(System.in);
		System.out.print("Enter your name: ");
		String name = input.nextLine();
		System.out.println("My name is " + name + ".\n");
		input.close(); // close Scanner

		// Trenary Operator (slide 47):
		int age = 18;
		String result = age < 100 ? "Less than 100" : "Greater than 100";
		System.out.println(result + "\n");

		// Division & Modulus (slide 53);
		int d = 5, e = 2;
		System.out.println("Integer division " + d + "/" + e + " = " + d / e);
		double f = 5.0;
		System.out.println("Floating-point division " + f + "/" + e + " = " + f / e);
		System.out.println("Integer modulus " + d + "%" + e + " = " + f % e);
		System.out.println("Floating-point modulus " + f + "%" + e + " = " + f % e + "\n");

		// Problem: Displaying Time (slide 56);
		int inSeconds = 86399;

		int seconds = inSeconds % 60;
		int hours = inSeconds / 60;
		int minutes = hours % 60;
		hours = hours / 60;

		System.out.println("Input seconds: " + inSeconds);
		System.out.println("Hours:Minutes:Seconds = " + hours + ":" + minutes + ":" + seconds + "\n");

		// Type casting (slide 61):
		byte i = 40;
		short j = i;
		int k = j;
		long l = k;
		float m = l;
		double n = m;
		System.out.println("byte value: " + i);
		System.out.println("short value: " + j);
		System.out.println("int value: " + k);
		System.out.println("long value: " + l);
		System.out.println("float value: " + m);
		System.out.println("double value: " + n);
		  	// s =  short(k); // Not Allowed - narrowing
		    // c = (char)(k); // Not Allowed - narrowing
		float fl = 1.5e3f;
		k = (int)f; // Explicit - okay!
			// k = fl // Not Allowed - narrowing


	}

}
