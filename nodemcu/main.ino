#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#define SS_PIN D2
#define RST_PIN D1
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
Servo myServo;                    // Define servo name

const char *ssid = "Tec-IoT";
const char *password = "spotless.magnetic.bridge";
const char *mqtt_server = "mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);

// Define authorized RFID tags
String authorizedTags[] = {
    "74 B5 8F 04",
    "89 E4 22 16",
    "EA 87 23 80",
    "7C D1 D2 DB",
    "FA 8E 0C 7D"};

void setup()
{
    Serial.begin(115200); // Initiate a serial communication
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    client.setServer(mqtt_server, 1883);

    SPI.begin();        // Initiate SPI bus
    mfrc522.PCD_Init(); // Initiate MFRC522
    myServo.attach(D4); // Servo pin
    myServo.write(0);   // Servo start position
    Serial.println("Waiting for car...");
    Serial.println();
}

void loop()
{
    // Look for new cards
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }

    // Show UID on the serial monitor
    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();

    // Check if the scanned tag is authorized
    bool isAuthorized = false;
    for (int i = 0; i < sizeof(authorizedTags) / sizeof(authorizedTags[0]); i++)
    {
        if (content.substring(1) == authorizedTags[i])
        {
            isAuthorized = true;
            break;
        }
    }

    if (isAuthorized)
    {
        Serial.println("Authorized access");
        Serial.println();
        sendMQTTMessage(content);
        delay(500);
        myServo.write(180);
        delay(5000);
        myServo.write(0);
    }
    else
    {
        Serial.println("Access denied");
    }
}

void sendMQTTMessage(String content)
{
    if (!client.connected())
    {
        reconnect();
    }
    client.publish("authorized-uid", content.c_str());
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP8266Client"))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}