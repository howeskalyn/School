package com.perscholas.java_basics;

import java.util.Arrays;

public class ArraysAssignment {

	public static void main(String[] args) {

		// 1:
		System.out.println("----Question 1----");
		int[] a = new int[3];
		for (int i = 0; i < a.length; i++) {
			a[i] = i + 1;
			System.out.println(a[i]);
		}

		// 2:
		System.out.println("\n----Question 2----");
		int[] b = { 13, 5, 7, 68, 2 };
		System.out.println(b[b.length / 2]);

		// 3:
		System.out.println("\n----Question 3----");
		String[] c = { "red", "green", "blue", "yellow" };
		System.out.println("Length: " + c.length);
		String[] copyArray = c.clone();
		System.out.println(c);
		System.out.println(copyArray.toString());

		// 4:
		System.out.println("\n----Question 4----");
		int[] d = { 5, 34, 56, 13, 78 };
		System.out.println("Value at first index: " + d[0]);
		System.out.println("Value at last index: " + d[d.length - 1]);
		// d[d.length] - wont run because length is 1 greater than the indexing
		// d[5] = 3 - wont run because index 5 does not exist

		// 5:
		System.out.println("\n----Question 5----");
		int[] e = new int[5];
		for (int i = 0; i < 5; i++) {
			e[i] = i;
			System.out.print(e[i] + " ");
		}

		// 6:
		System.out.println("\n\n----Question 6----");
		int[] f = new int[5];
		for (int i = 0; i < 5; i++) {
			f[i] = i * 2;
			System.out.print(f[i] + " ");
		}

		// 7:
		System.out.println("\n\n----Question 7----");
		int[] g = { 4, 86, 23, 6, 23 };
		for (int i = 0; i < 5; i++) {

			if (i == 2) {
				continue;
			}

			System.out.print(f[i] + " ");
		}

		// 8:
		System.out.println("\n\n----Question 8----");
		int[] h = { 56, 34, 2, 3, 5 };
		Arrays.toString(h);
		System.out.println();
		int temp = h[0];
		h[0] = h[2];
		h[2] = temp;
		Arrays.toString(h);

		// 9:
		System.out.println("\n\n----Question 9----");

		// 10:
		System.out.println("\n\n----Question 10----");

		// 11:
		System.out.println("\n\n----Question 11----");

	}

}
