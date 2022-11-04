package com.perscholas.java_basics;

import java.util.Arrays;

public class ArraySort {
	
	public static void main(String[] args) {
		
		int[] sort = {10, 2, 99, 4, 3, 2, 1, 5, 7, 8};
		System.out.println(Arrays.toString(sort));
		
		// bubble sort
		for (int i = 0; i < sort.length; i++) {
			for (int j = 0; j < sort.length - i - 1; j++) {
				if(sort[j] > sort[j+1]) {
					// swap j & j+1
					int temp = sort[j];
					sort[j] = sort[j+1];
					sort[j+1] = temp;
				}
			}
		}
		
		System.out.println(Arrays.toString(sort));
		
	}

}
