import cv2 
import time 
import board 
import neopixel 
from gpiozero import Button, TonalBuzzer, InputDevice 
MAGICWANDID = "69"

# set up camera object called Cap which we will use to find OpenCV 
cap = cv2.VideoCapture(0) 
  
# QR code detection Method 
detector = cv2.QRCodeDetector() 
  
pixels = neopixel.NeoPixel(board.D18, 5, brightness=1) 
  
button = Button(17) 
buzz = TonalBuzzer(27) 
charge = InputDevice(22) 
#This creates an Infinite loop to keep your camera searching for data at all times 
while True: 
    if button.is_pressed: 
        # Below is the method to get a image of the QR code 
        _, img = cap.read() 
         
        # Below is the method to read the QR code by detetecting the bounding box coords and decoding the hidden QR data  
        data, bbox, _ = detector.detectAndDecode(img) 
         
        # This is how we get that Blue Box around our Data. This will draw one, and then Write the Data along with the top (Alter the numbers here to change the colour and thickness of the text) 
        if(bbox is not None): 
            if data == "success": 
                pixels.fill((0, 0, 255)) 
                pixels.show 
                buzz.play(300) 
                time.sleep(.2) 
            if data == "fail": 
                pixels.fill((255, 0, 0)) 
                pixels.show() 
                buzz.play(800) 
                time.sleep(.2) 
            buzz.stop() 
            buzz.play(500) 
            time.sleep(.2) 
            buzz.stop() 
            time.sleep(3) 
            pixels.fill((0, 0, 0)) 
            pixels.show() 
             
    if charge.is_active: 
        pixels.fill((0, 255, 0)) 
        pixels.show() 
        while charge.is_active: 
            x = 1 
        pixels.fill((0, 0, 0)) 
        pixels.show() 
# When the code is stopped the below closes all the applications/windows that the above has created 
cap.release() 
cv2.destroyAllWindows() 
 
