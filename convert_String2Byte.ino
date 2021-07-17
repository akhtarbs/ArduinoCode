

void setup() {
  Serial.begin(9600);

  String data = "fauzanbs";
  String key = "fauzanbsfauzanbsfauzanbs";
  
  int i_data= data.length() + 1;
  char char_data[i_data];
  data.toCharArray(char_data,i_data);
  byte byte_data[data.length()];
  for(int i=0;i<data.length();i++){
    Serial.println(char_data[i]);
    byte_data[i] = (int)char_data[i];
    Serial.println(byte_data[i]);
    Serial.println("========");
  }

  int i_key= key.length() + 1;
  char char_key[i_key];
  key.toCharArray(char_key,i_key);
  byte byte_key[key.length()];
  for(int i=0;i<key.length();i++){
    Serial.println(char_key[i]);
    byte_key[i] = (int)char_key[i];
    Serial.println(byte_key[i]);
    Serial.println("========");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
