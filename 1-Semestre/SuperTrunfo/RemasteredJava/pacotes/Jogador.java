package pacotes;
import java.util.Scanner; 

public class Jogador {
	public String nome;
	public Carta carta;

	public Jogador(String nomeInit, int populacaoInit, int pontosTuristicosInit, float areaInit, float pibInit) {
		nome = nomeInit;
		this.carta = new Carta(populacaoInit, pontosTuristicosInit, areaInit, pibInit); // Inicializa um objeto dentro de uma classe
	}	

	public Jogador(){
		nome = "Desconhecido"; 
		this.carta = new Carta();
	}

	public void info(){
		System.out.printf("\n// Info //\nNome: %s\nPopulação: %d\nPontos Turisticos: %d\nArea: %.2f\nPib %.2f\n",
		nome, carta.populacao, carta.pontosTuristicos, carta.area, carta.pib);
	}

	// Preciso por cadastro do nome jogador, que e 'Desconhecido'

}
