import paho.mqtt.client as mqtt
import psutil
import time

def get_cpu_temp():
    with open(r"/sys/class/thermal/thermal_zone2/temp") as File:
        return int(float(File.readline()) / 1000)

CLIENT_ID = "rv20039"
SERVER_MQTT_HOST = "iot.df.lu.lv"
SERVER_MQTT_PORT = 1883

def on_disconnect(client, userdata, rc):
    print("Connection lost")

def mqtt_publish(client, topic, state):
    client.publish(topic, payload=state, qos=1, retain=True)

print("Creating MQTT client")
client = mqtt.Client()
client.on_disconnect = on_disconnect
print("Connecting MQTT client")
client.connect(SERVER_MQTT_HOST, SERVER_MQTT_PORT, 60)

while True:
    client.loop()
    cpu = str(get_cpu_temp())
    print("CPU Temp: " + cpu)
    mqtt_publish(client, "sensor/" + CLIENT_ID + "/temp1/state", cpu)

    time.sleep(60)