//Ian Kersz - Cartão UFRGS: 00338368
//08.03.22
//Botão

#define TAM 3
#define TEM 1000

int led[TAM+1] = {12,11,10,9};
int buttonPin = 2;

void PISCAR()
{
    for (int i = TAM; i >= 0; i--)
    {
        digitalWrite(led[i], HIGH);
        if (digitalRead(buttonPin) == 1)
            return;
        delay(TEM / 2);
    }
    for (int i = 0; i <= TAM; i++)
    {
        digitalWrite(led[i], LOW);
        if (digitalRead(buttonPin) == 1)
            return;
        delay(TEM / 2);
    }
}

void CONTADOR()
{
    int arr[4] = {0};
    for (int i = 0; i < 16; i++)
    {
        arr[3] = i % 2;
        arr[2] = i / 2 % 2;
        arr[1] = i / 2 / 2 % 2;
        arr[0] = i / 2 / 2 / 2 % 2;
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
}

void setup()
{
    for (int i = 0; i <= TAM; i++)
    {
        pinMode(led[i], OUTPUT);
    }
    pinMode(buttonPin, INPUT);
}

void loop()
{
    if (digitalRead(buttonPin) == 1)
        CONTADOR();
    if(digitalRead(buttonPin) == 0)
        PISCAR();
}