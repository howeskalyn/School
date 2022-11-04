package com.test.model;

import java.util.Date;
import javax.persistence.*;

import lombok.Getter;
import lombok.Setter;

@Entity
@Setter
@Getter
@Table(name = "orders")
public class Order {
	
	// PRIMARY KEY
	@Column(name = "orderNumber")
    @Id
    //@GeneratedValue(strategy = GenerationType.IDENTITY)
	private Integer orderNumber;
	
	// @Column represents the column name in the database and maps the database name to the java variable name
	@Column(name = "orderDate")
	private Date orderDate;
	
	@Column(name = "requiredDate")
	private Date requiredDate;
	
	@Column(name = "shippedDate")
	private Date shippedDate;
	
	@Column(name = "status")
	private String status;
	
	@Column(name = "comments", columnDefinition = "TEXT")
	private String comments;
	
	@Column(name = "customerNumber")
	private Integer customerNumber;

	@Override
	public String toString() {
		return "Order [orderNumber=" + orderNumber + ", orderDate=" + orderDate + ", requiredDate=" + requiredDate
				+ ", shippedDate=" + shippedDate + ", status=" + status + ", comments=" + comments + ", customerNumber="
				+ customerNumber + "]";
	}
}

	
// Constructors, getters and setters are not needed with Lombok usage.
//	public Order(Integer orderNumber, Date orderDate, Date requiredDate, Date shippedDate, String status,
//			String comments, Integer customerNumber) {
//		
//		this.orderNumber = orderNumber;
//		this.orderDate = orderDate;
//		this.requiredDate = requiredDate;
//		this.shippedDate = shippedDate;
//		this.status = status;
//		this.comments = comments;
//		this.customerNumber = customerNumber;
//	}
//	
//	public Order() {
//		
//	}
//
//	public Integer getOrderNumber() {
//		return orderNumber;
//	}
//
//	public void setOrderNumber(Integer orderNumber) {
//		this.orderNumber = orderNumber;
//	}
//
//	public Date getOrderDate() {
//		return orderDate;
//	}
//
//	public void setOrderDate(Date orderDate) {
//		this.orderDate = orderDate;
//	}
//
//	public Date getRequiredDate() {
//		return requiredDate;
//	}
//
//	public void setRequiredDate(Date requiredDate) {
//		this.requiredDate = requiredDate;
//	}
//
//	public Date getShippedDate() {
//		return shippedDate;
//	}
//
//	public void setShippedDate(Date shippedDate) {
//		this.shippedDate = shippedDate;
//	}
//
//	public String getStatus() {
//		return status;
//	}
//
//	public void setStatus(String status) {
//		this.status = status;
//	}
//
//	public String getComments() {
//		return comments;
//	}
//
//	public void setComments(String comments) {
//		this.comments = comments;
//	}
//
//	public Integer getCustomerNumber() {
//		return customerNumber;
//	}
//
//	public void setCustomerNumber(Integer customerNumber) {
//		this.customerNumber = customerNumber;
//	}
	
	
