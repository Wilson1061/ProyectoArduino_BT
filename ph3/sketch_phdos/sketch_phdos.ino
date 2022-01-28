#define SensorPin A0                 //medidor de ph es conectado con el arduino
unsigned long int avgValue;          //Alamacenamos el valor medido del sensor
float b;                             //Declaramos la variable float para b 
int buf [10], temp;                  //Declaramos una matriz de de variables 

void setup ()
{
  Serial.begin (9600);               // Inicializamos la comunicacion serial a 9600bps
  Serial.println ("Ready");          //probamos la pantalla 
  
}
void loop()
{
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
  delay(800);                                   
}
  
