import cv2
import numpy as np
from AutomateSuperPackage.AutomateSuperModule import DatabaseClass
import yaml
from random import randint

import ctypes
user32 = ctypes.windll.user32
screensize = user32.GetSystemMetrics(0), user32.GetSystemMetrics(1)
print(screensize[0],screensize[1])

config_file_path = "config.yaml"
with open(config_file_path, 'r') as f:
    YAML = yaml.safe_load(f)
ACCES = DatabaseClass().AccesDatabase
ACCES.multipleCursors([YAML["DATABASE"]]),

def getResult(Query):
    ACCES.MultipleWriteQuery(Query,[0])
    return ACCES.MultipleResultFromQuery([0])

Xmax = getResult("SELECT TOP 1 X FROM inserts ORDER by X DESC")[0][0]
Xmin = getResult("SELECT TOP 1 X FROM inserts ORDER by X ASC")[0][0]
Ymax = getResult("SELECT TOP 1 Y FROM inserts ORDER by Y DESC")[0][0]
Ymin = getResult("SELECT TOP 1 Y FROM inserts ORDER by Y ASC")[0][0]
offset_x,offset_y = getResult("SELECT X, Y FROM inserts WHERE type = 'Offset'")[0]
print(offset_x,offset_y)
res_x = Xmax-Xmin
res_y = Ymax-Ymin
print(res_x,res_y)

def cross(text:str,x:int,y:int,size:int,color:tuple, image):
    #cv2.line(img , pt1=(0,0) , pt2=(300,300), color=(0,0,255),thickness=3)
    ##rescale to resolution:
    offset_for_viewer_x = 20
    offset_for_viewer_y = 20
    x = int((x-Xmin)/(res_x) *(screensize[0]-offset_for_viewer_x) + offset_for_viewer_x/2)
    y = int((y-Ymin)/(res_y)* (screensize[1]-offset_for_viewer_y)+ offset_for_viewer_y/2) 
    #print(x,y)
    fontscale = 0.35
    font_thickness = 1
    cv2.line(img = image,pt1 = (int(x-size/2),y),pt2 = (int(x+size/2),y),color = color,thickness = 1)
    cv2.line(img = image,pt1 = (x,int(y-size/2)),pt2 = (x,int(y+size/2)),color = color,thickness = 1)
    (label_width, label_height), baseline = cv2.getTextSize(text, cv2.FONT_HERSHEY_COMPLEX, fontscale, font_thickness)
    cv2.putText(image, text, (int(x-label_width/2),int(y)), cv2.FONT_HERSHEY_COMPLEX, fontscale, color, font_thickness)

img = np.zeros((screensize[1],screensize[0],3), np.uint8)
img[:] = (255,255,255)

data = getResult("SELECT X,Y,onDevice FROM inserts WHERE onDevice like '1%'")
#data = getResult("SELECT inserts.onDevice, inserts.X, inserts.Y FROM inserts WHERE (((inserts.onDevice) Like '1*'));")
for row in data:
    #cross(row[2],row[0],row[1],4,(255,255,255),img)
    cross("",row[0],row[1],20,(0,0,0),img)
cv2.putText(img, "INSERTS: xmil type from (net 1%)", (int(1920/2-400),30), cv2.FONT_HERSHEY_COMPLEX, 0.75, (0,0,0), 1)

data = getResult("SELECT X,Y,onDevice FROM inserts WHERE onDevice like '2%'")
for row in data:
    #cross(row[2],row[0],row[1],4,(0,255,0),img)
    cross("",row[0],row[1],18,(0,255,0),img)
cv2.putText(img, "INSERTS: xmil type from (net 2%)", (int(1920/2-400),60), cv2.FONT_HERSHEY_COMPLEX, 0.75, (0,255,0), 1)

data = getResult("SELECT X,Y,Node FROM inserts WHERE type = 'PIN'")
#data = getResult("SELECT inserts.onDevice, inserts.X, inserts.Y FROM inserts WHERE (((inserts.onDevice) Like '1*'));")
for row in data:
    #cross(row[2],row[0],row[1],10,(255,0,0),img)
    cross("",row[0],row[1],16,(255,0,0),img)
cv2.putText(img, "INSERTS: PIN type from", (int(1920/2-400),90), cv2.FONT_HERSHEY_COMPLEX, 0.75, (255,0,0), 1)


data = getResult("SELECT X_from,Y_from FROM wires WHERE type_from = 'PIN'")
#data = getResult("SELECT inserts.onDevice, inserts.X, inserts.Y FROM inserts WHERE (((inserts.onDevice) Like '1*'));")
for row in data:
    #cross(row[2],row[0],row[1],10,(255,0,0),img)
    cross("",row[0],row[1],14,(0,0,255),img)
cv2.putText(img, "WIRES: FROM PIN type", (int(1920/2-400),120), cv2.FONT_HERSHEY_COMPLEX, 0.75, (0,0,255), 1)

data = getResult("SELECT X_from,Y_from FROM wires WHERE type_to = 'PIN'")
#data = getResult("SELECT inserts.onDevice, inserts.X, inserts.Y FROM inserts WHERE (((inserts.onDevice) Like '1*'));")
for row in data:
    #cross(row[2],row[0],row[1],10,(255,0,0),img)
    cross("",row[0],row[1],12,(255,50,255),img)
cv2.putText(img, "WIRES:X_FROM,Y_FROM TO PIN type", (int(1920/2-400),150), cv2.FONT_HERSHEY_COMPLEX, 0.75, (255,50,255), 1)

data = getResult("SELECT X_from,Y_from FROM wires WHERE type_to = 'PROBE'")
#data = getResult("SELECT inserts.onDevice, inserts.X, inserts.Y FROM inserts WHERE (((inserts.onDevice) Like '1*'));")
for row in data:
    #cross(row[2],row[0],row[1],10,(255,0,0),img)
    cross("",row[0],row[1],20,(75,95,0),img)
cv2.putText(img, "WIRES: X_FROM,Y_FROM TO PROBE type", (int(1920/2-400),180), cv2.FONT_HERSHEY_COMPLEX, 0.75, (75,95,0), 1)

data = getResult("SELECT X_to,Y_to FROM wires WHERE type_to = 'PROBE'")
for row in data:
    #cross(row[2],row[0],row[1],10,(255,0,0),img)
    cross("",row[0],row[1],20,(75,0,75),img)
cv2.putText(img, "WIRES: X_to,Y_to TO PROBE type", (int(1920/2-400),210), cv2.FONT_HERSHEY_COMPLEX, 0.75, (75,0,75), 1)


data = getResult("SELECT X_from,Y_from,net_name_to FROM wires WHERE type_to = 'NODE'")
#data = getResult("SELECT inserts.onDevice, inserts.X, inserts.Y FROM inserts WHERE (((inserts.onDevice) Like '1*'));")
for row in data:
    print(row)
    cross(row[2],row[0],row[1],8,(0,95,75),img)
cv2.putText(img, "WIRES: FROM_X, TO_X NODE type_to", (int(1920/2-400),240), cv2.FONT_HERSHEY_COMPLEX, 0.75, (0,95,75), 1)


#data = getResult("SELECT b_from, r_from, c_from FROM trace order by ID ASC")
##data = getResult("SELECT inserts.onDevice, inserts.X, inserts.Y FROM inserts WHERE (((inserts.onDevice) Like '1*'));")
img2 = np.zeros((screensize[1],screensize[0],3), np.uint8)
#for row in data:
#    Query = f"SELECT X,Y FROM inserts WHERE b = {row[0]} and r = {row[1]} and c = {row[2]}"
#    print(Query)
#    xy_data = getResult(Query)
#    for xy in xy_data:
#        print(xy)
#        cross("",xy[0],xy[1],20,(0,0,255),img2)
#cv2.putText(img2, "TTRACES TO WIRES: type_from", (int(1920/2-400),240), cv2.FONT_HERSHEY_COMPLEX, 0.75, (0,0,255), 1)


data = getResult("SELECT b_to, r_to, c_to FROM trace order by ID ASC")
#data = getResult("SELECT inserts.onDevice, inserts.X, inserts.Y FROM inserts WHERE (((inserts.onDevice) Like '1*'));")
for row in data:
    Query = f"SELECT X,Y FROM inserts WHERE b = {row[0]} and r = {row[1]} and c = {row[2]}"
    if row[0] == None:
       ...
    else:
        print(Query)
        xy_data = getResult(Query)
        for xy in xy_data:
            print(xy)
            cross("",xy[0],xy[1],14,(0,255,0),img2)
cv2.putText(img2, "TTRACES TO WIRES: type_to", (int(1920/2-400),300), cv2.FONT_HERSHEY_COMPLEX, 0.75, (0,255,0), 1)




cross("OFFSET",offset_x,offset_y,10,(0,0,255),img)
cv2.imwrite("output_wires_inserts.png", img)
cv2.imwrite("trace_wires.png", img2)

