import json
import numpy as np
import serial
import threading
import time
import playsound
import pygame
pygame.init()
py_serial = serial.Serial(port='/dev/cu.usbmodem21401', baudrate=9600)
with open('./data/subway2210.json', "r") as json_file:
  subway2210 = json.load(json_file)
time.sleep(2)

stations= []
for datum in subway2210:
  temp =  datum['SUB_STA_NM']
  stations.append(temp)
del_stations = ['용답','신답','신설동','도림천','양천구청','신정네거리','용두(동대문구청)']
filtered_stations = [x for x in stations if x not in del_stations]
pygame.mixer.music.load('subway_bgm.mp3')
pygame.mixer.music.play(-1)
while True:
  num_command = input('궁금한 시간대를 입력하세요(입력 숫자 형태: 0 ~ 23): ')
  playsound.playsound('subway_in.mp3', block=False)
  num_data = [d[num_command] for d in subway2210]
  want_data = { name:value for name, value in zip(filtered_stations, num_data) }
  want_data_sort = sorted(want_data.items(), key=lambda x: x[1])

  final_arr = np.array_split(want_data_sort,3)
  for i in range(len(final_arr)):
    if i == 0:
      for arr in final_arr[i]:
        arr[1] = '1' #녹색
    elif i == 1:
      for arr in final_arr[i]:
        arr[1] = '2'#노란색
    elif i == 2:
      for arr in final_arr[i]:
        arr[1] = '3' #빨간색

  final_datas = list(final_arr[0]) + list(final_arr[1]) + list(final_arr[2])
  final_datas.sort(key=lambda x: filtered_stations.index(x[0]))
  print(final_datas)
  last_elements = []
  for array in final_datas:
    last_element = array[-1]
    last_elements.append(last_element)
  last_elements_int = [int(x) for x in last_elements]
  for i in range(len(last_elements)):
    num = str(i)+","+last_elements[i]+"\n"
    py_serial.write(num.encode())
    print(num.encode())
    time.sleep(0.1)
  #py_serial.close()


