
void setupMainLoops() {
  mainLoops[0] = &initLoop;
}

void initLoop() {
  Serial.println("initLoop");
  delay(1000);
}


