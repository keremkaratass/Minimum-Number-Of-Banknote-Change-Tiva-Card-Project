/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

const int buttonPin = PUSH2;     // the number of the pushbutton pin
const int ledPin =  RED_LED;      // the number of the LED pin
const int ledPin2 =  GREEN_LED;
      int buttonState = 0; 
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  
  pinMode(PD_0, OUTPUT); 
  pinMode(PD_1, INPUT_PULLUP);
  pinMode(PD_2, INPUT_PULLUP);
  pinMode(PD_3, INPUT_PULLUP);
  pinMode(PB_0, INPUT_PULLUP);
  pinMode(PE_1, INPUT_PULLUP);
  pinMode(PE_2, INPUT_PULLUP);
  pinMode(PE_3, INPUT_PULLUP);
  pinMode(PB_1, INPUT_PULLUP);
  pinMode(PC_6, INPUT_PULLUP);
  pinMode(PC_4, INPUT_PULLUP);  
  pinMode(PC_5, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT); 
  pinMode(ledPin2, OUTPUT);      
  pinMode(buttonPin, INPUT_PULLUP);     
  Serial.begin(9600);
  
 
}

//banknot adetlerini tanımlıyoruz.
  int tl5=20;
  int tl10=20;
  int tl20=10;
  int tl50=30;
  int tl100=5;

//bu değerlerle o anki işlem sırasında kasaya aktarılan banknot adetlerini tutuyoruz.
  int atilantl5=0;
  int atilantl10=0;
  int atilantl20=0;
  int atilantl50=0;
  int atilantl100=0;

//para üstü olarak verilicek banknotları tutuyoruz.
  int paraustutl5=0;
  int paraustutl10=0;
  int paraustutl20=0;
  int paraustutl50=0;
  int paraustutl100=0;
  

//para atma işlemindeki butonların değerlerini boolean pn ler ile tutuyoruz.
  boolean p1;
  boolean p2;
  boolean p3;
  boolean p4;
  boolean p5;
  boolean p6;
  boolean p6used=false;
  int atilanpara=0;
  int toplampara=0;
// hizmet butonlarını tanımlıyoruz.
  boolean h1;
  boolean h2;
  boolean h3;
  boolean h4;
  boolean h5;
  int h1adet=30;
  int h2adet=50;
  int h3adet=100;
  int h4adet=20;

// hizmetlerin kaç kez kullanıldıgını tutuyoruz.
  int h1count=0;
  int h2count=0;
  int h3count=0;
  int h4count=0;

  int rnd=0;
  int hatacount=0;
  
// the loop routine runs over and over again forever:
void loop() {


  //buton giriş değerlerini boolean tanımlı verilere atıyoruz
    p1=  digitalRead(PD_1);
    p2=  digitalRead(PD_2);
    p3=  digitalRead(PD_3);
    p4=  digitalRead(PE_1);
    p5=  digitalRead(PE_2);
    p6=  digitalRead(PE_3); 
    h1=  digitalRead(PB_0);
    h2=  digitalRead(PB_1);
    h3=  digitalRead(PC_4);
    h4=  digitalRead(PC_5);
    h5=  digitalRead(PC_6);
    buttonState = digitalRead(buttonPin); 
    atilanpara=atilantl5*5+atilantl10*10+atilantl20*20+atilantl50*50+atilantl100*100;

    if(rnd==2){
      digitalWrite(ledPin2,LOW);
      digitalWrite(ledPin,HIGH);
    }
    else{
      digitalWrite(ledPin,LOW);
      digitalWrite(ledPin2,HIGH);
    }

    if(digitalRead(ledPin)==HIGH && hatacount==0){
      Serial.println("Paranız sıkıştı! İşlem iptali için reset butonunu tuşlayın.");
      hatacount++;
    }
      
      

    if(p1==LOW){
      tl5++;
      atilantl5++;
      delay(500);
    }
    
    if(p2==LOW){
      tl10++;
      atilantl10++;
      delay(500);
    }
    
    if(p3==LOW){
      tl20++;
      atilantl20++;
      delay(500);
    }
    
    if(p4==LOW){
      tl50++;
      atilantl50++;
      delay(500);
    }
   
    if(p5==LOW){
      tl100++;
      atilantl100++;
      delay(500);
    }
    


    if(p6==LOW){
      toplampara=atilanpara;
      Serial.print(atilanpara);  
      Serial.println("TL para attınız");  
      p6used=true;

      rnd=random(4);
      hatacount=0;
      delay(500);
    }
    
    if(h1==LOW){
      h1count++;
      toplampara-=15;
      h1adet--;
      delay(500);
    }

    if(h2==LOW){
      h2count++;
      toplampara-=10;
      h2adet--;
      delay(500);
    }

    if(h3==LOW){
      h3count++;
      toplampara-=5;
      h3adet--;
      delay(500);
    }

    if(h4==LOW){
      h4count++;
      toplampara-=50;
      h4adet--;
      delay(500);
    }

    if(h5==LOW){
      if(toplampara<0)
      Serial.println("Yeterli miktarda para yatırmadınız! Reset butonunu kullanınız.");
      else if(h1adet<0 || h2adet<0 || h3adet<0 || h4adet<0)
      Serial.println("Seçtiğiniz hizmetlerden birisi kullanılamıyor.");      
      else{
        Serial.print("Para üstünüz ");
        Serial.print(toplampara);
        Serial.println(" TL");
      
      //para üstünü en büyük banknotlarla verme işlemi

      paraustu:
      
      if(100<=toplampara && tl100>0){
        paraustutl100++;
        tl100--;
        toplampara-=100;
        goto paraustu;
      }

      if(50<=toplampara && tl50>0){
        paraustutl50++;
        tl50--;
        toplampara-=50;
        goto paraustu;
      }

      if(20<=toplampara && tl20>0){
        paraustutl20++;
        tl20--;
        toplampara-=20;
        goto paraustu;
      }

      if(10<=toplampara && tl10>0){
        paraustutl10++;
        tl10--;
        toplampara-=10;
        goto paraustu;
      }

      if(5<=toplampara && tl5>0){
        paraustutl5++;
        tl5--;
        toplampara-=5;
        goto paraustu;
      }

      if(toplampara==0){
        Serial.print(paraustutl5);
        Serial.println(" tane 5tl");
        Serial.print(paraustutl10);
        Serial.println(" tane 10tl");
        Serial.print(paraustutl20);
        Serial.println(" tane 20tl");
        Serial.print(paraustutl50);
        Serial.println(" tane 50tl");
        Serial.print(paraustutl100);
        Serial.println(" tane 100tl");
        paraustutl5=0;
        paraustutl10=0;
        paraustutl20=0;
        paraustutl50=0;
        paraustutl100=0;
        atilantl5=0;
        atilantl10=0;
        atilantl20=0;
        atilantl50=0;
        atilantl100=0;
        h1count=0;
        h2count=0;
        h3count=0;
        h4count=0;
        p6used=false;
      }
      else{
        Serial.println("para üstü verilemiyor.");
      }
      
      }
      
      delay(500);
      
    }

    //reset butonu (sw2)
    if(buttonState == LOW){
      if(p6used==true ){
        paraustutl5=atilantl5;
        paraustutl10=atilantl10;
        paraustutl20=atilantl20;
        paraustutl50=atilantl50;
        paraustutl100=atilantl100;
      }
        
        while(atilantl5>0){
          tl5--;
          atilantl5--;
        }
        while(atilantl10>0){
          tl10--;
          atilantl10--;
        }
        while(atilantl20>0){
          tl20--;
          atilantl20--;
        }
        while(atilantl50>0){
          tl50--;
          atilantl50--;
        }
        while(atilantl100>0){
          tl100--;
          atilantl100--;
        }
        while(h1count>0){
          toplampara+=15;
          h1adet++;
          h1count--;
        }
        while(h2count>0){
          toplampara+=10;
          h2adet++;
          h2count--;
        }
        while(h3count>0){
          toplampara+=5;
          h3adet++;
          h3count--;
        }
        while(h4count>0){
          toplampara+=50;
          h4adet++;
          h4count--;
        }
        
        Serial.print("Para iadeniz ");
        Serial.print(toplampara);
        Serial.println(" TL");
        Serial.print(paraustutl5);
        Serial.println(" tane 5tl");
        Serial.print(paraustutl10);
        Serial.println(" tane 10tl");
        Serial.print(paraustutl20);
        Serial.println(" tane 20tl");
        Serial.print(paraustutl50);
        Serial.println(" tane 50tl");
        Serial.print(paraustutl100);
        Serial.println(" tane 100tl");

         paraustutl5=0;
        paraustutl10=0;
        paraustutl20=0;
        paraustutl50=0;
        paraustutl100=0;
        toplampara=0;
        p6used=false;
        digitalWrite(ledPin,LOW);
        digitalWrite(ledPin2,HIGH);
        rnd=0;
        delay(500);
    }

    
    
}
