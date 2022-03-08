// Ian Kersz - Cartão ufrgs: 00338368
// 08.03.22
//Ler teclado e fazer Led acender

int ledPin = 13;

void setup()
{
    pinMode(ledPin,OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    char tecla;

    tecla = Serial.read();

    if (tecla == 'l')
    {
        digitalWrite(ledPin,HIGH);
    }
    else if( tecla == 'd')
    {
        digitalWrite(ledPin,LOW);
    }
    delay(1000);
}