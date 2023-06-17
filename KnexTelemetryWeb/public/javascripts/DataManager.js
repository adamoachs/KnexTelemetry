module.exports = class DataManager {

    constructor() {
        this.Data = {};
    }



    LogData(newData){
        //Add to local cache
        if(!this.Data[newData.dataKey])
            this.Data[newData.dataKey] = [];

        this.Data[newData.dataKey].push({
            dataValue: newData.dataValue,
            timestamp: newData.timestamp
        });

        //TODO: insert into DB
    }

}