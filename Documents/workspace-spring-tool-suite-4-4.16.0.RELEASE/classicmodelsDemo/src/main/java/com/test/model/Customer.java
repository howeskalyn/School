package com.test.model;

import javax.persistence.Column;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@Table(name = "customers")
public class Customer {

	// PRIMARY KEY
	@Column(name = "id")
	@Id
	// @GeneratedValue(strategy = GenerationType.IDENTITY)
	private Integer id;

	@Column(name = "customerName")
	private String name;

	@Column(name = "contactLastName")
	private String lastName;

	@Column(name = "contactFirstName")
	private String firstName;

	// database issue
	// @Column(name = "salesRepEmployeeNumber", insert="false" update="false")
	// private Integer salesRepId;
	// practicing using differing variable names from the table columns

	@ManyToOne(fetch = FetchType.EAGER, optional = false)
	// this is the column name in the table we are going to reference
	// the employee table primary key -> employeeNumber/id
	@JoinColumn(name = "salesRepEmployeeNumber", nullable = false)
	private Employee salesRep;

}
