function [P]=PCalculation(EnergyStatistics,TemperatureTable,energyStart,energyEnd,energyStep,Temperature)
    
    P=zeros(ceil((energyEnd-energyStart)/energyStep),2);
    count=1;
    
    for energy=energyStart:energyStep:energyEnd
        
        denominator=0;  %·ÖÄ¸
        for i=1:length(TemperatureTable(:,1))
            denominator=denominator+exp(TemperatureTable(i,1)*energy);
        end
        
        numerator=0;    %·Ö×Ó
        for i=1:length(EnergyStatistics(:,1))
            if energy==EnergyStatistics(i,1)
               numerator=EnergyStatistics(i,2)*exp(Temperature*energy);
            end
        end
        
        P(count,1:2)=[energy,numerator/denominator];
        count=count+1;
    end
    
    cosistance=sum(P(:,2));
    P(:,2)=P(:,2)/cosistance;
    
end