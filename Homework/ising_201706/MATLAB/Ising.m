function [result]=Ising(size,totalstep,temperature)
%{  
    变量说明
    size        晶格尺寸
    totalstep   模拟总步数
    result      模拟结果矩阵
    temperature 温度
    J           能量耦合常数
    Lattice     晶格矩阵
    row         检查格点的行坐标-1
    column      检查格点的列坐标-1
    energy      系统总能量
    deltaenergy 单次翻转能量变化
    flipcount   翻转计数
    timestart   计算开始时间
    timeend     计算结束时间
%}
%clear;%清理Workspace

%----------------常量定义---------------------
%k=1.3806505*10^(-23);   %玻尔兹曼常数
%----------------变量设置---------------------
%注释部分为作为主体时使用
%size=100;                   %晶格尺寸
%totalstep=5000000;          %模拟总步数
result=zeros(totalstep,3);  %模拟结果矩阵
%temperature=1;              %温度
Lattice=ones(size);         %晶格矩阵
energy=-2*size*size;        %系统总能量
flipcount=0;                %翻转计数器
timestart(1,:)=clock;       %计算开始时间
%-----------------开始计算--------------------
for i=1:totalstep
    
    %采样
    row=floor(rand*size);
    column=floor(rand*size);
    
    %获取采样点及周边晶格自旋方向
    p0=Lattice(row+1,column+1);
    p1=Lattice(mod(row-1,size)+1,mod(column-1,size)+1);
    p2=Lattice(mod(row-1,size)+1,column+1);
    p3=Lattice(row+1,mod(column-1,size)+1);
    p4=Lattice(row+1,mod(column+1,size)+1);
    p5=Lattice(mod(row+1,size)+1,column+1);
    p6=Lattice(mod(row+1,size)+1,mod(column+1,size)+1);

    %计算翻转能量差
    %deltaenergy=2*(p2+p3+p4+p5)*p0;        %正方形网格
    deltaenergy=2*(p1+p2+p3+p4+p5+p6)*p0;   %三角形网格

    %判断翻转    
    if deltaenergy<=0||rand()<exp(-deltaenergy*temperature)
        %能量差为负直接翻转，能量差为正计算概率
        Lattice(row+1,column+1)=-p0;    %翻转
        energy=energy+deltaenergy;      %计算系统能量
        flipcount=flipcount+1;          %翻转记录
    end

    %存储结果
    result(i,:)=[energy,sum(sum(Lattice)),flipcount];
end
%-----------------开始结束--------------------
timeend(1,:)=clock;         %计算结束时间
etime(timeend,timestart)    %计算耗时

%图像输出
figure(1)
plot(result(:,1))
figure(2)
plot(result(:,2))
end


