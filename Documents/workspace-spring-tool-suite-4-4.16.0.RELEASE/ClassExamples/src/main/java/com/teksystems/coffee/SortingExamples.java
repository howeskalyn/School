package com.teksystems.coffee;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class SortingExamples {

	private MenuItem[] menu = new MenuItem[] { new MenuItem("orange juice", "drink", 2.13),
			new MenuItem("lemonade", "drink", 0.85), new MenuItem("cranberry juice", "drink", 3.36),
			new MenuItem("lemonade", "drink", 0.65), new MenuItem("cranberry juice", "drink", 3.36),
			new MenuItem("pineapple juice", "drink", 1.89), new MenuItem("lemon iced tea", "drink", 1.28),
			new MenuItem("apple iced tea", "drink", 1.28), new MenuItem("vanilla chai latte", "drink", 2.48),
			new MenuItem("hot chocolate", "drink", 0.99), new MenuItem("iced coffee", "drink", 1.12),
			new MenuItem("tuna sandwich", "food", 0.95), new MenuItem("ham and cheese sandwich", "food", 1.35),
			new MenuItem("bacon and egg", "food", 1.15), new MenuItem("steak", "food", 3.28),
			new MenuItem("hamburger", "food", 1.05), new MenuItem("cinnamon roll", "food", 1.05),
			new MenuItem(null, "food", 1.05) };

	public static void main(String[] args) {
		SortingExamples se = new SortingExamples();
		//se.start();
		se.startEric();
	}

	public void start() {
		// first we convert the array to a list
		List<MenuItem> list = Arrays.asList(menu);
		System.out.println("Original Menu");
		print(list);

		// do these using collections sort or list sort or by stream

		// TODO - sort the list by name in descending order (z to a)
		Collections.sort(list, new Comparator<MenuItem>() {
			@Override
			public int compare(MenuItem p1, MenuItem p2) {
				if (p1.getItem() == null || p2.getItem() == null) {
					return -1;
				} else {
					return p2.getItem().compareTo(p1.getItem());
				}
				//return Comparator.nullsFirst(MenuItem::compareTo).compare(p1.getItem(), p2.getItem());
			}
		});
		System.out.println("\nMenu sorted Z-A, nulls first.");
		print(list);

		// TODO - sort the list by name in ascending order with nulls last
		Collections.sort(list, new Comparator<MenuItem>() {
			@Override
			public int compare(MenuItem p1, MenuItem p2) {
				if (p1.getItem() == null || p2.getItem() == null) {
					return -1;
				} else {
					return p2.getItem().compareTo(p1.getItem());
				}
			}
		});
		System.out.println("\nMenu sorted Z-A, nulls last.");
		print(list);
		
		
		// TODO - sort the list by name in ascending order with nulls first
		Collections.sort(list, new Comparator<MenuItem>() {
			@Override
			public int compare(MenuItem p1, MenuItem p2) {
				if (p1.getItem() == null || p2.getItem() == null) {
					return -1;
				} else {
					return p1.getItem().compareTo(p2.getItem());
				}
			}
		});
		System.out.println("\nMenu sorted A-Z, nulls first.");
		print(list);

		// TODO - filter the list and remove all food items - will produce a list of
		// drinks in alphabetical order
		ArrayList<MenuItem> drinks = new ArrayList<MenuItem>();

		for (MenuItem m : menu) {
			if (m.getType() == "drink") {
				drinks.add(m);
			}
		}
		System.out.println("\nDrinks only!");
		print(drinks);

	}
	
	// google: "array java filter" "list on object property"
	public void startEric() {
		//List<MenuItem> list = Arrays.asList(menu);
		List<MenuItem> list = new ArrayList<>();
		list.addAll(Arrays.asList(menu));
		System.out.println("Original Menu");
		print(list);
		
		// TODO - sort the list by name in descending order (z to a)
		Collections.sort(list, Comparator.comparing(MenuItem::getItem, Comparator.nullsLast(Comparator.naturalOrder())).reversed());
		System.out.println("\nZ-A nulls last");
		print(list);
		
		// TODO - sort the list by name in ascending order with nulls last
		Collections.sort(list, Comparator.comparing(MenuItem::getItem, Comparator.nullsLast(Comparator.naturalOrder())));
		System.out.println("\nA-Z nulls last");
		print(list);
		
		// TODO - sort the list by name in ascending order with nulls first
		Collections.sort(list, Comparator.comparing(MenuItem::getItem, Comparator.nullsFirst(Comparator.naturalOrder())));
		System.out.println("\nA-Z nulls first");
		print(list);
		
		// TODO - filter the list and remove all food items - will produce a list of
		// drinks in alphabetical order
		//list = list.stream().filter(p -> p.getType().equals("drink")).collect(Collectors.toList());
		list.removeIf(p -> p.getType().equals("food"));
		System.out.println("\nDrinks only!");
		print(list);
		
	}

	private void print(List<MenuItem> list) {
		System.out.println("=== MENU ===");
		for (MenuItem m : list) {
			m.printItem();
		}
	}
}
