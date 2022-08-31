/*
Name:		Adrian Stoop
Klasse:		En13a
Datum:		11.04.2016
Version:	1.0
Beschreibung: SW Rubikscube Solvroboter in C.
Datei:		rubiks.c
*/
#include "rubiks.h"
#include "rubiksMoves.h"
#include "funktionen.h"

#define F(a,b) 	for(a=0;a<b;++a)
#define W(a)	while(a)
#define S(a)	switch(a)
#define C(a)	case(a)
#define D() 	default

void Rubiks(void)
	{
		//setzte alles auf anfangszustand//
		W(R_Init_Status != 1)
 		// Muster 1, WinBex
		{R_Init(1,1);}
		

		//R_Scan();//scannt würfel

		R_Show_Muster();// zeige muster auf Bildschirm
		R_Show_Status();

		sleepSeconds(3);



		//löse den würfel:
		W(R_Stage_0_Status != 1){R_Stage_0();}
		W(R_Stage_1_Status != 1){R_Stage_1();}
		W(R_Stage_2_Status != 1){R_Stage_2();}
		W(R_Stage_3_Status != 1){R_Stage_3();}
		W(R_Stage_4_Status != 1){R_Stage_4();}
		W(R_Stage_5_Status != 1){R_Stage_5();}
		W(R_Stage_6_Status != 1){R_Stage_6();}
		W(R_Stage_7_Status != 1){R_Stage_7();}

		//würfel gelösst
		W(1);
	}









//Hier werden die Farben vom Würfel dem Array zugeordnet
//Muster = 0, ruft scanroutine auf.
//Muster > 0, ruft bsp. Muster auf. mögliche Muster: keins-
//Device = 1, WinBex
//Device = 2, Lego Ev3
//WinBex nur Muster > 0 möglich
void R_Init(char Muster, char Device)
	{
		//setzte alle Stage Prozesse auf 0.
		// 0 = noch nicht gemacht
		// 1 = Prozess gemacht
		R_Stage_0_Status = 0;
			F(var_i,12){R_Stage_0_2erPos[var_i] = 0;}
			R_Stage_0_2erStatus = 0;
			R_Stage_0_ausrichtung = 0;
		R_Stage_1_Status = 0;
		R_Stage_2_Status = 0;
		R_Stage_3_Status = 0;
		R_Stage_4_Status = 0;
		R_Stage_5_Status = 0;
		R_Stage_6_Status = 0;
		R_Stage_7_Status = 0;
		R_Init_Status = 0;
		//Device 0 gibt es nicht, darum wird es hier gesetzt.
		R_Device = 0;
		//0 = textmodus / 1 = grafik modus
		GF_Modus = 0;

		//zählt + 1 wenn würfel bewegt wird
		R_Zuege = 0;
		//zählt + 1 für jede vergleichsabfrage
		R_Berechnungen = 0;
		//zählt wieviel werte gewechselt wurden mit temp und rubiksfeld
		R_Wechsel = 0;
		//speichert lösungsweg(für Roboter)/ max 254 züge
		F(var_i,255){R_LWeg[var_i] = 0;}
		R_LWeg[254] = '\0';
		// "Q" dient als fehlererkennung fals das Array voll ist.
		R_LWeg[255] = 'Q';


		

		S(Device)
			{
				C(1)://WinBex
					{	
						//kontrolliert ob pharameter richtig sind.
						if(Muster == 0){R_fehler(8,"SW(DEVICE[WinBeX])","Muster ist 0!");}
						else
							{
							S(Muster)
								{
									C(1)://Muster 1
										{
											R_Lade_Muster(1);//ladet Muster 1 ins Array
											R_Init_Status = 1;//init abgeschlossen und Muster ist im Speicher, programm kann beginnen
											R_Device = 1;//WinBeX
											break;
										}
									D()://kein Muster mit dieser Nummer gefunden
										{
											R_fehler(8,"SW(DEVICE[WinBeX])/SW(MUSTER[DEFAULT])","Muster nicht gefunden!");
											break;
										}
								}
							}
						break;
					}
				C(2)://Lego Ev3
					{
						break;
					}
				D():
					{
						while(1);//fehlerausgabe benötigt Device Info...
					}

			}

	}



//Scannt würfel ab und tragt farben in das Array(Ev3)
void R_Scan(void);


//gibt genauen fehlercode aus. 
//Stage = welches Stage punkt, 8 = R_Init.
//Klammer = in welcher Klammer diese Funktion aufgeruffen wurde
//Hinweiss = zusatztinfo
void R_fehler(char Stage, char* Klammer, char* Hinweiss)
	{
		//welches Device für fehler ausgabe + vorbereitung
		switch(R_Device)
			{
				case(1)://WinBeX
					{
						//ist programm im grafik modus >> wechsle in den textmodus
						if(GF_Modus == 1)
							{
								GF_Modus = 0;
								int32_disable_gm();
							}
						//cursor auf 0,0 und screen löschen
						k_clear_screen();
				    	set_cursor(0,0);
				   		save_cursor();
				   		break;

					}
				default:
					{
						while(1);//kann fehler nicht ausgeben
					}
			}
		//in welchem abschnitt/funktion wurde der fehler ausgelösst	
		switch(Stage)
			{
				case(0)://Stage_0
					{printformat("\nFehler in Stage_0: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(1)://1
					{printformat("\nFehler in Stage_1: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(2)://2
					{printformat("\nFehler in Stage_2: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(3)://3
					{printformat("\nFehler in Stage_3: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(4)://4
					{printformat("\nFehler in Stage_4: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(5)://5
					{printformat("\nFehler in Stage_5: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(6)://6
					{printformat("\nFehler in Stage_6: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(7)://7
					{printformat("\nFehler in Stage_7: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(8)://R_Init
					{printformat("\nFehler in R_Init: %s \t INFO: %s",Klammer,Hinweiss);break;}
				case(9)://Funktionen
					{printformat("\nFehler in Funktion: %s \t INFO: %s",Klammer,Hinweiss);break;}
				default:
					{printformat("Stage nicht in R_fehler gefunden");break;}
			}
		//fehler wurde ausgegeben, warte
		while(1);
	}

//lädt bsp. Muster ins programm
void R_Lade_Muster(char Muster)
	{
		switch(Muster)
			{
				case(1):
					{
						R_Muster_1();
						break;
					}
				default:
					{
						R_fehler(9,"R_Lade_Muster","Muster nicht gefunden(default)!");
						break;
					}
			}
	}


// ladet Muster auf Bildschirm
void R_Show_Muster(void)
	{
		switch(R_Device)
			{
				case(1)://WinBeX
					{
						//wenn noch im textmodus wechse in grafik modus und bildschirm weiss + feld einzeichnen
						if(GF_Modus == 0){int32_enalbe_gm_0x13();int32_clear_screen_0x13(GRAY1);GF_Modus = 1;R_print();}


						//gib array auf bildschirm aus
						R_print_Array();
						break;
					}
				default:
					{
						R_fehler(9,"R_Show_Muster","Device nicht gefunden(default)!");
						break;
					}
			}
	}






// Bleibt solange aufgerufen bis 2 Ecksteine richtig ausgerichtet einer Farbe nebeneinander ist.
void R_Stage_0(void)
	{	
		//suche direkt ein zweierpaar(12 möglichkeiten). wenn nicht suche ein stein und bewege die anderen so, das es ein 2er paar gibt.
		//Ist das zweierpaar erstellt/gefunden teile stage 1 die position(12 möglichkeiten) des zweierpaar mit.

		//1. Möglichkeit
		if((RubiksFeld[0][3] == RubiksFeld[2][3]) && (RubiksFeld[3][0] == RubiksFeld[3][2]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[0] = 1;
			}
		//2. Möglichkeit
		if((RubiksFeld[5][0] == RubiksFeld[5][2]) && (RubiksFeld[6][3] == RubiksFeld[8][3]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[1] = 1;
			}
		//3. Möglichkeit
		if((RubiksFeld[6][5] == RubiksFeld[8][5]) && (RubiksFeld[5][6] == RubiksFeld[5][8]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[2] = 1;
			}
		//4. Möglichkeit
		if((RubiksFeld[3][6] == RubiksFeld[3][8]) && (RubiksFeld[2][5] == RubiksFeld[0][5]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[3] = 1;
			}
		//5. Möglichkeit
		if((RubiksFeld[2][3] == RubiksFeld[2][5]) && (RubiksFeld[3][3] == RubiksFeld[3][5]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[4] = 1;
			}
		//6. Möglichkeit
		if((RubiksFeld[3][2] == RubiksFeld[5][2]) && (RubiksFeld[3][3] == RubiksFeld[5][3]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[5] = 1;
			}
		//7. Möglichkeit
		if((RubiksFeld[5][3] == RubiksFeld[5][5]) && (RubiksFeld[6][3] == RubiksFeld[6][5]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[6] = 1;
			}
		//8. Möglichkeit
		if((RubiksFeld[5][5] == RubiksFeld[3][5]) && (RubiksFeld[3][6] == RubiksFeld[5][6]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[7] = 1;
			}
		//9. Möglichkeit
		if((RubiksFeld[3][8] == RubiksFeld[5][8]) && (RubiksFeld[3][9] == RubiksFeld[5][9]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[8] = 1;
			}
		//10. Möglichkeit
		if((RubiksFeld[3][11] == RubiksFeld[5][11]) && (RubiksFeld[3][0] == RubiksFeld[5][0]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[9] = 1;
			}
		//11. Möglichkeit
		if((RubiksFeld[5][9] == RubiksFeld[5][11]) && (RubiksFeld[8][3] == RubiksFeld[8][5]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[10] = 1;
			}
		//12. Möglichkeit
		if((RubiksFeld[3][9] == RubiksFeld[3][11]) && (RubiksFeld[0][3] == RubiksFeld[0][5]))
			{
				//zweierpaar gefunden, stage beenden. 
				R_Stage_0_Status = 1;
				R_Stage_0_2erPos[11] = 1;
			}

		//kontrolle ob ein zweierpaar gefunden wurde sonst mache eine drhehung und teste alles von vorne
		F(var_i,12)
			{
				//ist R_Stage_0_2erStatus > 0, dann ist min. 1 zweiepaar gefunden
				R_Stage_0_2erStatus = R_Stage_0_2erStatus + R_Stage_0_2erPos[var_i];
			}

		//wurde min. 1 zweierpaar gefunden?
		if(R_Stage_0_2erStatus > 0)
			{
				//ja, verlasse stage 0
				return;
			}
		else
			{
				//nein, bewege würfel und teste noch mal(12 seiten möglich, clk und !clk auf 6 seiten)
				//wenn eine andere seitenicht geht wieder in uhrstellung gehen und 90 grad daneben drhehen
				//bis es irgendwann klappt
				switch(R_Stage_0_ausrichtung)
					{
						case(0)://F
							{
								//standarstellung, wechsle in aussrichtung 1
								R_Stage_0_ausrichtung = 1;
								//bewege F und speichere zug im lösungsweg.
								R_MoveCube_F();
								R_LWeg[R_LWeg_pointer] = C_F;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(1)://Fi
							{
								//ausrichtung 1 hatte kein 2er paar gefunden
								// zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_Fi();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 2
								R_Stage_0_ausrichtung = 2;
								//bewege Fi und speichere zug im lösungsweg.
								R_MoveCube_Fi();
								R_LWeg[R_LWeg_pointer] = C_Fi;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(2)://U
							{
								//ausrichtung 2 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_F();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 3
								R_Stage_0_ausrichtung = 3;
								//bewege U und speichere zug im lösungsweg.
								R_MoveCube_U();
								R_LWeg[R_LWeg_pointer] = C_U;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(3)://Ui
							{
								//ausrichtung 3 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_Ui();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 4
								R_Stage_0_ausrichtung = 4;
								//bewege Ui und speichere zug im lösungsweg.
								R_MoveCube_Ui();
								R_LWeg[R_LWeg_pointer] = C_Ui;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(4)://L
							{
								//ausrichtung 4 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_U();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 5
								R_Stage_0_ausrichtung = 5;
								//bewege L und speichere zug im lösungsweg.
								R_MoveCube_L();
								R_LWeg[R_LWeg_pointer] = C_L;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(5)://Li
							{
								//ausrichtung 5 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_Li();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 6
								R_Stage_0_ausrichtung = 6;
								//bewege Li und speichere zug im lösungsweg.
								R_MoveCube_Li();
								R_LWeg[R_LWeg_pointer] = C_Li;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(6)://D
							{
								//ausrichtung 6 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_L();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 7
								R_Stage_0_ausrichtung = 7;
								//bewege D und speichere zug im lösungsweg.
								R_MoveCube_D();
								R_LWeg[R_LWeg_pointer] = C_D;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(7)://Di
							{
								//ausrichtung 7 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_Di();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 8
								R_Stage_0_ausrichtung = 8;
								//bewege Di und speichere zug im lösungsweg.
								R_MoveCube_Di();
								R_LWeg[R_LWeg_pointer] = C_Di;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(8)://R
							{
								//ausrichtung 8 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_D();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 9
								R_Stage_0_ausrichtung = 9;
								//bewege R und speichere zug im lösungsweg.
								R_MoveCube_R();
								R_LWeg[R_LWeg_pointer] = C_R;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(9)://Ri
							{
								//ausrichtung 9 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_Ri();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 10
								R_Stage_0_ausrichtung = 10;
								//bewege Ri und speichere zug im lösungsweg.
								R_MoveCube_Ri();
								R_LWeg[R_LWeg_pointer] = C_Ri;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(10)://B
							{
								//ausrichtung 9 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_R();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 11
								R_Stage_0_ausrichtung = 11;
								//bewege B und speichere zug im lösungsweg.
								R_MoveCube_B();
								R_LWeg[R_LWeg_pointer] = C_B;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						case(11)://Bi
							{
								//ausrichtung 9 hatte kein 2er paar gefunden
								//zurück zur Uhrstellung
								R_Stage_0_ausrichtung = 0;
								R_MoveCube_Bi();
								R_LWeg[R_LWeg_pointer] = 0; //0 ist kein zug, daher nix
								R_LWeg_pointer--;

								//standarstellung, wechsle in aussrichtung 10
								R_Stage_0_ausrichtung = 12;
								//bewege Bi und speichere zug im lösungsweg.
								R_MoveCube_Bi();
								R_LWeg[R_LWeg_pointer] = C_Bi;
								R_LWeg_pointer++;
								break;
								//gehe aus stage 0 raus und geginne den stage 0 von neu(neue ausrichtung)
							}
						default:
							{
								R_fehler(0,"SW[R_Stage_0_ausrichtung]","Schleife flog in defalut!");
							}
					}
			}
			
	}

// Bleibt solange aufgerufen bis 4 Ecksteine richtig ausgerichtet einer Farbe nebeneinander ist.
void R_Stage_1(void)
	{
		//zweierpaar wurde gefunden und wird mit übergab werten dem stage1 mitgeteilt wo die sich befinden
		//gemeint ist R_Stage_0_2erPos.

		//darum muss man von dieser Pos weiterarbeiten
		switch(R_Stage_0_2erPos)
			{
				case(1):
					{
						
						break;
					}
			}
	}

//würfel 180' drehen.
// Bleibt solange aufgerufen bis auf der anderen Seite Alle Ecksteine richtig ausgerichtet sind.
void R_Stage_2(void)
	{

	}

// Bleibt solange aufgerufefen bis 3 Mittelsteine richtig ausgerichtet sind.
void R_Stage_3(void)
	{

	}

// Bleibt solange aufgerufefen bis 3 Mittelsteine der anderen seite richtig ausgerichtet sind.
void R_Stage_4(void)
	{

	}

// Bleibt solange aufgerufefen bis alle auser 4 Mittelsteine ausgerichtet sind.
void R_Stage_5(void)
	{

	}

// Bleibt solange aufgerufefen bis der Würfel gelöst ist.
void R_Stage_6(void)
	{

	}

//Lässt den würfel fallen.
void R_Stage_7(void)
	{

	}





















































































































































































































void R_Muster_1(void)
	{
		RubiksFeld[0][0] = Dc;
		RubiksFeld[0][1] = Dc;
		RubiksFeld[0][2] = Dc;
		RubiksFeld[0][3] = Or; 
		RubiksFeld[0][4] = Or;
		RubiksFeld[0][5] = Or;
		RubiksFeld[0][6] = Dc;
		RubiksFeld[0][7] = Dc;
		RubiksFeld[0][8] = Dc;
		RubiksFeld[0][9] = Dc;
		RubiksFeld[0][10] = Dc;
		RubiksFeld[0][11] = Dc;

		RubiksFeld[1][0] = Dc;
		RubiksFeld[1][1] = Dc;
		RubiksFeld[1][2] = Dc;
		RubiksFeld[1][3] = Ge;
		RubiksFeld[1][4] = Ro;
		RubiksFeld[1][5] = Bl;
		RubiksFeld[1][6] = Dc;
		RubiksFeld[1][7] = Dc;
		RubiksFeld[1][8] = Dc;
		RubiksFeld[1][9] = Dc;
		RubiksFeld[1][10] = Dc;
		RubiksFeld[1][11] = Dc;

		RubiksFeld[2][0] = Dc;
		RubiksFeld[2][1] = Dc;
		RubiksFeld[2][2] = Dc;
		RubiksFeld[2][3] = Or;
		RubiksFeld[2][4] = Or;
		RubiksFeld[2][5] = Ro;
		RubiksFeld[2][6] = Dc;
		RubiksFeld[2][7] = Dc;
		RubiksFeld[2][8] = Dc;
		RubiksFeld[2][9] = Dc;
		RubiksFeld[2][10] = Dc;
		RubiksFeld[2][11] = Dc;

		RubiksFeld[3][0] = Ws;
		RubiksFeld[3][1] = Ro;
		RubiksFeld[3][2] = Ge;
		RubiksFeld[3][3] = Gr; 
		RubiksFeld[3][4] = Ge;
		RubiksFeld[3][5] = Ws;
		RubiksFeld[3][6] = Gr;
		RubiksFeld[3][7] = Ro;
		RubiksFeld[3][8] = Bl;
		RubiksFeld[3][9] = Ge;
		RubiksFeld[3][10] = Bl;
		RubiksFeld[3][11] = Gr;

		RubiksFeld[4][0] = Ws;
		RubiksFeld[4][1] = Bl;
		RubiksFeld[4][2] = Ws;
		RubiksFeld[4][3] = Or;
		RubiksFeld[4][4] = Ws;
		RubiksFeld[4][5] = Bl;
		RubiksFeld[4][6] = Ge;
		RubiksFeld[4][7] = Gr;
		RubiksFeld[4][8] = Ws;
		RubiksFeld[4][9] = Gr;
		RubiksFeld[4][10] = Ge;
		RubiksFeld[4][11] = Bl;

		RubiksFeld[5][0] = Gr;
		RubiksFeld[5][1] = Or;
		RubiksFeld[5][2] = Bl;
		RubiksFeld[5][3] = Ws;
		RubiksFeld[5][4] = Ws;
		RubiksFeld[5][5] = Bl;
		RubiksFeld[5][6] = Ge;
		RubiksFeld[5][7] = Gr;
		RubiksFeld[5][8] = Ws;
		RubiksFeld[5][9] = Bl;
		RubiksFeld[5][10] = Gr;
		RubiksFeld[5][11] = Ge;

		RubiksFeld[6][0] = Dc;
		RubiksFeld[6][1] = Dc;
		RubiksFeld[6][2] = Dc;
		RubiksFeld[6][3] = Or;
		RubiksFeld[6][4] = Ro;
		RubiksFeld[6][5] = Ro;
		RubiksFeld[6][6] = Dc;
		RubiksFeld[6][7] = Dc;
		RubiksFeld[6][8] = Dc;
		RubiksFeld[6][9] = Dc;
		RubiksFeld[6][10] = Dc;
		RubiksFeld[6][11] = Dc;

		RubiksFeld[7][0] = Dc;
		RubiksFeld[7][1] = Dc;
		RubiksFeld[7][2] = Dc;
		RubiksFeld[7][3] = Gr;
		RubiksFeld[7][4] = Or;
		RubiksFeld[7][5] = Ge;
		RubiksFeld[7][6] = Dc;
		RubiksFeld[7][7] = Dc;
		RubiksFeld[7][8] = Dc;
		RubiksFeld[7][9] = Dc;
		RubiksFeld[7][10] = Dc;
		RubiksFeld[7][11] = Dc;

		RubiksFeld[8][0] = Dc;
		RubiksFeld[8][1] = Dc;
		RubiksFeld[8][2] = Dc;
		RubiksFeld[8][3] = Ro;
		RubiksFeld[8][4] = Ro;
		RubiksFeld[8][5] = Ro;
		RubiksFeld[8][6] = Dc;
		RubiksFeld[8][7] = Dc;
		RubiksFeld[8][8] = Dc;
		RubiksFeld[8][9] = Dc;
		RubiksFeld[8][10] = Dc;
		RubiksFeld[8][11] = Dc;
	}


void R_print(void)
	{
		if(GF_Modus == 1)
			{
				//linien die 3 pixel breit sind / senkrecht
				int32_rechteck_0x13(30,66,32,132,BLACK);
				int32_rechteck_0x13(95,2,97,196,BLACK);
				int32_rechteck_0x13(160,2,162,196,BLACK);
				int32_rechteck_0x13(225,66,227,132,BLACK);
				int32_rechteck_0x13(290,66,292,132,BLACK);

				//linien die 3 pixel breit sind / waagrecht
				int32_rechteck_0x13(95,1,162,3,BLACK);
				int32_rechteck_0x13(30,66,289,68,BLACK);
				int32_rechteck_0x13(30,131,292,133,BLACK);
				int32_rechteck_0x13(95,196,162,198,BLACK);

				//linien die 1 pixel breit sind / senkrecht
				int32_line_0x13(53,66,53,132,BLACK);
				int32_line_0x13(74,66,74,132,BLACK);

				int32_line_0x13(118,2,118,196,BLACK);
				int32_line_0x13(139,2,139,196,BLACK);

				int32_line_0x13(183,66,183,132,BLACK);
				int32_line_0x13(204,66,204,132,BLACK);

				int32_line_0x13(248,66,248,132,BLACK);
				int32_line_0x13(269,66,269,132,BLACK);


				//linien die 1 pixel breit sind / waagrecht
				int32_rechteck_0x13(95,24,161,24,BLACK);
				int32_rechteck_0x13(95,45,161,45,BLACK);

				int32_rechteck_0x13(30,89,289,89,BLACK);
				int32_rechteck_0x13(30,110,289,110,BLACK);

				int32_rechteck_0x13(95,154,161,154,BLACK);
				int32_rechteck_0x13(95,175,161,175,BLACK);



			}
		else
			{
				R_fehler(9,"R_print","Modus ist auf Textmodus(GF_Modus)!");
			}
	}


void R_print_Array(void)
	{
		if(GF_Modus == 1)
			{
				char zaeler;
				char feld = 0;// 0 = dc
				//setze alle 54 felder des Arrays
				for(zaeler = 0; zaeler <= 53; zaeler++)
					{
						switch(zaeler)
							{
								case(0):{feld = RubiksFeld[0][3];break;}
								case(1):{feld = RubiksFeld[0][4];break;}
								case(2):{feld = RubiksFeld[0][5];break;}
								case(3):{feld = RubiksFeld[1][3];break;}
								case(4):{feld = RubiksFeld[1][4];break;}
								case(5):{feld = RubiksFeld[1][5];break;}
								case(6):{feld = RubiksFeld[2][3];break;}
								case(7):{feld = RubiksFeld[2][4];break;}
								case(8):{feld = RubiksFeld[2][5];break;}

								case(9):{feld  = RubiksFeld[3][0];break;}
								case(10):{feld = RubiksFeld[3][1];break;} 
								case(11):{feld = RubiksFeld[3][2];break;} 
								case(12):{feld = RubiksFeld[3][3];break;} 
								case(13):{feld = RubiksFeld[3][4];break;} 
								case(14):{feld = RubiksFeld[3][5];break;} 
								case(15):{feld = RubiksFeld[3][6];break;} 
								case(16):{feld = RubiksFeld[3][7];break;} 
								case(17):{feld = RubiksFeld[3][8];break;} 

								case(18):{feld = RubiksFeld[3][9];break;} 
								case(19):{feld = RubiksFeld[3][10];break;} 
								case(20):{feld = RubiksFeld[3][11];break;} 
								case(21):{feld = RubiksFeld[4][0];break;} 
								case(22):{feld = RubiksFeld[4][1];break;} 
								case(23):{feld = RubiksFeld[4][2];break;} 
								case(24):{feld = RubiksFeld[4][3];break;} 
								case(25):{feld = RubiksFeld[4][4];break;} 
								case(26):{feld = RubiksFeld[4][5];break;} 

								case(27):{feld = RubiksFeld[4][6];break;} 
								case(28):{feld = RubiksFeld[4][7];break;} 
								case(29):{feld = RubiksFeld[4][8];break;} 
								case(30):{feld = RubiksFeld[4][9];break;} 
								case(31):{feld = RubiksFeld[4][10];break;} 
								case(32):{feld = RubiksFeld[4][11];break;} 
								case(33):{feld = RubiksFeld[5][0];break;}
								case(34):{feld = RubiksFeld[5][1];break;}
								case(35):{feld = RubiksFeld[5][2];break;}

								case(36):{feld = RubiksFeld[5][3];break;}
								case(37):{feld = RubiksFeld[5][4];break;}
								case(38):{feld = RubiksFeld[5][5];break;}
								case(39):{feld = RubiksFeld[5][6];break;}
								case(40):{feld = RubiksFeld[5][7];break;}
								case(41):{feld = RubiksFeld[5][8];break;}
								case(42):{feld = RubiksFeld[5][9];break;}
								case(43):{feld = RubiksFeld[5][10];break;}
								case(44):{feld = RubiksFeld[5][11];break;}

								case(45):{feld = RubiksFeld[6][3];break;}
								case(46):{feld = RubiksFeld[6][4];break;}
								case(47):{feld = RubiksFeld[6][5];break;}
								case(48):{feld = RubiksFeld[7][3];break;}
								case(49):{feld = RubiksFeld[7][4];break;}
								case(50):{feld = RubiksFeld[7][5];break;}
								case(51):{feld = RubiksFeld[8][3];break;}
								case(52):{feld = RubiksFeld[8][4];break;}
								case(53):{feld = RubiksFeld[8][5];break;}
								default:{R_fehler(9,"R_print_Array","zeler>53");}
							}

						switch(zaeler)
							{
								case(0):{R_Paint(98,4,feld);break;}
								case(1):{R_Paint(119,4,feld);break;}
								case(2):{R_Paint(140,4,feld);break;}
								case(3):{R_Paint(98,25,feld);break;}
								case(4):{R_Paint(119,25,feld);break;}
								case(5):{R_Paint(140,25,feld);break;}
								case(6):{R_Paint(98,46,feld);break;}
								case(7):{R_Paint(119,46,feld);break;}
								case(8):{R_Paint(140,46,feld);break;}

								case(9):{R_Paint(33,69,feld);break;}
								case(10):{R_Paint(54,69,feld);break;}
								case(11):{R_Paint(75,69,feld);break;}
								case(12):{R_Paint(98,69,feld);break;}
								case(13):{R_Paint(119,69,feld);break;}
								case(14):{R_Paint(140,69,feld);break;}
								case(15):{R_Paint(163,69,feld);break;}
								case(16):{R_Paint(184,69,feld);break;}
								case(17):{R_Paint(205,69,feld);break;}
								case(18):{R_Paint(228,69,feld);break;}
								case(19):{R_Paint(249,69,feld);break;}
								case(20):{R_Paint(270,69,feld);break;}

								case(21):{R_Paint(33,90,feld);break;}
								case(22):{R_Paint(54,90,feld);break;}
								case(23):{R_Paint(75,90,feld);break;}
								case(24):{R_Paint(98,90,feld);break;}
								case(25):{R_Paint(119,90,feld);break;}
								case(26):{R_Paint(140,90,feld);break;}
								case(27):{R_Paint(163,90,feld);break;}
								case(28):{R_Paint(184,90,feld);break;}
								case(29):{R_Paint(205,90,feld);break;}
								case(30):{R_Paint(228,90,feld);break;}
								case(31):{R_Paint(249,90,feld);break;}
								case(32):{R_Paint(270,90,feld);break;}

								case(33):{R_Paint(33,111,feld);break;}
								case(34):{R_Paint(54,111,feld);break;}
								case(35):{R_Paint(75,111,feld);break;}
								case(36):{R_Paint(98,111,feld);break;}
								case(37):{R_Paint(119,111,feld);break;}
								case(38):{R_Paint(140,111,feld);break;}
								case(39):{R_Paint(163,111,feld);break;}
								case(40):{R_Paint(184,111,feld);break;}
								case(41):{R_Paint(205,111,feld);break;}
								case(42):{R_Paint(228,111,feld);break;}
								case(43):{R_Paint(249,111,feld);break;}
								case(44):{R_Paint(270,111,feld);break;}

								case(45):{R_Paint(98,134,feld);break;}
								case(46):{R_Paint(119,134,feld);break;}
								case(47):{R_Paint(140,134,feld);break;}
								case(48):{R_Paint(98,155,feld);break;}
								case(49):{R_Paint(119,155,feld);break;}
								case(50):{R_Paint(140,155,feld);break;}
								case(51):{R_Paint(98,176,feld);break;}
								case(52):{R_Paint(119,176,feld);break;}
								case(53):{R_Paint(140,176,feld);break;}
								default:{R_fehler(9,"R_print_Array","zeler>53");}
							}
					}

			}
		else
			{
				R_fehler(9,"R_print_Array","Modus ist auf Textmodus(GF_Modus)!");
			}
	}

void R_Paint(int x,int y,char feld)
	{
		switch(feld)
			{
		 		case(Ws):{int32_rechteck_0x13(x,y,x+19,y+19,WHITE);break;}
		 		case(Ro):{int32_rechteck_0x13(x,y,x+19,y+19,RED);break;}
		 		case(Bl):{int32_rechteck_0x13(x,y,x+19,y+19,BLUE);break;}
		 		case(Ge):{int32_rechteck_0x13(x,y,x+19,y+19,YELLOW);break;}
		 		case(Gr):{int32_rechteck_0x13(x,y,x+19,y+19,GREEN);break;}
		 		case(Or):{int32_rechteck_0x13(x,y,x+19,y+19,BROWN);break;}
		 		default: {R_fehler(9,"R_Paint","Feldinhalt nicht korrekt!");break;}
			}
	}


void R_Show_Status(void)
	{
		char Zuege[10];
		char Berechnungen[10];
		char Wechsel[10];

		//wandelt alle int in string um für ausgabe
		float2string(R_Zuege, 2, Zuege);
		float2string(R_Berechnungen, 2, Berechnungen);
		float2string(R_Wechsel, 2, Wechsel);


		switch(R_Device)
			{
				case(1)://WinBeX
					{
						R_printstring(Zuege,1);
						R_printstring(Berechnungen,2);
						R_printstring(Wechsel,3);
						break;
					}
				default:
					{
						R_fehler(9,"R_Show_Status","Device nicht gefunden(default)!");
						break;
					}
			}
	}


void R_printstring(char* string, char Zeile)
	{

		char Temp = 0;
		char i = 0;
		char fertig = 0;

		//pl = place. 
		int pl_x = 0;
		int pl_y = 0;

		switch(Zeile)//setzt start x/y werte um zahlen auf bildschirm rauszuschreiben
			{
				case(1):
					{
						pl_x = 10;
						pl_y = 10;
						break;
					}
				case(2):
					{
						pl_x = 10;
						pl_y = 17;
						break;
					}
				case(3):
					{
						pl_x = 10;
						pl_y = 24;
						break;
					}
				default:
					{
						R_fehler(9,"R_printstring","Zeile nicht vorhanden!");
						break;
					}
			}

		while(fertig != 1)
			{
				Temp = string[i];
				i++;

				switch(Temp)
					{
						case(0x30)://zeichne 0
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),GRAY1);
								break;
							}
						case(0x31)://zeichne 1
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),BLACK);
								break;
							}
						case(0x32)://zeichne 2
							{

								int32_setpixel_0x13((pl_x+0),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),BLACK);
								break;
							}
						case(0x33)://zeichne 3
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),GRAY1);
								break;
							}
						case(0x34)://zeichne 4
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),BLACK);
								break;
							}
						case(0x35)://zeichne 5
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),GRAY1);
								break;
							}
						case(0x36)://zeichne 6
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),GRAY1);
								break;
							}
						case(0x37)://zeichne 7
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),GRAY1);
								break;
							}
						case(0x38)://zeichne 8
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),GRAY1);
								break;
							}
						case(0x39)://zeichne 9
							{
								int32_setpixel_0x13((pl_x+0),(pl_y+0),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+0),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+0),GRAY1);

								int32_setpixel_0x13((pl_x+0),(pl_y+1),BLACK);
								int32_setpixel_0x13((pl_x+1),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+1),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+1),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+2),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+2),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+2),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+2),(pl_y+3),GRAY1);
								int32_setpixel_0x13((pl_x+3),(pl_y+3),BLACK);

								int32_setpixel_0x13((pl_x+0),(pl_y+4),GRAY1);
								int32_setpixel_0x13((pl_x+1),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+2),(pl_y+4),BLACK);
								int32_setpixel_0x13((pl_x+3),(pl_y+4),GRAY1);
								break;
							}
						case(0x2E):// "."
							{
								fertig = 1;
								break;
							}
						case(0x00):// "\0"
							{
								fertig = 1;
								break;
							}
						default:
							{
								R_fehler(9,"R_printstring","zeichen in temp ist != 0-9");
								break;
							}
					}
				//x erhöhen für nächste stelle
				pl_x = pl_x + 5;
				if(pl_x >= 320){R_fehler(9,"R_printstring","pl_x > 320!(bildrand)");}
			}
	}














