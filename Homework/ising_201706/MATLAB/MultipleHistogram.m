clear;
TemperatureTable=[0,0.1,0.2,0.3,0.4,0.5,0.6,0.8,1,2,5,7,10]';
size=18;
totalstep=1000000;
jumpdistance=1000;
pointnum=50;
DataTable=zeros(totalstep,3,length(TemperatureTable));
for i=1:length(TemperatureTable)
    temperature=TemperatureTable(i,1);
    DataTable(:,:,i)=Ising(size,totalstep,temperature);
end
EnergyStatistics=EnergyStatistics(totalstep,jumpdistance,pointnum,DataTable);
P=PCalculation(EnergyStatistics,TemperatureTable,-2*size*size,2*size*size,500,2);