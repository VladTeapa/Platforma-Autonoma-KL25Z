clear all
device = serialport("COM7", 9600);
x2 = 1:128;
y2 = 1:128;
p = plot(x2,y2);
xlim([0 128])
ylim([0 256])
xlabel('Index')
ylabel('Value')

p.XDataSource = 'x2';
p.YDataSource = 'y2';
while(true)
    data = read(device, 128, "uint8");
    x = diff(data);

    for t = 1:128
        x2(t) = t;
        y2(t) = data(t);   
    end
    refreshdata
    drawnow
end