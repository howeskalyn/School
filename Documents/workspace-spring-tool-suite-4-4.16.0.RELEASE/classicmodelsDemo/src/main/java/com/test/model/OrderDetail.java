package com.test.model;

//import java.util.Date;
import javax.persistence.*;

//import org.hibernate.annotations.NamedQuery;
//Using @NamedQuery for single HQL -> must use CLASS name here, not table name
//@NamedQuery(name = "getAllOrderDetails", query = "select o from OrderDetail o where orderNumber=:orderNumber")

import lombok.Getter;
import lombok.Setter;

@Entity
@Setter
@Getter
@Table(name = "orderdetails")
public class OrderDetail {

	// PRIMARY KEY
	@Column(name = "orderNumber")
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private Integer orderNumber;

	@Column(name = "productCode")
	private String productCode;

	@Column(name = "quantityOrdered")
	private Integer quantityOrdered;

	@Column(name = "priceEach", columnDefinition = "DECIMAL")
	private Integer priceEach;

	@Column(name = "orderLineNumber", columnDefinition = "SMALLINT")
	private Integer orderLineNumber;

	@Override
	public String toString() {
		return "OrderDetail [orderNumber=" + orderNumber + ", productCode=" + productCode + ", quantityOrdered="
				+ quantityOrdered + ", priceEach=" + priceEach + ", orderLineNumber=" + orderLineNumber + "]";
	}
}

// Constructors, getters and setters are not needed with Lombok usage.
//	public OrderDetail(Integer orderNumber, String productCode, Integer quantityOrdered, Integer priceEach,
//			Integer orderLineNumber) {
//
//		this.orderNumber = orderNumber;
//		this.productCode = productCode;
//		this.quantityOrdered = quantityOrdered;
//		this.priceEach = priceEach;
//		this.orderLineNumber = orderLineNumber;
//	}
//	
//	public OrderDetail() {
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
//	public String getProductCode() {
//		return productCode;
//	}
//
//	public void setProductCode(String productCode) {
//		this.productCode = productCode;
//	}
//
//	public Integer getQuantityOrdered() {
//		return quantityOrdered;
//	}
//
//	public void setQuantityOrdered(Integer quantityOrdered) {
//		this.quantityOrdered = quantityOrdered;
//	}
//
//	public Integer getPriceEach() {
//		return priceEach;
//	}
//
//	public void setPriceEach(Integer priceEach) {
//		this.priceEach = priceEach;
//	}
//
//	public Integer getOrderLineNumber() {
//		return orderLineNumber;
//	}
//
//	public void setOrderLineNumber(Integer orderLineNumber) {
//		this.orderLineNumber = orderLineNumber;
//	}
