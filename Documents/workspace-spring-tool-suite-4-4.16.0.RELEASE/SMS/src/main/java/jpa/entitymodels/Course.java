package jpa.entitymodels;

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
@Table(name = "Course")
public class Course {
	
	@Id
	@Column(name = "id")
	private Integer cId;
	
	@Column(name = "name")
	private String cName;
	
	@Column(name = "instructor")
	private String cInstructorName;
	
	// a single course can have many student courses
//	@ManyToOne(fetch = FetchType.EAGER, optional = false)
//	@JoinColumn(name = "cId", nullable = false)
//	private Student_Course studentCourses;
	

}