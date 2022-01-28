int val;                             // Declaramos la variable val de tipo entero 
void setup() {                      
Serial.begin (9600);                 // Inicializamos la comunicacion serial a 9600bps
pinMode(A1, INPUT);                  //Asignamos el pin A1 como entrada (sensor de temperatura)
pinMode(6, OUTPUT);                  //Asignamos el pin 6 como salida (led roja)
pinMode(7, OUTPUT);                  //Asignamos el pin 7 como salida (led verde)
}

void loop() {
val= analogRead (A1);               //Da la lectura al pin A1 del sensor y lo guarda en la variable val
float mv = (val/1024.0)*5000;       //Declaramos la variable float para operar y obtener el resultado
float temp =mv/10;                  //Declaramos la variable tipo floa y operamos para obtener el resultado

Serial.print ("TEMPERATURA = ");    //Imprimimos en pantalla "TEMPERATURA"
Serial.print (temp);                //Imprimimos el valor de la variable temp
Serial.print ("*C");                //Imprimimos en pantalla C
Serial.println ();                  //Salto de linea

if (temp<17){                       //Si temp es menor que 17
  digitalWrite(6,HIGH);             //Encienda el led rojo
  digitalWrite(7,LOW);              //Apague el led verde
}
else if (temp>17 && temp<35){       //Si temp es mayor a 17 y menor a 35
  digitalWrite(6,LOW);              //Apaga luz roja
  digitalWrite(7,HIGH);             //Enciende el led verde
  
}
else {                              // de lo contrario
  digitalWrite(6,HIGH);             //Enciende luz roja
  digitalWrite(7, LOW);             //Apaga luz verde
}
  

delay (1000);                       //Espera 1 segundo 
}
