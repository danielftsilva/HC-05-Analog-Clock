char Incoming_value = 0;
                
void setup() 
{
  Serial.begin(9600);         
  pinMode(10, OUTPUT);
}

void loop()
{
  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");        
    if(Incoming_value == '1')             
      analogWrite(10, 150);
    else if(Incoming_value == '0')       
      analogWrite(10, 0);
  }                            
} 
