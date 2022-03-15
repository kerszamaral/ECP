//Ian Kersz - Cartão UFRGS: 00338368
//13.03.22

//LEDs acendem em ordem crescente e apagam em ordem decrescente,
//Ao pressionar o botão, os lEDs viram um contador de bits
//Após isso, retornam a sua função normal 
//Agora sem mais o bugo do delay!

//Variaveis e Definições globais (É possivel fazer o contador ter quantos bits quiser) 
#define TAM 4   //Quantidade de LEDs (sempre -1 do que no real)
#define TEM 1000    //Delay de todas as atividades em Millisegundos
const int led[TAM + 1] = {11,10,9,6,5};  //Adicionar portas dos LEDs
const int trigPin = 3, echoPin = 2; //Porta do botão

void setup()    //Setup das portas do arduino
{
    Serial.begin(9600);
    for (int i = 0; i <= TAM; i++)  //Loop para configurar todos os LEDs e botão
        pinMode(led[i], OUTPUT);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}
int duracao = 0, distancia = 0;
void loop() //Loop de execução do arduino
{
    digitalWrite(trigPin,0);
    delayMicroseconds(2);
    digitalWrite(trigPin,1);
    delayMicroseconds(10);
    digitalWrite(trigPin,0);
    duracao = pulseIn(echoPin, 1);
    distancia = (duracao/2.0)*0.034;
    
    int arr[9] = {0}, i = 9, y = 0, x = distancia;   //Definição do array para contar os bits
    if(distancia >= 2 && distancia <=31){
        while (x!=0)
        {
            y=x%2;
            x=x/2;
            arr[i]=y;
            i--;
        }
        for (int j = 0; j <= 9; j++)  //Loop On/Off LED da posição j
        {
            if (arr[j] == 1)
                digitalWrite(led[j-5], 1);
            else
                digitalWrite(led[j-5], 0);
        }
    }
    if (distancia >= 32)
    {
        for (int i = 4; i >= 0; i--){
            for (int j = 0; j < 256; j++){
                analogWrite(led[i], j);
                delay(TEM / 1000);
            }
        }
        for (int i = 0; i < 5; i++){
            for (int j = 255; j >= 0; j--){
                analogWrite(led[i], j);
                delay(TEM / 1000);
            }
        }
    }
    delay(50);
    // entre 32 e 340
    // 5 leds
    //255 niveis por led
}