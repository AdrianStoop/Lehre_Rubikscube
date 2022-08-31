/*
Name:		Adrian Stoop
Klasse:		En13a
Datum:		11.04.2016
Version:	1.0
Beschreibung: SW Rubikscube Solvroboter in C.
Datei:		rubiks.h
*/

#define Dc 0 	//dont Care
#define Ws 1 	//Weiss/schwarz
#define Ro 2	//Rot
#define Bl 3	//Blau
#define Ge 4	//Gelb
#define Gr 5	//Grün
#define Or 6	//Orage

//R_MoveFullCube_right
#define MVC_Right 	0
//R_MoveFullCube_left
#define MVC_Left 	1
//R_MoveFullCube_up
#define MVC_Up 		2
//R_MoveFullCube_down
#define MVC_Down 	3
//R_MoveFullCube_Clock
#define MVC_CLK 	4
//R_MoveFullCube_NotClock
#define MVC_NOTCLK 	5

//varaiblen um kurzfristig daten zu speichern beim drehen des würfels
//würfel anordnung:
char Temp_1, Temp_2, Temp_3;
char Temp_4, Temp_5, Temp_6;
char Temp_7, Temp_8, Temp_9;




//Arrayfeld mit rubiks farben
char RubiksFeld[9][12] = {//Default stellung/Ziel
							//Oben
		{ Dc, Dc, Dc,  		Ro,  Ro,  Ro,  		Dc,  Dc,  Dc, 		Dc,  Dc,  Dc},
		{ Dc, Dc, Dc,  		Ro,  Ro,  Ro,  		Dc,  Dc,  Dc,  		Dc,  Dc,  Dc},
		{ Dc, Dc, Dc,  		Ro,  Ro,  Ro,  		Dc,  Dc,  Dc,  		Dc,  Dc,  Dc},

		//Links 			front 				Rechts 				Back
		{ Bl, Bl, Bl,  		Ws,  Ws,  Ws,  		Gr,  Gr,  Gr,  		Ge,  Ge,  Ge},
		{ Bl, Bl, Bl,  		Ws,  Ws,  Ws,  		Gr,  Gr,  Gr,  		Ge,  Ge,  Ge},
		{ Bl, Bl, Bl,  		Ws,  Ws,  Ws,  		Gr,  Gr,  Gr,  		Ge,  Ge,  Ge},

							//Unten
		{ Dc, Dc, Dc,  		Or,  Or,  Or,  		Dc,  Dc,  Dc,  		Dc,  Dc,  Dc},
		{ Dc, Dc, Dc,  		Or,  Or,  Or,  		Dc,  Dc,  Dc,  		Dc,  Dc,  Dc},
		{ Dc, Dc, Dc,  		Or,  Or,  Or,  		Dc,  Dc,  Dc,  		Dc,  Dc,  Dc},
};


//hilfsvariable 
int var_i;


//Hauptfunktion
void Rubiks(void);


//Hier werden die Farben vom Würfel dem Array zugeordnet
//Muster = 0, ruft scanroutine auf.
//Muster > 0, ruft bsp. Muster auf. mögliche Muster: keins-
//Device = 1, WinBex
//Device = 2, Lego Ev3
//WinBex nur Muster > 0 möglich
void R_Init(char Muster, char Device);
char R_Device;
char R_Init_Status = 0;


//Scannt würfel ab und tragt farben in das Array(Ev3)
void R_Scan(void);

//gibt genauen fehlercode aus. 
//Stage = welches Stage punkt, 8 = R_Init. 8 < subruntinen.
//Klammer = in welcher Klammer diese Funktion aufgeruffen wurde
//Hinweiss = zusatztinfo
void R_fehler(char Stage, char* Klammer, char* Hinweiss);

//lädt bsp. Muster ins programm
void R_Lade_Muster(char Muster);


//läd muster 1 ins array
void R_Muster_1(void);

// ladet Muster auf Bildschirm
void R_Show_Muster(void);
char GF_Modus;

//zeichent raster
void R_print(void);

//sub von R_Show_Muster
void R_print_Array(void);

//sub von R_print_Array
void R_Paint(int x,int y,char feld);


void R_Show_Status(void);
//varablen um geschwindigkeit + züge zu zählen
//zählt + 1 wenn würfel bewegt wird
float R_Zuege;
//zählt + 1 für jede vergleichsabfrage
float R_Berechnungen;
//zählt wieviel werte gewechselt wurden mit temp und rubiksfeld
float R_Wechsel;
//speichert lösungsweg(für Roboter)/ max 254 züge
char R_LWeg[256];
char R_LWeg_pointer = 0;

//dreht lösungsweg wenn würfel gedreht wird.
void R_LWeg_change(char Seite);

//gibt string auf einer der 3 linien aus
void R_printstring(char* string, char Zeile);

//dreht ganzer würfel 90' von oben gesehen nach rechts
void R_MoveFullCube_right(void);
//dreht ganzer würfel 90' von oben gesehen nach links
void R_MoveFullCube_left(void);
//dreht ganzer würfel 90' von oben gesehen nach oben
void R_MoveFullCube_up(void);
//dreht ganzer würfel 90' von oben gesehen nach unten
void R_MoveFullCube_down(void);
//drhet den würfel oben in uhrzeigerrichtung
void R_MoveFullCube_Clock(void);
//drhet den würfel oben gegen den uhrzeigerrichtung
void R_MoveFullCube_NotClock(void);

//drgeht den zug R
#define C_R 1
void R_MoveCube_R(void);

//drgeht den zug Ri
#define C_Ri 2
void R_MoveCube_Ri(void);

//drgeht den zug L
#define C_L 3
void R_MoveCube_L(void);

//drgeht den zug Li
#define C_Li 4
void R_MoveCube_Li(void);

//drgeht den zug U
#define C_U 5
void R_MoveCube_U(void);

//drgeht den zug Ui
#define C_Ui 6
void R_MoveCube_Ui(void);

//drgeht den zug D
#define C_D 7
void R_MoveCube_D(void);

//drgeht den zug Di
#define C_Di 8
void R_MoveCube_Di(void);

//drgeht den zug F
#define C_F 9
void R_MoveCube_F(void);

//drgeht den zug Fi
#define C_Fi 10
void R_MoveCube_Fi(void);

//drgeht den zug B
#define C_B 11
void R_MoveCube_B(void);

//drgeht den zug Bi
#define C_Bi 12
void R_MoveCube_Bi(void);

//drgeht den zug M
#define C_M 13
void R_MoveCube_M(void);

//drgeht den zug Mi
#define C_Mi 14
void R_MoveCube_Mi(void);

//drgeht den zug S
#define C_S 15
void R_MoveCube_S(void);

//drgeht den zug Si
#define C_Si 16
void R_MoveCube_Si(void);

//drgeht den zug E
#define C_E 17
void R_MoveCube_E(void);

//drgeht den zug Ei
#define C_Ei 18
void R_MoveCube_Ei(void);








// Bleibt solange aufgerufen bis 2 Ecksteine richtig ausgerichtet einer Farbe nebeneinander ist.
void R_Stage_0(void);
char R_Stage_0_Status;
char R_Stage_0_2erPos[12];
char R_Stage_0_2erStatus = 0;
char R_Stage_0_ausrichtung = 0;

// Bleibt solange aufgerufen bis 4 Ecksteine richtig ausgerichtet einer Farbe nebeneinander ist.
void R_Stage_1(void);
char R_Stage_1_Status;

//würfel 180' drehen.
// Bleibt solange aufgerufen bis auf der anderen Seite Alle Ecksteine richtig ausgerichtet sind.
void R_Stage_2(void);
char R_Stage_2_Status;

// Bleibt solange aufgerufefen bis 3 Mittelsteine richtig ausgerichtet sind.
void R_Stage_3(void);
char R_Stage_3_Status;

// Bleibt solange aufgerufefen bis 3 Mittelsteine der anderen seite richtig ausgerichtet sind.
void R_Stage_4(void);
char R_Stage_4_Status;

// Bleibt solange aufgerufefen bis alle auser 4 Mittelsteine ausgerichtet sind.
void R_Stage_5(void);
char R_Stage_5_Status;

// Bleibt solange aufgerufefen bis der Würfel gelöst ist.
void R_Stage_6(void);
char R_Stage_6_Status;

//Lässt den würfel fallen.
void R_Stage_7(void);
char R_Stage_7_Status;





