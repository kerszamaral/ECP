//Ian Kersz - Cartão UFRGS: 00338368
//08.03.22

//LEDs acendem em ordem crescente e apagam em ordem decrescente,
//Ao pressionar o botão, os lEDs viram um contador de bits
//Após isso, retornam a sua função normal 

//Variaveis e Definições globais (É possivel fazer o contador ter quantos bits quiser) 
#define TAM 3   //Quantidade de LEDs (sempre -1 do que no real)
#define TEM 1000    //Delay de todas as atividades em Millisegundos
int led[TAM + 1] = {12,11,10,9};  //Adicionar portas dos LEDs
int buttonPin = 2; //Porta do botão

void TODOS(int estado)  //Criação da função para apagar todos os LEDs
{
    for (int i = TAM; i >= 0; i--)
        digitalWrite(led[i], estado);
}
void PISCAR(char ordem, int estado) //Criação da função para fazer os LEDs piscarem
{
    if (ordem == 'c') //Ordem crescente
    {
        for (int i = TAM; i >= 0; i--)
        {
            digitalWrite(led[i], estado);
            //caso o botão seja pressionado no meio da função
            if (digitalRead(buttonPin) == 1)
            return;
            delay(TEM / 2); //Delay mais curto
        }
    }
    else if (ordem == 'd') //Ordem decrescente
    {
        for (int i = 0; i <= TAM; i++)
        {
            digitalWrite(led[i], estado);
            //caso o botão seja pressionado no meio da função
            if (digitalRead(buttonPin) == 1)
                return;
            delay(TEM / 2); //Delay mais curto
        }
    }
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
    switch (digitalRead(buttonPin)) //Função para ver se o botão está pressionado ou não
    {
    case 1: //Caso sim, inicia o contador
        CONTADOR();
        break;
    case 0: //Caso não, inicia piscar, com Ordem e estado desejado
        PISCAR('c',1);
        PISCAR('d',0);
        break;
    }
}