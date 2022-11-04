package com.teksystems;

import java.util.Arrays;
import java.util.Scanner;

// Day 3 & Day 4

public class Day3 {

	public static void main(String[] args) {

//		day3();
//		arraysExample();
		arraysInit();

	}

	public static void day3() {
		// Day 3:
		// print all numbers divisible by 5 with no remainder between 1 & 100
		for (int n = 1; n <= 100; n++) {

			if (n % 5 == 0) {
				System.out.println(n);
			}
		}
	}

	// from day4:
	public static void arraysExample() {
		String[] days = { "Mon", "Tues", "W", "Thurs", "Fried" };
		double[] values = new double[10];

		System.out.println("Before " + Arrays.toString(days));
		// sort will modify the content of the existing array
		// and will not create a new array - arrays are mutable
		Arrays.sort(days);
		System.out.println("Sorted " + Arrays.toString(days));

		System.out.println("==========================");
		// position 0, 1, 2
		int[] sourceArray = { 1, 2, 3 };
		int[] targetArray = sourceArray.clone();

		sourceArray[2] = 500;

		System.out.println("Source Array: " + Arrays.toString(sourceArray));
		System.out.println("Target Array: " + Arrays.toString(targetArray));

		// now we change the pointer of the source array to be equal to the
		// target array - will both print the same thing
		sourceArray = targetArray;

		System.out.println("Source Array: " + Arrays.toString(sourceArray));
		System.out.println("Target Array: " + Arrays.toString(targetArray));

	}

	public static void arraysInit() {
		Scanner sc = new Scanner(System.in);

		System.out.print("Enter the number of elements you want to store: ");
		int n = sc.nextInt();
		int[] array = new int[n];

		for (int i = 0; i < n; i++) {
			System.out.print("Enter the element " + i + " of the array: ");
			array[i] = sc.nextInt();
		}

//		System.out.print("Array elements are: ");
//		System.out.print(Arrays.toString(array) + "\n");

		// print out comma separated list of the elements: 1, 2, 3, 4...
//		for (int i = 0; i < n; i++) {
//			if (i == n - 1) {
//				System.out.print(array[i]);
//			} else {
//				System.out.print(array[i] + ", ");
//			}
//		}
		
		// ????
		for (int i : array) {
			System.out.print(i);
			if (i < n - 1) {
				System.out.print(",");
			}
		}

	}

}
