package testingDemos;

import java.util.ArrayList;
import java.util.Arrays;

// From Introduction to JUnit slides - 25
public class TestThis {
	
    ArrayList<String> names = new ArrayList<String>(Arrays.asList(
            new String[]{"Mike", "Bairon", "Tony"}
    ));

    public String getNameAtIndex(int index){
        return names.get(index);
    }

    public void addName(String name){
        names.add(name);
    }

    public ArrayList<String> getNames(){
        return names;
    }
}