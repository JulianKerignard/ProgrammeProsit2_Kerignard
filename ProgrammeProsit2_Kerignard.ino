//************************************//
//Programme C/ASM pour le Prosit N°2 //
//Bloc Systèmes embarqués 2024-25   //
//Fait par julian Kerignard        //
//CESI Ecole D'ingenieur Nancy    //
//IDE JetBrain Rider             //
//******************************//


long a = 1;  //1 var long pour la suite fibonacci ASM
long b = 2;  //  2e var long pour la suite ASM
long fiboa = 1;  // 1er var pour la suite mais en l'angage C
long fibob = 2;  // 2e var pour la suite mais en l'angage C

void setup() {
  Serial.begin(9600);  

  long start = micros();  // Enregistre le temps initial en microsecondes
  int compt = 0;          // Compteur boucle en ASM
  int compt2 = 0;         // Compteur boucle en langage C
  int limit = 11;         // Nombre d'iterations de la suite

  // Boucle pour calculer celon la limit donner en ASM
  while (compt < limit) {
    fiboASM();  // Appel de la fonction en assembleur
    compt++;    // Incrément du compteur
  }

  long endASM = micros();  // Enregistre le temps après l'exécution ASM


  // Boucle pour calculer la suite celon la var limit
  while (compt2 < limit) {
    fibo();     // Appel de la fonction en C
    compt2++;   // Incrément du compteur
  }

  long endN = micros();  // Enregistre le temps après l'execution en C

  // Affichage du temps d'exécution pour chaque méthode ASM puis C
  Serial.print("ASM time : ");
  Serial.println(endASM - start);  // Temps écoulé pour les calculs en assembleur
  Serial.print("C time : ");
  Serial.println(endN - endASM);   // Temps écoulé pour les calculs en C
}


void loop() {
  // La fonction loop reste vide mais pour eviter une erreur on la laisse dans le code
}



// Fonction qui calcule la suite en assembleur
long fiboASM() {
  long result;  //Var qui vas venir stocker le resultat de la suite

  // Code en ASM pour ajouter deux longs (en 32 bits) stockés dans les vars a et b
  asm volatile(
    "mov r24, %A1\n\t"  // Charge l'octet a dans r24
    "mov r25, %B1\n\t"  // Charge l'octet a dans r25
    "mov r26, %A2\n\t"  // Charge l'octet b dans r26
    "mov r27, %B2\n\t"  // Charge l'octet b dans r27
    "add r24, r26\n\t"  // Additionne 
    "adc r25, r27\n\t"  
    "mov %A0, r24\n\t"  
    "mov %B0, r25\n\t"  // Stocke l'octet du résultat dans la var result
    : "=&r" (result)    // La sortie est stockée dans 'result'
    : "r" (a), "r" (b)  // Les entrées sont 'a' et 'b'
    : "r24", "r25", "r26", "r27"  // Registres utilisés (r24,r25,26,r27)
  );



  Serial.println(result);  
  a = b;                   
  b = result;              
  return result;          
}


// Fonction suite en C
long fibo() {
  long r = fiboa + fibob;  // Additionne les deux derniers termes
  fiboa = fibob;           // Met à jour 'fiboa' avec la valeur de 'fibob'
  fibob = r;               // Met à jour 'fibob' avec le nouveau résultat
  Serial.println(r);       // Affiche le résultat
  return r;                // Retourne le résultat
}
