🗑️ Smart Garbage Monitoring System with Blynk

An Arduino-based system that monitors garbage level using an ultrasonic sensor and sends real-time updates to your phone via the Blynk app. A buzzer alerts when the bin is nearly full, preventing overflow.

🚀 Features

- 📏 Calculates distance of garbage using HC-SR04
- 📊 Sends percentage full to Blynk app
- 🔔 Buzzer alert when garbage exceeds warning level 
- 🌐 WiFi-enabled using ESP8266
- 📱 Remote monitoring on smartphone

🛠️ Hardware Used

- Arduino Uno or NodeMCU
- HC-SR04 Ultrasonic Sensor
- Buzzer
- WiFi module 
- Blynk app

📲 Blynk Configuration

- Virtual Pin `V0`: Gauge to show percentage full
- Add `Notification` widget (optional)
- Add `Event Trigger` for custom alerts

🧠 Logic

- Calculates distance from sensor to garbage.
- Calculates % full = `(binHeight - distance) / binHeight * 100`
- If distance ≤ warning threshold → buzzer ON + app alert
- Else → buzzer OFF

