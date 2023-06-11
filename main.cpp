#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void pixels(Mat imagem, Mat imagemCinza) {
	cvtColor(imagem, imagemCinza, COLOR_BGR2GRAY); // Copia a imagem original, torna cinza e salva na nova variavel.
	int pixel;	// Variavel para armazenar o pixel atual da matriz.
	int minimo = 0;	// Variavel para contar quantidade de cinza minimo.
	int maximo = 0;	// Variavel para contar quantidade de cinza maximo.
	int vetor[256];	// Cada posicao do vetor e referente a um tom de cinza de 0 a 255.
	int contador = 0;	// Contador do loop.
	for (contador; contador < 256; contador++) {
		vetor[contador] = 0;	// Armazena 1 para cada nivel do cinza com base no pixel atual.
	}

	for (int i = 0; i < imagemCinza.rows; i++) {
		for (int j = 0; j < imagemCinza.cols; j++) {
			pixel = (int)imagemCinza.at<uchar>(i, j);
			vetor[pixel] += 1;
		}
	}
	cout << "\nMinimo (Preto): " << vetor[0];
	cout << "\nMaximo (Branco): " << vetor[255];
	cout << "\n\n";

	float atual = 0;
	float contadorporcentagem = 0.0;
	int contadorimpressao = 0;
	for (contadorimpressao; contadorimpressao < 256; contadorimpressao++) {
		atual = float(vetor[contadorimpressao]) / float(imagemCinza.rows * imagemCinza.cols);
		cout << "\nGrau de " << contadorimpressao << ": " << atual;
		contadorporcentagem += atual;
	}
	cout << "\nContagem: " << contadorporcentagem * 100;
	imshow("Imagem Cinza", imagemCinza);
	waitKey();
}

void criarHistograma(Mat imagem) {
	Mat imagemCinza;
	cvtColor(imagem, imagemCinza, COLOR_BGR2GRAY);

	int histograma[256] = { 0 }; // Inicializa o histograma com zeros para cada nível de cinza

	for (int i = 0; i < imagemCinza.rows; i++) {
		for (int j = 0; j < imagemCinza.cols; j++) {
			int pixel = (int)imagemCinza.at<uchar>(i, j);
			histograma[pixel]++; // Incrementa a contagem para o nível de cinza atual
		}
	}

	// Encontra o valor máximo do histograma para dimensionar o gráfico
	int maxCount = 0;
	for (int i = 0; i < 256; i++) {
		if (histograma[i] > maxCount) {
			maxCount = histograma[i];
		}
	}

	int histWidth = 512;
	int histHeight = 400;
	int binWidth = cvRound((double)histWidth / 256);

	Mat histogramaImagem(histHeight, histWidth, CV_8UC3, Scalar(255, 255, 255));

	// Desenha o gráfico do histograma
	for (int i = 0; i < 256; i++) {
		int binHeight = cvRound((double)histograma[i] / maxCount * histHeight);
		rectangle(histogramaImagem, Point(i * binWidth, histHeight - binHeight), Point((i + 1) * binWidth - 1, histHeight), Scalar(0, 0, 0), FILLED);
	}

	imshow("Histograma", histogramaImagem);
	waitKey();
}

int main() {
	
	// Variavel responssavel por armazenar o endereco da imagem.
	auto nomeArquivo = "C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\graf1.png";

	const char* enderecos[10] = {
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\aloeL.jpg",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\apple.jpg",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\baboon.jpg",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\ela_modified.jpg",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\board.jpg",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\building.jpg",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\butterfly.jpg",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\chicky_512.png",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\graf1.png",
		"C:\\Program Files (x86)\\OpenCV\\opencv\\sources\\samples\\data\\orange.jpg"
	};

	
	Mat imagem = imread(nomeArquivo);	// Variavel para armazenar imagem original.
	Mat imagemCinza;					// Variavel para criar uma copia cinza da imagem original.
	Mat_<Vec3b> imagemMatriz;			// Variavel utilizada para criar uma matriz de imagem.
	imagemMatriz = imread(nomeArquivo);	// Transforma a imagem em matriz.
	Mat imagemBlur;
	Mat imagemConvolucao;
	Mat imagemErosao;
	
	int opcao = 0;	// Opcao do menu.


	cout << "\n=== Menu ===";
	cout << "\n1. Exibir a imagem";
	cout << "\n2. Escala de cinza";
	cout << "\n3. Propriedades";
	cout << "\n4. Propriedades da imagem cinza";
	cout << "\n5. Exibir 10 imagens com propriedades";
	cout << "\n6. Histograma";
	cout << "\n7. Filtros";

	cout << "\nDigite sua opcao: ";
	cin >> opcao;


	while (opcao < 1 || opcao > 7) {
		cout << "\n Opcao invalida, digite novamente: ";
		cin >> opcao;
	}

	switch (opcao) {
	case 1:
		imshow("Imagem", imagem);	// Funcao utilizada para realizar a exibicao da imagem.
		waitKey();					// Funcao para a imagem ficar aberta ate o usuario pressionar alguma tecla.
		break;
	case 2:
		cvtColor(imagem, imagemCinza, COLOR_BGR2GRAY);	// Copia a imagem original, torna cinza e salva na nova variavel.
		imshow("Imagem colorida", imagem);		// Exibe a imagem colorida.
		imshow("Imagem Cinza", imagemCinza);	// Exibe a imagem preto e branco.
		waitKey();	// Funcao para a imagem ficar aberta ate o usuario pressionar alguma tecla.
		break;
	case 3:
		cout << "\nLargura da imagem: " << imagem.cols;	// Funcao utilizada para retornar o numero de colunas na imagem.
		cout << "\nAltura da imagem: " << imagem.rows << "\n\n\n";	// Funcao utilizada para retornar o numero de linhas na imagem.
		imshow("Imagem", imagem);	// Funcao utilizada para realizar a exibicao da imagem.
		waitKey();	// Funcao para a imagem ficar aberta ate o usuario pressionar alguma tecla.
		break;
	case 4:
		pixels(imagem, imagemCinza);
		break;
	case 5:
		for (int j = 0; j < 10; j++) {
			cout << "=== Imagem " << j + 1 << " ====";
			imagem = imread(enderecos[j]);
			pixels(imagem, imagemCinza);
			cout << "\n\n\n";
		};
		break;

	case 6:
		for (int j = 0; j < 10; j++) {
			cout << "\n=== Imagem " << j + 1 << " ====";
			imagem = imread(enderecos[j]);
			imshow("Imagem", imagem);
			criarHistograma(imagem);
		};
		break;
	case 7:
		int vetorKernel[3];
		int opcaoFiltro = 0;
		String vetorNomes[3] = { "Primeiro Kernel", "Segundo Kernel", "Terceiro Kernel"};
		cout << "\n\n=== Menu de Filtros ===";
		cout << "\n1. Blur";
		cout << "\n2. Filtro de Convolucao";
		cout << "\n3. Erosao";

		cout << "\nOpcao: ";
		cin >> opcaoFiltro;
		if (opcaoFiltro == 1) {
			cout << "Digite o primeiro valor para o kernel: ";
			cin >> vetorKernel[0];

			cout << "Digite o segundo valor para o kernel: ";
			cin >> vetorKernel[1];

			cout << "Digite o terceiro valor para o kernel: ";
			cin >> vetorKernel[2];

			imshow("Imagem original", imagem);
			for (int z = 0; z < 3; z++) {
				blur(imagem, imagemBlur, Size(vetorKernel[z], vetorKernel[z]));
				imshow(vetorNomes[z], imagemBlur);
				waitKey();
			}
			waitKey();
		}
		else if (opcaoFiltro == 2) {
			cout << "Digite o primeiro valor para o kernel: ";
			cin >> vetorKernel[0];

			cout << "Digite o segundo valor para o kernel: ";
			cin >> vetorKernel[1];

			cout << "Digite o terceiro valor para o kernel: ";
			cin >> vetorKernel[2];

			imshow("Imagem original", imagem);
			for (int z = 0; z < 3; z++) {
				filter2D(imagem, imagemConvolucao, -1, vetorKernel[z]);
				imshow(vetorNomes[z], imagemConvolucao);
				waitKey();
			}
			waitKey();
		}
		else if (opcaoFiltro == 3) {
			cout << "Digite o primeiro valor para o kernel: ";
			cin >> vetorKernel[0];

			cout << "Digite o segundo valor para o kernel: ";
			cin >> vetorKernel[1];

			cout << "Digite o terceiro valor para o kernel: ";
			cin >> vetorKernel[2];

			imshow("Imagem original", imagem);
			for (int z = 0; z < 3; z++) {
				erode(imagem, imagemErosao, vetorKernel[z]);
				imshow(vetorNomes[z], imagemErosao);
				waitKey();
			}
			waitKey();
		}
		
		break;
	}

	return 0;
}

