
void setup() {
  Serial.begin(9600);
  String datacipher = "04c83a31564aec1a";
  
  int i_datacipher= datacipher.length() + 1;
  char char_datacipher[i_datacipher];
  datacipher.toCharArray(char_datacipher,i_datacipher);
  
  for(int i=0;i<datacipher.length();i++){
    if(i%2==0){
      String str_datacipher = String(char_datacipher[i])+String(char_datacipher[i+1]);
      Serial.print(str_datacipher);      
      char char_buff[3];
      str_datacipher.toCharArray(char_buff,3);
      int nilaiint = strtol(char_buff,0,16);
      Serial.print(" = "); 
      Serial.print(nilaiint);
      Serial.print(" = "); 
      Serial.print(byte(nilaiint));

      Serial.println();
    }  
  }
char data[3]={'e','8'};
int nilaiint = strtol(data,0,16);
Serial.println(nilaiint);

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
