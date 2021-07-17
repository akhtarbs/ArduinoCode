void setup() {
  Serial.begin(9600);
  String Keyhex = "4f2dfbdb5767e19880dc58bd29ae8cf240e490f1";//40 hex 160 bit
  //4f2dfbdb5767e19880dc 20 hex 80 bit
  //6661757a616e62756469 20 hex 80 bit
  //6661757a616e62756469--4f2dfbdb5767e19880dc

//  4f2dfbdb5767e19880dc
//  58bd29ae8cf240e490f1
uint32_t coba_uint32;
  coba_uint32=0x00000001+285620;
  Serial.println(coba_uint32);
  coba_uint32=0x00000002;
  Serial.println(coba_uint32);
  coba_uint32=0x00000003;
  Serial.println(coba_uint32);
  coba_uint32=0x00045bb8;//285624
  Serial.println(coba_uint32);

  
//  uint32_t coba_32[5];
//  for (int i = 0; i < 5; i++) {
//      coba_32[i]+=coba_uint32;
//      Serial.println(coba_32[i]);
//  }
//  
  
//    
//  unsigned int key1 [20]={0x4,0xf,0x2,0xd,0xf,0xb,0xd,0xb,0x5,0x7,0x6,0x7,0xe,0x1,0x9,0x8,0x8,0x0,0xd,0xc};
//  unsigned int key2 [20]={0x5,0x8,0xb,0xd,0x2,0x9,0xa,0xe,0x8,0xc,0xf,0x2,0x4,0x0,0xe,0x4,0x9,0x0,0xf,0x1};
//    
//  char c_keya[21];
//  Keyhex.substring(0, 20).toCharArray(c_keya, 21);
//  char c_keyb[21];
//  Keyhex.substring(20, 40).toCharArray(c_keyb, 21);
//
//  unsigned int key_a[20];
//  for (int i = 0; i < 20; i++) {
//    String buff = "0x" + String(c_keya[i]);
//    const char* buf = buff.c_str();
//    key_a[i] = strtol(buf, 0, 16);
//  }
//  unsigned int key_b[20];
//  for (int i = 0; i < 20; i++) {
//    String buff = "0x" + String(c_keyb[i]);
//    const char* buf = buff.c_str();
//    key_b[i] = strtol(buf, 0, 16);
//  }
//    Serial.println("--------1---------");
//    for(int i=0;i<20;i++){
//        Serial.print(key_a[i]);
//        Serial.print(" = ");
//        Serial.println(key1[i]);
//    }
//    Serial.println("--------2---------");
//    for(int i=0;i<20;i++){
//        Serial.print(key_b[i]);
//        Serial.print(" = ");
//        Serial.println(key2[i]);
//    }
//    Serial.println("---------Done--------");
//    
//
//  Serial.println("---------IV--------");
//  String IVhex = "0d2682b993ba4834";
//  uint32_t nilai_IV[2];
//  for(int i=0;i<IVhex.length()/8;i++){
//      int a=i*8;
//      int b=a+8;
//      nilai_IV[i]= convert_StrUint32(IVhex.substring(a,b));
//  }
//  for(int i=0;i<IVhex.length()/8;i++){
//      Serial.println(nilai_IV[i]);
//  }
//
//  
//
//  Serial.println("---------Data--------");
//  String Datahex = "d10be6e5736cea7b824bac328b2c7aef";
//  uint32_t nilai_Data[4];
//  for(int i=0;i<Datahex.length()/8;i++){
//      int a=i*8;
//      int b=a+8;
//      nilai_Data[i]= convert_StrUint32(Datahex.substring(a,b));
//  }
//  
//  for(int i=0;i<Datahex.length()/8;i++){
//      Serial.println(nilai_Data[i]);
//  }
//
//
//  
//
//  Serial.println("---------CEK--------");
//  uint32_t IV1 = 0x0d2682b9;
//  Serial.println(IV1);
//  uint32_t IV2 = 0x93ba4834;
//  Serial.println(IV2);
//  uint32_t m1 = 0xd10be6e5;
//  Serial.println(m1);
//  uint32_t m2 = 0x736cea7b;
//  Serial.println(m2);
//  uint32_t m3 = 0x824bac32;
//  Serial.println(m3);
//  uint32_t m4 = 0x8b2c7aef;
//  Serial.println(m4);
// 

}

void loop() {
  // put your main code here, to run repeatedly:

}


uint32_t convert_StrUint32(String data){
  data="0x"+data;
//  Serial.println(data);
  const char* buf = data.c_str();
  long ia = strtoul(buf, 0, 16);
//  Serial.println(ia);
  uint32_t nilai_Data=(uint32_t)ia;
  return nilai_Data;
}
