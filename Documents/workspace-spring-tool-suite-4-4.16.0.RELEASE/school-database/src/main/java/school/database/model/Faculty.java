package school.database.model;

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
@Table(name = "faculty")
public class Faculty {

	// PRIMARY KEY
	@Id
	@Column(name = "id")
	// @GeneratedValue(strategy = GenerationType.IDENTITY)
	private Integer id;

	@Column(name = "firstname")
	private String firstname;

	@Column(name = "lastname")
	private String lastname;

	@Column(name = "deptId", insertable = false, updatable = false)
	private Integer deptId;

	@ManyToOne(fetch = FetchType.EAGER, optional = false)
	@JoinColumn(name = "deptId", nullable = false)
	private Department department;

}

