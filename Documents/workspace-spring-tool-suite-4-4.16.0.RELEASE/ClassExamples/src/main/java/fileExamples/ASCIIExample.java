package fileExamples;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class ASCIIExample {

	public static void main(String[] args) throws IOException {
		
		FileReader in = null;
		FileWriter out = null;
		try {
			// change below file path as per your file path
			in = new FileReader("/Users/kalynhowes/Desktop/TEKSystems_Training/SampleFiles/file1.txt");
			out = new FileWriter("/Users/kalynhowes/Desktop/TEKSystems_Training/SampleFiles/ASCIIOutput.txt");
			int c;
			while ((c = in.read()) != -1) {
//				System.out.println(c);
				
				// ASCII: A-Z 65-90, space = 32, a-z 97-122
				if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 32) {
					out.write(c); // writing data in file
				}
			}
			System.out.println("Reading and Writing in a file is done!!!");
		} catch (Exception e) {
			System.out.println(e);
		} finally {
			if (in != null) {
				in.close();
			}
			if (out != null) {
				out.close();
			}
		}

	}

}
