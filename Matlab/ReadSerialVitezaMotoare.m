clear all
device = serialport("COM4", 9600);
speed = [];
i=0;
while(1)
    i = i+1;
    aux = read(device,1, "uint8");
    if(aux == -1)
        continue
    end
    speed = [speed aux];
end