#include <curses.h>
#include <iostream>
#include <stdio.h>
#include <random>
struct pos {
  int x;
  int y;
};
enum colors {
  color_card_inv, color_card, player1, player2, title1, title2, oscuzul, color_blue, color_red
};
void printpos(pos p, int c, colors uncolor) {
  color_set(uncolor, NULL);
  mvaddch( p.x, p.y, c );
  mvaddch( p.x, p.y+1, c );
  mvaddch(p.x,p.y+2,c);
  mvaddch(p.x,p.y+3,c);
}

short color_from_RGB(char r, char g, char b) {
    return (r*36 + g*6 + b*1) + 16;
}

short grey_from_24(char g) {
    return 216 + g + 16;
}
//titulo
void title_memory (int x, int y, colors elcolor){
    color_set(elcolor, NULL);
    for (int i = 0; i<=4; i++){//lineas verticales largas de las letras
        mvaddch(x+2+i,y+1,' ');//M
        mvaddch(x+2+i,y+5,' ');//M
        mvaddch(x+2+i,y+7,' ');//E
        mvaddch(x+2+i,y+13,' ');//M
        mvaddch(x+2+i,y+17,' ');//M
        mvaddch(x+2+i,y+19,' ');//O
        mvaddch(x+2+i,y+23,' ');//O
        mvaddch(x+2+i,y+25,' ');//R
    }
    for ( int j=0 ; j<=4 ; j++){//lineas verticales de las letras
        mvaddch(x+2,y+7+j,' ');//E
        mvaddch(x+4,y+7+j,' ');//E
        mvaddch(x+6,y+7+j,' ');//E
        mvaddch(x+2,y+19+j,' ');//O
        mvaddch(x+6,y+19+j,' ');//O
        mvaddch(x+2,y+25+j,' ');//R
        mvaddch(x+4,y+25+j,' ');//R
    }
    mvaddch(x+3,y+2,' ');//M
    mvaddch(x+4,y+3,' ');//M
    mvaddch(x+3,y+4,' ');//M

    mvaddch(x+3,y+14,' ');//M
    mvaddch(x+4,y+15,' ');//M
    mvaddch(x+3,y+16,' ');//M

    mvaddch(x+3,y+29,' ');//R
    mvaddch(x+5,y+28,' ');//R
    mvaddch(x+6,y+29,' ');//R

    mvaddch(x+2,y+31,' ');//Y
    mvaddch(x+2,y+35,' ');//Y
    mvaddch(x+3,y+32,' ');//Y
    mvaddch(x+3,y+34,' ');//Y
    mvaddch(x+4,y+33,' ');//Y
    mvaddch(x+5,y+33,' ');//Y
    mvaddch(x+6,y+33,' ');//Y

    color_set(title2,NULL);

    mvaddstr(x  ,y, "                                     ");
    mvaddstr(x+8,y, "                                     ");

    color_set(color_card_inv,NULL);

}
void title_puzzle (int x, int y, colors elcolor){
    color_set(elcolor, NULL);
    for (int i = 0; i<=4; i++){//lineas verticales largas de las letras
        mvaddch(x+2+i,y+1,' ');//P
        mvaddch(x+2+i,y+7,' ');//U
        mvaddch(x+2+i,y+11,' ');//U
        //mvaddch(x+2+i,y+13,' ');//M
        //mvaddch(x+2+i,y+17,' ');//M
        mvaddch(x+2+i,y+25,' ');//L
        mvaddch(x+2+i,y+31,' ');//E

    }
    for ( int j=0 ; j<=4 ; j++){//lineas verticales de las letras
        mvaddch(x+2,y+1+j,' ');//P
        mvaddch(x+4,y+1+j,' ');//P
        mvaddch(x+6,y+7+j,' ');//U
        mvaddch(x+2,y+13+j,' ');//Z
        mvaddch(x+6,y+13+j,' ');//Z
        mvaddch(x+2,y+19+j,' ');//Z
        mvaddch(x+6,y+19+j,' ');//Z
        mvaddch(x+6,y+25+j,' ');//L
        mvaddch(x+2,y+31+j,' ');//E
        mvaddch(x+4,y+31+j,' ');//E
        mvaddch(x+6,y+31+j,' ');//E
    }
    mvaddch(x+3,y+5,' ');//P

    mvaddch(x+5,y+14,' ');//Z
    mvaddch(x+4,y+15,' ');//Z
    mvaddch(x+3,y+16,' ');//Z

    mvaddch(x+5,y+20,' ');//Z
    mvaddch(x+4,y+21,' ');//Z
    mvaddch(x+3,y+22,' ');//Z



    color_set(title2,NULL);

    mvaddstr(x  ,y, "                                     ");
    mvaddstr(x+8,y, "                                     ");

    color_set(color_card_inv,NULL);

}
//fin titulo
//animar titulo
void memory_anim(int x, int y, colors mancha){
    title_memory(x, y-37, mancha);
    title_puzzle(x, y+2 , mancha);
}
//fin animar titulo
//interfaz
void interfaz(int a){
    int mx, my;
    getmaxyx( stdscr, mx, my );//obtener tamaño de pantalla
      for (int i = 0; i < mx ; i++){
        for (int j = 0; j < my ; j++){
            if ((j>=a && i>=1) && (j<= my-2 && i<=mx-2) ){//espacio para instrucciones e interfaz
                color_set(title2,NULL);
                mvaddch(i,j,' ');
                color_set(color_card_inv,NULL);
            }
            if (i==0 || i==mx-1 || j==0 || j==my-1 || j==(a)-1 || (i==2*mx/3 && j>=a)){//marco
                color_set(title1, NULL);
                mvaddch(i,j,' ');
                color_set(color_card_inv,NULL);
            }
        }
      }
      color_set(title2,NULL);
      mvaddstr((2*mx/3)+1, a+1 , "INSTRUCCIONES:");
      mvaddstr((2*mx/3)+2, a+1 , "Flechas: movimiento");
      mvaddstr((2*mx/3)+3, a+1 , "W : seleccionar");
      mvaddstr((2*mx/3)+4, a+1 , "Q : salir");
  }
//fin interfaz
void lisqua(int x,int lonx,int y,int lony){

     int a = x+y;
     pos relleno;
     relleno.x= x;
     relleno.y=y;
     mvaddch(x,y, ACS_ULCORNER);
     mvaddch(x,y+lony, ACS_URCORNER);
     mvaddch(x+lonx,y, ACS_LLCORNER);
     mvaddch(x+lonx,y+lony, ACS_LRCORNER);

     for(int i = 1; i < lonx; i++){

        mvaddch(x+i,y, ACS_VLINE);
        mvaddch(x+i,y+lony,ACS_VLINE);
     }
     for(int j = 1; j<lony;j++){
        mvaddch(x, y+j ,ACS_HLINE);
        mvaddch(x+lonx ,y+j ,ACS_HLINE);
     }

     printpos(pos{relleno.x+1,relleno.y+1},' ', color_card);
     printpos(pos{relleno.x+2,relleno.y+1},' ' , color_card);
     printpos(pos{relleno.x+3,relleno.y+1},' ', color_card);

     color_set(color_card_inv,NULL);
 }

int main(){

    std::random_device rd;

  bool f=true;
  bool g=true;
  pos oldcursor;
  int zurich=0;
  int kiev=0;
  int t=-1;
  int sofia=0;
  int jug=0;
  int mx, my;//aqui se guarda la longitud total de la pantalla



  ttytype[0] = 35;  ttytype[1] = 45; // 35 to 45 lines height
  ttytype[2] = 80;  ttytype[3] = (unsigned char)130; // 80 to 130 characters width

  // Initializing window to print in
  initscr();   // starting screen

  getmaxyx( stdscr, mx, my );//obtener tamaño de pantalla

  cbreak();
  noecho();    // consume characters without showing them in screen
  curs_set(0); // setting cursor as invisible
  keypad(stdscr, true); // allowing ncurses to convert press keys into curses representation (useful for KEY_UP)
  start_color(); // asking ncurses to use colors

  system("mode con: cols=100 lines=50");

  init_pair(color_card,     grey_from_24(0), color_from_RGB(3,1,3));
  init_pair(color_card_inv,     grey_from_24(23), color_from_RGB(0,0,0));
  init_pair(player1,     grey_from_24(0), color_from_RGB(5,0,0));
  init_pair(player2,     grey_from_24(0), color_from_RGB(0,0,5));
  init_pair(title1,     grey_from_24(0), color_from_RGB(5,5,0));
  init_pair(title2,     grey_from_24(0), color_from_RGB(2,1,0));
  init_pair(oscuzul,   grey_from_24(0), color_from_RGB(0,0,1));
  init_pair(color_blue,     grey_from_24(0), color_from_RGB(5,3,1));
  init_pair(color_red,     grey_from_24(0), color_from_RGB(5,0,0));

  clear();
  pos card;
  int fase = 0;

  while (fase<3){
    if (fase==0){//pantalla de titulo
        clear();
        for(int i=0;i<mx;i++){
            for (int j=0;j<my;j++){
                if ((i%2 == 1 && j%2 == 0)||(i%2 == 0 && j%2 == 1)){
                color_set(oscuzul,NULL);
                mvaddch(i,j,' ');

                }
            }

        }
        memory_anim((mx/2)-4,my/2,title1);

        mvaddstr((mx/2)+7,(my/2)-11, "Presione cualquier tecla");
        color_set(color_card_inv,NULL);


        getch();
        clear();
        fase++;

    }
    mvaddstr(1,1, "Seleccione el número de jugadores que desea, entre 1 y 9.");
        jug=getch()-48;
        while (!(jug>=1 && jug<10)==true){
                jug = getch() - 48;
              }
        int jugadores [jug];
        for(int i=0;i<jug;i++){
            jugadores[i]=0;
        }
    if (fase==1){//aqui va el juego
        mvaddstr(1,1, "Seleccione la cantidad de columnas con números del 2 al 9. ");
        mvaddstr(3,1,"Tenga en cuenta si ingresa otro caracter la grilla será muy grande ");
        addstr("y no cabrá en la pantalla.");
        card.x = getch() - 48;
              while (!(card.x>=2 && card.x<=10)==true){
                card.x = getch() - 48;
              }
              clear();
        mvaddstr(1,1, "Seleccione la cantidad de filas con números del 2 al 9. ");
        mvaddstr(3,1,"Tenga en cuenta si ingresa otro caracter la grilla será muy grande ");
        addstr("y no cabrá en la pantalla.");

        card.y = getch() - 48;
          while (!(card.y>=2 && card.y<=10)==true){
            card.y = getch() - 48;
          }

          clear();
        int totalcards;
          // calculating total number of cards
          if( (card.x * card.y) % 2 == 0) {
            totalcards = card.x * card.y;
          } else {
            totalcards = card.x * card.y - 1;
          } //Se mira cuantas cartas deben haber en la grilla para que se formen bien las parejas

          int totalpairs = totalcards/2; //Se mira cuantas parejas habran en la grilla
          int cards[ totalcards ]; //un arreglo con el total de cartas en la grilla


          // defining and zeroing all cards
          int a [card.x][card.y];
          int duitama [card.x][card.y];
          for(int i=0;i<card.x;i++){
            for(int j=0;j<card.y;j++){
              a [i][j]=0;
              duitama[i][j]=0;
            }
          }

          // ---------------- putting cards randomly in board -------------------
          // creating deck of cards: {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, ...}
          for (int i = 0; i < totalpairs; i++) {       // Escribe el numero del 1 al  N
            cards[2*i  ] = i+1;
            cards[2*i+1] = i+1;
          }

          // randomizing deck of cards // using this algorithm: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
          for (int i = totalcards-1; i > 0; i--) { //Paso 1, reduce n para el paso 1, se repite para hacer un random total
            // position to swap with current last element (i)
            int pos = (unsigned int)rd() % i; //genera un numero aleatorio //Paso 1, elige un numero aleatorio entre los numeros que queden entre  1 y n
            // swaping elements
            int swap_temp = cards[pos];//Paso 1, elige un numero aleatorio entre los numeros que queden entre  1 y n
            cards[pos] = cards[i];//paso 2, cuenta de el numero mayor al menor, lo tacha y lo copia en otro arreglo
            cards[i] = swap_temp;//paso 3, arreglo randomizado //paso 2, cuenta de el numero mayor al menor, lo tacha y lo copia en otro arreglo
          }

          // copia del arreglo randomizado a la matriz a
          int i = 0;
          int j = 0;
          for(int k=0; k<totalcards; k++){
            a[i][j] = cards[k];
            j++;
            if(j % card.y == 0) {
              i++;
              j = 0;
            }
          }
  // -END------------ putting cards randomly in board -------------------


        int londres=0;
  int roma=0;

  while(f){//_________________________________________WHILE1_______________________________________________________________

    mvaddstr(1,1, "Turno del jugador");
    move(1,19);
    printw("%d",roma+1);
    roma++;
    mvaddstr(3,1, "Presione cualquier tecla para comenzar");
    getch();
    clear();


    pos cursor={4,7};
    londres=0;

    bool madrid=false;
    bool munich=false;
    int num_pressed_W = 0;

    while (f&&g){//___________________________________________WHILE2__________________________________________________________
      interfaz(6*card.y+7);
      for (int i = 0 ; i < card.x ; i++){
        for (int j = 0; j < card.y; j++){
          mvaddch(4+ 5*i, 1, i +48);
          mvaddch(1, 6+ 5*j +j, j+48 );
          // print a rectangle unless there is an odd (impar) number of cards
        for(int i=0;i<card.x;i++){
        for(int j=0;j<card.y;j++){
          if(duitama[i][j]==0&&!(i==card.x-1 && j==card.y-1 && (card.x*card.y) % 2 != 0)){
            lisqua( 2+ 5*i, 4, 4+ 5*j +j, 5);

          }
        }
      }
        }
        }
      int paris=-1;

      if(((londres%2)!=0)){
        paris=a[(oldcursor.x-4)/5][(oldcursor.y-7)/6];
        sofia=duitama[(oldcursor.x-4)/5][(oldcursor.y-7)/6];
        move(oldcursor.x,oldcursor.y);
        if (paris>0){
          printw("%d",paris);
        }else if(paris<=0){
          printw("%d",sofia);
        }
      }
         color_set(color_blue, NULL);
        if(cursor.x<4){
            cursor.x=4;
            mvaddch(cursor.x,cursor.y, ' ' );
        }else if(cursor.y<7){
            cursor.y=7;
            mvaddch(cursor.x,cursor.y, ' ' );
        }else if( cursor.x>(5*card.x)){
            cursor.x=5*card.x -1;
            mvaddch(cursor.x,cursor.y, ' ' );
        }else if(cursor.y>6*card.y){
            cursor.y=6*card.y+1;
            mvaddch(cursor.x,cursor.y, ' ' );
        }else{
            mvaddch(cursor.x,cursor.y,' ');
        }


      int york=a[(cursor.x-4)/5][(cursor.y-7)/6];
      int bruselas=duitama[(cursor.x-4)/5][(cursor.y-7)/6];

      if(num_pressed_W%2!=0 && madrid==true) {
        oldcursor.x=cursor.x;
        oldcursor.y=cursor.y;
      }

      if((madrid==true)){
        move(cursor.x,cursor.y);
        if (york>0){
          printw("%d",york);
        }else if(york<=0){
          printw("%d",bruselas);
        }
        madrid=false;
        londres++;
        kiev++;
      }

      if (((num_pressed_W%2==0)&& num_pressed_W!=0) && (paris == york) && (munich==true)){
        if((oldcursor.x!=cursor.x)||(oldcursor.y!=cursor.y)){
          duitama[(cursor.x-4)/5][(cursor.y-7)/6]=york;
          duitama[(oldcursor.x-4)/5][(oldcursor.y-7)/6]=paris;
          t--;
          a[(cursor.x-4)/5][(cursor.y-7)/6]=t;
          t--;
          a[(oldcursor.x-4)/5][(oldcursor.y-7)/6]=t;
        zurich++;
        londres=0;
        for(int i=1;i<=jug;i++){
        if(roma==i){
        jugadores[i-1]++;
        }
        }
        }
        munich=false;
      }
      mvaddstr(9,(6*card.y)+8,"Parejas de cartas encontradas: ");
      printw("%d",zurich);
      mvaddstr(7,(6*card.y)+8,"Cartas volteadas: ");
      printw("%d",kiev);

      mvaddstr(5,(6*card.y)+8,"Parejas en la grilla: ");
      printw("%d", totalpairs);

        for(int i=0; i<jug; i++){
      mvaddstr(11+i*2,(6*card.y)+8,"Puntaje del jugador ");
      printw("%d: ", i+1);
      printw("%d", jugadores[i]);

    }
      if(zurich == totalpairs){
        int j=0;
        for(int i=0; i<jug; i++){
        if(jugadores[i]>=j){
            j=jugadores[i];
        }
        for(int i=0; i<jug; i++){
        if(jugadores[i]==j){
      mvaddstr(11+2*i,(10*card.y)+28,"HA GANADO EL JUGADOR ");
      printw("%d", i+1);
      f=false;
        }
      }
      }
      }

      if ((londres%2==0)&&(londres!=0)){
        g=false;
      }
    int k= getch();

      switch(k){
        case KEY_DOWN:
            if (a[(cursor.x+1)/5][(cursor.y-7)/6]){
             cursor.x+=5;
            }
             break;
        case KEY_UP:    cursor.x-=5; break;
        case KEY_LEFT:  cursor.y-=6; break;
        case KEY_RIGHT:
            if(a[(cursor.x-4)/5][(cursor.y-1)/6]){
                cursor.y+=6;
            }
             break;
        case 'q':       f=false;     break;
        case 'w':
            if(a[(cursor.x-4)/5][(cursor.y-7)/6]>0){
          madrid=true;
          munich=true;
          num_pressed_W++;}
          break;
      }

      clear();
    };

    if(zurich == totalpairs){
      napms(100);
    }
          if(roma==jug){
        roma=0;
    }
    g=true;

  }

        fase++;
    }
    if (fase==2){//preguntar por otra partida
        clear();
        mvaddstr((mx/2),(my/2)-11,"Quieres volver a jugar? (Y/N)");
        char answer = getch();
        while (!(answer=='Y'||answer=='y'||answer=='n'||answer=='N')==true){
            answer = getch();
        }

        if (answer == 'Y'||answer =='y'){
            //clear();
            mvaddstr((mx/2)+1,(my/2)-6,"VUELTA A EMPEZAR");
            getch();
            f=true;
            zurich=0;
            kiev=0;
            fase=0;
            for(int i=0;i<jug;i++){
                jugadores[i]=0;
            }
        }else if (answer == 'N'||answer == 'n'){
            //clear();
            fase++;
            mvaddstr((mx/2)+1,(my/2)-6,"HASTA LA PROXIMA");
        }
    }

  }

  getch();
  clear();

  nodelay(stdscr, false);

  endwin(); // closing window

  return 0;
}
