#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	//MATRIZ GENERADORA
	int G[8][12]={{1,1,1,0,0,0,0,0,0,0,0,0},
				  {1,0,0,1,1,0,0,0,0,0,0,0},
				  {0,1,0,1,0,1,0,0,0,0,0,0},
				  {1,1,0,1,0,0,1,0,0,0,0,0},
				  {1,0,0,0,0,0,0,1,1,0,0,0},
				  {0,1,0,0,0,0,0,1,0,1,0,0},
				  {1,1,0,0,0,0,0,1,0,0,1,0},
				  {0,0,0,1,0,0,0,1,0,0,0,1}};
	//MATRIZ CONTROL DE PARIDAD
	int H[4][12]={{0,0,0,0,0,0,0,1,1,1,1,1},
				  {0,0,0,1,1,1,1,0,0,0,0,1},
				  {0,1,1,0,0,1,1,0,0,1,1,0},
				  {1,0,1,0,1,0,1,0,1,0,1,0}};
				  
	int contP, numP, contF,contD, contC, op=0, palabraCodigo[12]={0,0,0,0,0,0,0,0,0,0,0,0}, palabraDecodificada[8],error[4],errorPalabra,exp;
	//int error2[8][4];
	unsigned char c[256],palabraCodigoString[12],caracter;
				  
	//COMPROBACION MATRICES
	/*int htr[12][4]={{0,0,0,1},
					{0,0,1,0},
					{0,0,1,1},
					{0,1,0,0},
					{0,1,0,1},
					{0,1,1,0},
					{0,1,1,1},
					{1,0,0,0},
					{1,0,0,1},
					{1,0,1,0},
					{1,0,1,1},
					{1,1,0,0}};
				
	for(contF=0;contF<8;contF++){
				for(contD=0;contD<4;contD++){
					error2[contF][contD]=0;
					for(contC=0;contC<12;contC++){
						error2[contF][contD]+=G[contF][contC]*htr[contC][contD];
					}
					error2[contF][contD]=error2[contF][contD]%2;
				}
			}
	for(contF=0;contF<8;contF++){
		printf("%d\t%d\t%d\t%d\n",error2[contF][0],error2[contF][1],error2[contF][2],error2[contF][3]);
	}*/
			
	do{	
	printf("Implementacion de un codigo 1-corrector/2-detector\n");
	printf("Este programa codifica cadenas de hasta 256 caracteres\n");
	printf("Menu\n");
	printf("1.Codificar\n");
	printf("2.Decodificar\n");
	printf("3.Salir\n");
	printf("Introduce la opcion deseada\n");
	do{
		fflush(stdin);
		scanf("%d",&op);
		if(op<1 || op>3) printf("Opcion incorrecta.\n");
	}while(op<1 || op>3);
	
	switch(op){
		case 1:
			fflush(stdin);
			printf("Introduzca cadena a codificar: ");
			scanf("%s",c);
			
			printf("Caracter\tBinario\t\tBinario Codificado\n");
			
			for(contP=0,numP=strlen(c);numP>contP;contP++){
				int aux=c[contP];
				for(contC=7;contC>0;contC--,aux=aux/2){
					palabraDecodificada[contC]=aux%2;
				}
				palabraDecodificada[0]=aux;
				
				printf("\n");
				for(contC=0;contC<12;contC++){
					palabraCodigo[contC]=0;
					for(contF=0;contF<8;contF++){
						palabraCodigo[contC]+=palabraDecodificada[contF]*G[contF][contC];
					}
				palabraCodigo[contC]=palabraCodigo[contC]%2;
				}
				printf("%c\t\t",c[contP]);
				for(contC=0;contC<8;contC++){
					printf("%d",palabraDecodificada[contC]);
				}
					printf("\t");
				for(contC=0;contC<12;contC++){
					printf("%d",palabraCodigo[contC]);
				}
					printf("\n\n");
			}

			break;
		case 2:
			printf("Introduzca palabra codigo: ");
			fflush(stdin);
			scanf("%s",palabraCodigoString);
			for(contC=0;contC<12;contC++){
				palabraCodigo[contC]=palabraCodigoString[contC];
				palabraCodigo[contC]=palabraCodigo[contC]-48;
			}
			for(contF=0;contF<4;contF++){
				error[contF]=0;
				for(contC=0;contC<12;contC++){
					error[contF]+=palabraCodigo[contC]*H[contF][contC];
				}
				error[contF]=error[contF]%2;
			}
						
			for(contC=0,exp=3,errorPalabra=0;contC<4;contC++,exp--){
					errorPalabra+=(error[contC]*pow(2,exp));
			}
			
			if(errorPalabra!=0){
				printf("Error encontrado en la posicion %d\n",errorPalabra);
				palabraCodigo[errorPalabra-1]=(palabraCodigo[errorPalabra-1]-1)*-1;
				
				printf("Palabra Codigo Correcta: ");
				for(contC=0;contC<12;contC++){
					printf("%d",palabraCodigo[contC]);
				}
				printf("\n");
			} else {
				printf("La palabra codigo es correcta.\n\n");
			}
			for(contF=2,contC=0;contF<12;contF++){
					if(contF!=3 && contF!=7){
						palabraDecodificada[contC]=palabraCodigo[contF];
						contC++;
					}
			}
			
			int sum=0;
			for(contC=0,exp=7;contC<8;contC++,exp--){
					sum+=(palabraDecodificada[contC]*pow(2,exp));
			}
			printf("Binario Codificado\tBinario\t\tCaracter\n");
			for(contC=0;contC<12;contC++){
					printf("%d",palabraCodigo[contC]);
			}
			printf("\t\t");
			for(contC=0;contC<8;contC++){
					printf("%d",palabraDecodificada[contC]);
			}
			printf("\t");
			printf("%c\n\n",sum);
			break;
	}
	
	}while(op!=3);
}
