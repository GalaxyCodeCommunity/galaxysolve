package dev.binekrasik.solvedgalaxy;

public class second {
	public static void main(String[] args) {
		String[] pole = new String[] {
				"1",
				"2",
				"3",
				"4"
		};
		
		Object[] obracenePole = obratit(pole);
		System.out.println("> Originální Pole:");
		for (int i = 0; i < pole.length; i++) {
			System.out.println(pole[i]);
		}
		System.out.println("- - - - - -\n> Obrácené Pole:");
		for (int i = 0; i < obracenePole.length; i++) {
			System.out.println(obracenePole[i]);
		}
	}
	
	public static Object[] obratit(Object[] pole) {
		Object[] invPole = new Object[pole.length];
		for (int i = pole.length; i > 0; i--) {
			invPole[pole.length - i] = pole[i - 1];
		}
		
		return invPole;
	}
}
