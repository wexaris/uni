import paho.mqtt.client as mqtt
from notify import notification

CLIENT_ID = "rv20039"
SERVER_MQTT_HOST = "192.168.1.68"
SERVER_MQTT_PORT = 1883

CPU_hot = False

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("+/" + CLIENT_ID + "/#")
    client.loop_start()

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    value = msg.payload.decode()
    print("Received: " + msg.topic + " " + str(value))
    if msg.topic == "sensor/" + CLIENT_ID + "/temp1/state":
        global CPU_hot
        if int(value) >= 45:
            if not CPU_hot:
                print("Emitting notification")
                notification("CPU exceeding 45°C")
                CPU_hot = True
        else:
            CPU_hot = False

def on_disconnect(client, userdata, rc):
    print("Connection lost")


print("Creating MQTT client")
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
print("Connecting MQTT client")
client.connect(SERVER_MQTT_HOST, SERVER_MQTT_PORT, 60)

print("Listening...")
client.loop_forever()
