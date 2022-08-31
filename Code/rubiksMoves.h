/*
Name:		Adrian Stoop
Klasse:		En13a
Datum:		11.04.2016
Version:	1.0
Beschreibung: SW Rubikscube Solvroboter in C. Optimiert für Sublime Text 3
Datei:		rubiksMoves.h
*/

/*
Hier werden alle Bewegungsfunktionen aufgeliestet.
Spart Platzt und ermöglicht einen besseren überblick im main file(rubiks.c)


Inhaltsverzeichniss:	  Zeile:

R_MoveFullCube_right			  52
R_MoveFullCube_left				 141
R_MoveFullCube_up				 228
R_MoveFullCube_down				 315
R_MoveFullCube_Clock 			 401
R_MoveFullCube_NotClock			 487

R_MoveCube_R 					 576
R_MoveCube_Ri 					 616

R_MoveCube_L 					 656
R_MoveCube_Li 					 696

R_MoveCube_U 					 736
R_MoveCube_Ui 					 776

R_MoveCube_D 					 816
R_MoveCube_Di 					 856

R_MoveCube_F 					 896
R_MoveCube_Fi  					 936

R_MoveCube_B 					 976
R_MoveCube_Bi 					1016

R_MoveCube_M 					1056
R_MoveCube_Mi 					1081

R_MoveCube_S 					1106
R_MoveCube_Si 					1131

R_MoveCube_E 					1156
R_MoveCube_Ei 					1181

*/
void R_MoveFullCube_right(void)
	{
		Temp_1 = RubiksFeld[3][3];
		Temp_2 = RubiksFeld[3][4];
		Temp_3 = RubiksFeld[3][5];
		Temp_4 = RubiksFeld[4][3];
		Temp_5 = RubiksFeld[4][4];
		Temp_6 = RubiksFeld[4][5];
		Temp_7 = RubiksFeld[5][3];
		Temp_8 = RubiksFeld[5][4];
		Temp_9 = RubiksFeld[5][5];

		RubiksFeld[3][3] = RubiksFeld[3][0];
		RubiksFeld[3][4] = RubiksFeld[3][1];
		RubiksFeld[3][5] = RubiksFeld[3][2];
		RubiksFeld[4][3] = RubiksFeld[4][0];
		RubiksFeld[4][4] = RubiksFeld[4][1];
		RubiksFeld[4][5] = RubiksFeld[4][2];
		RubiksFeld[5][3] = RubiksFeld[5][0];
		RubiksFeld[5][4] = RubiksFeld[5][1];
		RubiksFeld[5][5] = RubiksFeld[5][2];

		RubiksFeld[3][0] = RubiksFeld[3][9];
		RubiksFeld[3][1] = RubiksFeld[3][10];
		RubiksFeld[3][2] = RubiksFeld[3][11];
		RubiksFeld[4][0] = RubiksFeld[4][9];
		RubiksFeld[4][1] = RubiksFeld[4][10];
		RubiksFeld[4][2] = RubiksFeld[4][11];
		RubiksFeld[5][0] = RubiksFeld[5][9];
		RubiksFeld[5][1] = RubiksFeld[5][10];
		RubiksFeld[5][2] = RubiksFeld[5][11];

		RubiksFeld[3][9] = RubiksFeld[3][6];
		RubiksFeld[3][10] = RubiksFeld[3][7];
		RubiksFeld[3][11] = RubiksFeld[3][8];
		RubiksFeld[4][9] = RubiksFeld[4][6];
		RubiksFeld[4][10] = RubiksFeld[4][7];
		RubiksFeld[4][11] = RubiksFeld[4][8];
		RubiksFeld[5][9] = RubiksFeld[5][6];
		RubiksFeld[5][10] = RubiksFeld[5][7];
		RubiksFeld[5][11] = RubiksFeld[5][8];

		RubiksFeld[3][6] = Temp_1; 
		RubiksFeld[3][7] = Temp_2; 
		RubiksFeld[3][8] = Temp_3; 
		RubiksFeld[4][6] = Temp_4; 
		RubiksFeld[4][7] = Temp_5; 
		RubiksFeld[4][8] = Temp_6; 
		RubiksFeld[5][6] = Temp_7; 
		RubiksFeld[5][7] = Temp_8; 
		RubiksFeld[5][8] = Temp_9;

		//vorne
		Temp_1 = RubiksFeld[2][3];
		Temp_2 = RubiksFeld[2][4];

		RubiksFeld[2][3] = RubiksFeld[0][3];
		RubiksFeld[2][4] = RubiksFeld[1][3];

		RubiksFeld[0][3] = RubiksFeld[0][5];
		RubiksFeld[1][3] = RubiksFeld[0][4];

		RubiksFeld[0][5] = RubiksFeld[2][5];
		RubiksFeld[0][4] = RubiksFeld[1][5];

		RubiksFeld[2][5] = Temp_1;
		RubiksFeld[1][5] = Temp_2;

		//hinten
		Temp_1 = RubiksFeld[6][3];
		Temp_2 = RubiksFeld[6][4];

		RubiksFeld[6][3] = RubiksFeld[8][3];
		RubiksFeld[6][4] = RubiksFeld[7][3];

		RubiksFeld[8][3] = RubiksFeld[8][5];
		RubiksFeld[7][3] = RubiksFeld[8][4];

		RubiksFeld[8][5] = RubiksFeld[6][5];
		RubiksFeld[8][4] = RubiksFeld[7][5];

		RubiksFeld[6][5] = Temp_1; 
		RubiksFeld[7][5] = Temp_2;

		R_Wechsel = R_Wechsel + 65; R_Zuege++;
	}


//dreht ganzer würfel 90' von oben gesehen nach links
void R_MoveFullCube_left(void)
	{
		Temp_1 = RubiksFeld[3][3];
		Temp_2 = RubiksFeld[3][4];
		Temp_3 = RubiksFeld[3][5];
		Temp_4 = RubiksFeld[4][3];
		Temp_5 = RubiksFeld[4][4];
		Temp_6 = RubiksFeld[4][5];
		Temp_7 = RubiksFeld[5][3];
		Temp_8 = RubiksFeld[5][4];
		Temp_9 = RubiksFeld[5][5];

		RubiksFeld[3][3] = RubiksFeld[3][6];
		RubiksFeld[3][4] = RubiksFeld[3][7];
		RubiksFeld[3][5] = RubiksFeld[3][8];
		RubiksFeld[4][3] = RubiksFeld[4][6];
		RubiksFeld[4][4] = RubiksFeld[4][7]; 
		RubiksFeld[4][5] = RubiksFeld[4][8];
		RubiksFeld[5][3] = RubiksFeld[5][6];
		RubiksFeld[5][4] = RubiksFeld[5][7];
		RubiksFeld[5][5] = RubiksFeld[5][8];

		RubiksFeld[3][6] = RubiksFeld[3][9];
		RubiksFeld[3][7] = RubiksFeld[3][10];
		RubiksFeld[3][8] = RubiksFeld[3][11];
		RubiksFeld[4][6] = RubiksFeld[4][9];
		RubiksFeld[4][7] = RubiksFeld[4][10];
		RubiksFeld[4][8] = RubiksFeld[4][11];
		RubiksFeld[5][6] = RubiksFeld[5][9];
		RubiksFeld[5][7] = RubiksFeld[5][10];
		RubiksFeld[5][8] = RubiksFeld[5][11];

		RubiksFeld[3][9]  = RubiksFeld[3][0];
		RubiksFeld[3][10] = RubiksFeld[3][1];
		RubiksFeld[3][11] = RubiksFeld[3][2];
		RubiksFeld[4][9]  = RubiksFeld[4][0];
		RubiksFeld[4][10] = RubiksFeld[4][1];
		RubiksFeld[4][11] = RubiksFeld[4][2];
		RubiksFeld[5][9]  = RubiksFeld[5][0];
		RubiksFeld[5][10] = RubiksFeld[5][1];
		RubiksFeld[5][11] = RubiksFeld[5][2];

		RubiksFeld[3][0] = Temp_1; 
		RubiksFeld[3][1] = Temp_2; 
		RubiksFeld[3][2] = Temp_3; 
		RubiksFeld[4][0] = Temp_4; 
		RubiksFeld[4][1] = Temp_5; 
		RubiksFeld[4][2] = Temp_6; 
		RubiksFeld[5][0] = Temp_7; 
		RubiksFeld[5][1] = Temp_8; 
		RubiksFeld[5][2] = Temp_9;

		Temp_1 = RubiksFeld[2][3];
		Temp_2 = RubiksFeld[2][4];

		RubiksFeld[2][3] = RubiksFeld[2][5];
		RubiksFeld[2][4] = RubiksFeld[1][5];

		RubiksFeld[2][5] = RubiksFeld[0][5];
		RubiksFeld[1][5] = RubiksFeld[0][4];

		RubiksFeld[0][5] = RubiksFeld[0][3];
		RubiksFeld[0][4] = RubiksFeld[1][3];

		RubiksFeld[0][3] = Temp_1; 
		RubiksFeld[1][3] = Temp_2; 


		Temp_1 = RubiksFeld[6][3];
		Temp_2 = RubiksFeld[6][4];

		RubiksFeld[6][3] = RubiksFeld[6][5];
		RubiksFeld[6][4] = RubiksFeld[7][5];

		RubiksFeld[6][5] = RubiksFeld[8][5];
		RubiksFeld[7][5] = RubiksFeld[8][4];

		RubiksFeld[8][5] = RubiksFeld[8][3];
		RubiksFeld[8][4] = RubiksFeld[7][3];

		RubiksFeld[8][3] = Temp_1; 
		RubiksFeld[7][3] = Temp_2; 

		R_Wechsel = R_Wechsel + 65; R_Zuege++;
	}

//dreht ganzer würfel 90' von oben gesehen nach oben
void R_MoveFullCube_up(void)
	{
		Temp_1 = RubiksFeld[3][3];
		Temp_2 = RubiksFeld[3][4];
		Temp_3 = RubiksFeld[3][5];
		Temp_4 = RubiksFeld[4][3];
		Temp_5 = RubiksFeld[4][4];
		Temp_6 = RubiksFeld[4][5];
		Temp_7 = RubiksFeld[5][3];
		Temp_8 = RubiksFeld[5][4];
		Temp_9 = RubiksFeld[5][5];

		RubiksFeld[3][3] = RubiksFeld[6][3];
		RubiksFeld[3][4] = RubiksFeld[6][4];
		RubiksFeld[3][5] = RubiksFeld[6][5];
		RubiksFeld[4][3] = RubiksFeld[7][3];
		RubiksFeld[4][4] = RubiksFeld[7][4];
		RubiksFeld[4][5] = RubiksFeld[7][5];
		RubiksFeld[5][3] = RubiksFeld[8][3];
		RubiksFeld[5][4] = RubiksFeld[8][4];
		RubiksFeld[5][5] = RubiksFeld[8][5];

		RubiksFeld[6][3] = RubiksFeld[5][11];
		RubiksFeld[6][4] = RubiksFeld[5][10];
		RubiksFeld[6][5] = RubiksFeld[5][9];
		RubiksFeld[7][3] = RubiksFeld[4][11];
		RubiksFeld[7][4] = RubiksFeld[4][10];
		RubiksFeld[7][5] = RubiksFeld[4][9];
		RubiksFeld[8][3] = RubiksFeld[3][11];
		RubiksFeld[8][4] = RubiksFeld[3][10];
		RubiksFeld[8][5] = RubiksFeld[3][9];

		RubiksFeld[5][11] = RubiksFeld[0][3];
		RubiksFeld[5][10] = RubiksFeld[0][4];
		RubiksFeld[5][9]  = RubiksFeld[0][5];
		RubiksFeld[4][11] = RubiksFeld[1][3];
		RubiksFeld[4][10] = RubiksFeld[1][4];
		RubiksFeld[4][9]  = RubiksFeld[1][5];
		RubiksFeld[3][11] = RubiksFeld[2][3];
		RubiksFeld[3][10] = RubiksFeld[2][4];
		RubiksFeld[3][9]  = RubiksFeld[2][5];

		RubiksFeld[0][3] = Temp_1; 
		RubiksFeld[0][4] = Temp_2; 
		RubiksFeld[0][5] = Temp_3; 
		RubiksFeld[1][3] = Temp_4; 
		RubiksFeld[1][4] = Temp_5; 
		RubiksFeld[1][5] = Temp_6; 
		RubiksFeld[2][3] = Temp_7; 
		RubiksFeld[2][4] = Temp_8; 
		RubiksFeld[2][5] = Temp_9;

		Temp_1 = RubiksFeld[3][6];
		Temp_2 = RubiksFeld[4][6];

		RubiksFeld[3][6] = RubiksFeld[5][6];
		RubiksFeld[4][6] = RubiksFeld[5][7];

		RubiksFeld[5][6] = RubiksFeld[5][8];
		RubiksFeld[5][7] = RubiksFeld[4][8];

		RubiksFeld[5][8] = RubiksFeld[3][8];
		RubiksFeld[4][8] = RubiksFeld[3][7];

		RubiksFeld[3][8] = Temp_1; 
		RubiksFeld[3][7] = Temp_2; 


		Temp_1 = RubiksFeld[3][2];
		Temp_2 = RubiksFeld[4][2];

		RubiksFeld[3][2] = RubiksFeld[5][2];
		RubiksFeld[4][2] = RubiksFeld[5][1];

		RubiksFeld[5][2] = RubiksFeld[5][0];
		RubiksFeld[5][1] = RubiksFeld[4][0];

		RubiksFeld[5][0] = RubiksFeld[3][0];
		RubiksFeld[4][0] = RubiksFeld[3][1];

		RubiksFeld[3][0] = Temp_1; 
		RubiksFeld[3][1] = Temp_2; 

		R_Wechsel = R_Wechsel + 65; R_Zuege++;
	}

//dreht ganzer würfel 90' von oben gesehen nach unten
void R_MoveFullCube_down(void)
	{
		Temp_1 = RubiksFeld[3][3];
		Temp_2 = RubiksFeld[3][4];
		Temp_3 = RubiksFeld[3][5];
		Temp_4 = RubiksFeld[4][3];
		Temp_5 = RubiksFeld[4][4];
		Temp_6 = RubiksFeld[4][5];
		Temp_7 = RubiksFeld[5][3];
		Temp_8 = RubiksFeld[5][4];
		Temp_9 = RubiksFeld[5][5];

		RubiksFeld[3][3] = RubiksFeld[0][3];
		RubiksFeld[3][4] = RubiksFeld[0][4];
		RubiksFeld[3][5] = RubiksFeld[0][5];
		RubiksFeld[4][3] = RubiksFeld[1][3];
		RubiksFeld[4][4] = RubiksFeld[1][4];
		RubiksFeld[4][5] = RubiksFeld[1][5];
		RubiksFeld[5][3] = RubiksFeld[2][3];
		RubiksFeld[5][4] = RubiksFeld[2][4];
		RubiksFeld[5][5] = RubiksFeld[2][5];

		RubiksFeld[0][3] = RubiksFeld[5][11];
		RubiksFeld[0][4] = RubiksFeld[5][10];
		RubiksFeld[0][5] = RubiksFeld[5][9];
		RubiksFeld[1][3] = RubiksFeld[4][11];
		RubiksFeld[1][4] = RubiksFeld[4][10];
		RubiksFeld[1][5] = RubiksFeld[4][9];
		RubiksFeld[2][3] = RubiksFeld[3][11];
		RubiksFeld[2][4] = RubiksFeld[3][10];
		RubiksFeld[2][5] = RubiksFeld[3][9];

		RubiksFeld[5][11] = RubiksFeld[6][3];
		RubiksFeld[5][10] = RubiksFeld[6][4];
		RubiksFeld[5][9]  = RubiksFeld[6][5];
		RubiksFeld[4][11] = RubiksFeld[7][3];
		RubiksFeld[4][10] = RubiksFeld[7][4];
		RubiksFeld[4][9]  = RubiksFeld[7][5];
		RubiksFeld[3][11] = RubiksFeld[8][3];
		RubiksFeld[3][10] = RubiksFeld[8][4];
		RubiksFeld[3][9]  = RubiksFeld[8][5];

		RubiksFeld[6][3] = Temp_1; 
		RubiksFeld[6][4] = Temp_2; 
		RubiksFeld[6][5] = Temp_3; 
		RubiksFeld[7][3] = Temp_4; 
		RubiksFeld[7][4] = Temp_5; 
		RubiksFeld[7][5] = Temp_6; 
		RubiksFeld[8][3] = Temp_7; 
		RubiksFeld[8][4] = Temp_8; 
		RubiksFeld[8][5] = Temp_9;

		Temp_1 = RubiksFeld[3][6];
		Temp_2 = RubiksFeld[4][6];

		RubiksFeld[3][6] = RubiksFeld[3][8];
		RubiksFeld[4][6] = RubiksFeld[3][7];

		RubiksFeld[3][8] = RubiksFeld[5][8];
		RubiksFeld[3][7] = RubiksFeld[4][8];

		RubiksFeld[5][8] = RubiksFeld[5][6];
		RubiksFeld[4][8] = RubiksFeld[5][7];

		RubiksFeld[5][6] = Temp_1; 
		RubiksFeld[5][7] = Temp_2; 


		Temp_1 = RubiksFeld[3][2];
		Temp_2 = RubiksFeld[4][2];

		RubiksFeld[3][2] = RubiksFeld[3][0];
		RubiksFeld[4][2] = RubiksFeld[3][1];

		RubiksFeld[3][0] = RubiksFeld[5][0];
		RubiksFeld[3][1] = RubiksFeld[4][0];

		RubiksFeld[5][0] = RubiksFeld[5][2];
		RubiksFeld[4][0] = RubiksFeld[5][1];

		RubiksFeld[5][2] = Temp_1; 
		RubiksFeld[5][1] = Temp_2; 

		R_Wechsel = R_Wechsel + 65; R_Zuege++;
	}
//drhet den würfel oben in uhrzeigerrichtung
void R_MoveFullCube_Clock(void)
	{
		Temp_1 = RubiksFeld[6][3];
		Temp_2 = RubiksFeld[6][4];
		Temp_3 = RubiksFeld[6][5];
		Temp_4 = RubiksFeld[7][3];
		Temp_5 = RubiksFeld[7][4];
		Temp_6 = RubiksFeld[7][5];
		Temp_7 = RubiksFeld[8][3];
		Temp_8 = RubiksFeld[8][4];
		Temp_9 = RubiksFeld[8][5];

		RubiksFeld[6][3] = RubiksFeld[5][6];
		RubiksFeld[6][4] = RubiksFeld[4][6];
		RubiksFeld[6][5] = RubiksFeld[3][6];
		RubiksFeld[7][3] = RubiksFeld[5][7];
		RubiksFeld[7][4] = RubiksFeld[4][7];
		RubiksFeld[7][5] = RubiksFeld[3][7];
		RubiksFeld[8][3] = RubiksFeld[5][8];
		RubiksFeld[8][4] = RubiksFeld[4][8];
		RubiksFeld[8][5] = RubiksFeld[3][8];

		RubiksFeld[5][6] = RubiksFeld[2][5];
		RubiksFeld[4][6] = RubiksFeld[2][4];
		RubiksFeld[3][6] = RubiksFeld[2][3];
		RubiksFeld[5][7] = RubiksFeld[1][5];
		RubiksFeld[4][7] = RubiksFeld[1][4];
		RubiksFeld[3][7] = RubiksFeld[1][3];
		RubiksFeld[5][8] = RubiksFeld[0][5];
		RubiksFeld[4][8] = RubiksFeld[0][4];
		RubiksFeld[3][8] = RubiksFeld[0][3];

		RubiksFeld[2][5] = RubiksFeld[3][2];
		RubiksFeld[2][4] = RubiksFeld[4][2];
		RubiksFeld[2][3] = RubiksFeld[5][2];
		RubiksFeld[1][5] = RubiksFeld[3][1];
		RubiksFeld[1][4] = RubiksFeld[4][1];
		RubiksFeld[1][3] = RubiksFeld[5][1];
		RubiksFeld[0][5] = RubiksFeld[3][0];
		RubiksFeld[0][4] = RubiksFeld[4][0];
		RubiksFeld[0][3] = RubiksFeld[5][0];

		RubiksFeld[3][2] = Temp_1; 
		RubiksFeld[4][2] = Temp_2; 
		RubiksFeld[5][2] = Temp_3; 
		RubiksFeld[3][1] = Temp_4; 
		RubiksFeld[4][1] = Temp_5; 
		RubiksFeld[5][1] = Temp_6; 
		RubiksFeld[3][0] = Temp_7; 
		RubiksFeld[4][0] = Temp_8; 
		RubiksFeld[5][0] = Temp_9;

		Temp_1 = RubiksFeld[3][5];
		Temp_2 = RubiksFeld[4][5];

		RubiksFeld[3][5] = RubiksFeld[3][3];
		RubiksFeld[4][5] = RubiksFeld[3][4];

		RubiksFeld[3][3] = RubiksFeld[5][3];
		RubiksFeld[3][4] = RubiksFeld[4][3];

		RubiksFeld[5][3] = RubiksFeld[5][5];
		RubiksFeld[4][3] = RubiksFeld[5][4];

		RubiksFeld[5][5] = Temp_1; 
		RubiksFeld[5][4] = Temp_2; 


		Temp_1 = RubiksFeld[3][11];
		Temp_2 = RubiksFeld[4][11];

		RubiksFeld[3][11] = RubiksFeld[5][11];
		RubiksFeld[4][11] = RubiksFeld[5][10];

		RubiksFeld[5][11] = RubiksFeld[5][9];
		RubiksFeld[5][10] = RubiksFeld[4][9];

		RubiksFeld[5][9]  = RubiksFeld[3][9];
		RubiksFeld[4][9]  = RubiksFeld[3][10];

		RubiksFeld[3][9]  = Temp_1; 
		RubiksFeld[3][10] = Temp_2; 

		R_Wechsel = R_Wechsel + 65; R_Zuege++;
	}
//drhet den würfel oben gegen den uhrzeigerrichtung
void R_MoveFullCube_NotClock(void)
	{
		Temp_1 = RubiksFeld[6][3];
		Temp_2 = RubiksFeld[6][4];
		Temp_3 = RubiksFeld[6][5];
		Temp_4 = RubiksFeld[7][3];
		Temp_5 = RubiksFeld[7][4];
		Temp_6 = RubiksFeld[7][5];
		Temp_7 = RubiksFeld[8][3];
		Temp_8 = RubiksFeld[8][4];
		Temp_9 = RubiksFeld[8][5];

		RubiksFeld[6][3] = RubiksFeld[3][2];
		RubiksFeld[6][4] = RubiksFeld[4][2];
		RubiksFeld[6][5] = RubiksFeld[5][2];
		RubiksFeld[7][3] = RubiksFeld[3][1];
		RubiksFeld[7][4] = RubiksFeld[4][1];
		RubiksFeld[7][5] = RubiksFeld[5][1];
		RubiksFeld[8][3] = RubiksFeld[3][0];
		RubiksFeld[8][4] = RubiksFeld[4][0];
		RubiksFeld[8][5] = RubiksFeld[5][0];

		RubiksFeld[3][2] = RubiksFeld[2][5];
		RubiksFeld[4][2] = RubiksFeld[2][4];
		RubiksFeld[5][2] = RubiksFeld[2][3];
		RubiksFeld[3][1] = RubiksFeld[1][5];
		RubiksFeld[4][1] = RubiksFeld[1][4];
		RubiksFeld[5][1] = RubiksFeld[1][3];
		RubiksFeld[3][0] = RubiksFeld[0][5];
		RubiksFeld[4][0] = RubiksFeld[0][4];
		RubiksFeld[5][0] = RubiksFeld[0][3];

		RubiksFeld[2][5] = RubiksFeld[5][6];
		RubiksFeld[2][4] = RubiksFeld[4][6];
		RubiksFeld[2][3] = RubiksFeld[3][6];
		RubiksFeld[1][5] = RubiksFeld[5][7];
		RubiksFeld[1][4] = RubiksFeld[4][7];
		RubiksFeld[1][3] = RubiksFeld[3][7];
		RubiksFeld[0][5] = RubiksFeld[5][8];
		RubiksFeld[0][4] = RubiksFeld[4][8];
		RubiksFeld[0][3] = RubiksFeld[3][8];

		RubiksFeld[5][6] = Temp_1; 
		RubiksFeld[4][6] = Temp_2; 
		RubiksFeld[3][6] = Temp_3; 
		RubiksFeld[5][7] = Temp_4; 
		RubiksFeld[4][7] = Temp_5; 
		RubiksFeld[3][7] = Temp_6; 
		RubiksFeld[5][8] = Temp_7; 
		RubiksFeld[4][8] = Temp_8; 
		RubiksFeld[3][8] = Temp_9;

		Temp_1 = RubiksFeld[3][5];
		Temp_2 = RubiksFeld[4][5];

		RubiksFeld[3][5] = RubiksFeld[5][5];
		RubiksFeld[4][5] = RubiksFeld[5][4];

		RubiksFeld[5][5] = RubiksFeld[5][3];
		RubiksFeld[5][4] = RubiksFeld[4][3];

		RubiksFeld[5][3] = RubiksFeld[3][3];
		RubiksFeld[4][3] = RubiksFeld[3][4];

		RubiksFeld[3][3] = Temp_1; 
		RubiksFeld[3][4] = Temp_2; 


		Temp_1 = RubiksFeld[3][11];
		Temp_2 = RubiksFeld[4][11];

		RubiksFeld[3][11] = RubiksFeld[3][9];
		RubiksFeld[4][11] = RubiksFeld[3][10];

		RubiksFeld[3][9]  = RubiksFeld[5][9];
		RubiksFeld[3][10] = RubiksFeld[4][9];

		RubiksFeld[5][9] = RubiksFeld[5][11];
		RubiksFeld[4][9] = RubiksFeld[5][10];

		RubiksFeld[5][11] = Temp_1; 
		RubiksFeld[5][10] = Temp_2; 

		R_Wechsel = R_Wechsel + 65; R_Zuege++;
	}


//drgeht den zug R

void R_MoveCube_R(void)
	{
		Temp_1 = RubiksFeld[3][5];
		Temp_2 = RubiksFeld[4][5];
		Temp_3 = RubiksFeld[5][5];

		RubiksFeld[3][5] = RubiksFeld[6][5];
		RubiksFeld[4][5] = RubiksFeld[7][5];
		RubiksFeld[5][5] = RubiksFeld[8][5];

		RubiksFeld[6][5] = RubiksFeld[5][9];
		RubiksFeld[7][5] = RubiksFeld[4][9];
		RubiksFeld[8][5] = RubiksFeld[3][9];

		RubiksFeld[5][9] = RubiksFeld[0][5];
		RubiksFeld[4][9] = RubiksFeld[1][5];
		RubiksFeld[3][9] = RubiksFeld[2][5];

		RubiksFeld[0][5] = Temp_1;
		RubiksFeld[1][5] = Temp_2;
		RubiksFeld[2][5] = Temp_3;

		Temp_1 = RubiksFeld[3][6];
		Temp_2 = RubiksFeld[4][6];

		RubiksFeld[3][6] = RubiksFeld[5][6];
		RubiksFeld[4][6] = RubiksFeld[5][7];

		RubiksFeld[5][6] = RubiksFeld[5][8];
		RubiksFeld[5][7] = RubiksFeld[4][8];

		RubiksFeld[5][8] = RubiksFeld[3][8];
		RubiksFeld[4][8] = RubiksFeld[3][7];

		RubiksFeld[3][8] = Temp_1; 
		RubiksFeld[3][7] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug Ri
void R_MoveCube_Ri(void)
	{
		Temp_1 = RubiksFeld[3][5];
		Temp_2 = RubiksFeld[4][5];
		Temp_3 = RubiksFeld[5][5];

		RubiksFeld[3][5] = RubiksFeld[0][5];
		RubiksFeld[4][5] = RubiksFeld[1][5];
		RubiksFeld[5][5] = RubiksFeld[2][5];

		RubiksFeld[0][5] = RubiksFeld[5][9];
		RubiksFeld[1][5] = RubiksFeld[4][9];
		RubiksFeld[2][5] = RubiksFeld[3][9];

		RubiksFeld[5][9] = RubiksFeld[6][5];
		RubiksFeld[4][9] = RubiksFeld[7][5];
		RubiksFeld[3][9] = RubiksFeld[8][5];

		RubiksFeld[6][5] = Temp_1;
		RubiksFeld[7][5] = Temp_2;
		RubiksFeld[8][5] = Temp_3;

		Temp_1 = RubiksFeld[3][6];
		Temp_2 = RubiksFeld[4][6];

		RubiksFeld[3][6] = RubiksFeld[3][8];
		RubiksFeld[4][6] = RubiksFeld[3][7];

		RubiksFeld[3][8] = RubiksFeld[5][8];
		RubiksFeld[3][7] = RubiksFeld[4][8];

		RubiksFeld[5][8] = RubiksFeld[5][6];
		RubiksFeld[4][8] = RubiksFeld[5][7];

		RubiksFeld[5][6] = Temp_1; 
		RubiksFeld[5][7] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug L
void R_MoveCube_L(void)
	{
		Temp_1 = RubiksFeld[3][3];
		Temp_2 = RubiksFeld[4][3];
		Temp_3 = RubiksFeld[5][3];

		RubiksFeld[3][3] = RubiksFeld[0][3];
		RubiksFeld[4][3] = RubiksFeld[1][3];
		RubiksFeld[5][3] = RubiksFeld[2][3];

		RubiksFeld[0][3] = RubiksFeld[5][11];
		RubiksFeld[1][3] = RubiksFeld[4][11];
		RubiksFeld[2][3] = RubiksFeld[3][11];

		RubiksFeld[5][11] = RubiksFeld[6][3];
		RubiksFeld[4][11] = RubiksFeld[7][3];
		RubiksFeld[3][11] = RubiksFeld[8][3];

		RubiksFeld[6][3] = Temp_1;
		RubiksFeld[7][3] = Temp_2;
		RubiksFeld[8][3] = Temp_3;

		Temp_1 = RubiksFeld[3][2];
		Temp_2 = RubiksFeld[4][2];

		RubiksFeld[3][2] = RubiksFeld[3][0];
		RubiksFeld[4][2] = RubiksFeld[3][1];

		RubiksFeld[3][0] = RubiksFeld[5][0];
		RubiksFeld[3][1] = RubiksFeld[4][0];

		RubiksFeld[5][0] = RubiksFeld[5][2];
		RubiksFeld[4][0] = RubiksFeld[5][1];

		RubiksFeld[5][2] = Temp_1; 
		RubiksFeld[5][1] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug Li
void R_MoveCube_Li(void)
	{
		Temp_1 = RubiksFeld[3][3];
		Temp_2 = RubiksFeld[4][3];
		Temp_3 = RubiksFeld[5][3];

		RubiksFeld[3][3] = RubiksFeld[6][3];
		RubiksFeld[4][3] = RubiksFeld[7][3];
		RubiksFeld[5][3] = RubiksFeld[8][3];

		RubiksFeld[6][3] = RubiksFeld[5][11];
		RubiksFeld[7][3] = RubiksFeld[4][11];
		RubiksFeld[8][3] = RubiksFeld[3][11];

		RubiksFeld[5][11] = RubiksFeld[0][3];
		RubiksFeld[4][11] = RubiksFeld[1][3];
		RubiksFeld[3][11] = RubiksFeld[2][3];

		RubiksFeld[0][3] = Temp_1;
		RubiksFeld[1][3] = Temp_2;
		RubiksFeld[2][3] = Temp_3;

		Temp_1 = RubiksFeld[3][2];
		Temp_2 = RubiksFeld[4][2];

		RubiksFeld[3][2] = RubiksFeld[5][2];
		RubiksFeld[4][2] = RubiksFeld[5][1];

		RubiksFeld[5][2] = RubiksFeld[5][0];
		RubiksFeld[5][1] = RubiksFeld[4][0];

		RubiksFeld[5][0] = RubiksFeld[3][0];
		RubiksFeld[4][0] = RubiksFeld[3][1];

		RubiksFeld[3][0] = Temp_1; 
		RubiksFeld[3][1] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug U
void R_MoveCube_U(void)
	{
		Temp_1 = RubiksFeld[3][3];
		Temp_2 = RubiksFeld[3][4];
		Temp_3 = RubiksFeld[3][5];

		RubiksFeld[3][3] = RubiksFeld[3][6];
		RubiksFeld[3][4] = RubiksFeld[3][7];
		RubiksFeld[3][5] = RubiksFeld[3][8];

		RubiksFeld[3][6] = RubiksFeld[3][9];
		RubiksFeld[3][7] = RubiksFeld[3][10];
		RubiksFeld[3][8] = RubiksFeld[3][11];

		RubiksFeld[3][9]  = RubiksFeld[3][0];
		RubiksFeld[3][10] = RubiksFeld[3][1];
		RubiksFeld[3][11] = RubiksFeld[3][2];

		RubiksFeld[3][0] = Temp_1;
		RubiksFeld[3][1] = Temp_2;
		RubiksFeld[3][2] = Temp_3;

		Temp_1 = RubiksFeld[2][3];
		Temp_2 = RubiksFeld[2][4];

		RubiksFeld[2][3] = RubiksFeld[2][5];
		RubiksFeld[2][4] = RubiksFeld[1][5];

		RubiksFeld[2][5] = RubiksFeld[0][5];
		RubiksFeld[1][5] = RubiksFeld[0][4];

		RubiksFeld[0][5] = RubiksFeld[0][3];
		RubiksFeld[0][4] = RubiksFeld[1][3];

		RubiksFeld[0][3] = Temp_1; 
		RubiksFeld[1][3] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug Ui
void R_MoveCube_Ui(void)
	{
		Temp_1 = RubiksFeld[3][3];
		Temp_2 = RubiksFeld[3][4];
		Temp_3 = RubiksFeld[3][5];

		RubiksFeld[3][3] = RubiksFeld[3][0];
		RubiksFeld[3][4] = RubiksFeld[3][1];
		RubiksFeld[3][5] = RubiksFeld[3][2];

		RubiksFeld[3][0] = RubiksFeld[3][9];
		RubiksFeld[3][1] = RubiksFeld[3][10];
		RubiksFeld[3][2] = RubiksFeld[3][11];

		RubiksFeld[3][9]  = RubiksFeld[3][6];
		RubiksFeld[3][10] = RubiksFeld[3][7];
		RubiksFeld[3][11] = RubiksFeld[3][8];

		RubiksFeld[3][6] = Temp_1;
		RubiksFeld[3][7] = Temp_2;
		RubiksFeld[3][8] = Temp_3;

		Temp_1 = RubiksFeld[2][5];
		Temp_2 = RubiksFeld[2][4];

		RubiksFeld[2][5] = RubiksFeld[2][3];
		RubiksFeld[2][4] = RubiksFeld[1][3];

		RubiksFeld[2][3] = RubiksFeld[0][3];
		RubiksFeld[1][3] = RubiksFeld[0][4];

		RubiksFeld[0][3] = RubiksFeld[0][5];
		RubiksFeld[0][4] = RubiksFeld[1][5];

		RubiksFeld[0][5] = Temp_1; 
		RubiksFeld[1][5] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug D
void R_MoveCube_D(void)
	{
		Temp_1 = RubiksFeld[5][3];
		Temp_2 = RubiksFeld[5][4];
		Temp_3 = RubiksFeld[5][5];

		RubiksFeld[5][3] = RubiksFeld[5][0];
		RubiksFeld[5][4] = RubiksFeld[5][1];
		RubiksFeld[5][5] = RubiksFeld[5][2];

		RubiksFeld[5][0] = RubiksFeld[5][9];
		RubiksFeld[5][1] = RubiksFeld[5][10];
		RubiksFeld[5][2] = RubiksFeld[5][11];

		RubiksFeld[5][9]  = RubiksFeld[5][6];
		RubiksFeld[5][10] = RubiksFeld[5][7];
		RubiksFeld[5][11] = RubiksFeld[5][8];

		RubiksFeld[5][6] = Temp_1;
		RubiksFeld[5][7] = Temp_2;
		RubiksFeld[5][8] = Temp_3;

		Temp_1 = RubiksFeld[6][5];
		Temp_2 = RubiksFeld[6][4];

		RubiksFeld[6][5] = RubiksFeld[6][3];
		RubiksFeld[6][4] = RubiksFeld[7][3];

		RubiksFeld[6][3] = RubiksFeld[8][3];
		RubiksFeld[7][3] = RubiksFeld[8][4];

		RubiksFeld[8][3] = RubiksFeld[8][5];
		RubiksFeld[8][4] = RubiksFeld[7][5];

		RubiksFeld[8][5] = Temp_1; 
		RubiksFeld[7][5] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug Di
void R_MoveCube_Di(void)
	{
		Temp_1 = RubiksFeld[5][3];
		Temp_2 = RubiksFeld[5][4];
		Temp_3 = RubiksFeld[5][5];

		RubiksFeld[5][3] = RubiksFeld[5][6];
		RubiksFeld[5][4] = RubiksFeld[5][7];
		RubiksFeld[5][5] = RubiksFeld[5][8];

		RubiksFeld[5][6] = RubiksFeld[5][9];
		RubiksFeld[5][7] = RubiksFeld[5][10];
		RubiksFeld[5][8] = RubiksFeld[5][11];

		RubiksFeld[5][9]  = RubiksFeld[5][0];
		RubiksFeld[5][10] = RubiksFeld[5][1];
		RubiksFeld[5][11] = RubiksFeld[5][2];

		RubiksFeld[5][0] = Temp_1;
		RubiksFeld[5][1] = Temp_2;
		RubiksFeld[5][2] = Temp_3;

		Temp_1 = RubiksFeld[6][5];
		Temp_2 = RubiksFeld[6][4];

		RubiksFeld[6][5] = RubiksFeld[8][5];
		RubiksFeld[6][4] = RubiksFeld[7][5];

		RubiksFeld[8][5] = RubiksFeld[8][3];
		RubiksFeld[7][5] = RubiksFeld[8][4];

		RubiksFeld[8][3] = RubiksFeld[6][3];
		RubiksFeld[8][4] = RubiksFeld[7][3];

		RubiksFeld[6][3] = Temp_1; 
		RubiksFeld[7][3] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug F
void R_MoveCube_F(void)
	{
		Temp_1 = RubiksFeld[6][3];
		Temp_2 = RubiksFeld[6][4];
		Temp_3 = RubiksFeld[6][5];

		RubiksFeld[6][3] = RubiksFeld[5][6];
		RubiksFeld[6][4] = RubiksFeld[4][6];
		RubiksFeld[6][5] = RubiksFeld[3][6];

		RubiksFeld[5][6] = RubiksFeld[2][5];
		RubiksFeld[4][6] = RubiksFeld[2][4];
		RubiksFeld[3][6] = RubiksFeld[2][3];

		RubiksFeld[2][5] = RubiksFeld[3][2];
		RubiksFeld[2][4] = RubiksFeld[4][2];
		RubiksFeld[2][3] = RubiksFeld[5][2];

		RubiksFeld[3][2] = Temp_1;
		RubiksFeld[4][2] = Temp_2;
		RubiksFeld[5][2] = Temp_3;

		Temp_1 = RubiksFeld[3][5];
		Temp_2 = RubiksFeld[3][4];

		RubiksFeld[3][5] = RubiksFeld[3][3];
		RubiksFeld[3][4] = RubiksFeld[4][3];

		RubiksFeld[3][3] = RubiksFeld[5][3];
		RubiksFeld[4][3] = RubiksFeld[5][4];

		RubiksFeld[5][3] = RubiksFeld[5][5];
		RubiksFeld[5][4] = RubiksFeld[4][5];

		RubiksFeld[5][5] = Temp_1; 
		RubiksFeld[4][5] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug Fi
void R_MoveCube_Fi(void)
	{
		Temp_1 = RubiksFeld[6][3];
		Temp_2 = RubiksFeld[6][4];
		Temp_3 = RubiksFeld[6][5];

		RubiksFeld[6][3] = RubiksFeld[3][2];
		RubiksFeld[6][4] = RubiksFeld[4][2];
		RubiksFeld[6][5] = RubiksFeld[5][2];

		RubiksFeld[3][2] = RubiksFeld[2][5];
		RubiksFeld[4][2] = RubiksFeld[2][4];
		RubiksFeld[5][2] = RubiksFeld[2][3];

		RubiksFeld[2][5] = RubiksFeld[5][6];
		RubiksFeld[2][4] = RubiksFeld[4][6];
		RubiksFeld[2][3] = RubiksFeld[3][6];

		RubiksFeld[5][6] = Temp_1;
		RubiksFeld[4][6] = Temp_2;
		RubiksFeld[3][6] = Temp_3;

		Temp_1 = RubiksFeld[5][5];
		Temp_2 = RubiksFeld[5][4];

		RubiksFeld[5][5] = RubiksFeld[5][3];
		RubiksFeld[5][4] = RubiksFeld[4][3];

		RubiksFeld[5][3] = RubiksFeld[3][3];
		RubiksFeld[4][3] = RubiksFeld[3][4];

		RubiksFeld[3][3] = RubiksFeld[3][5];
		RubiksFeld[3][4] = RubiksFeld[4][5];

		RubiksFeld[3][5] = Temp_1; 
		RubiksFeld[4][5] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug B
void R_MoveCube_B(void)
	{
		Temp_1 = RubiksFeld[8][3];
		Temp_2 = RubiksFeld[8][4];
		Temp_3 = RubiksFeld[8][5];

		RubiksFeld[8][3] = RubiksFeld[3][0];
		RubiksFeld[8][4] = RubiksFeld[4][0];
		RubiksFeld[8][5] = RubiksFeld[5][0];

		RubiksFeld[3][0] = RubiksFeld[0][5];
		RubiksFeld[4][0] = RubiksFeld[0][4];
		RubiksFeld[5][0] = RubiksFeld[0][3];

		RubiksFeld[0][5] = RubiksFeld[5][8];
		RubiksFeld[0][4] = RubiksFeld[4][8];
		RubiksFeld[0][3] = RubiksFeld[3][8];

		RubiksFeld[5][8] = Temp_1;
		RubiksFeld[4][8] = Temp_2;
		RubiksFeld[3][8] = Temp_3;

		Temp_1 = RubiksFeld[5][9];
		Temp_2 = RubiksFeld[4][9];

		RubiksFeld[5][9] = RubiksFeld[5][11];
		RubiksFeld[4][9] = RubiksFeld[5][10];

		RubiksFeld[5][11] = RubiksFeld[3][11];
		RubiksFeld[5][10] = RubiksFeld[4][11];

		RubiksFeld[3][11] = RubiksFeld[3][9];
		RubiksFeld[4][11] = RubiksFeld[3][10];

		RubiksFeld[3][9]  = Temp_1; 
		RubiksFeld[3][10] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug Bi
void R_MoveCube_Bi(void)
	{
		Temp_1 = RubiksFeld[8][5];
		Temp_2 = RubiksFeld[8][4];
		Temp_3 = RubiksFeld[8][3];

		RubiksFeld[8][5] = RubiksFeld[3][8];
		RubiksFeld[8][4] = RubiksFeld[4][8];
		RubiksFeld[8][3] = RubiksFeld[5][8];

		RubiksFeld[3][8] = RubiksFeld[0][3];
		RubiksFeld[4][8] = RubiksFeld[0][4];
		RubiksFeld[5][8] = RubiksFeld[0][5];

		RubiksFeld[0][3] = RubiksFeld[5][0];
		RubiksFeld[0][4] = RubiksFeld[4][0];
		RubiksFeld[0][5] = RubiksFeld[3][0];

		RubiksFeld[5][0] = Temp_1;
		RubiksFeld[4][0] = Temp_2;
		RubiksFeld[3][0] = Temp_3;

		Temp_1 = RubiksFeld[5][11];
		Temp_2 = RubiksFeld[5][10];

		RubiksFeld[5][11] = RubiksFeld[5][9];
		RubiksFeld[5][10] = RubiksFeld[4][9];

		RubiksFeld[5][9] = RubiksFeld[3][9];
		RubiksFeld[4][9] = RubiksFeld[3][10];

		RubiksFeld[3][9]  = RubiksFeld[3][11];
		RubiksFeld[3][10] = RubiksFeld[4][11];

		RubiksFeld[3][11] = Temp_1; 
		RubiksFeld[4][11] = Temp_2; 

		R_Wechsel = R_Wechsel + 25; R_Zuege++;
	}
//drgeht den zug M
void R_MoveCube_M(void)
	{
		Temp_1 = RubiksFeld[3][4];
		Temp_2 = RubiksFeld[4][4];
		Temp_3 = RubiksFeld[5][4];

		RubiksFeld[3][4] = RubiksFeld[0][4];
		RubiksFeld[4][4] = RubiksFeld[1][4];
		RubiksFeld[5][4] = RubiksFeld[2][4];

		RubiksFeld[0][4] = RubiksFeld[5][10];
		RubiksFeld[1][4] = RubiksFeld[4][10];
		RubiksFeld[2][4] = RubiksFeld[3][10];

		RubiksFeld[5][10] = RubiksFeld[6][4];
		RubiksFeld[4][10] = RubiksFeld[7][4];
		RubiksFeld[3][10] = RubiksFeld[8][4];

		RubiksFeld[6][4] = Temp_1;
		RubiksFeld[7][4] = Temp_2;
		RubiksFeld[8][4] = Temp_3;

		R_Wechsel = R_Wechsel + 15; R_Zuege++;
	}
//drgeht den zug Mi
void R_MoveCube_Mi(void)
	{
		Temp_1 = RubiksFeld[3][4];
		Temp_2 = RubiksFeld[4][4];
		Temp_3 = RubiksFeld[5][4];

		RubiksFeld[3][4] = RubiksFeld[6][4];
		RubiksFeld[4][4] = RubiksFeld[7][4];
		RubiksFeld[5][4] = RubiksFeld[8][4];

		RubiksFeld[6][4] = RubiksFeld[5][10];
		RubiksFeld[7][4] = RubiksFeld[4][10];
		RubiksFeld[8][4] = RubiksFeld[3][10];

		RubiksFeld[5][10] = RubiksFeld[0][4];
		RubiksFeld[4][10] = RubiksFeld[1][4];
		RubiksFeld[3][10] = RubiksFeld[2][4];

		RubiksFeld[0][4] = Temp_1;
		RubiksFeld[1][4] = Temp_2;
		RubiksFeld[2][4] = Temp_3;

		R_Wechsel = R_Wechsel + 15; R_Zuege++;
	}
//drgeht den zug S
void R_MoveCube_S(void)
	{
		Temp_1 = RubiksFeld[7][5];
		Temp_2 = RubiksFeld[7][4];
		Temp_3 = RubiksFeld[7][3];

		RubiksFeld[7][5] = RubiksFeld[3][7];
		RubiksFeld[7][4] = RubiksFeld[4][7];
		RubiksFeld[7][3] = RubiksFeld[5][7];

		RubiksFeld[3][7] = RubiksFeld[1][3];
		RubiksFeld[4][7] = RubiksFeld[1][4];
		RubiksFeld[5][7] = RubiksFeld[1][5];

		RubiksFeld[1][3] = RubiksFeld[5][1];
		RubiksFeld[1][4] = RubiksFeld[4][1];
		RubiksFeld[1][5] = RubiksFeld[3][1];

		RubiksFeld[5][1] = Temp_1;
		RubiksFeld[4][1] = Temp_2;
		RubiksFeld[3][1] = Temp_3;

		R_Wechsel = R_Wechsel + 15; R_Zuege++;
	}
//drgeht den zug Si
void R_MoveCube_Si(void)
	{
		Temp_1 = RubiksFeld[7][5];
		Temp_2 = RubiksFeld[7][4];
		Temp_3 = RubiksFeld[7][3];

		RubiksFeld[7][5] = RubiksFeld[5][1];
		RubiksFeld[7][4] = RubiksFeld[4][1];
		RubiksFeld[7][3] = RubiksFeld[3][1];

		RubiksFeld[5][1] = RubiksFeld[1][3];
		RubiksFeld[4][1] = RubiksFeld[1][4];
		RubiksFeld[3][1] = RubiksFeld[1][5];

		RubiksFeld[1][3] = RubiksFeld[3][7];
		RubiksFeld[1][4] = RubiksFeld[4][7];
		RubiksFeld[1][5] = RubiksFeld[5][7];

		RubiksFeld[3][7] = Temp_1;
		RubiksFeld[4][7] = Temp_2;
		RubiksFeld[5][7] = Temp_3; 

		R_Wechsel = R_Wechsel + 15; R_Zuege++;
	}
//drgeht den zug E
void R_MoveCube_E(void)
	{
		Temp_1 = RubiksFeld[4][0];
		Temp_2 = RubiksFeld[4][1];
		Temp_3 = RubiksFeld[4][2];

		RubiksFeld[4][0] = RubiksFeld[4][9];
		RubiksFeld[4][1] = RubiksFeld[4][10];
		RubiksFeld[4][2] = RubiksFeld[4][11];

		RubiksFeld[4][9]  = RubiksFeld[4][6];
		RubiksFeld[4][10] = RubiksFeld[4][7];
		RubiksFeld[4][11] = RubiksFeld[4][8];

		RubiksFeld[4][6] = RubiksFeld[4][3];
		RubiksFeld[4][7] = RubiksFeld[4][4];
		RubiksFeld[4][8] = RubiksFeld[4][5];

		RubiksFeld[4][3] = Temp_1;
		RubiksFeld[4][4] = Temp_2;
		RubiksFeld[4][5] = Temp_3;

		R_Wechsel = R_Wechsel + 15; R_Zuege++;
	}
//drgeht den zug Ei
void R_MoveCube_Ei(void)
	{
		Temp_1 = RubiksFeld[4][0];
		Temp_2 = RubiksFeld[4][1];
		Temp_3 = RubiksFeld[4][2];

		RubiksFeld[4][0] = RubiksFeld[4][3];
		RubiksFeld[4][1] = RubiksFeld[4][4];
		RubiksFeld[4][2] = RubiksFeld[4][5];

		RubiksFeld[4][3] = RubiksFeld[4][6];
		RubiksFeld[4][4] = RubiksFeld[4][7];
		RubiksFeld[4][5] = RubiksFeld[4][8];

		RubiksFeld[4][6] = RubiksFeld[4][9];
		RubiksFeld[4][7] = RubiksFeld[4][10];
		RubiksFeld[4][8] = RubiksFeld[4][11];

		RubiksFeld[4][9]  = Temp_1;
		RubiksFeld[4][10] = Temp_2;
		RubiksFeld[4][11] = Temp_3;

		R_Wechsel = R_Wechsel + 15; R_Zuege++;
	}

