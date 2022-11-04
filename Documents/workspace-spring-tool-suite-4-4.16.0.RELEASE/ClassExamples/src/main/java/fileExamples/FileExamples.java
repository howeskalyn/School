package fileExamples;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class FileExamples {

	public static void main(String[] args) throws IOException {

		// ./ current file directory
		// ../ parent directory
		System.out.println("Operating system slash is " + File.separator);

//		File macRoot = new File("/");
//		File windowsRoot = new File("\\");
//
//		for (File f : macRoot.listFiles()) {
//			System.out.println(f.getAbsolutePath() + " is directory? " + f.isDirectory());
//		}
//
//		System.out.println("=======================");
//		File desktop = new File("/Users/kalynhowes/Desktop/TEKSystems_Training/SampleFiles/test.txt");
//		System.out.println(desktop.getName() + " file exists? " + desktop.exists());
//		System.out.println(desktop.getAbsolutePath() + " file exists? " + desktop.exists());
//
//		// Slide 14 Example:
//		System.out.println("=======================");
//		String path = "/Users/kalynhowes/Desktop/TEKSystems_Training/SampleFiles/testingFile.txt";
//		File f1 = new File(path);
//		System.out.println("File Name: " + f1.getName());
//		System.out.println("File Path: " + f1.getPath());
//		System.out.println("Is path absolute: " + f1.isAbsolute());
//		System.out.println("Return Absolute path of the File " + f1.getAbsolutePath());
//		System.out.println("Return Parent folder of the given File " + f1.getParent());
//		System.out.println("File is Exist " + f1.exists());
//		System.out.println(f1.exists() ? "Yes file exists" : "file does not exist");
//		if (f1.exists()) { // return true or False
//			System.out.println("File is Found");
//			System.out.println("IS file Readable " + f1.canRead());
//			System.out.println("IS file Writeable " + f1.canWrite());
//			System.out.println("File size in a bytes " + f1.length()); // file size in byte
//		}
//
//		// Slide 15 Example:
//		System.out.println("=======================");
//		try {
//			File f = new File("/Users/kalynhowes/Desktop/TEKSystems_Training/SampleFiles/Datafile.txt");
//			if (f.createNewFile()) {
//				System.out.println("New File created!");
//			} else {
//				System.out.println("The file already exists.");
//			}
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//
//		// Slide 18 Example:
//		System.out.println("=======================");
//		try {
//			File f = new File("/Users/kalynhowes/Desktop/TEKSystems_Training/SampleFiles/Datafile.txt");
//			Scanner sc = new Scanner(f);
//			String data = "";
//			while (sc.hasNextLine()) {
//				data = sc.nextLine();
//				System.out.println(data);
//			}
//		} catch (FileNotFoundException e) {
//			System.out.println("Either file is not found or file is not able to access");
//			System.out.println(e.getStackTrace());
//			e.printStackTrace();
//		}

		// Slide 41 Example
		FileReader in = null;
		FileWriter out = null;
		try {
			// change below file path as per your file path
			in = new FileReader("/Users/kalynhowes/Desktop/TEKSystems_Training/SampleFiles/Datafile.txt");
			out = new FileWriter("/Users/kalynhowes/Desktop/TEKSystems_Training/SampleFiles/sampleOutput3.txt");
			int c;
			while ((c = in.read()) != -1) {
				out.write(c); // writing data in file
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
