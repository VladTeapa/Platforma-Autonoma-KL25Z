clear all
device = serialport("COM7", 9600);
semnal = [];
figure
while(1)
   aux = read(device, 1, "uint8");
   if(aux == -1)
        continue
   end
   plot(1,aux,'d')
   semnal = [semnal aux];
end