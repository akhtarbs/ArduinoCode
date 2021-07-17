#include <EEPROM.h>
#include <SHA256.h>

////////////////////////////////////////////////////////////////////////////////
//Declare HMAC SHA256
SHA256 sha256;

////////////////////////////////////////////////////////////////////////////////
//Declare Kunci HMAC
String hmac_key = "proton";
int jumlahUser_maks =22;

void setup() {
  Serial.begin(9600);
}

void loop() {  
  Serial.println(F("\n======================\n"));
  Serial.println(F("Welcome to Menu"));
  Serial.println(F("a. Daftar User"));
  Serial.println(F("b. Login User"));
  Serial.println(F("c. Delete User"));
  Serial.println(F("\n======================\n"));

//  ini fungsi while nunggu sampai ada inputan di serial monitor.
    while (!Serial.available());
    String data = Serial.readStringUntil("\n");
    data.replace("\n","");
    data = data.substring(0,1);
    Serial.println("Pilihan = "+data);
    if(data=="a"){
//  Ini buat code isi menu daftar user     
      Serial.println(F("Menu Daftar User"));
      menu_daftaruser();
    }
    else if(data=="b"){
//  Ini buat code isi menu login user  
      Serial.println(F("Menu Login User"));
      menu_loginuser();
    }
    else if(data=="c"){
//  Ini buat code isi menu login user  
      Serial.println(F("Menu Delete User"));
      menu_deleteuser();
    }

    else{
//  Ini buat code menu dipilih tidak ada  
      Serial.println(F("Menu Tidak Ada"));
    }
}

//=============================================================================//
void menu_daftaruser(){
  String i_username;
  String i_password;
  String buff;
  Serial.println(F("===== Menu Daftar ====="));
//  input Username
  Serial.println(F("Masukkan Username!"));
  while (!Serial.available());
  i_username = Serial.readStringUntil("\n");
  i_username.replace("\n","");
  Serial.println("Username = "+i_username);
  
//  input Password
  Serial.println(F("Masukkan Password!"));
  while (!Serial.available());
  i_password = Serial.readStringUntil("\n");
  i_password.replace("\n","");
  buff = i_password;
  i_password = fungsi_hmac(&sha256,hmac_key,i_password);
  Serial.println("Password = "+i_password);
  
  if(i_username.length()<9 && i_password.length()==64 && buff.length()>7){
    Serial.println(F("Proses Menyimpan Username dan Password"));
    int stat_save = fungsi_simpanUsernamePassword(i_username,i_password);
    if(stat_save==1){
      Serial.println(F("===== Proses Simpan ke Database Berhasil ====="));   
    }
    else{
      Serial.println(F("===== Proses Simpan ke Database Gagal =====")); 
    }
  }
  else{
    Serial.println(F("===== Masukkan Username dan Password dengan Benar =====")); 
  }

}
//=============================================================================//
void menu_loginuser(){
  String i_username;
  String i_password;
  Serial.println(F("===== Menu Login ====="));
//  input Username
  Serial.println(F("Masukkan Username Anda!"));
  while (!Serial.available());
  i_username = Serial.readStringUntil("\n");
  i_username.replace("\n","");
  Serial.println("Username = "+i_username);
  
//  input Password
  Serial.println(F("Masukkan Password Anda!"));
  while (!Serial.available());
  i_password = Serial.readStringUntil("\n");
  i_password.replace("\n","");
  i_password = fungsi_hmac(&sha256,hmac_key,i_password);
  Serial.println("Password = "+i_password);
  
  int a = fungsi_cekUsernamPassword(i_username,i_password);
  if(a==1){
    Serial.println(F("===== Proses Login Berhasil ====="));
  }
  else{
    Serial.println(F("===== Proses Login Gagal ====="));
  }
}
//=============================================================================//
void menu_deleteuser(){
  String i_username;
  String i_password;
  Serial.println(F("===== Menu Delete Account ====="));
//  input Username
  Serial.println(F("Masukkan Username!"));
  while (!Serial.available());
  i_username = Serial.readStringUntil("\n");
  i_username.replace("\n","");
  Serial.println("Username = "+i_username);
  
//  input Password
  Serial.println(F("Masukkan Password!"));
  while (!Serial.available());
  i_password = Serial.readStringUntil("\n");
  i_password.replace("\n","");
  i_password = fungsi_hmac(&sha256,hmac_key,i_password);
  Serial.println("Password = "+i_password);
  
  if(i_password.length()==64){
    Serial.println(F("Proses Menyimpan Username dan Password"));
    int stat_save = fungsi_hapusAkun(i_username,i_password);
    if(stat_save==1){
      Serial.println(F("===== Proses Delete Akun Berhasil ====="));   
    }
    else{
      Serial.println(F("===== Proses Delete Akun Gagal =====")); 
    }
  }
  else{
    Serial.println(F("===== Masukkan Username dan Password dengan Benar =====")); 
  }
}
//=============================================================================//



/////////////////////////////////////////////////////////////////////////////////////////////////
//Fungsi HMAC SHA 256 input string kunci dan data
String fungsi_hmac(Hash *hash, String stringkey, String stringtext){  
    int i_key = stringkey.length() + 1;
    char key[i_key];
    stringkey.toCharArray(key,i_key);
    int i_text = stringtext.length() + 1;
    char text[i_text];
    stringtext.toCharArray(text,i_text);
    uint8_t result[32];
    hash->resetHMAC(key, strlen(key));
    hash->update(text, strlen(text));
    hash->finalizeHMAC(key, strlen(key), result, sizeof(result));
    String out_hex="";
    for (int i = 0; i <= sizeof(result)-1; i++) {
      String a = String(result[i],HEX);
      if(a.length()<2){
        a="0"+a;
      }
      out_hex = out_hex+a;
    }
    return out_hex;
}
////////////////////////////////////////////////////////////////////////////////////////
//Fungsi Cek Alamat EEPROM Kosong Jumlah User maksimal 1024/42 = 21 akun
int fungsi_cekaddress(){
  for (int i = 0; i <jumlahUser_maks; i++){
    int buf_status = EEPROM.read((i*41)+1);
    if(buf_status!=1){
      return (i*41)+1;
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
//Fungsi Buat Menu Daftar, simpan Username dan Password
int fungsi_simpanUsernamePassword(String i_uname, String i_passwd){
  int user = EEPROM.read(0);
  Serial.println("Jumlah User dalam EEPROM  = "+ String(user));
  int w_start = fungsi_cekaddress();    //posisi simpan akun
  int w_uname = w_start+1;              //posisi mulai simpan username akun
  int w_pass = w_uname+8;               //posisi mulai simpan password akun
  Serial.println("Posisi Simpan Akun        = "+String(w_start));
  Serial.println("Start Username            = "+String(w_uname));
  Serial.println("Start Password            = "+String(w_pass));

  if(user<jumlahUser_maks && w_start!=0){
    for(int i=0;i<8;i++){
      if(i_uname.length()<8){
        i_uname+="-";
      }
    }
    char char_uname[9];
    i_uname.toCharArray(char_uname,9);
    char charbuff_pass[65];
    i_passwd.toCharArray(charbuff_pass,65);
    int char_pass[32];
    int array_buff=0;
    for (int i = 0; i <64; i++){
      if(i%2==0){
            String buf_pass = String(charbuff_pass[i])+String(charbuff_pass[i+1]);
            char ArrayStrHex[3];
            char * nilaiChar;
            buf_pass.toCharArray(ArrayStrHex,3);
            int nilaiInt = strtol(ArrayStrHex,&nilaiChar,16);
            char_pass[array_buff]=nilaiInt;
            array_buff++;
        }
    }
//    proses simpan Username
    for (int i = 0; i < 8; i++){
      EEPROM.write(w_uname, int(char_uname[i]));
      w_uname++;
    } 
//    proses simpan Password
    for (int i = 0; i < 32 ; i++){
      EEPROM.write(w_pass,char_pass[i]);
      w_pass++;
    }
    EEPROM.write(w_start,1);          //ganti status posisi terisi
    EEPROM.write(0, user+1);          //jumlah user di address 0 ditambah
    Serial.println("Jumlah User Terbaru dalam EEPROM = "+ String(user+1));
    Serial.println(F("Simpan Username dan Password, BERHASIL!!!")); 
    return 1;
  }
  else{
    Serial.println(F("EEPROM PENUH!!!"));
    return 0;
  }
}
////////////////////////////////////////////////////////////////////////////////////////
//Fungsi Read Username dan Password di EEPROM berdasarkan posisi
void fungsi_readUsernamePassword(int posisi, String &username, String &password){
  int eeprom_uname[9];
  int eeprom_passwd[32];
  int r_status = ((posisi-1)*41)+1;
  int stat = EEPROM.read(r_status);
  if(stat==1 && posisi!=0){
    for (int i = r_status+1; i < r_status+1+8; i++){
      eeprom_uname[i] = EEPROM.read(i);
      username+=char(eeprom_uname[i]);
    }
    for (int i = r_status+1+8; i < r_status+1+8+32; i++){
      eeprom_passwd[i] = EEPROM.read(i);
      String a = String(eeprom_passwd[i],HEX);
      if(a.length()<2){
        a="0"+a;
      }
      password+=a;
    }
  }
  username.replace("-","");
}

////////////////////////////////////////////////////////////////////////////////////////
//Fungsi Cek Username dan Password di EEPROM
int fungsi_cekUsernamPassword(String inputUname, String inputPass){
  int user = EEPROM.read(0);
  if(user !=0){
    //  Looping Cek Input Username dan Password Di database
      int buf_status="";
      for (int i = 1; i < jumlahUser_maks; i++){
        int a = EEPROM.read(((i-1)*41)+1);
        String db_uname="";
        String db_pass="";
        fungsi_readUsernamePassword(i,db_uname,db_pass);
    //    Cek Username di Database
        if(inputUname==db_uname){
          if(inputPass==db_pass){
            buf_status= 1;
            break;
          }
          else{buf_status= 2;}
        }
        else{buf_status= 3;}
      }
      if(buf_status==1){
        Serial.println(F("Berhasil Login"));  
        return 1;     
      }
      else if(buf_status==2){
        Serial.println(F("Password Salah!!!"));
        return 0;  
      }
      else if(buf_status==3){
          Serial.println(F("Username tidak terdaftar di Database EEPROM"));
        return 0;  
      } 
  }
  else{
    Serial.println(F("Database EEPROM Kosong"));
    return 0;
  }
}
////////////////////////////////////////////////////////////////////////////////////////
//Fungsi Delete Akun dengan inputan Username dan Password
int fungsi_hapusAkun(String inputUname, String inputPass){
  int user = EEPROM.read(0);
  Serial.println("Jumlah User dalam Database = "+String(user));
  if(user !=0){      
      int buf_status="";
    //  Looping Cek Input Username dan Password Di database
      for (int i = 1; i < jumlahUser_maks; i++){
        int pos_delete = ((i-1)*41)+1;
        String db_uname="";
        String db_pass="";
        fungsi_readUsernamePassword(i,db_uname,db_pass);
        if(inputUname==db_uname&&inputPass==db_pass){
          for(int i=0;i<41;i++){
            EEPROM.write(pos_delete,0);
            pos_delete++;
          }
          EEPROM.write(0,user-1);
          Serial.println("Jumlah User Terbaru dalam EEPROM = "+ String(EEPROM.read(0)));
          buf_status=1;
          break;
        }
        else{
          buf_status=2;
        }
      }
      if(buf_status==1){
        Serial.println(F("Berhasil Delete Akun!!!"));  
        return 1;     
      }
      else if(buf_status==2){
        Serial.println(F("Akun Tidak Terdaftar!!!"));
        return 0;  
      }
  }
  else{
    Serial.println(F("Database EEPROM Kosong"));
    return 0;
  }
}
////////////////////////////////////////////////////////////////////////////////////////
