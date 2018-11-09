package mainApplication;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class Canvas extends JPanel implements Runnable, KeyListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 6244965887359695579L;
	
	private int h,w;
	
	private BufferedImage[] cenario = new BufferedImage[3];
	
	
	
	//= new BufferedImage(null, null, false , null);
	//cenario = ImageIO.read(new File("asd"));
	
	//constructor
	public Canvas(int h, int w) {
		
		this.h = h;
		this.w = w;
		//carrega cenario
		for(int i = 0; i < 3;i++) {
			try {
				cenario[i] = ImageIO.read(new File("Data/Scenes/game"+ i + ".png"));
				 cenario[i] = resize(cenario[i],h, w);
			}catch(IOException e) {
				System.out.println("nao carregou background");
	            Logger.getLogger(Canvas.class.getName()).log(Level.SEVERE, null, e);
				
			}
			
		}
		
		Thread gameLoop = new Thread(this);
		gameLoop.start();
	
		
	}
	
	//instrucoes
	public void run() {
		while(true) {
			atualiza();
			repaint();
			dorme();	
		}	
	}
	
	//instrucao para atualizar componentes do jogo
	public void atualiza() {
		
	}
	//instrucao para gerar delay no thread
	public void dorme() {
		try {
			Thread.sleep(16);
		} catch(InterruptedException e) {
			Logger.getLogger(Canvas.class.getName()).log(Level.SEVERE, null, e);
		}
	}
	
	//pintura dos componentes(repaint)
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		Graphics2D g2d = (Graphics2D) g.create();
		
		//pinta o background
		//g2d.setColor(Color.black);
	    //g2d.fillRect(0,0,h,w);
		g2d.drawImage(cenario[1], null, 0,0 );
		g2d.drawImage(cenario[0], null, 0, 0);
		g2d.drawImage(cenario[2], null, 0, 0);
		
		
	}
	
	
	
	//implementacao de keyListener
	
	public void keyPressed(KeyEvent e) {
		
		//esquerda
		if(e.getKeyCode() == KeyEvent.VK_A) {
		//	jogador.acaoDirecao(-1);
		}
		
		//direita
		if(e.getKeyCode() == KeyEvent.VK_D) {
			//jogador.acaoDirecao(1);
		}
		
		//saltar
		if(e.getKeyCode() == KeyEvent.VK_W) {
			//jogador.saltar(true);
		}
		
		//atirar
		if(e.getKeyCode() == KeyEvent.VK_SPACE ) {
			//jogador.disparar(true);
		}
		
	}
	
	public void keyReleased(KeyEvent e) {
		
		if(e.getKeyCode() == KeyEvent.VK_A) {
			//jogador.acaoDirecao(0);
		}
		
		if(e.getKeyCode() == KeyEvent.VK_D) {
			//jogador.acaoDirecao(0);
		}
		
		if(e.getKeyCode() == KeyEvent.VK_W) {
			//jogador.realizarAcao('a');
		}
		
	}
	
	public void keyTyped(KeyEvent e) {
		
	}
	
	//estudar essa bagaca
	public static BufferedImage resize(BufferedImage img, int W, int H) { 
		
	    Image temp = img.getScaledInstance(W, H, Image.SCALE_SMOOTH);
	    BufferedImage novaImagem = new BufferedImage(W, H, BufferedImage.TYPE_INT_ARGB);

	    Graphics2D g2d = novaImagem.createGraphics();
	    g2d.drawImage(temp, 0, 0, null);
	    g2d.dispose();

	    return novaImagem;
	}  
}
