#include <stdio.h>   //Libreria basica de entrada salida
#include <stdlib.h>  //Libreria para el uso de rand( )
#include <time.h>    //Libreria para el uso de time( )
#include <string.h>  //Libreria para el uso de strcpy( )

//Creamos un tipo jugador
struct jug{         //El jugador cero es la banca
    float puntos;           //Puntos
    int partidas_ganadas;  //Numero de partidas ganadas
    int se_ha_plantado;    //Indica si el jugador se ha plantado (0=no | 1=si)
    int num_cartas;        //num de cartas que lleva
    int cartas[10];        //Las cartas que lleva, maximo 10, maximo 3 jugadores +  la banca
};
typedef struct jug jugador;




//Incluimos las funciones:


//Suponemos que tenemos un vector del 1 al 40, y que las 10 primeras son oros,
//del 11 al 20 bastos, del 21 al 30 espadas, y del 31 al 40 copas -->> ESTA SERA LA BARAJA


//Devuelve el valor de la carta al pasarle el numero que indica la posicion en la baraja
float valor_carta(int pos);

//Devuelve el nombre de la carta, por referencia, al pasarle el numero que indica la posicion en la baraja
void carta(int pos, char * nombre_carta);

//Recibe el vector de cartas, y el numero de cartas que quedan por sacar, por referencia.
//Devolvera por valor un numero al azar entre las cartas que no se han sacado.
int saca_carta(int baraja[], int * num_cartas_que_quedan_por_sacar);

//Recibe un vector de jugadores y el numero de jugadores, y limpia la pantalla y muestra las puntuaciones
//de los jugadores y de la banca (el jugador 0).
void imprime_puntuaciones(jugador * jugadores, int num_jugadores);

//Recibe un vector de jugadores,el numero de jugadores por valor y
// el numero de cartas que quedan por sacar por referencia. La funcion pondra a 0 los atributos: puntos, se_ha_plantado,
// y num_cartas, de los jugadores. Y a 40 el numero de cartas que quedan por sacar. PARA REINICIAR EL JUEGO
void reinicia(jugador * jugadores,int num_jugadores, int * num_cartas_que_quedan_por_sacar);

//Simulacion de la desicion de la banca
//Recibe un vector de jugadores y el numero de jugadores, y devuelve el caracter 'c' si saca carta,
//o 'p' si se planta.
//NOTA: Se plantara si tiene la puntuacion mas alta de todos los jugadores, siempre que esta sea mayor que 5.5, o si todos se han
//plantado
char juega_banca(jugador * jugadores,int num_jugadores);


//Simulacion de la jugada de un jugador
//Imprimira las puntuaciones y que le toca al jugador actual
//Devuelve 'c' si saca carta y 'p' si se planta
char juega_jugador(jugador * jugadores, int num_jugadores, int jugador_actual);


int main(){

    //Variables
    int num_jugadores=0,i,j,fin_partida=0;
    int num_partidas_ganadas;
    float val_car,puntos_max;  //el valor de la carta y los puntos maximos
    int numero_de_carta;       //Indica la posicion de la carta en el vector

    int aux;
    char tecla;

    int num_cart_baraja=40; //numero de cartas de la baraja
    int num_cartas_que_quedan_por_sacar;
    int baraja[40];         //Un numero asociado a cada carta
    char nombre_carta[14];  //Cadena de caracteres con el nombre de la carta

    jugador jugadores[4];   //Vector de jugadores

    num_cartas_que_quedan_por_sacar = num_cart_baraja;


    //rellenamos la baraja, la ordenamos
    for(i=0;i<=num_cart_baraja;i++){
        baraja[i] = i+1;
    }

    //Pedimos el numeor de jugadores, mas de 4 no hay cartas
    while(num_jugadores<=0 || num_jugadores>3){
      printf("\n\n Bienvenido al juego de cartas de la siete y media \n\n");
      printf("Introduzca el numero de jugadores (1-3), el jugador 0 es la banca: \n");
      fflush(stdin);
      scanf("%d",&num_jugadores);
      system("clear"); //Borramos la pantalla
    }//Fin while num_jugadores

     //Iniciamos los valores de los jugadores
     for(i=0;i<=num_jugadores;i++){
       jugadores[i].puntos = 0.0;
       jugadores[i].partidas_ganadas = 0;
       jugadores[i].se_ha_plantado = 0;
       jugadores[i].num_cartas = 0;
     }//Fin for inicia jugadores

    i=0;

    while(fin_partida==0){

       //Por cada jugador incluido la banca (0)
       for(i=0;i<=num_jugadores;i++){

          //Si el jugador i no se ha plantado
          if(jugadores[i].se_ha_plantado==0){

             //Si es la banca
             if(i==0){
                 //Juega la banca ella misma de side que hacer segun el criterio
                 tecla = juega_banca(jugadores,num_jugadores);

             //Si no es la banca, juegan los jugadores, sacan carta o se plantan
             }else{
                         //El jugador actual es la i
                 tecla = juega_jugador(jugadores,num_jugadores,i);

             }//Fin si si es la banca


              //Analizamos las acciones, si la tecla es 'c' saca una carta, y si es 'p' se planta
              if(tecla=='c'){

                   //Recibe el vector de cartas, y el numero de cartas que quedan por sacar, por referencia.
                   //Devolvera por valor un numero al azar entre las cartas que no se han sacado.
                   numero_de_carta = saca_carta(baraja, &num_cartas_que_quedan_por_sacar);

                   //Devuelve el valor de la carta al pasarle el numero que indica la posicion en la baraja
                   val_car = valor_carta(numero_de_carta);

                   //guardamos la carta sacada en el vector de cartas de jugador, en la posicion
                   //dependiendo de las cartas que lleve
                   jugadores[i].cartas[jugadores[i].num_cartas] = numero_de_carta;

                   //Sacamos el nombre de la carta dependiendo de su numero
                   carta(numero_de_carta,nombre_carta);

                   //Mostramos el nombre de la carta que se acaba de sacar
                   printf("La carta sacada es %s \n",nombre_carta);

                   //Calculamos los puntos del jugador
                   jugadores[i].puntos += val_car;

                   //incrementamos el valor de las cartas sacadas del jugador
                   jugadores[i].num_cartas++;

                   //Comprobamos si el jugador ha perdido
                   if(jugadores[i].puntos>7.5){

                       printf("\n Has perdido te has pasado!!!! \n");

                       //Ponemos que te has plantado para que no puedas seguir jugando mas
                        jugadores[i].se_ha_plantado = 1;

                   }//Fin comprobacion si ha perdido

                   system("read");

              }//Fin si la tecla es 'c' (saca carta)


              if(tecla=='p'){
                 printf("El jugador %d se ha plantado \n",i);
                 jugadores[i].se_ha_plantado = 1;
                 system("read");
              }//Fin si el jugador se ha plantado pulsando 'p'




          }else{//Si el jugador i  se ha plantado o perdido

               //imprimimos las puntuaciones en cualquiera de los dos casos
               imprime_puntuaciones(jugadores,num_jugadores);

               //Si ha perdido
               if(jugadores[i].puntos>7.5){
                   printf("\n\n El jugador %d se ha pasado\n",i);
               }else{
                   printf("\n\n El jugador %d se ha plantado\n",i);
               }//Fin si muestra se ha pasado o plantado

               fflush(stdin);
               system("read");

          }//Fin si el jugador i se ha plantado o perdido
       }//Fin for Por cada jugador



       //Una vez realizadas las acciones de todos los jugadores y de la banca
       //Suponemos que la partida se ha acabao y luego comprobamos que no
       fin_partida=1;

       //Comprobamos si se han plantado todos los jugadores incluida la banca
       for(j=0;j<=num_jugadores;j++){

           //Si encontramos al menos uno que no se haya plantado entonces
           //Seguimos la partido
           if(jugadores[j].se_ha_plantado==0){
               fin_partida = 0;
           }
       }//Fin for


       //Si se ha acabado la partida, comprobamos los ganadores
       if(fin_partida == 1){

         puntos_max = 0;

          //Sacamos la puntuacion mas alta
         for(j=0;j<=num_jugadores;j++){

            if(jugadores[j].puntos>puntos_max && jugadores[j].puntos<7.5){
                puntos_max = jugadores[j].puntos;
            }
         }

         //imprimimos las puntutaciones
         imprime_puntuaciones(jugadores,num_jugadores);

         //Ganan aquellos jugadores que tengan la puntuacion mas alta
         //Puede haber varios ganadores
         for(j=0;j<=num_jugadores;j++){
             if(jugadores[j].puntos==puntos_max){
                 printf("\n El jugador %d es el ganador!!!!");
                 //incrementamos el cotador de partidas ganadas del jugador
                 jugadores[j].partidas_ganadas++;
             }
         }


         //preguntamos de nuevo si se quiere jugar otra partida

         system("read");
         aux=0;
         while(aux==0){

             system("clear");
             printf("\n\n\n ¿Desea jugar otra partida? (s/n): \n");
             fflush(stdin);
             scanf("%c",&tecla);

             //Si se desea jugar otra partida ponemos fin_partido=0
             //y reiniciamos las puntuaciones
             if(tecla=='s'){
                 fin_partida = 0;
                  reinicia(jugadores,num_jugadores,&num_cartas_que_quedan_por_sacar);
                  aux=1;
             }//Fin si tecla 's'

             //Si no se desea jugar otra partido imprimimos los resultados,
             // y mostramos el jugador con mas partidas ganadas
             if(tecla=='n'){
                 system("clear");
                 printf("Resumen de partidas\n\n");
                 num_partidas_ganadas = 0;
                 for(i=0;i<=num_jugadores;i++){

                    if(i==0){
                      printf("\n La banca ");
                    }else{
                      printf("\n El jugador %d ",i);
                    }
                    printf("ha ganado %d partidas \n",jugadores[i].partidas_ganadas);

                    //Almacenamos maximo de las partidas gandas
                    if(jugadores[i].partidas_ganadas>num_partidas_ganadas){
                       num_partidas_ganadas = jugadores[i].partidas_ganadas;
                    }
                 }//Fin recorre jugadores partidas ganadas


                 for(j=0;j<=num_jugadores;j++){
                   //Si el jugador tiene el maximo de partidas ganadas
                   if(jugadores[j].partidas_ganadas == num_partidas_ganadas && j==0){
                       printf("\n La Banca gana!!!! con %d partidas ganadas",num_partidas_ganadas);
                   }else if(jugadores[j].partidas_ganadas == num_partidas_ganadas){
                       printf("\n El jugador %d es el ganador !!!! con %d partidas ganadas",j,num_partidas_ganadas);
                   }
                 }

                 //Ponemos aux=1 para salir
                 aux=1;


             }//Fin tecla 'n'

         }//Fin while aux (jugar otra partida)



       }//Fin Si es FIN partida y comprueba ganadores




    }//Fin while fin_partida


  //system("read");

  return 0;

}//Fin main

//Definicion de funciones




//Devuelve el valor de la carta
float valor_carta(int pos){

   float valor;

   if(pos<=10 ){ //Oros
       if(pos>7){
           valor = 0.5;

       }else{
           valor = pos;
       }
   } //Fin oros

   if(pos>10 && pos<=20){  //bastos
       if(pos>17){
         valor = 0.5;
       }else{
         valor = pos - 10;
       }

   } //Fin bastos


    if(pos>20 && pos<=30){ //Espadas
        if(pos>27){
            valor = 0.5;
        }else{
            valor = pos - 20;

        }


    }//Fin espadas

    if(pos>30 && pos<=40){ //Copas
        if(pos>37){
            valor = 0.5;
        }else{
            valor = pos - 30;

        }
    }//Fin Copas

    return valor;

}


//Devuelve el nombre de la carta al pasarle el numero
void carta(int pos, char * nombre_carta){

   int num;

   if(pos<=10){ //El palo es el oro
      if(pos>7){
        num = pos + 2;
      }else{
          num = pos;
      }

      sprintf(nombre_carta, "%d de oros",num);
   } //Fin palo oro


   if(pos>10 && pos<=20){ //El palo es el basto
      if(pos>17){
        num = pos - 10 + 2;
      }else{
          num = pos - 10;
      }

      sprintf(nombre_carta, "%d de bastos",num);
   } //Fin palo de bastos

   if(pos>20 && pos<=30){ //El palo de espadas
      if(pos>27){
        num = pos - 20 + 2;
      }else{
          num = pos - 20;
      }

      sprintf(nombre_carta, "%d de espadas",num);
   } //Fin palo de espadas


   if(pos>30 && pos<=40){ //El palo de copas
      if(pos>37){
        num = pos - 30 + 2;
      }else{
          num = pos - 30;
      }

      sprintf(nombre_carta, "%d de espadas",num);
   } //Fin palo de copas


}//Fin funcion carta

//funcion saca_carta:
//Recibe el vector de cartas, y el numero de cartas que
//quedan por sacar, por referencia.
//Devolvera por valor un numero al azar entre
//las cartas que no se han sacado

int saca_carta(int baraja[],int * num_cartas_que_quedan_por_sacar){

    int res,ind,i,aux;
    int hora;

    hora = time(NULL);
    srand(hora);
    ind = rand() % (* num_cartas_que_quedan_por_sacar); //ind es un numero al azar entre 0 y el numero de cartas que quedan por sacar-1

    res = baraja[ind]; //recogemos una carta al azar


    //Guardamos la carta sacada para ponerla al final de la baraja
    aux = res;

    //Reordenamos la baraja
    for(i=ind;i<39;i++){

        baraja[i] = baraja[i+1];

    }

    //Ponemos la carta sacada al final de la baraja, esta ya no volvera a salir
    baraja[39]= aux;

    *num_cartas_que_quedan_por_sacar = *num_cartas_que_quedan_por_sacar-1;

    return res;

}//Fin funcion saca carta


//Recibe un vector de jugadores y el numero de jugadores, y limpia la pantalla y muestra las puntuaciones
//de los jugadores y de la banca (el jugador 0).
void imprime_puntuaciones(jugador * jugadores, int num_jugadores){

    int i,j;
    char car[14];

    //Limpiamos la pantalla
    system("clear");

    for(i=0;i<=num_jugadores;i++){

      if(i==0){

         printf("Jugador %d, Banca\n",i);

      }else{

         printf("\nJugador %d \n",i);
         printf("Puntos= %1.1f \n",jugadores[i].puntos);
         printf("Las cartas sacadas son: \n");

          for(j=0;j<jugadores[i].num_cartas;j++){


              //Hacemos la llamada a la funcion carta para que nos muestre el nombre de la carta,
              //le pasamos el numero de la carta del jugador que indica la posicion en la baraja, y una cadena por referencia.
              //Devuelve el nombre de la carta, por referencia.
              carta(jugadores[i].cartas[j],car);

              printf("%s\n",car);

          }


      }


    }

}//Fin funcion imprime_puntuaciones



//Recibe un vector de jugadores,el numero de jugadores por valor y
// el numero de cartas que quedan por sacar por referencia. La funcion pondra a 0 los atributos: puntos, se_ha_plantado,
// y num_cartas, de los jugadores. Y a 40 el numero de cartas que quedan por sacar. PARA REINICIAR EL JUEGO
void reinicia(jugador * jugadores,int num_jugadores, int * num_cartas_que_quedan_por_sacar){

    int i;

    for(i=0;i<=num_jugadores;i++){

       jugadores[i].puntos = 0;
       jugadores[i].se_ha_plantado = 0;
       jugadores[i].num_cartas = 0;
    }

    *num_cartas_que_quedan_por_sacar = 40;

}//Fin funcion reinicia


//Simulacion de la desicion de la banca
//Recibe un vector de jugadores y el numero de jugadores, y devuelve el caracter 'c' si saca carta,
//o 'p' si se planta
//NOTA: Se plantara si tiene la puntuacion mas alta de todos los jugadores, siempre que esta sea mayor que 5.5, o si todos se han
//plantado
char juega_banca(jugador * jugadores,int num_jugadores){

    //imprimimos las puntuaciones
    imprime_puntuaciones(jugadores,num_jugadores);

    float punt_max=0;
    //Variable booleana para ver si todos los jugadores se han pasado
    int pas = 1;
    char tecla;
    int j;

    printf("\n Juega la Banca\n");

    //Recorremos todos los jugadores para saber la maxima puntuacion
    for(j=1;j<=num_jugadores;j++){

        //Si el jugador tiene la maxima puntuacion y no se ha pasao de 7.5
        if(jugadores[j].puntos>punt_max && jugadores[j].puntos<=7.5){
            punt_max = jugadores[j].puntos;
        }

        if(jugadores[j].puntos<=7.5){
           pas = 0; //Si pas=0, quiere decir que NO todos los jugadores se han pasao
        }

    }//Fin for


    //A partir de aqui ya se si todos los jugadores se han pasao (pas=1), cual es la puntuacion mas alta

    if( (jugadores[0].puntos>punt_max && jugadores[0].puntos>=5.5) || pas==1 ){
        tecla = 'p';

    }else{
        tecla = 'c';
    }

    return tecla;

}//Fin funcion juega_banca



//Simulacion de la jugada de un jugador
//Imprimira las puntuaciones y que le toca al jugador actual
//Devuelve 'c' si saca carta y 'p' si se planta
char juega_jugador(jugador * jugadores, int num_jugadores, int jugador_actual){

    char tecla;
    int aux = 0;

    while(aux==0){
        //Imprimimos las puntuaciones
        imprime_puntuaciones(jugadores,num_jugadores);
        printf("\n\n Juega el jugador %d\n",jugador_actual);
        printf(" Si quieres sacar carta pulsa 'c' \n");
        printf(" Si quieres plantarte pulsa 'p' \n");
        fflush(stdin);
        scanf("%c",&tecla);

        if(tecla=='c' || tecla=='p'){

           aux = 1;

        }

    }//Fin while

    return tecla;

}//Fin funcion juega_jugador


