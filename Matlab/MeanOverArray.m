speedMean = [];
for i=1:length(speed)
    if i==1
        speedMean = [speedMean (speed(i))];
        continue
    end
    speedMean = [speedMean (speed(i)+speed(i-1))/2];
end