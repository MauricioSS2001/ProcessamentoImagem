#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


int main() {
	
	// Variavel responssavel por armazenar o endereco da imagem.
	auto nomeArquivo = "C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\baboon.jpg";

	
	auto imagem = imread(nomeArquivo);	// Variavel para armazenar imagem original.
	Mat imagemCinza;					// Variavel para criar uma copia cinza da imagem original.


	int opcao = 0;

	cout << "\n=== Menu ===";
	cout << "\n1. Exibir a imagem";
	cout << "\n2. Escala de cinza";
	cout << "\n3. Propriedades";
	
	cout << "\nDigite sua opcao: ";
	cin >> opcao;

	switch (opcao) {
		case 1:
			imshow("Imagem", imagem);
			waitKey();
			break;
		case 2:
			cvtColor(imagem, imagemCinza, COLOR_BGR2GRAY);	// Copia a imagem original, torna cinza e salva na nova variavel.
			imshow("Imagem colorida", imagem);
			imshow("Imagem Cinza", imagemCinza);
			waitKey();
			break;
		case 3:
			cout << "\nLargura da imagem: " << imagem.cols;
			cout << "\nAltura da imagem: " << imagem.rows << "\n\n\n";
			imshow("Imagem", imagem);
			waitKey();
			break;
	}


	return 0;
}
