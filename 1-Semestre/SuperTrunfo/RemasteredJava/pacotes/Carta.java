package pacotes;
import java.util.Scanner;

public class Carta {
	public int populacao;
	public int pontosTuristicos;
	// Essas variaveis não funcina direito quando cadastra
	public double area;
	public double pib;

	public Carta(int populacaoInit, int pontosTuristicosInit, float areaInit, float pibInit){
		populacao = populacaoInit;
		pontosTuristicos = pontosTuristicosInit;
		area = areaInit;
		pib = pibInit;
	} 

	public Carta() {
		populacao = 0;
		pontosTuristicos = 0;
		area = 0;
		pib = 0;
	}

	public void cadastroCarta(){
		Scanner entrada = new Scanner(System.in);
		
		System.out.printf("// Cadastro De Cartas //\nPopulação: ");
		populacao = entrada.nextInt();

		System.out.printf("Pontos Turisticos: ");
		pontosTuristicos = entrada.nextInt();

		System.out.printf("Pontos Aréa: ");
		area = entrada.nextDouble();

		System.out.printf("Pontos PIB: ");
		pib = entrada.nextDouble();			
	}
}
