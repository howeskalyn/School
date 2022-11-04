package com.teksystems;

import java.util.Scanner;

public class Day2 {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		System.out.print("Input weight in kilogram: ");
		double weight = sc.nextDouble();
		System.out.print("\nInput height in meters: ");
		double height = sc.nextDouble();
		
		double BMI = (weight) / (height * height);
		
		if (BMI < 18.5)
			System.out.println("Underweight");
		else if (BMI <25 && BMI >= 18.5)
			System.out.println("Normal");
		
		sc.close();

	}

}
