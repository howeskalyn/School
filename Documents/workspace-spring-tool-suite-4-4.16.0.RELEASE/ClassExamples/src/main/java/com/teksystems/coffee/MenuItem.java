package com.teksystems.coffee;

public class MenuItem {

	private String item;
	private String type;
	private double price;

	public MenuItem(String item, String type, double price) {
		this.item = item;
		this.type = type;
		this.price = price;
	}

	public String getItem() {
		return item;
	}

	public void setItem(String name) {
		this.item = name;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public double getPrice() {
		return price;
	}

	public void setPrice(double price) {
		this.price = price;
	}
	
	public void printItem() {
		System.out.println(item + " (" + type + ") : " + price);
	}
}
