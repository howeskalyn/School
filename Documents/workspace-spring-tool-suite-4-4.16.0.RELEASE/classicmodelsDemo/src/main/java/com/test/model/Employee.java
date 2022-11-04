package com.test.model;

import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.persistence.Table;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Entity
@Setter
@Getter
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "employees")
public class Employee {

	// PRIMARY KEY
	@Column(name = "id")
    @Id
    //@GeneratedValue(strategy = GenerationType.IDENTITY)
	private Integer employeeNumber;
	
	@Column(name = "lastName")
	private String lastName;
	
	@Column(name = "firstName")
	private String firstName;
	
	@Column(name = "extension")
	private String extension;
	
	@Column(name = "officeCode")
	private String officeCode;
	
	// map by the name of the actual Java variable we are linking too
	@OneToMany(mappedBy = "salesRep", fetch = FetchType.EAGER, 
			cascade = CascadeType.ALL)
	private List<Customer> customers;
	

}
