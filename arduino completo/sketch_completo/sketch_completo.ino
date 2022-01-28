//Oxigeno
#include <Wire.h>                     //Libreria
#include <LiquidCrystal_I2C.h>        //Libreria responsable del manejo de la pantalla LCD
LiquidCrystal_I2C lcd(0x3F,16,2);     //Adaptador de protocolo I2C permitir comunicacion display con arduino
int pot = A0;                        //Variable de 8bits que tiene de entrada A0 y puede guardar valores de el potenciometro
int value = 0;                        //lectrura del valor del potenciometro en un entero

//PH
#define SensorPin A2                 //medidor de ph es conectado con el arduino
unsigned long int avgValue;          //Alamacenamos el valor medido del sensor
float b;                             //Declaramos la variable float para b 
int buf [10], temp;                  //Declaramos una matriz de de variables 

//Temperatura
int val;                             // Declaramos la variable val de tipo entero 


void setup() {
  //Oxigeno
  
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  Serial.begin(9600);                 //Inicializamos la comunicacion serial a 9600bps
  lcd.init();                         //iniciamos el lCD
  lcd.backlight();                    //Retroiluminacion 
  lcd.print("OXIGENO AGUA");          //Imprimimos en pantalla oxigeno en el agua
  lcd.setCursor(0,1);                 //Situamos el cursor en columna 0 y fila 1
  lcd.print("Valor: ");               //Imprimimos en esa fila de la palabra valor 

   


//PH
  Serial.println ("Ready");          //probamos la pantalla 

//Temperatura


pinMode(A1, INPUT);                  //Asignamos el pin A1 como entrada (sensor de temperatura)
pinMode(6, OUTPUT);                  //Asignamos el pin 6 como salida (led roja)
pinMode(7, OUTPUT);                  //Asignamos el pin 7 como salida (led verde)
 
}
void loop() { 
  //Oxigeno
  medirOxigeno();
  delay(300); 

  //PH
  medirPh();
  delay(300);

  //Temperatura
    medirTemperatura();
    delay (300); 
  
}

//Funcion que mide el oxigeno
void medirOxigeno(){
  value = analogRead(pot);            //leemos la entrada analogica
  delay(100);
  Serial.print("Valor pot: ");       //Imprimos valor pote
  Serial.println(value);              //Imprimimos ese valor
  lcd.setCursor(7,1);                 //Ubicamos el cursor del display en la columna 7 y fila 1
  lcd.print ("  ");                   //dejamos 4 columnas para que limpie cada ves que se mueva el potenciometro 
  lcd.setCursor(7,1);                 //Ubicamos otra ves la columna 7 y fila 1
  lcd.print(value);                   //Imprimimos el valor                 
}//Fin funcion medir oxigeno

 
//Funcion que mide el Ph
void medirPh(){
   for (int i=0;i<10;i++)             //obtenemos unos valores de muestra 
    { 
      buf [i]=analogRead (SensorPin);  //Asignamos a i sensor 
      delay(10);                       //Esperamos 10 segundos
    }
    for(int i=0;i<9;i++)                //ordenamos los valores 
    {
      for(int j=i+1;j<10;j++)           //creamos un contador de j=i  
      {
        if (buf[i]>buf[j])              //creamos una condicion 
        {
          temp=buf[i];                  //asignamos temp
          buf[i]=buf[j];
          buf[j]=temp;
        } 
      }   
    }
    avgValue=0;                         //lectura del medidor de ph
    for(int i=2;i<8;i++)                
      avgValue+=buf[i];                    //lectura del medidor mas la matriz
    
    float phValue=(float)avgValue*5.0/1024/6;   //ecuacion para la medida de ph
    phValue=3.5*phValue;                        //multiplicamos el valor por 3*5      
    Serial.print("   pH:");                      //Imprimimos ph
    Serial.print(phValue,5);                     // Imprimimos el valor
    Serial.println(" ");
}//Fin funcion medir Ph

//Funcion que mide la Temperatura

void medirTemperatura(){
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
}//Fin funcion medir Temperatura
