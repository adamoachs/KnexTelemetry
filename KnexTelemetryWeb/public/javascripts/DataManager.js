//This class handles storing and caching of data in memory, as well as storing and retrieving from DB

const sqlite3 = require('sqlite3');
const fs = require('fs');
const dotenv = require('dotenv');
dotenv.config({path: 'app.env'});

class DataManager {

    static dbPath = './knexdata.db';
    static instance;

    static GetInstance() {
        if(DataManager.instance == null)
            DataManager.instance = new DataManager();
            
        return DataManager.instance;
    }

    constructor() {
        this.Data = {};
        this.Status = {};

        if(fs.existsSync(DataManager.dbPath))
            this.#OpenDatabase(DataManager.dbPath);
        else
            this.#CreateAndOpenDatabase(DataManager.dbPath);
    }

    LogData(newData) {
        this.#LogDataLocal(newData);
        this.#LogDataDatabase(newData);
    }

    PruneOldData() {
        this.#PruneDataLocal();
        this.#PruneDataDatabase();
    }

    SetStatus(newStatus) {
        this.Status[newStatus.StatusName] = {
            StatusValue: newStatus.StatusValue, 
            Timestamp: newStatus.Timestamp
        };
        //Not logging status to DB, as we only keep current status and not history
    }

    //Return the latest entry in Data[dataKey]
    GetLatestDataByKey(dataKey) {
        var data = this.Data[dataKey];
        if(!data)
            return { DataValue: null };

        data.sort((a, b) => b.Timestamp - a.Timestamp);
        return data[0];
    }

    //Returns Data filtered down so each DataKey, instead of pointing to an array, points to a single object containing the most recent data
    GetLatestData() {
        //todo
    }

    GetStatus(statusName) {
        return this.Status[statusName] ?? { StatusValue: "Unknown" };
    }

    #LogDataLocal(newData) {
        //Add to local cache
        if (!this.Data[newData.DataKey])
            this.Data[newData.DataKey] = [];

        this.Data[newData.DataKey].push({
            DataValue: newData.DataValue,
            Timestamp: newData.Timestamp
        });
    }

    #LogDataDatabase(newData) {
        //Add to database
        const sql = `
            INSERT INTO Telemetry
            (DataKey, DataValue, Timestamp)
            VALUES
            ($DataKey, $DataValue, $Timestamp);
        `;
        const params = {
            $DataKey: newData.DataKey,
            $DataValue: newData.DataValue,
            $Timestamp: newData.Timestamp
        };
        this.Database.run(sql, params);
    }

    #PruneDataLocal() {
        //Prune old data from local cache
        const hours = (process.env.DATALIFETIMEHOURS || 72);
        if(hours == -1)
            return;

        const dateCutoff = (Date.now() / 1000) - (hours * 60 * 60);

        for(const DataKey in this.Data){
            //for(const item of this.Data[DataKey])
            for(let i = this.Data[DataKey].length - 1; i >= 0; i--)
            {
                let item = this.Data[DataKey][i];
                if(item.Timestamp < dateCutoff) {
                    const index = this.Data[DataKey].indexOf(item);
                    this.Data[DataKey].splice(index, 1);
                }
            }
        }
    }

    #PruneDataDatabase() {
        //Prune old data from database
        const hours = (process.env.DATALIFETIMEHOURS || 72);
        if(hours == -1)
            return;

        const sql = `
            DELETE FROM Telemetry
            WHERE TimeStamp < $DateCutoff
        `;
        const params = { $DateCutoff: Date.now() - (hours * 60 * 60) };

        this.Database.run(sql, params);
    }

    #CreateAndOpenDatabase(path) {
        this.Database = new sqlite3.Database(path);

        this.Database.exec(`
            CREATE TABLE Telemetry (
                DataId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                DataKey VARCHAR(50) NOT NULL,
                DataValue VARCHAR(50) NOT NULL,
                Timestamp DATETIME NOT NULL
            );
        `);
    }

    #OpenDatabase(path) {
        this.Database = new sqlite3.Database(path, sqlite3.OPEN_READWRITE);  
        const sql = `SELECT DataKey, DataValue, Timestamp FROM Telemetry`;
        const params = [];

        //Clear old data before loading it into memory
        this.#PruneDataDatabase();
        
        this.Database.all(sql, params, (err, rows) => {
            rows.forEach(row => {
                //Add row to local Data cache
                const rowdata = {
                    DataKey: row.DataKey, 
                    DataValue: row.DataValue,
                    Timestamp: row.Timestamp, 
                };
                this.#LogDataLocal(rowdata);
            });
        });
    }

}

module.exports = DataManager;