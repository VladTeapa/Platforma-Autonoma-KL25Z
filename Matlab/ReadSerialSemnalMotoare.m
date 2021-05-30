clear all
device = serialport("COM4", 9600);
signal = [];
i=0;
while(1)
    i = i+1;
    aux = read(device,1, "uint8");
    if(aux == -1)
        continue
    end
    aux = aux-50;
    aux = aux/50;
    signal = [signal aux];
end