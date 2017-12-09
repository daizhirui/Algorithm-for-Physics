function [EnergyStatistics]=EnergyStatistics(totalstep,jumpdistance,pointnum,result)

    EnergyStatistics=zeros(1,2);
    count=1;
    for i=1:length(result(1,1,:))
        for j=totalstep-jumpdistance*(pointnum-1):jumpdistance:totalstep
            existance=0;
            for k=1:length(EnergyStatistics(:,1))
                if result(j,1,i)==EnergyStatistics(k,1)
                    existance=1;
                    EnergyStatistics(k,2)=EnergyStatistics(k,2)+1;
                    break
                end
            end
            if existance==0
                EnergyStatistics(count,1:2)=[result(j,1,i),1];
                count=count+1;
            end
        end
    end
end