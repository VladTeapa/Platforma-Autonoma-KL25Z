speedMean = [];
for i=1:length(speed)-1
    speedMean = [speedMean (speed(i)+speed(i+1))/2];
end