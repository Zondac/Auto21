from picamera import PiCamera
from picamera.array import PiRGBArray
import time

cam = PiCamera()

def CapImg(resolution=(1280,960)):
    # get picamrea object
    # set resolution
    cam.resolution = resolution
    # Get a "pointer" to the raw feed of the camera, better quality than saving first.
    RawFeed = PiRGBArray(cam)
    # sleep since camera needs to focus/asjust to light
    time.sleep(0.5)
    # Actually capture image
    cam.capture(RawFeed, format="bgr")
    # get image to variable
    img = RawFeed.array
    # return image
    return img
