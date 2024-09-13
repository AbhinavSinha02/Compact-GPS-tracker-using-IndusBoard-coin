### Summary

This Arduino code reads GPS coordinates from a GPS module connected to pins 43 (RX) and 44 (TX) and sends the location to a specified phone number via SMS every 30 minutes. It uses the **TinyGPS++** library to parse the GPS data and the **SIM** library for GSM communication to send SMS.

### How It Works:
1. The code initializes the GPS module and the GSM module.
2. It constantly reads GPS data and checks if the GPS location is valid and updated.
3. Every 30 minutes (configurable), it sends an SMS containing a Google Maps link with the device's current location (latitude and longitude) to the specified phone number.

### How to Use:
1. **Hardware Setup**:
   - Connect a GPS module to pins 43 (RX) and 44 (TX) of your microcontroller.
   - Connect a GSM module (e.g., SIM800) for sending SMS.

2. **Software Setup**:
   - Install the required libraries: **TinyGPS++**, **AsyncSMS**, and **SIM**.
   - Modify the placeholder `"10digitphonenumber"` in the code with the actual phone number where the SMS should be sent.
   
3. **Upload the Code**:
   - Save the file as `gps_sms.ino` and upload it to your microcontroller using the Arduino IDE.

4. **Result**:
   - The device will send an SMS with a Google Maps link to the phone number every 30 minutes, showing the current location.

This provides a simple GPS tracker that sends periodic location updates via SMS.
