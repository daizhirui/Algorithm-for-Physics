filename = fullfile('./','build/result1.txt');
filein = fopen(filename);
fileout = fopen('temp','w');
while ~feof(filein)
    line = fgetl(filein);
    if double(line(1))>=48&&double(line(1))<=57
        fprintf(fileout,'%s\n',line);
        continue;
    end
end
fclose(fileout);
fclose(filein);
buffer = importdata('temp');

[row col] = size(buffer);
[min_x pos_x] = min(buffer(:,2));
[max_x pos_x] = max(buffer(:,2));
[min_y pos_y] = min(buffer(:,3));
[max_y pos_y] = max(buffer(:,3));
mp4obj = VideoWriter('test.avi','Archival');
open(mp4obj);
fig = figure;
box on;
axis([round(min_x)-10 round(max_x)+10 round(min_y)-10 round(max_y)+10]);
hold on;
for t = 1:1000:row
    disp(t)
    plot(buffer(1:t,2),buffer(1:t,3),'b-');
    f = getframe(gcf);
    f.cdata = imresize(f.cdata, [337 442]);
    writeVideo(mp4obj,f);
end
close(fig);
close(mp4obj);