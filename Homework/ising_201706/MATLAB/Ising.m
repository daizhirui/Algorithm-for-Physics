function [result]=Ising(size,totalstep,temperature)
%{  
    ����˵��
    size        ����ߴ�
    totalstep   ģ���ܲ���
    result      ģ��������
    temperature �¶�
    J           ������ϳ���
    Lattice     �������
    row         ������������-1
    column      ������������-1
    energy      ϵͳ������
    deltaenergy ���η�ת�����仯
    flipcount   ��ת����
    timestart   ���㿪ʼʱ��
    timeend     �������ʱ��
%}
%clear;%����Workspace

%----------------��������---------------------
%k=1.3806505*10^(-23);   %������������
%----------------��������---------------------
%ע�Ͳ���Ϊ��Ϊ����ʱʹ��
%size=100;                   %����ߴ�
%totalstep=5000000;          %ģ���ܲ���
result=zeros(totalstep,3);  %ģ��������
%temperature=1;              %�¶�
Lattice=ones(size);         %�������
energy=-2*size*size;        %ϵͳ������
flipcount=0;                %��ת������
timestart(1,:)=clock;       %���㿪ʼʱ��
%-----------------��ʼ����--------------------
for i=1:totalstep
    
    %����
    row=floor(rand*size);
    column=floor(rand*size);
    
    %��ȡ�����㼰�ܱ߾�����������
    p0=Lattice(row+1,column+1);
    p1=Lattice(mod(row-1,size)+1,mod(column-1,size)+1);
    p2=Lattice(mod(row-1,size)+1,column+1);
    p3=Lattice(row+1,mod(column-1,size)+1);
    p4=Lattice(row+1,mod(column+1,size)+1);
    p5=Lattice(mod(row+1,size)+1,column+1);
    p6=Lattice(mod(row+1,size)+1,mod(column+1,size)+1);

    %���㷭ת������
    %deltaenergy=2*(p2+p3+p4+p5)*p0;        %����������
    deltaenergy=2*(p1+p2+p3+p4+p5+p6)*p0;   %����������

    %�жϷ�ת    
    if deltaenergy<=0||rand()<exp(-deltaenergy*temperature)
        %������Ϊ��ֱ�ӷ�ת��������Ϊ���������
        Lattice(row+1,column+1)=-p0;    %��ת
        energy=energy+deltaenergy;      %����ϵͳ����
        flipcount=flipcount+1;          %��ת��¼
    end

    %�洢���
    result(i,:)=[energy,sum(sum(Lattice)),flipcount];
end
%-----------------��ʼ����--------------------
timeend(1,:)=clock;         %�������ʱ��
etime(timeend,timestart)    %�����ʱ

%ͼ�����
figure(1)
plot(result(:,1))
figure(2)
plot(result(:,2))
end


