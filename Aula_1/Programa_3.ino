// Ian Kersz - Cartão ufrgs: 00338368
// 08.03.22
//Botão

int ledPin = 13;
int buttonPin = 8;

void setup()
{
    pinMode(ledPin,OUTPUT);
    pinMode(buttonPin,INPUT);
}

void loop()
{
    int x;
    x = digitalRead(buttonPin);

    if (x == 1)
    {
        digitalWrite(ledPin,HIGH);
    }
    else if(x == 0)
    {
        digitalWrite(ledPin,LOW);
    }
    delay(1000);
}