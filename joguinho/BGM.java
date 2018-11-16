package mainApplication;

import jplay.Sound;

public class BGM {
	
	private static Sound musica;
	
	public static void play (String audio) {
		stop();
		musica = new Sound(audio);
		BGM.musica.play();
		BGM.musica.setRepeat(true);
	}
	
	public static void stop () {
		if(BGM.musica != null) {
			musica.stop();
		}
	}
}
