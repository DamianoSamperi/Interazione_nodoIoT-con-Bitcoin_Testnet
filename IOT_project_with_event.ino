#include "Bitcoin.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Conversion.h"

#define ledPin 27
#define TOKEN "52ce69b94e114b1aa2136666eac0dbe5"
//Use pin 25 to receive the signal from the module
#define PIR_MOTION_SENSOR 25

// unsigned long noMotionDetectedTime = 0;  // Timer per gestire le brevi interruzioni
unsigned long motionDetectedTime = 0;
unsigned long motionThreshold = 10000;  // Soglia di tempo in millisecondi (10 secondi)

const char* ssid = "iPhone";
const char* password = "lasolita";
const char* url_create_tx = "https://api.blockcypher.com/v1/btc/test3/txs/new";
char url_send_tx[256];

void connected_to_ap(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("\nConnected to the WiFi network");
}

void disconnected_from_ap(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("[-] Disconnected from the WiFi AP");
  WiFi.begin(ssid, password);
}

void got_ip_from_ap(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}
void writeToBlockchain() {
  //  get private key from wif
  PrivateKey pk;
  pk.fromWIF("cT1ffmnU45AHFJEpwHK8VBvFrhiKGjAEi74QxMguTvpbMAbw7Z4P");
  PublicKey pub = pk.publicKey();
  // Corpo della richiesta (data JSON)
  String jsonData = "{\"inputs\":[{\"addresses\":[\"mztNoKYciZB6DdggMLtJzHVhhuDX8cUDjR\"]}],\"outputs\":[{\"addresses\":[\"n4BgWRTw7ndk2ZYThbGuD6xAY28Y3GGf1n\"],\"value\":1},{\"script_type\":\"null-data\",\"script\":\"6a0474727565\",\"value\":0}],\"fees\":241}";
  // String jsonData = "{\"inputs\":[{\"addresses\":[\"mztNoKYciZB6DdggMLtJzHVhhuDX8cUDjR\"]}],\"outputs\":[{\"addresses\":[\"n4BgWRTw7ndk2ZYThbGuD6xAY28Y3GGf1n\"],\"value\":1}],\"fees\":541}";
  // String jsonData = "{\"inputs\":[{\"addresses\":[\"mztNoKYciZB6DdggMLtJzHVhhuDX8cUDjR\"]}],\"outputs\":[{\"addresses\":[\"tb1qerzrlxcfu24davlur5sqmgzzgsal6wusda40er\"],\"value\":1},{\"script_type\":\"null-data\",\"script\":\"6a0474727565\",\"value\":0}],\"fees\":2452}";
  HTTPClient http;
  http.begin(url_create_tx);
  http.addHeader("Content-Type", "application/json");
  // Invio della richiesta POST con i dati
  int httpCode = http.POST(jsonData);
  // Verifica della risposta
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Risposta del server:");
    Serial.println(payload);
    // Parsing del JSON
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    // Verifica se c'è un campo "errors" nel payload
    if (doc.containsKey("errors") && !doc["errors"].isNull()) {
      Serial.println("Errore trovato nel campo 'errors'. Transazione non inviata.");
      return;  // Esce dalla funzione, evitando di inviare la transazione
    }

    // Estrarre il campo "tosign" e "tx"
    JsonArray tosign = doc["tosign"].as<JsonArray>();
    JsonObject tx = doc["tx"];
    // Create a string to hold the serialized JSON
    String tx_String;

    // Serialize the tx object into the jsonData_send string
    serializeJson(tx, tx_String);
    // Stampare il valore di "tosign"
    for (JsonVariant v : tosign) {
      String tosignStr = v.as<String>();  // Converte il valore in una stringa
      Serial.print("toSign: ");
      Serial.println(tosignStr);


      //Prima di passare la stringa a pk.sign() la convertiamo
      uint8_t to_sign_buffer[32];
      size_t len_arr = sizeof(to_sign_buffer);
      size_t written;
      // from hex
      written = fromHex(tosignStr, to_sign_buffer, len_arr);
      Signature sig = pk.sign(to_sign_buffer);
      // verify the signature
      if (pub.verify(sig, to_sign_buffer)) {
        Serial.println("Ok, Mi fido di te.");
      } else {
        Serial.println("No, Non sei chi dici di essere!");
      }
      uint8_t* arr = nullptr;  // Variabile per contenere i dati binari della firma
      size_t len = 0;          // Lunghezza della firma
      uint8_t bytes[256];
      // Ottieni la firma in formato DER (binario)
      len = sig.der(bytes, sizeof(bytes));  // Ottieni la firma in formato DER


      // Ora converti i dati binari in formato Hex
      String signedHex = toHex(bytes, len);

      //Json per inviare la transazione
      String jsonData_send = "{\"tx\": " + tx_String + ","
                                                       "\"tosign\": [\""
                             + tosignStr + "\"],"
                                           "\"signatures\": [\""
                             + signedHex + "\"],"
                                           "\"pubkeys\": [\""
                             + pub + "\"]}";
      HTTPClient httpPost;
      httpPost.begin(url_send_tx);  // URL della richiesta per inviare la transazione
      httpPost.addHeader("Content-Type", "application/json");

      // Invio della richiesta POST con i dati JSON
      int httpCodePost = httpPost.POST(jsonData_send);
      if (httpCodePost > 0) {
        String payloadPost = httpPost.getString();
        Serial.println("Risposta della richiesta send transaction:");
        Serial.println(payloadPost);  // Stampa la risposta del server
      } else {
        Serial.printf("Errore nella richiesta POST: %s\n", httpPost.errorToString(httpCodePost).c_str());
      }

      // Chiudi la connessione HTTP
      httpPost.end();
    }
  } else {
    Serial.printf("Errore nella richiesta HTTP: %s\n", http.errorToString(httpCode).c_str());
  }

  // Chiudi la connessione HTTP
  http.end();
}
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(PIR_MOTION_SENSOR, INPUT);
  // concateniamo il TOKEN nell'URL
  sprintf(url_send_tx, "https://api.blockcypher.com/v1/btc/test3/txs/send?token=%s", TOKEN);

  //WI-FI SETUP
  WiFi.mode(WIFI_STA);  //Optional
  WiFi.onEvent(connected_to_ap, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(got_ip_from_ap, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(disconnected_from_ap, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 5) {
    delay(1000);  // Ritardo tra i tentativi
    retries++;
    Serial.print(".");
  }
}

void loop() {
  //dobbiamo fare in modo che il led sia acceso solo se il sensore di moviemnto riscontra moviemnto quindi
  //if sensore podixionr == ON, sndrà in alto allora si accende la luce
  //da momento che si attiva il sensore di moviemtno parte un timer, se supera una certa soglia allora bisognerà
  //fare una transazione e scrivere nella blockchain il fatto che è stato rilevato moviemnto continuo per tot tempo
  if (digitalRead(PIR_MOTION_SENSOR)) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Hi, people is coming");
    if (motionDetectedTime == 0) {
      motionDetectedTime = millis();  // Inizia il timer
    }
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Watching");
    motionDetectedTime = 0;  // Resetta il timer principale
  }

  if (motionDetectedTime != 0 && (millis() - motionDetectedTime > motionThreshold)) {
    Serial.println("Continuous motion detected, writing to blockchain...");
    writeToBlockchain();
    motionDetectedTime = 0;  // Resetta il timer dopo aver scritto sulla blockchain
  }

  delay(200);
}