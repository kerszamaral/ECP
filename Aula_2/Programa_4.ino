//Ian Kersz - Cartão UFRGS: 00338368
//15.03.22

//Os LEDs viram um contador de distancia entre 2 e 31cm
//Após isso, LEDs acendem em ordem crescente e apagam em ordem decrescente gradualmente

//Variaveis e Definições globais
const int led[5] = {11, 10, 9, 6, 5};  //Portas dos LEDs
const int trigPin = 3, echoPin = 2; //Portas do sensor
int bri = 0, fade = 15, m = 4, l = 0; // Brightness, o quanto PWM varia, contadores pros LEDs

int sensor()    //Função para ativar o sensor e converter o tempo para distancia
{
    int distancia = 0, dur = 0;

    digitalWrite(trigPin, 0); 
    delayMicroseconds(2);
    digitalWrite(trigPin, 1);
    delayMicroseconds(10);
    digitalWrite(trigPin, 0);
    dur = pulseIn(echoPin, 1);
    distancia = (dur / 2.0) * 0.034;

    return distancia;   //Retorna a distancia 
}

void reset() //Função para resetar as variaveis do fade
{
    l = 0;
    m = 4;
    fade = 15;
    bri = 0;
}

void setup()    //Setup das portas do arduino
{
    for (int i = 0; i <= 4; i++)  //Loop para configurar todos os LEDs
        pinMode(led[i], OUTPUT);

    pinMode(trigPin, OUTPUT); //Output pin do sensor
    pinMode(echoPin, INPUT); //Input pin do sensor
}

void loop() //Loop de execução do arduino
{
    int arr[9] = {0}, k = 9, x = 0, d = 0;   //Definição das variaveis para contar
    //Array de tamanho 9 pois a distancia maxima do sensor é 500 cm, assim não causando overflow (2^9 = 512)
    //Contador só mede até 32 cm
    x = d = sensor(); //Duplicação da variavel d em x

    if(d > 2 && d < 32) //Teste para só contar se a d é entre 2 e 32 cm
    {
        while (x!=0) //Transforma a d em decimal para binario e coloca no bit correto do array
        {
            arr[k] = x % 2;
            x = x/2;
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
        for (int i = 4; i >= 0; i--) //Apaga todos
            digitalWrite(led[i], 0);
        reset();
    }
    else //Caso a distancia seja maior pisca
    {   
        analogWrite(led[m], bri); //Escreve bri para o LED m
        bri = bri + fade; //Adiciona a variação ao bri
        if (l <= 4) //Contador para saber se chegamos no quinto LED em potencia maxima
        {   
            if (bri > 255) //Reset de bri e passa para o proximo LED na cadeia
            {
                bri = 0;
                m--;
                l++;
            }
        }
        else //Após chegar no ultimo LED e potencia Max
        {
            if (bri < 0) //Reset de bri e passa para o LED anterior na cadeia
            {
                bri = 255;
                m++;
            }
        }
        if (m == -1) //Troca o sinal da variação pra poder apagar em ordem reversa
            fade = -fade;
        if (m == 5) //Reset do Loop inteiro de LEDs
            reset();
        delay(5);
    }
}