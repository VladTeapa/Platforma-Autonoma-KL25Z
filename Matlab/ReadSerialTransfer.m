clear all
device = serialport("COM4", 9600);
signal = [];
speed = [];
i=0;
while(1)
    i = i+1;
    aux = read(device,1, "uint8");
    if(aux == -1)
        continue
    end
    if(aux > 10)
        aux = aux-11;
        aux= aux/100;
        speed = [speed aux];
    else
        aux = aux/10;
        signal = [signal aux];
    end
end