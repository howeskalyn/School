package school.database.util;

import static org.junit.Assert.assertEquals;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import school.database.controller.CourseDAO;
import school.database.model.Course;

class CourseTest {

	@ParameterizedTest
	@CsvSource({ "1,Accounting & Finance,2", "4,American Studies,3" })
	public void csvTest(Integer id, String name, Integer deptId) {

		Course expected = new Course();
		Course actual = new Course();
		CourseDAO dao = new CourseDAO();

		expected.setId(id);
		expected.setName(name);
		expected.setDeptId(deptId);

		actual = dao.findById(id);

		assertEquals(expected, actual);

	}

}
