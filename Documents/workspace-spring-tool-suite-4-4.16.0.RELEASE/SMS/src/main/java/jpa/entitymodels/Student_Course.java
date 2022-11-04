package jpa.entitymodels;

import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.persistence.Table;

import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@Table(name = "Student_Course")
public class Student_Course {
	
	@Id
	@Column(name = "id")
	private Integer id;
	
	@Column(name = "studentId")
	private String studentId;
	
	@Column(name = "courseId")
	private Integer courseId;
	
	// a single row of student_course can only have 1 course and 1 student	
//	@OneToMany(mappedBy = "studentCourses", fetch = FetchType.EAGER, cascade = CascadeType.ALL)
//	@EqualsAndHashCode.Exclude
//	@ToString.Exclude
//	private List<Student> students;

//	@OneToMany(mappedBy = "studentCourses", fetch = FetchType.EAGER, cascade = CascadeType.ALL)
//	@EqualsAndHashCode.Exclude
//	@ToString.Exclude
//	private List<Course> courses;

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((courseId == null) ? 0 : courseId.hashCode());
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		result = prime * result + ((studentId == null) ? 0 : studentId.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Student_Course other = (Student_Course) obj;
		if (courseId == null) {
			if (other.courseId != null)
				return false;
		} else if (!courseId.equals(other.courseId))
			return false;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		if (studentId == null) {
			if (other.studentId != null)
				return false;
		} else if (!studentId.equals(other.studentId))
			return false;
		return true;
	}

	
	
}
