//IMPORTANTE: MANTER PORTAS NA MSM ORDEM, mesmo que as portas em si sejam alteradas
int vermelho_norte  = 13;
int amarelo_norte   = 12;
int verde_norte     = 11;

int vermelho_oeste  = 10;
int amarelo_oeste   = 9 ;
int verde_oeste     = 8 ;

int vermelho_sul    = 7 ;
int amarelo_sul     = 6 ;
int verde_sul       = 5 ;

int vermelho_leste  = 4 ;
int amarelo_leste   = 3 ;
int verde_leste     = 2 ;

unsigned long int current_timer = 0;
int next_action     = 0 ;
int current_mode    = 0 ;
int current_signal  = 1 ;

/*int carro_sul = ;
int carro_oeste = ;
int carro_norte = ;
int carro_leste = ;


int Pvermelho_norte  = ;
int Pverde_norte     = ;

int Pvermelho_oeste  = ;
int Pverde_oeste     = ;

int Pvermelho_sul    = ;
int Pverde_sul       = ;

int Pvermelho_leste  = ;
int Pverde_leste     = ;


int pedestre_sul = ;
int pedestre_oeste = ;
int pedestre_norte = ;
int pedestre_leste = ;


#define P_ON_LEFT 1
#define P_ON_UP 1
#define P_ON_RIGHT 1
#define P_ON_BOTTOM 1
int pedestre[4]={P_ON_LEFT,P_ON_UP,P_ON_RIGHT,P_ON_BOTTOM};*/
//pinos com interrupt no arduino mega: 	2, 3, 18, 19, 20, 21 (pins 20 & 21 nem sempre, pois podem ser usados pra comunicação)


#define CAR_ON_LEFT 1
#define CAR_ON_UP 1
#define CAR_ON_RIGHT 1
#define CAR_ON_BOTTOM 1
int carros[4]={CAR_ON_LEFT,CAR_ON_UP,CAR_ON_RIGHT,CAR_ON_BOTTOM};

void ligar_sul  ();
void ligar_norte();
void ligar_leste();
void ligar_oeste();

void setup() {

  pinMode(vermelho_norte, OUTPUT);
  pinMode(amarelo_norte, OUTPUT);
  pinMode(verde_norte, OUTPUT);
 
  pinMode(vermelho_oeste, OUTPUT);
  pinMode(amarelo_oeste, OUTPUT);
  pinMode(verde_oeste, OUTPUT);
  
  pinMode(vermelho_sul, OUTPUT);
  pinMode(amarelo_sul, OUTPUT);
  pinMode(verde_sul, OUTPUT);
  
  pinMode(vermelho_leste, OUTPUT);
  pinMode(amarelo_leste, OUTPUT);
  pinMode(verde_leste, OUTPUT);
  
  /*
  pinMode(Pvermelho_norte, OUTPUT);
  pinMode(Pverde_norte, OUTPUT);
 
  pinMode(Pvermelho_oeste, OUTPUT);
  pinMode(Pverde_oeste, OUTPUT);
  
  pinMode(Pvermelho_sul, OUTPUT);
  pinMode(Pverde_sul, OUTPUT);
  
  pinMode(Pvermelho_leste, OUTPUT);
  pinMode(Pverde_leste, OUTPUT);
  
  */
  
  Serial.begin(9600);
  digitalWrite(vermelho_sul   , HIGH);
  digitalWrite(vermelho_oeste , HIGH);
  digitalWrite(vermelho_norte , HIGH);
  digitalWrite(vermelho_leste , HIGH);

  Serial.print("Digite o comando: 's', 'o', 'n', 'l' para sinaleiras\n'S', 'O', 'N', 'L' para pedestres\n");

  /*pinMode(carro_sul  , INPUT);
  pinMode(carro_oeste, INPUT);
  pinMode(carro_norte, INPUT);
  pinMode(carro_leste, INPUT);

  pinMode(pedestre_sul  , INPUT);
  pinMode(pedestre_oeste, INPUT);
  pinMode(pedestre_norte, INPUT);
  pinMode(pedestre_leste, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(pedestre_sul  ), Ppedestre_sul, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pedestre_norte), Ppedestre_norte, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pedestre_oeste), Ppedestre_oeste, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pedestre_leste), Ppedestre_leste, CHANGE);*/
}

void transition(int first, int last, int pedestre){
    delay(500);
  	/*if(pedestre){
        digitalWrite(Pverde_leste+(first*2)  , LOW);
        digitalWrite(Pverde_leste+(first*2)+1, HIGH);
    }*/
    digitalWrite(verde_leste+(first*3)   , LOW );//carro desliga verde atual
    digitalWrite(verde_leste+(first*3)+1 , HIGH);//carro liga amarelo atual
    delay(1000);
    digitalWrite(verde_leste+(first*3)+1 , LOW );//carro desliga amarelo atual
    digitalWrite(verde_leste+(first*3)+2 , HIGH);//carro liga vermelho atual
  	/*if(pedestre){
    	digitalWrite(Pverde_leste+(last*2), HIGH);
        digitalWrite(Pverde_leste+(last*2)+1, LOW);
    }*/
    digitalWrite(verde_leste+(last*3)+1   , HIGH);//carro liga amarelo futuro
    digitalWrite(verde_leste+(last*3)+2   , LOW);//carro desliga vermelho futuro
    delay(1000);
    digitalWrite(verde_leste+(last*3)    , HIGH);//carro liga verde futuro
    digitalWrite(verde_leste+(last*3)+1   , LOW);//carro desliga amarelo futuro
    current_signal = last;
}

void loop() {
    switch(current_mode){  
        case 0:
      		/*if(pedestre[0]){
                transition(current_signal, 1, 1);
                delay(4000);
                pedestre[0] = 0;
            }
            if(pedestre[1]){
                transition(current_signal, 2, 1);
                delay(4000);
                pedestre[1] = 0;
            }
            if(pedestre[2]){
                transition(current_signal, 3, 1);
                delay(4000);
                pedestre[2] = 0;
            }
            if(pedestre[3]){
                transition(current_signal, 0, 1);
                delay(4000);
                pedestre[3] = 0;
            }*/
            if(carros[0]){
                transition(current_signal, 2, 0);
                delay(4000);
                carros[0] = 0;
            }
            if(carros[1]){
                transition(current_signal, 3, 0);
                delay(4000);
                carros[1] = 0;
            }
            if(carros[2]){
                transition(current_signal, 0, 0);
                delay(4000);
                carros[2] = 0;
            }
            if(carros[3]){
                transition(current_signal, 1, 0);
                delay(4000);
                carros[3] = 0;
            }
        case -1:
            break;
            default:
            transition(current_signal, 3, 0);
            current_mode = -1;
            break;
    }
    if(carros[0]==0 && carros[1]==0 && carros[2]==0 && carros[3]==0){
        if(current_mode!=-1){
            current_mode = -2;
        }
    }else{
        current_mode = 0;
    }
    char comando = Serial.read();
    if(comando == 's' /*|| digitalRead(carro_sul)*/){
        carros[3] = 1;
    }
    if(comando == 'l' /*|| digitalRead(carro_leste)*/){
        carros[2] = 1;
    }
    if(comando == 'n' /*|| digitalRead(carro_norte)*/){
        carros[1] = 1;
    }
    if(comando == 'o' /*|| digitalRead(carro_oeste)*/){
        carros[0] = 1;
    }
    
    if(comando == 'S'){
        Ppedestre_sul  ();
    }
    if(comando == 'L'){
        Ppedestre_leste();
    }
    if(comando == 'N'){
        Ppedestre_norte();
    }
    if(comando == 'O'){
        Ppedestre_oeste();
    }
}


void Ppedestre_sul(){
	carros[0] = 0;
    carros[1] = 0;
    carros[2] = 1;
    carros[3] = 0;
}

void Ppedestre_leste(){
	carros[0] = 0;
    carros[1] = 1;
    carros[2] = 0;
    carros[3] = 0;
}

void Ppedestre_norte(){
	carros[0] = 1;
    carros[1] = 0;
    carros[2] = 0;
    carros[3] = 0;
}

void Ppedestre_oeste(){
	carros[0] = 0;
    carros[1] = 0;
    carros[2] = 0;
    carros[3] = 1;
}