#include "funktionen.h"

void int32_enalbe_gm_0x12()
  {
    regs16_t regs;
      regs.ax = 0x0012;
      int32(0x10, &regs);
  }

void int32_enalbe_gm_0x13()
	{
		regs16_t regs;
    	regs.ax = 0x0013;
    	int32(0x10, &regs);
	}



void int32_disable_gm()
	{
		regs16_t regs;
    	regs.ax = 0x0003;
    	int32(0x10, &regs);
	}

void int32_clear_screen_0x13(char farbe)
	{
		k_memset((char *)0xA0000, farbe, (320*200));
	}

void int32_clear_screen_0x12(char farbe)
  {
    //http://webpages.charter.net/danrollins/techhelp/0089.HTM
    char Plane0, Plane1, Plane2, Plane3;


    if((farbe & 0x1) == 0x1){Plane0 = 0xFF;}
      else{Plane0 = 0x00;}

    if((farbe & 0x2) == 0x2){Plane1 = 0xFF;}
      else{Plane1 = 0x00;}

    if((farbe & 0x4) == 0x4){Plane2 = 0xFF;}
      else{Plane2 = 0x00;}

    if((farbe & 0x8) == 0x8){Plane3 = 0xFF;}
      else{Plane3 = 0x00;}

        outportw(0x3CE,0x0005);//setup plane masking
        outportw(0x3c4,0x0102);//plane 0
        k_memset((char*) 0xA0000,Plane0,38400);
        outportw(0x3c4,0x0202);//plane 1
        k_memset((char*) 0xA0000,Plane1,38400);
        outportw(0x3c4,0x0402);//plane 2
        k_memset((char*) 0xA0000,Plane2,38400);
        outportw(0x3c4,0x0802);//plane 3
        k_memset((char*) 0xA0000,Plane3,38400);
        outportw(0x3c4,0x0F02);//restore normal plane mask
  }

void int32_setpixel_0x12(int x, int y, char farbe)
  {
    char Plane0[2];
    char Plane1[2];
    char Plane2[2];
    char Plane3[2];
    int getPosPixel = (y*640) + x;//wieviele pixel von oben links gesehen
    int BytePos = getPosPixel /8;//welches byte anwählen
    int modulo = getPosPixel % 8;//welches bit im byte anwählen

    char* vidmem = (char*) 0xA0000;

    //holle byte das verändert werden muss(4x wegen planes)
    outportw(0x3CE,0x0005);//setup plane masking
    outportw(0x3c4,0x0102);//plane 0
    outportw(0x3c4,0x0F02);//restore normal plane mask
    k_memcpy(Plane0,(vidmem + BytePos), 1);
    outportw(0x3CE,0x0005);//setup plane masking
    outportw(0x3c4,0x0202);//plane 1
    outportw(0x3c4,0x0F02);//restore normal plane mask
    k_memcpy(Plane1,(vidmem + BytePos), 1);
    outportw(0x3CE,0x0005);//setup plane masking
    outportw(0x3c4,0x0402);//plane 2
    outportw(0x3c4,0x0F02);//restore normal plane mask
    k_memcpy(Plane2,(vidmem + BytePos), 1);
    outportw(0x3CE,0x0005);//setup plane masking
    outportw(0x3c4,0x0802);//plane 3
    outportw(0x3c4,0x0F02);//restore normal plane mask
    k_memcpy(Plane3,(vidmem + BytePos), 1);
    



    //ändere bits
    switch(modulo)
      {
        case(0):
          {
            if((farbe & 0x1) == 0x1){Plane0[0] |= 0x80;}//1000'0000
              else{Plane0[0] &= 0x7F;}//0111'1111

            if((farbe & 0x2) == 0x2){Plane1[0] |= 0x80;}
              else{Plane1[0] &= 0x7F;}

            if((farbe & 0x4) == 0x4){Plane2[0] |= 0x80;}
              else{Plane2[0] &= 0x7F;}

            if((farbe & 0x8) == 0x8){Plane3[0] |= 0x80;}
              else{Plane3[0] &= 0x7F;}

            break;
          }
      }
    

    //byte zurück in video speicher
    outportw(0x3CE,0x0005);//setup plane masking
    outportw(0x3c4,0x0102);//plane 0
    k_memset((vidmem + BytePos), Plane0[0], 1);
    outportw(0x3c4,0x0202);//plane 1
    k_memset((vidmem + BytePos), Plane1[0], 1);
    outportw(0x3c4,0x0402);//plane 2
    k_memset((vidmem + BytePos), Plane2[0], 1);
    outportw(0x3c4,0x0802);//plane 3
    k_memset((vidmem + BytePos), Plane3[0], 1); 
    outportw(0x3c4,0x0F02);//restore normal plane mask
    


  }





void int32_setpixel_0x13(int x, int y, char farbe)
	{
		k_memset((char *)0xA0000 + (y*320 + x), farbe, 1);
	}

/* signum function */
int sgn(int x){
  return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

void int32_line_0x13(int xstart,int ystart,int xend,int yend, char farbe)
/*--------------------------------------------------------------
 * Bresenham-Algorithmus: Linien auf Rastergeräten zeichnen
 *
 * Eingabeparameter:
 *    int xstart, ystart        = Koordinaten des Startpunkts
 *    int xend, yend            = Koordinaten des Endpunkts
 *
 * Ausgabe:
 *    void SetPixel(int x, int y) setze ein Pixel in der Grafik
 *         (wird in dieser oder aehnlicher Form vorausgesetzt)
 *---------------------------------------------------------------
 */
{
    int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;

/* Entfernung in beiden Dimensionen berechnen */
   dx = xend - xstart;
   dy = yend - ystart;

/* Vorzeichen des Inkrements bestimmen */
   incx = sgn(dx);
   incy = sgn(dy);
   if(dx<0) dx = -dx;
   if(dy<0) dy = -dy;

/* feststellen, welche Entfernung größer ist */
   if (dx>dy)
   {
      /* x ist schnelle Richtung */
      pdx=incx; pdy=0;    /* pd. ist Parallelschritt */
      ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
      es =dy;   el =dx;   /* Fehlerschritte schnell, langsam */
   } else
   {
      /* y ist schnelle Richtung */
      pdx=0;    pdy=incy; /* pd. ist Parallelschritt */
      ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
      es =dx;   el =dy;   /* Fehlerschritte schnell, langsam */
   }

/* Initialisierungen vor Schleifenbeginn */
   x = xstart;
   y = ystart;
   err = el/2;
   int32_setpixel_0x13(x,y,farbe);

/* Pixel berechnen */
   for(t=0; t<el; ++t) /* t zaehlt die Pixel, el ist auch Anzahl */
   {
      /* Aktualisierung Fehlerterm */
      err -= es;
      if(err<0)
      {
          /* Fehlerterm wieder positiv (>=0) machen */
          err += el;
          /* Schritt in langsame Richtung, Diagonalschritt */
          x += ddx;
          y += ddy;
      } else
      {
          /* Schritt in schnelle Richtung, Parallelschritt */
          x += pdx;
          y += pdy;
      }
      int32_setpixel_0x13(x,y,farbe);
   }
} /* gbham() */


// xstart und ystart müssen kleiner sein als ihr end
void int32_rechteck_0x13(int xstart, int ystart, int xend, int yend, char farbe)
  {
    int x_distanz, y_distanz;

    for(x_distanz = xend - xstart; x_distanz >= 0; x_distanz--)
      {
        for(y_distanz = yend - ystart; y_distanz >= 0; y_distanz--)
          {
              int32_setpixel_0x13(xstart + x_distanz, ystart + y_distanz, farbe);
          }
      }
  }


void int32_rasterCircle_0x13(int x0, int y0, int radius, char farbe)
  {
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    int32_setpixel_0x13(x0, y0 + radius, farbe);
    int32_setpixel_0x13(x0, y0 - radius, farbe);
    int32_setpixel_0x13(x0 + radius, y0, farbe);
    int32_setpixel_0x13(x0 - radius, y0, farbe);

    while(x < y)
    {
      if(f >= 0)
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x + 1;

      int32_setpixel_0x13(x0 + x, y0 + y, farbe);
      int32_setpixel_0x13(x0 - x, y0 + y, farbe);
      int32_setpixel_0x13(x0 + x, y0 - y, farbe);
      int32_setpixel_0x13(x0 - x, y0 - y, farbe);
      int32_setpixel_0x13(x0 + y, y0 + x, farbe);
      int32_setpixel_0x13(x0 - y, y0 + x, farbe);
      int32_setpixel_0x13(x0 + y, y0 - x, farbe);
      int32_setpixel_0x13(x0 - y, y0 - x, farbe);
    }
  }

 void int32_ellipse_0x13(int xm, int ym, int a, int b, char farbe)
{
   int dx = 0, dy = b; /* im I. Quadranten von links oben nach rechts unten */
   long a2 = a*a, b2 = b*b;
   long err = b2-(2*b-1)*a2, e2; /* Fehler im 1. Schritt */

   do {
       int32_setpixel_0x13(xm+dx, ym+dy, farbe); /* I. Quadrant */
       int32_setpixel_0x13(xm-dx, ym+dy, farbe); /* II. Quadrant */
       int32_setpixel_0x13(xm-dx, ym-dy, farbe); /* III. Quadrant */
       int32_setpixel_0x13(xm+dx, ym-dy, farbe); /* IV. Quadrant */

       e2 = 2*err;
       if (e2 <  (2*dx+1)*b2) { dx++; err += (2*dx+1)*b2; }
       if (e2 > -(2*dy-1)*a2) { dy--; err -= (2*dy-1)*a2; }
   } while (dy >= 0);

   while (dx++ < a) { /* fehlerhafter Abbruch bei flachen Ellipsen (b=1) */
       int32_setpixel_0x13(xm+dx, ym, farbe); /* -> Spitze der Ellipse vollenden */
       int32_setpixel_0x13(xm-dx, ym, farbe);
   }
}

void int32_whaitforkey()
	{
		regs16_t regs;
		regs.ax = 0x0000;
    	int32(0x16, &regs);
	}


// int32 test
void int32_test()
{
    char *offset; 
    char color = RED; // red = 0xC
    int x = 320;
    int y = 320;
    char bitmask;
  
    //Bitmaske mit dem zu ändernden Pixel erstellen 
    offset = (char*)0xA0000 + y * 640 + x / 8; 
    bitmask = 0x80 >> (x & 7); 
      
    //die Farbe schreibst du in das Set/Reset Register 
    outportb(0x3CE,0x0);     //Index 0 
    outportb(0x3CF,color);   //Farbe eintragen 
      
    //Alle Ebenen öffnen im Set/Reset Enable Register 
    outportb(0x3CE,0x1);     //Index 1 
    outportb(0x3CF,0xF);     //Bit 0 bis 3 setzen 
      
    //Im Bit Mask Register nur das berechnete Bit setzen! 
    outportb(0x3CE,0x8);     //Index 8 
    outportb(0x3CF,bitmask); //Bit setzen bei welchem die Farbe geändert werden soll 
      
    //beliebigen Wert an die Adresse schreiben 
    *offset = 0xFF;
    //(*offset)--; egal welches >> gleiches ergebnis = keine änderung des diplsays :/
      
    //Register wieder herstellen   
}

int int32_apfel_checkC(double reC, double imC)
	{
		double reZ = 0;
		double imZ = 0;

		double reZminus1 = 0;
		double imZminus1 = 0;

		int i = 1;

		for(i = 0; i<=30 ; i++)
			{
				imZ = (2*reZminus1*imZminus1)+imC;
				reZ = (reZminus1*reZminus1)-(imZminus1*imZminus1)+reC;
				if ((reZ*reZ)+(imZ*imZ)>4)
						{
							return (i);
						} 
				      reZminus1 = reZ;
            	imZminus1 = imZ;
			}
		return (i);
	}

void int32_apfel_paint_0x13()
	{
		double reC = 0.9;//x
		double imC = 1.1;//y

    //double reC_max = -2;
    double imC_max = -1.1;

    double reC_funktion = reC;
    double imC_funktion = imC;

    int Resultat = 0;

		int x = 0;
		int y = 0;

		double Xzelle = (imC - imC_max)/200; //ein pixel / im 
    double Yzelle = Xzelle; //ein pixel / real

		imC_funktion = imC;

		for(y = 0; y<=200;y++)
			{
				reC_funktion = reC;
				for(x = 0; x <= 320; x++)
					{  
            Resultat = int32_apfel_checkC(reC_funktion,imC_funktion);

            switch(Resultat)
              {
                case(30):{int32_setpixel_0x13(x,y,YELLOW);break;}
                case(29):{int32_setpixel_0x13(x,y,MAGENTA);break;}
                case(28):{int32_setpixel_0x13(x,y,MAGENTA);break;}
                case(27):{int32_setpixel_0x13(x,y,RED);break;}
                case(26):{int32_setpixel_0x13(x,y,RED);break;}
                case(25):{int32_setpixel_0x13(x,y,BLUE);break;}
                case(24):{int32_setpixel_0x13(x,y,BLUE);break;}
                case(23):{int32_setpixel_0x13(x,y,GREEN);break;}
                case(22):{int32_setpixel_0x13(x,y,GREEN);break;}
                case(21):{int32_setpixel_0x13(x,y,DARKBLUE);break;}
                case(20):{int32_setpixel_0x13(x,y,DARKBLUE);break;}
                case(19):{int32_setpixel_0x13(x,y,BROWN);break;}
                case(18):{int32_setpixel_0x13(x,y,BROWN);break;}
                case(17):{int32_setpixel_0x13(x,y,DARKMAGENTA);break;}
                case(16):{int32_setpixel_0x13(x,y,DARKMAGENTA);break;}
                case(15):{int32_setpixel_0x13(x,y,DARKRED);break;}
                case(14):{int32_setpixel_0x13(x,y,DARKRED);break;}
                case(13):{int32_setpixel_0x13(x,y,TURKY);break;}
                case(12):{int32_setpixel_0x13(x,y,TURKY);break;}
                case(11):{int32_setpixel_0x13(x,y,TURKY);break;}
                case(10):{int32_setpixel_0x13(x,y,TURKY);break;}
                case(9): {int32_setpixel_0x13(x,y,DARKGREEN);break;}
                case(8): {int32_setpixel_0x13(x,y,DARKGREEN);break;}
                case(7): {int32_setpixel_0x13(x,y,DARKGREEN);break;}
                case(6): {int32_setpixel_0x13(x,y,DARKGREEN);break;}
                case(5): {int32_setpixel_0x13(x,y,DEEPBLUE);break;}
                case(4): {int32_setpixel_0x13(x,y,DEEPBLUE);break;}
                case(3): {int32_setpixel_0x13(x,y,DEEPBLUE);break;}
                case(2): {int32_setpixel_0x13(x,y,BLACK);break;}
                case(1): {int32_setpixel_0x13(x,y,BLACK);break;}
              }


							reC_funktion = reC_funktion - Xzelle;
					}
					imC_funktion = imC_funktion - Yzelle;
			}
	}
