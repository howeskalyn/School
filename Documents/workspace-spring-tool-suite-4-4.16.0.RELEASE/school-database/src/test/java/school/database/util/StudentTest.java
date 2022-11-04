package school.database.util;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import school.database.model.Student;

class StudentTest {

	@Test
	public void testStudent() {
		Student a = new Student();
		a.setId(1);
		a.setFirstname("Mike");
		a.setLastname("Gabriel");
		a.setStreet("Grove");
		a.setMajorId(2);
		
		Student b = new Student();
		b.setId(1);
		b.setFirstname("Mike");
		b.setLastname("Gabriel");
		b.setStreet("Grove");
		b.setMajorId(2);
		
		assertEquals(a, b);
	}


}
