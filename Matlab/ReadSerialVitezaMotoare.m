clear all
device = serialport("COM7", 9600);
speed = [];
i=0;
while(1)
    i = i+1;
    aux = read(device,1, "uint8");
    if(aux == -1)
        continue
    end
    aux = aux*0.2093;
    speed = [speed aux];
end