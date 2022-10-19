import cv2
import numpy as np
from CapPic import CapImg
from scipy.spatial import distance
import os

def drawCard():
    directory = "maskImg"
    maskImgList = []
    nameList = []
    pictureFolder = os.listdir(directory)

    for picture in pictureFolder:
        imgCur = cv2.imread(f"{directory}/{picture}", cv2.IMREAD_UNCHANGED)
        maskImgList.append(imgCur)
        nameList.append(os.path.splitext(picture)[0])

    # captures image fro picamera feed and returns image, can add resolution as parameter
    #xxx = 1500
    #yyy = 1000
    #resolution = (xxx,yyy)
    #imageCenter = (xxx/2,yyy/2)
    resolution = (3008,2000)
    imageCenter = (1200,800)
    img = CapImg(resolution)
    #img = cv2.blur(img, (10,10))
    #img = cv2.imread('card44.jpg')
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
    cv2.imshow("mask",mask)
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

    # Showing the image with contour
    cv2.imshow("Output", output)


    x, y, w, h = cv2.boundingRect(contours[nr])

    rect = cv2.rectangle(img, (x-10,y-10), (x+w+10,y+h+10), (0,255,0), 2)
    cropped = mask[y:y+h,x:x+w]
    cropped = cv2.resize(cropped,(300,900))
    cv2.imshow("rect2",cropped)

    bestRankDiff = 9999999
    index = 0

    for item in maskImgList:
        item = cv2.resize(item,(300,900))
        diffImg = cv2.absdiff(cropped, item)
        rankDiff = int(np.sum(diffImg)/255)
        
        if rankDiff < bestRankDiff:
            bestRankDiffImg = diffImg
            bestRankDiff = rankDiff
            bestRankName = nameList[index]
        index+= 1
    
    return bestRankName


