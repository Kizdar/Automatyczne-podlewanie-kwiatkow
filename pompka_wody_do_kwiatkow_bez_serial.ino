#define Czuj_wilg A0
#define PWM 5
#define S1 2
#define S11 3
#define baterie A1
unsigned long aktualnyCzas=0;
unsigned long zapamietanyCzas=0;
int progmax=100;
int progmin=75;
char dane;
int Czuj_wilg1=0;
int stanBaterii=0;
boolean Wlacz_komunikacje=false;
int i=0;
int sprawdzenie_wilg1=0;
boolean stan_pompy=false;

void setup() {
 Serial.begin(9600);
 pinMode(baterie,INPUT);
 pinMode(Czuj_wilg,INPUT);
 pinMode(PWM,OUTPUT);
 pinMode(S1,OUTPUT);
 pinMode(S11,OUTPUT);
 digitalWrite(S1,LOW);
 digitalWrite(S11,LOW);
 //ProbaSystemu();
}

void DoBloutooth(){
  if (stan_pompy==true)
  Serial.println("*zR0G255B0*");
  else
  Serial.println("*zR255G0B0*");
  stanBaterii=map(analogRead(baterie),400,1024,0,100);
  Serial.print("*T");
  Serial.print(stanBaterii);
  Serial.println("*");
Serial.print("*D");
Serial.print(Czuj_wilg1);
Serial.println("*");
Serial.print("*HX"+String(i++)+"Y"+String(Czuj_wilg1));  
if(i==500){
  Serial.print("*HX"+String(i++)+"Y"+String(0));  
i=0;
  }
}

void Wlacz_pompe(){
  stan_pompy=true;
  digitalWrite(S1, HIGH);
   digitalWrite(S11, LOW);
   analogWrite(PWM, 255);
  }
  
void Wylacz_pompe(){
  stan_pompy=false;
  digitalWrite(S1, LOW);
   digitalWrite(S11, LOW);
   analogWrite(PWM, LOW);
  }

void Czytanie_danych(){  
  if(dane == 'L') // Przełącznik po lewej
  ;
  if(dane == 'l')
  ;
  if(dane == 'C') // Przycisk zasilania
  Wlacz_komunikacje=true;
  if(dane == 'c')
  Wlacz_komunikacje=false;
  if(dane == 'P') // Przełącznik po prawej
  progmin=0;
  if(dane == 'p')
  progmin=75; // Uwaga!!! czy pompa nie bedzie cały czas wylaczona
  if(dane == 'R') // Przycisk czerwony
  ;
  if(dane == 'r')
  ;
  if(dane == 'G') // Przycisk zielony
  ;
  if(dane == 'g')
  ;
  if(dane == 'B') // Przycisk niebieski
  i=0;
  if(dane == 'b')
  ;
/*  if(dane=='S'){
    Suwak_srodek=Serial.parseInt();
  }
  if(dane=='A'){
    Suwak_lewy=Serial.parseInt();
  }
  if(dane=='a'){
    Suwak_prawy=Serial.parseInt();
  }
  if(dane=='i'){
    while(true){
      if(Serial.available()){
        dane=Serial.read();
        if(dane=='X') Galka_lewax=serial.parseInt();
        if(dane=='Y') Galka_leway=serial.parseInt();
        if(dane=='Y') break;
        }
      }
    }

    if(dane=='k'){
    while(true){
      if(Serial.available()){
        dane=Serial.read();
        if(dane=='X') Galka_prawax=serial.parseInt();
        if(dane=='Y') Galka_praway=serial.parseInt();
        if(dane=='Y') break;
        }
      }
    }*/
}


void loop() {
  
    if (Serial.available()){
  dane=Serial.read();
  Czytanie_danych();
  }
 
 Czuj_wilg1=map(analogRead(Czuj_wilg),0,1024,0,150);
 // Serial.print("Czujnik = ");
 // Serial.println(Czuj_wilg1);
  
  if(Czuj_wilg1> progmin)
   Wlacz_pompe();
    else
   Wylacz_pompe();

    aktualnyCzas= millis();
    
   if(aktualnyCzas-zapamietanyCzas >= 2000UL){
  zapamietanyCzas=aktualnyCzas;
   if(Wlacz_komunikacje==true)
   DoBloutooth();
   }
}

void ProbaSystemu(){
  digitalWrite(S1,HIGH);
  digitalWrite(S11,LOW);
  for(int i=0;i<=255;i=i+5){
    analogWrite(PWM,i);
    delay(100);
   // Serial.print("i= ");
   // Serial.print(i);
   // Serial.print("    ");
  //  Serial.print("Stan silnika: ");
   // Serial.print(digitalRead(S1));
   // Serial.print(", ");
   // Serial.println(digitalRead(S11));
    }
    digitalWrite(S1,LOW);
    digitalWrite(S11,LOW);
    analogWrite(PWM, LOW);
 
  }
