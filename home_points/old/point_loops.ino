//#define POINT_SEND_EVENT_EVERY 5000
//#define POINT_SEND_SETUP_EVERY 10000
//void point_initLoop() {
  //uint32_t num = pointNum();
  //unsigned long last_event = millis();
  //unsigned long last_setup = millis();

  //while(state == POINT_INIT_STATE) {

    //if(outgoing_pointer == 0 && last_setup - millis() > POINT_SEND_SETUP_EVERY) {
      //point_sendSetupRequest();
      //last_setup = millis();
    //}

    //if(last_event - millis() > POINT_SEND_EVENT_EVERY) {
      //last_event = millis();
    //}

    //point_radioLoop();
  //}
//}

//void point_radioLoop() {
  //point_checkRadio();
//}

//void point_checkRadio() {
  //if (radioStream.available() > 4) {
    //uint32_t length = StreamPack::radioReadLength();

    //char pack[length+1];
    //pack[length] = 0;

    //StreamPack::radioReadPack(pack, length);

    //Parser::JsonParser<JSON_PARSER_TOKENS> parser;
    //Parser::JsonObject root = parser.parse(pack);

    //if (root.success()) {
      //evalPointCommand(root);
    //} else {
      ////TODO: send error to router
    //}
  //}
//}

//uint32_t pointNum () {
  //return uint32_t(eeprom_point_num);
//}


