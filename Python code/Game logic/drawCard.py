import cv2
import numpy as np
from CapPic import CapImg
from scipy.spatial import distance
import os

def drawCard(drawCardCount, nameList, maskImgList):
    
    if drawCardCount < 15:
        imageCenter = (2100,1000)
    elif drawCardCount  < 30:
        imageCenter = (2000,1000)
    elif drawCardCount  < 45:
        imageCenter = (1900,1000)
    elif drawCardCount  < 60:
        imageCenter = (1800,1000)
    else:
        imageCenter = (1700,1000)
     # captures image fro picamera feed and returns image, can add resolution as parameter
    resolution = (3008,2000)    
    img = CapImg(resolution)

    imageSize = resolution
    img = cv2.resize(img, imageSize)
    
    # turning picture to black and white
    
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)


    # Turns picture to HSV color code.
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # lower bound and upper bound for black color
    lower_black = np.array([0, 0, 0])
    upper_black = np.array([180, 255, 130])
    # Apply mask to image, black color turn white, else all black.
    mask = cv2.inRange(hsv, lower_black, upper_black)

    #Smooth image / remove noise
    smooth = np.ones((4,4),np.uint8)
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, smooth)
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, smooth)

    # Find contours from the mask image, contours around the white in image
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    #variables used in if statement under
    dist = 99999999
    turn = 0

    for i in contours:
        # moment function does some math that gives the average "weight" of an image, related to shape and intensity of image,
        #used alot in image prossesing and is needed here to find center of contour
        moment = cv2.moments(i)
        ix = int(moment["m10"] / moment["m00"])
        iy = int(moment["m01"] / moment["m00"])
        # center of contour
        contourCenter = (ix,iy)
        #draw center dot on image
        cv2.circle(img,contourCenter,7,(0,255,0),-1)
        cv2.circle(img,imageCenter,7,(255,0,0),-1)
        # find distance from contour center to image center
        centerDist = (distance.euclidean(imageCenter, contourCenter))
        # finds contour with lowest distance to imageCenter
        if centerDist < dist:
            dist = centerDist
            nr = turn
        turn+=1
        
    # Drawcontours need the hierrchy variable and  uses img and contour to draw contour on image.
    # Uses nr from for loop to only draw contour closest to imageCenter
    output = cv2.drawContours(img, contours[nr], -1, (0, 0, 255), 3)

    
    # finds square around contour, adding to w to to find a larger square.

    x, y, w, h = cv2.boundingRect(contours[nr])
    test = 1.6
    w=int(int(w)*test)
    rect = cv2.rectangle(img, (x-10,y-10), (x+w+10,y+h+10), (0,255,0), 2)
    cropped = mask[y:y+h,x:x+w]
    cropped = cv2.resize(cropped,(300,500))

    bestRankDiff = 9999999
    index = 0

    for item in maskImgList:
        item = cv2.resize(item,(300,500))
        diffImg = cv2.absdiff(cropped, item)
        rankDiff = int(np.sum(diffImg)/255)
        
        if rankDiff < bestRankDiff:
            bestRankDiffImg = diffImg
            bestRankDiff = rankDiff
            bestRankName = nameList[index]
        index+= 1
    cv2.destroyAllWindows()
    drawCardCount += 1
    return bestRankName, drawCardCount