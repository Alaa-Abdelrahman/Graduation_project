import serial
import time
import csv
import glob
end_time=time.time()+6
no_of_samples=0
ports=glob.glob('/dev/tty*')
port=ports[0]

with serial.Serial(port=port,baudrate=115200) as ser:
    print("connected to: " + ser.portstr)
    while no_of_samples<=10:
        info=str(ser.readline())
        info=info[2:-5]
        print(info)
        if 'spread' in info:
            while time.time()<end_time:
                pass
            ser.write(b's')

        if 'hold' in info:
            while time.time()<end_time:
                pass
            ser.write(b'h')


        print('get ready')

        for num_of_readings in range(10) :
            with open('file.csv','a')as csvfile:
                datafile=csv.writer(csvfile)
                for no_of_lines_per_reading in range(0,100,2):   
                    getData=str(ser.readline())            
                    data=getData[2:][:-5]
                    data=data.split(',')
                    print(data)
                    datafile.writerow(data)

        