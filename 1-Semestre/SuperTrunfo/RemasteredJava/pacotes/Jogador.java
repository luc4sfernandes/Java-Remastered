package pacotes; 

public class Jogador {
	public String nome;
	private Carta carta;

	public Jogador(String nomeInit, int populacaoInit, int pontosTuristicosInit, float areaInit, float pibInit) {
		nome = nomeInit;
		this.carta = new Carta(populacaoInit, pontosTuristicosInit, areaInit, pibInit); // Inicializa um objeto dentro de uma classe
	}	

	public void info(){
		System.out.printf("Nome: %s\nPopulação: %d\nPontos Turisticos: %d\nArea: %.2f\nPib %.2f\n",
		nome, carta.populacao, carta.pontosTuristicos, carta.area, carta.pib);
	}

	// Definir metodos para cadastro das cartas
}
