#include <Wire.h>                     //Libreria
#include <LiquidCrystal_I2C.h>        //Libreria responsable del manejo de la pantalla LCD
LiquidCrystal_I2C lcd(0x3F,16,2);     //Adaptador de protocolo I2C permitir comunicacion display con arduino

byte pot = A0;                        //Variable de 8bits que tiene de entrada A0 y puede guardar valores de el potenciometro
int value = 0;                        //lectrura del valor del potenciometro en un entero

void setup(){
  Serial.begin(9600);                 //Inicializamos la comunicacion serial a 9600bps
  lcd.init();                         //iniciamos el lCD
  lcd.backlight();                    //Retroiluminacion 
  lcd.print("OXIGENO AGUA");          //Imprimimos en pantalla oxigeno en el agua
  lcd.setCursor(0,1);                 //Situamos el cursor en columna 0 y fila 1
  lcd.print("Valor: ");               //Imprimimos en esa fila de la palabra valor 
}

void loop (){
  value = analogRead(pot);            //leemos la entrada analogica
  Serial.print("Valor pote: ");       //Imprimos valor pote
  Serial.println(value);              //Imprimimos ese valor
  lcd.setCursor(7,1);                 //Ubicamos el cursor del display en la columna 7 y fila 1
  lcd.print ("  ");                   //dejamos 4 columnas para que limpie cada ves que se mueva el potenciometro 
  lcd.setCursor(7,1);                 //Ubicamos otra ves la columna 7 y fila 1
  lcd.print(value);                   //Imprimimos el valor
  delay(300);                         //Esperamos unos segundos 
 
}
