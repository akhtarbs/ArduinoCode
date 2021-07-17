//26
//132
//78
//95
//27
//154
//60
//70
//165
//144
//140
//48
//169
//47
//57
//232


void setup() {
  Serial.begin(9600);
  String cipher_data ="1a844e5f1b9a3c46a5908c30a92f39e8";
  int input_len = cipher_data.length();
  int i_datacipher= cipher_data.length() + 1;
  char char_datacipher[i_datacipher];
  cipher_data.toCharArray(char_datacipher,i_datacipher);
  
  uint8_t data_uint8[input_len/2];
  int a=0;
  for(int i=0;i<cipher_data.length();i++){
    if(i%2==0){
      String buf_a=String(char_datacipher[i])+String(char_datacipher[i+1]);
      char char_buff[3];
      buf_a.toCharArray(char_buff,3);
      data_uint8[a]  = strtol(char_buff,NULL,16);
      a++;
    }
  }

  
  for(int i=0;i<16;i++){
    Serial.println(data_uint8[i]);
  }




  
}

void loop() {
  // put your main code here, to run repeatedly:

}
