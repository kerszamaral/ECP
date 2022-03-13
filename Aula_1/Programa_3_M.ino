//Ian Kersz - Cartão UFRGS: 00338368
//13.03.22

//LEDs acendem em ordem crescente e apagam em ordem decrescente,
//Ao pressionar o botão, os lEDs viram um contador de bits
//Após isso, retornam a sua função normal 

//Variaveis e Definições globais (É possivel fazer o contador ter quantos bits quiser) 
#define TAM 3   //Quantidade de LEDs (sempre -1 do que no real)
#define TEM 1000    //Delay de todas as atividades em Millisegundos
const int led[TAM + 1] = {12,11,10,9};  //Adicionar portas dos LEDs
const int buttonPin = 2; //Porta do botão
unsigned long previousMillis = 0;
int k = TAM, l = 0; //Variaveis utilizada para piscar

void TODOS(int estado)  //Criação da função para apagar todos os LEDs
{
    for (int i = TAM; i >= 0; i--)
        digitalWrite(led[i], estado);
}

void CONTADOR() //Criação da função para LEDs serem um contador de 4 bits
{
    int arr[TAM + 1] = {0};   //Definição do array para contar os bits
    
    for (int i = 0; i < pow(2, TAM + 1); i++)  //Loop para contar até 16
    {
        for (int j = TAM; j >= 0; j--)  //Matematica para configurar Posição On/Off no array
            arr[j]= i / (int)ceil(pow(2, TAM - j)) % 2;
        
        for (int j = 0; j <= TAM; j++)  //Loop On/Off LED da posição j
        {
            if (arr[j] == 1)
                digitalWrite(led[j], 1);
            else
                digitalWrite(led[j], 0);
        }
        delay(TEM);
    }
    TODOS(0);
    delay(TEM / 2);
}

void setup()    //Setup das portas do arduino
{
    for (int i = 0; i <= TAM; i++)  //Loop para configurar todos os LEDs e botão
        pinMode(led[i], OUTPUT);

    pinMode(buttonPin, INPUT);
}

void loop() //Loop de execução do arduino
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= TEM/3) 
    {
        previousMillis = currentMillis;
        if(l == 0)
        {
            if (k == 0)
                l = 1;
            digitalWrite(led[k], 1);
            k--;
        }
        if(l == 1)
        {
            if (k == TAM)
                l = 0;
            digitalWrite(led[k], 0);
            k++;
        }
    }
    if (digitalRead(buttonPin) == 1)
        CONTADOR();
    
}