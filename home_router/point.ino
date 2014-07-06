
void setupPoint() {
}

void pointLoop() {
  
  cmdRadioMessenger.feedinSerialData();
  //cmdMessenger.feedinSerialData();
  
  delay(500);
  

  //  if ( radio.available() ){
  //    char val[17] = {""};
  //
  //    Log.Info("getPayloadSize ==== %d", radio.getPayloadSize());
  //
  //    radio.read( val, sizeof(val) - 1 );
  //    Log.Info("Got %s... %T"CR, val);
  //
  //    delay(20);
  //  } else {
  //    Log.Info("Do not available"CR);
   // }

  //if (radioStream.available()) {
  //  String tmp = radioStream.readStringUntil(0);
  //
  //  char val[10];
  //  
  //  for(int i = 0;i < tmp.length();i++){
  //    val[i] = tmp[i];
  //  }
  //  
  //  val[tmp.length()] = 0;
  //
  //  Log.Info("Read string: %s"CR, val);
  //} else {
  //  Log.Info("Not available"CR);
  //}

}
