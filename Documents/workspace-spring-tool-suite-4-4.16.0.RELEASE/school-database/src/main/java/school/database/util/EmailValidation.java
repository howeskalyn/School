package school.database.util;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class EmailValidation {

	// Requirements:
	// 1) not empty & not null
	// 2) has an @ in it
	// 3) has only letter or numbers before the @
	// 4) ends with a "." and 3 characters with no numbers
	// return true if all conditions pass & false otherwise (check negatives first)
	public boolean isValidEmail(String email) {

		String[] prefix = email.split("@");
		Pattern p = Pattern.compile("[^A-Za-z0-9]");
		Matcher m = p.matcher(prefix[0]);
		// if m.find is true, there is a special character & therefore the email is invalid
		
		// requirements 1, 2 & 3
		if (email.isEmpty() || email == null || !email.contains("@") || m.find()) {
			return false;
		}

		// get last 4 characters from the email
		String end = email.substring(email.length() - 4);
		
		if (end.charAt(0) != '.') {
			return false;
			
		// if end[1-3] are not numbers
		} else if (Character.isDigit(end.charAt(1)) || Character.isDigit(end.charAt(2)) 
				|| Character.isDigit(end.charAt(3))) { 
			return false;
		}
		
		return true;
	}
}
