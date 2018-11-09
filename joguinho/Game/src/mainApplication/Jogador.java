package mainApplication;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

public class Jogador extends Personagem{

	/*
	 * Animacoes utilizadas pelo jogador
	 */
	BufferedImage[] correndo;
	BufferedImage[] parado;
	BufferedImage[] pulo;
	BufferedImage[] soco;
	private int imagemAtual;
	private int imagemAtualSoco;
	
	private int timer;
	private int velocidadeDasAnimacoes;
	private int quantidadeDeFrames;
	private int quantidadeDeFramesSoco;
	private int tempoDoSoco;
	
	/*
	 * Variaveis de controle
	 */
	private boolean atacando;
	private boolean pulando;
	private int quantidadeDeSaltos;
	private int tamanhoDeUmSalto;
	private int pulandoCima;
	private int pulandoBaixo;
	
	public Jogador(int posX, int posY, int altura, int largura,int velocidade) {
		super(posX, posY, altura, largura, velocidade);
		//variaveis que necessitam inicializacao
		this.pulando = false;
		this.atacando = false;
		pulandoCima = 0;
		pulandoBaixo = 0;
		timer = 0;
		imagemAtual = 0;
		imagemAtualSoco = 0;
		tempoDoSoco = 5;
		
		//velocidadeDasAnimacoes; quanto menor mais rapido
		velocidadeDasAnimacoes= 12;
		//quantidadeDeFrames deve ser igual ao tamanho das animacoes usado no criar imagens - 1
		quantidadeDeFrames = 5;
		//quantidadeDeFramesSoco deve ser igual a quantidade de frames que ele possui
		quantidadeDeFramesSoco = 3;
		//quantidadeDeSaltos deve ser maior do que o tamanho das animacoes
		// lim x --> variavel  =  quantidadeDeSaltos x tamanhoDeUmSalto = altura do salto
		//transformar um dos valores como constante e a outra variavel
		quantidadeDeSaltos = 15;
		tamanhoDeUmSalto = 8;
	}
	
	/*
	 * carrega animacoes a serem utilizadas
	 */
	public void criarAnimacoes() {
		correndo = carregarImagens("Data/Sprites/Run/adventurer-run-0", 6, "png");
		parado = carregarImagens("Data/Sprites/Idle/adventurer-idle-0", 6, "png");
		pulo = carregarImagens("Data/Sprites/Jump/adventurer-jump-0", 6, "png");
		soco = carregarImagens("Data/Sprites/Punch/adventurer-attack1-0", 3,"png");
		
		
	}
	
	//controle de posicoes e de frames
	public void atualizar() {
		/*
		 * ataca() = atualiza a imagemAtual de atacar e realiza ataque
		 * atualizarContadorDeImagem() = atualiza imagemAtual na quantidade de frames padrao definida pela gente
		 * anda() = atualiza a locomocao no eixo X do personagem
		 * pula() = realiza salto e atualiza imagemAtual de acordo com o salto
		 */
		if(pulando == false) {
			if(atacando == true) {
				ataca();
			}else{
				atualizarContadorDeImagem();	
				anda();
			}
		}else {
			if(atacando == true) {
				ataca();
				pula();
				anda();
			}else {
				pula();
				anda();
			}
			
		}
	}
	
	/*
	 * o tratamento quanto a direcao é feito na classe personagem
	 * nesse metodo so eh definido qual animacao sera pintar
	 */
	public void pintarJogador(Graphics2D g) {
		//se pulando
		if(pulando == true) {
			if(atacando == false) {
				pintar(g, pulo, imagemAtual);
			}else {
				/*
				 * alguma animacao dele batendo no ar
				 * enviar imagemAtualSoco
				 */
			}
				
		}else if(atacando == false){
			if(getDirecao() == 1) {
				pintar(g, correndo, imagemAtual);
			}else if (getDirecao() == -1) {
				pintar(g, correndo, imagemAtual);
			}else {
				pintar(g, parado, imagemAtual);
			}
		}else {
			pintar(g,soco,imagemAtualSoco);
		}
		
	}
	
	
	/*
	 * define a direcao de observacao
	 */
	public void andar(int direcao) {
		
		if(direcao != 0) {
			setDirecao(direcao);
			setUltimaDirecao(direcao);
		}else {
			setDirecao(direcao);
		}
	}
	
	/*
	 * inicia o pulo
	 */
	public void pular() {
		this.imagemAtual = 0;
		this.pulando = true;
	}
	
	/*
	 * atualizacao do posicao do personagem durante o pulo e das imagens utilizadas
	 */
	public void pula() {
		if(pulandoCima < quantidadeDeSaltos) {
			//atualiza imagem
			if(pulandoCima/2 == 0) {
				imagemAtual++;
			}
			pulandoCima++;
			somarPosY(-tamanhoDeUmSalto);
		}else if(pulandoBaixo < quantidadeDeSaltos ){
			//atualiza imagem
			if(pulandoBaixo/2 == 0) {
				imagemAtual++;
			}
			pulandoBaixo++;
			somarPosY(tamanhoDeUmSalto);
		}else {
			pulando = false;
			imagemAtual = 0;
			pulandoCima = 0;
			pulandoBaixo = 0;
		}				
	}
	//atualiza imagemAtual com base em um timer
	public void atualizarContadorDeImagem() {
		timer++;
		if(timer >= velocidadeDasAnimacoes){
			imagemAtual++;
			if(imagemAtual == quantidadeDeFrames){
				imagemAtual = 0;
			}
			timer = 0;
		}
	}

	//inicia o ataque
	public void atacar() {
		if(!atacando) {
			this.atacando = true;
			this.imagemAtualSoco = 0;
			timer = 0;
		}
		
	}
	
	/*
	 * implementar aq algum tipo de verificacao de colisao para saber se o ataque atingiu algum inimigo
	 * cria um contador menor para a animacao do soco
	 * e verifica se tem inimigos na regiao prox
	 */
	public void ataca() {

		if(timer >= tempoDoSoco) {
			imagemAtualSoco++;
			//verifica se tem inimigo
			if(imagemAtualSoco == quantidadeDeFramesSoco) {
				imagemAtualSoco = 0;
				atacando = false;
			}
			timer = 0;
		}
		timer++;
	}
	
	/*
	 * Metodos de acesso
	 */
	public int getImagemAtual() {
		return imagemAtual;
	}

	public void setImagemAtual(int imagemAtual) {
		this.imagemAtual = imagemAtual;
	}

	public int getQuantidadeDeFrames() {
		return quantidadeDeFrames;
	}

	public void setQuantidadeDeFrames(int quantidadeDeFrames) {
		this.quantidadeDeFrames = quantidadeDeFrames;
	}

	public boolean isPulando() {
		return pulando;
	}

	public void setPulando(boolean pulando) {
		this.pulando = pulando;
	}

	public int getQuantidadeDeSaltos() {
		return quantidadeDeSaltos;
	}

	public void setQuantidadeDeSaltos(int quantidadeDeSaltos) {
		this.quantidadeDeSaltos = quantidadeDeSaltos;
	}

	public int getTamanhoDeUmSalto() {
		return tamanhoDeUmSalto;
	}

	public void setTamanhoDeUmSalto(int tamanhoDeUmSalto) {
		this.tamanhoDeUmSalto = tamanhoDeUmSalto;
	}

	public int getPulandoCima() {
		return pulandoCima;
	}

	public void setPulandoCima(int pulandoCima) {
		this.pulandoCima = pulandoCima;
	}

	public int getPulandoBaixo() {
		return pulandoBaixo;
	}

	public void setPulandoBaixo(int pulandoBaixo) {
		this.pulandoBaixo = pulandoBaixo;
	}
	
	
	
}
