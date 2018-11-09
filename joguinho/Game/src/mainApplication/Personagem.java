package mainApplication;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

/*
 * Classe abstrata para servir de base na criacao do jogador e dos inimigos
 */

abstract public class Personagem {
	
	/*
	 * Atributos fundamentais que cada personagem devera ter
	 * Adcionar demais atributos na classe herdeira
	 */
	
	// Atributos relativos a localizacao
	private int posX;
	private int posY;
	
	// Atributos relativos as dimensoes
	private int largura;
	private int altura;
	
	// Atributos para controle de movimento
	private int direcao;
	private int ultimaDirecao;
	private int velocidade;

	// Atributos relacionados a animacoes devem ser criados nas classes herdeiras
	//private BufferedImage[] correndo;
	//private BufferedImage[] parado;
	//private BufferedImage[] pulando;
	//private int imagemAtual;
	
	/* Constructor com varios atributos para facilitar o reuso desse trecho
	 * 
	 */
	
	public Personagem(int posX, int posY, int altura, int largura,int velocidade) {
		this.posX = posX;
		this.posY = posY;
		this.altura = altura;
		this.largura = largura;
		this.velocidade = velocidade;
		this.direcao = 0;
		
		/*
		 * Instanciacao das animacoes
		 */
		criarAnimacoes();
		
	}
	
	
	//metodos abstratos	
	// Atualizar movimentos e variaveis de controle
	abstract public void atualizar();
	
	/*
	 * Utilizar esse metodo para fazer o carregamento de todas as animacoes necessarias no personagem
	 * EX :
	 * 		correndo = carregarImagens("enderecoBonitinho", 10);
	 *		parado = carregarImagens("enderecoBonitinho", 10);
	 *		pulando = carregarImagens("enderecoBonitinho", 10);
	 */
	abstract public void criarAnimacoes();
	
	
	
	
	/* metodo para pintar animacao
	 * enviar component de pintura vindo do canvas, e a animacao a ser utilizada
	 * o indice da animacao nesse metodo eh fixo
	 * ver documentacao do metodo drawImage herdado de java.awt.Graphics e java.awt.Graphics2D
	 */
	public void pintar(Graphics2D g, BufferedImage[] animacao, int imagemAtual) {
		if(ultimaDirecao == 1){      
	        g.drawImage(
	             animacao[imagemAtual],
	             posX,posY,
	             posX + largura, posY + altura,
	             0, 0,
	             animacao[imagemAtual].getWidth(), animacao[imagemAtual].getHeight(),
	             null);
	    }else if(ultimaDirecao == -1){
	            g.drawImage(
	            	animacao[imagemAtual],
	                posX,posY,
	                posX + largura, posY + altura,
	                animacao[imagemAtual].getWidth(),0,
	                0, animacao[imagemAtual].getHeight(),
	            null);
	    }
	}
	
	
	
	/* metodo para carregar imagens em um vetor
	 * enviar endereco, e quantidade de imagens e o tipo de extensao sem o ponto (.)
	 * o endereco das imagens devem ser iguais e enumerados no final de 1 ao size
	 * 
	 */
	public BufferedImage[] carregarImagens(String endereco, int size,  String extensao) {
		BufferedImage[] imagem = new BufferedImage[size];
		
		for(int i = 1; i <= size; i++) {	
			try {
				imagem[i-1] = ImageIO.read(new File(endereco + i + "." + extensao));
			}catch(IOException e) {
				System.out.println("Metodo carregarImagens : nao carregou imagens "+ endereco+i+"." + extensao);
			}
			
		}
		return imagem;
		
	}
	
	/*
	 * atualizacao da movimentacao lateral
	 */
	public void anda(){
		if(direcao == 1) {
			posX += velocidade;
		}else if(direcao == -1){
			posX -= velocidade;
		}
	}
	
	
	/*
	 * metodos para alterar posicao caso necessario
	 */
	public void somarPosY(int soma){
		this.posY += soma;
		
	}
	public void somarPosX(int soma) {
		this.posX += soma;
		
	}
	
	/*
	 * Metodos de acesso
	 */
	public int getPosX() {
		return posX;
	}

	public void setPosX(int posX) {
		this.posX = posX;
	}

	public int getPosY() {
		return posY;
	}

	public void setPosY(int posY) {
		this.posY = posY;
	}

	public int getLargura() {
		return largura;
	}

	public void setLargura(int largura) {
		this.largura = largura;
	}

	public int getAltura() {
		return altura;
	}

	public void setAltura(int altura) {
		this.altura = altura;
	}

	public int getDirecao() {
		return direcao;
	}

	public void setDirecao(int direcao) {
		this.direcao = direcao;
	}

	public int getUltimaDirecao() {
		return ultimaDirecao;
	}

	public void setUltimaDirecao(int ultimaDirecao) {
		this.ultimaDirecao = ultimaDirecao;
	}

	public int getVelocidade() {
		return velocidade;
	}

	public void setVelocidade(int velocidade) {
		this.velocidade = velocidade;
	}
}
