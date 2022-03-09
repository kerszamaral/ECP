//Ian Kersz - Cartão UFRGS: 00338368
//08.03.22
//4 lEDs acendem em ordem crescente e apagam em ordem decrescente,
//Ao pressionar o botão, os 4 lEDs viram um contador de 4 bits(ou seja, 16 numeros)
//Após isso, retornam a sua função normal 

//Definição da quantidade de lEDs(-1) e definição do tempo de delay em milisegundos
//É possivel fazer o contador ter quantos bits quiser, 
//basta incrementar o TAM(Será sempre o numero de LEDs -1) e adicionar a porta ao array
#define TAM 3
#define TEM 1000

//Definição das variaveis globais, que são as portas dos LEDs e do botão
int led[TAM+1] = {12,11,10,9};
int buttonPin = 2;

//Criação da função para apagar todos os LEDs
void TODOS(int estado)
{
    for (int i = TAM; i >= 0; i--)
    {
        digitalWrite(led[i], estado);
    }
}
//Criação da função para fazer os LEDs piscarem
void PISCAR(char ordem, int estado)
{
    if (ordem == 'c') //Ordem crescente
    {
        for (int i = TAM; i >= 0; i--)
        {
            digitalWrite(led[i], estado);
            //caso o botão seja pressionado no meio da função
            if (digitalRead(buttonPin) == 1)
            return;
            //Delay mais curto
            delay(TEM / 2);
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
            //Delay mais curto
            delay(TEM / 2);
        }
    }
    
}
//Criação da função para fazer os LEDs serem um contador de 4 bits
void CONTADOR()
{
    //Definição do array para contar os bits
    int arr[TAM+1] = {0};
    //Loop para contar até 16
    for (int i = 0; i < pow(2,TAM+1); i++)
    {
        //Matematica para configurar qual LED está aceso no array ou não naquele momento
        for (int j = TAM; j >= 0; j--)
        {
            arr[j]= i / (int)ceil(pow(2,TAM-j)) % 2;
        }
        //Loop para acender ou apagar o LED da posição j em função do bit localizado em j
        for (int j = 0; j <= TAM; j++)
        {
            if (arr[j] == 1)
            {
                digitalWrite(led[j], HIGH);
            }
            else
            {
                digitalWrite(led[j], LOW);
            }
        }
        delay(TEM);
    }
    TODOS(0);
}
//Setup das portas do arduino
void setup()
{
    //Loop para configurar todos os LEDs e depois o botão
    for (int i = 0; i <= TAM; i++)
    {
        pinMode(led[i], OUTPUT);
    }
    pinMode(buttonPin, INPUT);
}
//Loop de execução do arduino
void loop()
{
    //Função para ver se o botão está pressionado ou não
    switch (digitalRead(buttonPin))
    {
    case 1: //Caso sim, inicia o contador
        CONTADOR();
        break;
    case 0: //caso não, inicia piscar
        PISCAR('c',1);
        PISCAR('d',0);
        break;
    }
}