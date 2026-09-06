package pacotes;

public class Carta {
	public int populacao;
	public int pontosTuristicos;
	public float area;
	public float pib;

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
}
