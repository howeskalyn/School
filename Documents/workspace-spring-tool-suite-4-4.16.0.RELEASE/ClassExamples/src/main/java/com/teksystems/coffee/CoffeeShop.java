package com.teksystems.coffee;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Comparator;

public class CoffeeShop {

	private String name = "Kalyn's Coffee Shop";

	// private String[] orders = new String[0];
	ArrayList<String> orders = new ArrayList<>();

	ArrayList<MenuItem> menu = new ArrayList<>(List.of(new MenuItem("orange juice", "drink", 2.13),
			new MenuItem("lemonade", "drink", 0.85), new MenuItem("cranberry juice", "drink", 3.36),
			new MenuItem("pineapple juice", "drink", 1.89), new MenuItem("lemon iced tea", "drink", 1.28),
			new MenuItem("apple iced tea", "drink", 1.28), new MenuItem("vanilla chai latte", "drink", 2.48),
			new MenuItem("hot chocolate", "drink", 0.99), new MenuItem("iced coffee", "drink", 1.12),
			new MenuItem("tuna sandwich", "food", 0.95), new MenuItem("ham and cheese sandwich", "food", 1.35),
			new MenuItem("bacon and egg", "food", 1.15), new MenuItem("steak", "food", 3.28),
			new MenuItem("hamburger", "food", 1.05), new MenuItem("cinnamon roll", "food", 1.05)));

//	MenuItem[] menu = { new MenuItem("orange juice", "drink", 2.13), new MenuItem("lemonade", "drink", 0.85),
//			new MenuItem("cranberry juice", "drink", 3.36), new MenuItem("pineapple juice", "drink", 1.89),
//			new MenuItem("lemon iced tea", "drink", 1.28), new MenuItem("apple iced tea", "drink", 1.28),
//			new MenuItem("vanilla chai latte", "drink", 2.48), new MenuItem("hot chocolate", "drink", 0.99),
//			new MenuItem("iced coffee", "drink", 1.12), new MenuItem("tuna sandwich", "food", 0.95),
//			new MenuItem("ham and cheese sandwich", "food", 1.35), new MenuItem("bacon and egg", "food", 1.15),
//			new MenuItem("steak", "food", 3.28), new MenuItem("hamburger", "food", 1.05),
//			new MenuItem("cinnamon roll", "food", 1.05) };

	public void addOrder(String name) {
		boolean found = false;
		for (MenuItem m : menu) {
			if (m.getItem().equals(name)) {
//				// make a copy of array & increase length by 1
//				orders = Arrays.copyOf(orders, orders.length + 1);
//				orders[orders.length - 1] = name;
				orders.add(name);
				System.out.println("Order added.");
				found = true;
			}
		}

		if (!found) {
			System.out.println("This item is currently unavailable!");
		}
	}

	/*
	 * for an array: public void removeOrder(String name) { boolean found = false;
	 * int indexRemove = 0; String[] removed = new String[orders.length - 1];
	 * 
	 * // look for item in order list & determine its index for (int i = 0; i <
	 * orders.length; i++) { if (orders[i].equals(name)) { // once item is found
	 * found = true; indexRemove = i; // store index } }
	 * 
	 * // if item was found if (found) { // add all elements to new array besides
	 * one we want to delete for (int i = 0, j = 0; i < orders.length; i++) { if (i
	 * != indexRemove) { removed[j] = orders[i]; j++; } }
	 * 
	 * orders = Arrays.copyOf(removed, removed.length); // place back into orders
	 * variable System.out.println(name + " has been removed from the order.");
	 * 
	 * } else { System.out.
	 * println("The item you want to remove was not found in your orders."); } }
	 */

	// for ArrayList
	public void removeOrder(String name) {
		if (orders.contains(name)) {
			orders.remove(name);
			System.out.println(name + " has been removed from the order.");

		} else {
			System.out.println("The item you want to remove was not found in your orders.");

		}
	}

	public String fulfillOrder() {
		// if (orders.length == 0) {
		if (orders.size() == 0) {
			return "All orders have been fulfilled!";
		} else {
			String currentOrder = orders.get(0); // orders[0];
			orders.remove(currentOrder);
			// orders = Arrays.copyOfRange(orders, 1, orders.length);
			return "The " + currentOrder + " is ready!";
		}
	}

	public void listOrders() {
		System.out.println("\n=== Your Order ===");
		if (orders.size() == 0) { // orders.length
			System.out.println("There are no items in your order.");
		} else {
			// System.out.println("Your order currently contains: " +
			// Arrays.toString(orders));
			printList(orders);
		}
	}

	public double dueAmount() {
		double total = 0.0;
		for (String itemName : orders) {
			for (MenuItem menuItem : menu) {
				if (menuItem.getItem().equals(itemName)) {
					total += menuItem.getPrice();
				}
			}
		}

		return total;
	}

	public String cheapestItem() {
		// if (menu.length == 0) {
		if (menu.size() == 0) {
			return null;
		} else {
			double cheapest = menu.get(0).getPrice(); // initialize to first menu item
			String cheapestName = menu.get(0).getItem();
//			double cheapest = menu[0].getPrice();
//			String cheapestName = menu[0].getItem();

			for (MenuItem m : menu) {
				if (m.getPrice() < cheapest) {
					cheapest = m.getPrice();
					cheapestName = m.getItem();
				}
			}
			return cheapestName;
		}
	}

	/*
	 * with arrays public String[] findByType(String typeOfItem) { String[] ret =
	 * new String[0];
	 * 
	 * for (MenuItem m : menu) { if (m.getType().equalsIgnoreCase(typeOfItem)) { ret
	 * = Arrays.copyOf(ret, ret.length + 1); ret[ret.length - 1] = m.getItem();
	 * 
	 * } }
	 * 
	 * return ret; }
	 */

	// with arraylist
	public ArrayList<String> findByType(String typeOfItem) {
		ArrayList<String> ret = new ArrayList<String>();

		for (MenuItem m : menu) {
			if (m.getType().equalsIgnoreCase(typeOfItem)) {
				ret.add(m.getItem());
			}
		}

		return ret;
	}

	public void listMenu(String listBy) {
		sortMenu(listBy);

		System.out.println("\n=== MENU ===");
		for (MenuItem m : menu) {
			m.printItem();
		}
	}

	// sort menu by either item, type, or price
	public void sortMenu(String sortBy) {
		// List<MenuItem> list = Arrays.asList(menu);

		if (sortBy.equalsIgnoreCase("item") || sortBy.equalsIgnoreCase("type") || sortBy.equalsIgnoreCase("price")) {
			Collections.sort(menu, new Comparator<MenuItem>() {
				@Override
				public int compare(MenuItem p1, MenuItem p2) {
					if (sortBy.equalsIgnoreCase("item")) {
						return p1.getItem().compareTo(p2.getItem());

					} else if (sortBy.equalsIgnoreCase("type")) {
						return p1.getType().compareTo(p2.getType());

					} else if (sortBy.equalsIgnoreCase("price")) {

						if (p1.getPrice() > p2.getPrice()) {
							return -1;
						} else if (p1.getPrice() < p2.getPrice()) {
							return 1;
						} else {
							return 0;
						}

					} else {
						return -1;
					}

				}
			});

		} else {
			System.out.println("Cannot sort menu by your input, printing menu normally...");
		}
	}

	public void printList(ArrayList<String> list) {
		for (int i = 0; i < list.size(); i++) {
			System.out.println(list.get(i) + " ");
		}
	}
	
}
