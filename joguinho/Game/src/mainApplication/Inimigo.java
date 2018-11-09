package mainApplication;

import java.awt.image.BufferedImage;

public class Inimigo extends Personagem {
	
	/*
	 * Animacoes utilizadas pelo jogador
	 */
	BufferedImage[] correndo;
	BufferedImage[] parado;
	BufferedImage[] soco;
	
	
	public Inimigo(int posX, int posY, int altura, int largura,int velocidade) {
		super(posX, posY, altura, largura, velocidade);
		
	}
	
	public void criarAnimacoes() {
		System.out.println("animacao do inimigo");
	/*	
		correndo = carregarImagens("endereco top", 5);
		parado = carregarImagens("endereco top", 5);
		soco = carregarImagens("endereco top", 5);
		*/
		
	}
	
	
	public void atualizar() {
		
		
	}
	
}
