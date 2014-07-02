
void ledTurnOn() {
  led_val = HIGH;
  led_val.save();
  digitalWrite(LED, led_val);
}

void ledTurnOff() {
  led_val = LOW;
  led_val.save();
  digitalWrite(LED, led_val);
}

void setupLed() {
  pinMode(LED, OUTPUT);
  led_val.restore();
  digitalWrite(LED, led_val);
}
