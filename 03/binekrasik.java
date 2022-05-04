package dev.binekrasik.solvedgalaxy;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class third {

	public static void main(String[] args) {
		System.out.println(isHexColor("#54b5c66")); //false
		
		System.out.println("- - - -\n" + isHexColor("#54b5c6")); //true
	}
	
	public static boolean isHexColor(String hexStr) {
		String regex = "^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$";
        Pattern pattern = Pattern.compile(regex);
        if (hexStr == null) {
        	return false;
        }
        Matcher m = pattern.matcher(hexStr);
        return m.matches();
	}

}
