package dev.binekrasik.solvedgalaxy;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class first {

	public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(
            new InputStreamReader(System.in));
        int input = 0;
        try {
        	System.out.print("Zadej ËÌslo > ");
    		input = Integer.parseInt(reader.readLine());
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		System.out.println("»Ìslo: " + input);
		
		for (int i = 1; i < input + 1; i++) {
			if (jeDel(3, i) && jeDel(5, i)) {
				System.out.println(i + " - fizzbuzz");
			} else if (jeDel(3, i)) {
				System.out.println(i + " - fizz");
			} else if (jeDel(5, i)) {
				System.out.println(i + " - buzz");
			} else {
				System.out.println(i);
			}
		}
		
		System.out.println("⁄spÏönÏ dokonËeno.");
	}
	
	private static boolean jeDel(int delitel, int delenec) {
		if (delenec % delitel == 0) {
			return true;
		} else {
			return false;
		}
	}
}
