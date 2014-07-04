
void setupPoint() {
}

void pointLoop() {
  cmdMessenger.feedinSerialData();

  //if( radioStream.available() ) {
  //  cmdRadioMessenger.feedinSerialData();
  //}

  //Log.Info("%d, %d"CR, radio.available(), radioStream.available());
  
  if(radio.available()){
    Log.Info("Radio avail = %d"CR, radio.available());
  }

  if (radioStream.available() >= 8) {
    char buffer[8];
    for (int i = 0; i < 8; i++) {
      buffer[i] = radioStream.read();
    }

    Log.Info("Message: %s"CR, buffer);
  }

  // if ( radioStream.available() )
  //  {
  //    Log.Info("Avail"CR);
  //    String str = radioStream.readStringUntil('\n');
  //   Log.Info("Message: %s"CR, str);
  //
  //   delay(20);
  //}
}
