package mainApplication;
import javax.swing.JFrame;

public class Janela {

	private final static int altura = 640;
	private final static int largura = 1280;
	
	public static void main(String[] args) {

		//definindo Jframe que usaremos
		JFrame janela = new JFrame("Nome do Jogo");
		janela.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		janela.setSize(largura, altura);
		janela.setResizable(false);
		
		//instanciando jogo
		Canvas jogo = new Canvas(largura,altura);
		//adicionando o jogo component e seu keyListener ao JFrame criado
		janela.add(jogo);
		janela.addKeyListener(jogo);
		janela.setVisible(true);
	}
}
