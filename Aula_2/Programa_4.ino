//Ian Kersz - Cartão UFRGS: 00338368
//15.03.22

//Os LEDs viram um contador de distancia entre 2 e 31cm
//Após isso, LEDs acendem em ordem crescente e apagam em ordem decrescente gradualmente

//Variaveis e Definições globais
const int led[5] = {11,10,9,6,5};  //Portas dos LEDs
const int trigPin = 3, echoPin = 2; //Portas do sensor

void setup()    //Setup das portas do arduino
{
    for (int i = 0; i <= 4; i++)  //Loop para configurar todos os LEDs e botão
        pinMode(led[i], OUTPUT);

    pinMode(trigPin, OUTPUT); //Output pin do sensor
    pinMode(echoPin, INPUT); //Input pin do sensor
}

void loop() //Loop de execução do arduino
{
    int arr[9] = {0}, k = 9, x = 0, distancia = 0, duracao = 0;   //Definição das variaveis para contar

    digitalWrite(trigPin, 0); //Função para ativar o sensor e converter o tempo para distancia
    delayMicroseconds(2);
    digitalWrite(trigPin, 1);
    delayMicroseconds(10);
    digitalWrite(trigPin, 0);
    duracao = pulseIn(echoPin, 1);
    distancia = (duracao/2.0)*0.034;
    x = distancia; //Duplicação da variavel distancia em x

    if(distancia > 2 && distancia < 32) //Teste para só contar se a distancia é entre 2 e 32 cm
    {
        while (x!=0) //Transforma a distancia em decimal para binario e coloca no bit correto do array
        {
            arr[k]=x%2;
            x=x/2;
            k--;
        }
        for (int j = 0; j <= 9; j++)  //Loop On/Off LED da posição j
        {
            if (arr[j] == 1)
                digitalWrite(led[j-5], 1);
            else
                digitalWrite(led[j-5], 0);
        }
        delay(50);
    }
    if (distancia >= 32) //Caso a distancia seja maior pisca
    {
        for (int i = 4; i >= 0; i--) //Apaga todos
            digitalWrite(led[i], 0);
        for (int i = 4; i >= 0; i--) //Acende todos em ordem crescente PWM
        {
            for (int j = 0; j < 256; j++)
            {
                analogWrite(led[i], j);
                delay(1);
            }
        }
        for (int i = 0; i < 5; i++) //Apaga todos em ordem decrescente PWM
        {
            for (int j = 255; j >= 0; j--)
            {
                analogWrite(led[i], j);
                delay(1);
            }
        }
    }
}