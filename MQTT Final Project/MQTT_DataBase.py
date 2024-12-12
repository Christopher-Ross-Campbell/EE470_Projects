import paho.mqtt.client as mqtt
import mysql.connector

# Database Configuration
HOST = "82.197.82.72"  # Hostinger database IP
USER = "u699644480_db_ChrisCampbe"  # Database username
PASSWORD = "Mk-18Mjolnir"  # Database password
DATABASE = "u699644480_ChrisCampbell"  # Database name

# MQTT Configuration
BROKER_URL = "broker.hivemq.com"
BROKER_PORT = 1883
TOPIC = "campbellESP8266/MQTT/outTopic/POT"

# Insert potentiometer value into the database
def push_value_to_db(pot_value):
   try:
       # Connect to the database
       connection = mysql.connector.connect(
           host=HOST,
           user=USER,
           password=PASSWORD,
           database=DATABASE
       )


       if connection.is_connected():
           print("Connected to the database!")


           # Create a cursor object
           cursor = connection.cursor()


           # SQL query to insert data
           insert_query = "INSERT INTO potentiometer_table (POT_value) VALUES (%s)"
           cursor.execute(insert_query, (pot_value,))


           # Commit the transaction
           connection.commit()
           print(f"Value {pot_value} inserted into Potentiometer_value table!")


   except mysql.connector.Error as err:
       print(f"Error: {err}")
   finally:
       if connection.is_connected():
           cursor.close()
           connection.close()
           print("Database connection closed.")

# MQTT Callbacks
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker!")
        client.subscribe(TOPIC)
        print(f"Subscribed to topic: {TOPIC}")
    else:
        print(f"Failed to connect to MQTT broker, return code {rc}")

def on_message(client, userdata, msg):
    try:
        pot_value = float(msg.payload.decode())
        print(f"Received value: {pot_value}")
        push_value_to_db(pot_value)
    except ValueError:
        print("Error: Received non-numeric value.")

# Main
if __name__ == "__main__":
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(BROKER_URL, BROKER_PORT, 60)
    print("Starting MQTT client loop...")
    client.loop_forever()