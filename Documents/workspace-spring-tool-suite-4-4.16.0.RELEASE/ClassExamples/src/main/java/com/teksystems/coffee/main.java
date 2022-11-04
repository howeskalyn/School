package com.teksystems.coffee;

import java.util.Arrays;
import java.util.StringJoiner;
import java.util.Scanner;

public class main {

	private static CoffeeShop tcs = new CoffeeShop();
	private static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {

		// simpleStart();
		start();

	}

	public static void start() {
		boolean ordering = true;
		while (ordering) {

			int input = printOptionsGetInput();
			sc.nextLine();

			switch (input) {
			case 1:
				System.out.print("Enter order item to add: ");
				String orderItem = sc.nextLine();
				tcs.addOrder(orderItem);
				break;
			case 2:
				tcs.listOrders();
				break;
			case 3:
				System.out.println(tcs.fulfillOrder());
				break;
			case 4:
				System.out.print("Would you like to list the menu by item, type, or price? ");
				String listBy = sc.nextLine();
				tcs.listMenu(listBy);
				break;
			case 5:
				System.out.printf("Current total Due: $%.2f\n", tcs.dueAmount());
				break;
			case 6:
				System.out.println("\n=== Drinks ===\n" + tcs.findByType("drink"));
				break;
			case 7:
				System.out.println("\n=== Food ===\n" + tcs.findByType("food"));
				break;
			case 8:
				System.out.print("Enter order item to remove: ");
				String removeItem = sc.nextLine();
				tcs.removeOrder(removeItem);
				break;
			case 9:
				ordering = false;
				System.out.println("Exiting...");

			}
		}

	}

	public static int printOptionsGetInput() {
		System.out.println("\n----- OPTIONS -----");
		System.out.println(
				"1) Add Item to Order\n2) List Items in Order \n3) Fulfill Order\n4) List Menu\n5) Print Total");
		System.out.println("6) List Menu Drinks\n7) List Menu Food\n8) Remove Item from Order\n9) Exit");

		System.out.print("Choose an option 1-9: ");
		int input = 0;
		try {
			input = sc.nextInt();
		} catch (Exception e) {
			System.out.println("Please enter a number from 1-9.\n");
		}

		return input;

	}

//	public static void simpleStart() {
//		System.out.println(tcs.addOrder("hot cocoa"));
//		System.out.println(tcs.addOrder("cinnamon roll"));
//		System.out.println(tcs.addOrder("iced coffee"));
//
//		// System.out.println(Arrays.toString(tcs.listOrders()));
//		System.out.println(tcs.dueAmount());
//
//		System.out.println(tcs.fulfillOrder());
//		System.out.println(tcs.fulfillOrder());
//		System.out.println(tcs.fulfillOrder());
//
//		// System.out.println(Arrays.toString(tcs.listOrders()));
//		System.out.println(tcs.dueAmount());
//
//		System.out.println(tcs.cheapestItem());
//		System.out.println(Arrays.toString(tcs.findByType("drink")));
//		System.out.println(Arrays.toString(tcs.findByType("food")));
//	}

}
