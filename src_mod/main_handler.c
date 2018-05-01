#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "image.h"


int main(int argc, char const *argv[])
{
	
	printf("Se inicia el pipeline.\n");

	//Se inicia el proceso para la lectura de la imagen.
	pid_t pidLecturaImg;
	int pipe_read[2];
	pipe(pipe_read);
	if((pidLecturaImg = fork())==0){
		//Si es el hijo.
		close(pipe_read[0]);
		//Se convierte pipe a char*
		char pipe_to_string[12];
		snprintf(pipe_to_string, 12, "%i", pipe_read[1]);
		printf("hola");
		int res = execlp("./readImage","readImage","prueba.bmp", &pipe_to_string,(char*)NULL);
		printf("Resultado execlp = %u\n", res);
	}else{
		//Si soy el padre.
		close(pipe_read[1]);
		
		Image *img = malloc(sizeof(img));
		/*img->triads = (Triad**)malloc(sizeof(Triad*)*512);
		for (int i = 0; i < 512; i++)
		{
			img->triads[i] = (Triad*)malloc(sizeof(Triad)*512);
		}
		*/
		
		//read(pipe_read[0], img, sizeof(Image));
		read(pipe_read[0], &img->width, sizeof(int));
		read(pipe_read[0], &img->height, sizeof(int));
		read(pipe_read[0], &img->tam_img, sizeof(int));
		//printf("Respuesta en el padre de Image->type: %i\n", img->type);
		printf("Respuesta en padre image->width: %d\n", img->width);
		printf("Respuesta en padre image->height: %d\n", img->height);
		
		
		unsigned char *data = malloc(sizeof(unsigned char)*img->tam_img);
		//read(pipe_read[0], data, sizeof(unsigned char)*img->tam_img);
		int aux = 0;
		for(aux = 0; aux<img->tam_img; aux++){
			read(pipe_read[0], &data[aux], sizeof(unsigned char));
		}
		for(aux = 0; aux<img->tam_img; aux++){
				printf("R: %i ", data[aux]);
				aux++;
				printf("B: %i ", data[aux]);
				aux++;
				printf("G: %i ", data[aux]);
				aux++;
				printf("A: %i\n", data[aux]);
		}
		
		/*
		int x;
		int y;
		Triad** triads = (Triad**)malloc(sizeof(Triad*)*img->width);
		Triad triad;
		for(x =0; x<img->width; x++){
			triads[x] = (Triad*)malloc(sizeof(Triad)*img->height);
			for(y =0; y<img->height; y++){
			//read(pipe_read[0],triad,sizeof(Triad)*img->height);
				read(pipe_read[0],&triad,sizeof(Triad));
				//printf("(%d,%d,%d)\n", triad.r,triad.g,triad.b);
			}
		}
		*/

		//printf("Prueba Triad Papi [50][100] : (%d,%d,%d,%d)\n", img->triads[50][100].r,img->triads[50][100].g,img->triads[50][100].b,img->triads[50][100].a );
	}























	/*

		int numImgs = -1;
	int umbral = -1;
	int umbralNearlyBlack = -1;
	int flag = 0;
	int aux;

	while ((aux = getopt (argc, argv, "c:u:n:b")) != -1){
		switch (aux){
			case 'c':
				numImgs = atoi(optarg);
				break;
			case 'u':
				umbral = atoi(optarg);
				break;
			case 'n':
				umbralNearlyBlack = atoi(optarg);
				break;
			case 'b':
				flag = 1;
				break;
			default:
				abort();
		}
	}
    //Comprobaciones getopt
    if((umbral < 0 ) || (umbral > 255)){
        printf("\nValor del umbral incorrecto, debe ser entre 0 y 255, saliendo...\n\n");
        return -1;
    }
    if((umbralNearlyBlack < 0) || (umbralNearlyBlack > 100)){
        printf("\nValor del umbral para la categoría inválido, debe ser un porcentaje entre 0 y 100\n\n");
        return -1;
    }
    if(numImgs <= 0){
        printf("\nCantidad de imágenes inválida, debe ser igual o mayor a 1\n\n");
        return -1;
    }
    if((numImgs == -1) || (umbral == -1) || (umbralNearlyBlack == -1)){
        printf("\nNo ha ingresado todas las opciones, revisar leeme\n\n");
        return -1;
    }

	int op = 0;
	char **imageNames = (char**)malloc(sizeof(char*)*numImgs);
	int x;
	for(x = 0; x<numImgs; x++){
		imageNames[x] = (char*)malloc(sizeof(char)*100);
		printf("Ingrese el nombre de la imágen %d sin su extensión y luego presione Enter...\n",x+1);
		scanf("%s",imageNames[x]);
		strcat(imageNames[x],".bmp");
		fflush( stdin );
		printf("Imagen: %s\n",imageNames[x]);

        FILE *archivo = openImage(imageNames[x]); //Comprobación de que el archivo existe
        if(archivo == NULL){
            printf("\nError: Archivo no existe, ingreselo nuevamente\n\n");
            x--;
        } else {
            closeImage(archivo);
        }

	}
	*/



	return 0;
}