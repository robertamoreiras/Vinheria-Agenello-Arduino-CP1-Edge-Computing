/*	Grupo:Lara Mofid Essa Alssabak     RM:567947

          Maria Luisa Boucinhas Franco RM:567355

          Roberta Moreira dos Santos   RM:567825

*/

//Biblioteca para controlar o display LCD
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

// Pino do sensor
const int pinLDR  = A0; //pino para o sensor analógico de luminosidade

// LEDs
const int ledGreen   = 9; //Led verde indica condições normais
const int ledYellow  = 10; //Led amarelo indica condições de alerta
const int ledRed = 11; //Led vermelho indica condições criticas 

// Buzzer
const int buzzer = 13; //pino digital que conecta o buzzer

// Limites aceitaveis de luminosidade (%)
const int lumMin    = 40; //porcentagem minima de luminosidade
const int lumMax    = 80; //porcentagem maxima de luminosidade
const int margemLum = 10; //margem de tolerância para alerta

//Configurações da animação que aparecera no LCD
byte garrafa1[8] = {B00000, B01111, B01000, B01000, B01000, B01111, B00000, B00000}; //código fundo da garrafa
byte garrafa2[8] = {B00000, B11111, B11100, B11100, B11100, B11111, B00000, B00000}; //código meio da garrafa
byte garrafa3[8] = {B00000, B11110, B00011, B00001, B00011, B11110, B00000, B00000}; //código começo da garrafa
byte garrafa4 [8] = {B00000, B00000, B00000, B11000, B00000, B00000, B00000, B00000}; //código rolha da garrafa
byte gota [8] = {B00000, B00000, B00000, B11000, B00100, B00100, B01110, B00100}; //código gota de vinho saindo da garrafa
byte tacaVazia[8] = { B10001, B10001, B01010, B00100, B00100, B00100, B11111, B00000 };  //código taça vazia
byte tacaMetade[8] = { B10001, B11111, B01110, B00100, B00100, B00100, B11111, B00000 }; //código taca na metade
byte tacaCheia[8] = { B11111, B11111, B01110, B00100, B00100, B00100, B11111, B00000 }; //código taca cheia

void setup() {
  lcd.begin(16, 2); //Inicia o LCD com 16 colunas e 2 linhas
 lcd.createChar (0, garrafa1);
lcd.createChar (1, garrafa2);
lcd.createChar (2, garrafa3);
lcd.createChar (3, garrafa4);
lcd.createChar (4, gota);
lcd.createChar (5, tacaVazia);
lcd.createChar (6, tacaMetade);
lcd.createChar (7, tacaCheia);

//Faz a animação da garrafa de vinho enchendo a taça em 3 etapas e no final mostra somente a taça cheia
lcd.clear(); 
lcd.setCursor (5,0);
lcd.write(byte(0));
lcd.setCursor (6,0);
lcd.write(byte(1));
lcd.setCursor (7,0);
lcd.write(byte(2));
lcd.setCursor (8,0);
lcd.write(byte(3));
lcd.setCursor (8,1);
lcd.write(byte(5));
delay (500);

lcd.clear();
lcd.setCursor (5,0);
lcd.write(byte(0));
lcd.setCursor (6,0);
lcd.write(byte(1));
lcd.setCursor (7,0);
lcd.write(byte(2));
lcd.setCursor (8,0);
lcd.write(byte(4));
lcd.setCursor (8,1);
lcd.write(byte(6));
delay(500);

lcd.clear();
lcd.setCursor (5,0);
lcd.write(byte(0));
lcd.setCursor (6,0);
lcd.write(byte(1));
lcd.setCursor (7,0);
lcd.write(byte(2));
lcd.setCursor (8,0);
lcd.write(byte(4));
lcd.setCursor (8,1);
lcd.write(byte(7));
delay (500);
  
lcd.clear();
lcd.setCursor (5,0);
lcd.write(byte(0));
lcd.setCursor (6,0);
lcd.write(byte(1));
lcd.setCursor (7,0);
lcd.write(byte(2));
lcd.setCursor (8,0);
lcd.write(byte(3));
lcd.setCursor (8,1);
lcd.write(byte(7));
delay (500);

  lcd.setCursor(0, 0); //Posiciona o inicio da frase na primeira linha,primeira coluna
  lcd.print(" BEM-VINDO(a)!  "); //Exibe a mensagem bem-vindo(a)
  lcd.setCursor(0, 1); //Posiciona a segunda parte na segunda linha
  lcd.print("Vinheria Agnello"); //Nome da Vinharia
  delay(5000);//Aguarda 5 segundos antes de iniciar o loop principal

//Configura os pinos dos LEDs e buzzer como saída de informações da luminosidade
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);

//Garante que os LEDs e o buzzer comecem desligados
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(buzzer, LOW);
}

//Inicia o loop
void loop() {
  // Leitura do sensor 
  int leituraLDR = analogRead(pinLDR); //Lê o valor da luminosidade
  float luminosidade = map(leituraLDR, 0, 1023, 0, 100); //Converte o valor da luminosidade para uma escala 0% a 100%


  //Determinar status da luminosidade
  String statusLum;
  if (luminosidade < (lumMin - margemLum) || luminosidade > (lumMax + margemLum))
    statusLum = "Critica"; //Luminosidade fora do ideal
  else if ((luminosidade >= (lumMin - margemLum) && luminosidade < lumMin) ||
           (luminosidade > lumMax && luminosidade <= (lumMax + margemLum)))
    statusLum = "Alerta";//Luminosidade próxima do limite
  else
    statusLum = "OK";//Luminosidade dentro do intervalo estabelecido previsamente

  // Controle dos LEDs (baseado em luminosidade)
  if (statusLum == "OK") {
    digitalWrite(ledGreen, HIGH); //Led Verde acesso= luminosidade adequada
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
  } else if (statusLum == "Alerta") { //Led Amarelo acesso = atenção
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
  } else {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH); //Led Vermelho acesso = problema
  }

  // Buzzer vai tocar por 3 segundos se algum status for alerta ou crítico
  if (statusLum == "Critica") {
    // Estado crítico toca o buzzerccontínuo por 3 segundos
    tone(buzzer, 1000);   // Toca som de 1000 Hz
    delay(3000);          // Mantém som por 3 segundos
    noTone(buzzer);       // Desliga o som
  }

  else if (statusLum == "Alerta") {
    // Estado de alerta 3 bipes de 1 segundo cada, com pausa de 1 segundo
    for (int i = 0; i < 3; i++) { // Repete 3 vezes
      tone(buzzer, 1000);   // Liga buzzer
      delay(1000);          // Mantém som por 1 segundo
      noTone(buzzer);       // Desliga buzzer
      delay(1000);          // Espera 1 segundo antes do próximo toque
    }
  }

  else {
    // Estado normal garante que o buzzer fique desligado
    noTone(buzzer);
  }

 
  // Exibir luminosidade
  lcd.clear();
  lcd.setCursor(0, 0); //Define em qual linha a mensagem Luminosidade vai aparecer
  lcd.print("Luminosidade: ");
  lcd.print(luminosidade, 0); //Mostra luminosidade como numero inteiro
  lcd.print("%"); //Coloca o valor da luminosidade como porcentageem 
  lcd.setCursor(0, 1); //Define em qual linha vai aparecer o Status da luminosidade
  lcd.print("Status: ");
  lcd.print(statusLum); //Mostra qual é o status da luminosidade com base nas limitações que definimos anteriormente 
  delay(5000);
}
