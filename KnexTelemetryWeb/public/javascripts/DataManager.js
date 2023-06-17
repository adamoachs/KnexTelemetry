//This class handles storing and caching of data in memory, as well as storing and retrieving from DB

//TODO: Periodically prune data from this.Data that's older than dataLifetimeHours

const sqlite3 = require('sqlite3');
const fs = require('fs');

class DataManager {

    static dbPath = './knexdata.db';
    static dataLifetimeHours = 72;

    constructor() {
        this.Data = {};

        if(fs.existsSync(DataManager.dbPath))
            this.Database = this.#OpenDatabase(DataManager.dbPath);
        else
            this.Database = this.#CreateAndOpenDatabase(DataManager.dbPath);
    }

    LogData(newData) {
        this.#LogDataLocal(newData);
        this.#LogDataDatabase(newData);
    }

    #LogDataLocal(newData) {
        //Add to local cache
        if (!this.Data[newData.DataKey])
            this.Data[newData.DataKey] = [];

        this.Data[newData.DataKey].push({
            dataValue: newData.DataValue,
            timestamp: newData.Timestamp
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

    #CreateAndOpenDatabase(path) {
        const newdb = new sqlite3.Database(path);

        newdb.exec(`
            CREATE TABLE Telemetry (
                DataId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                DataKey VARCHAR(50) NOT NULL,
                DataValue VARCHAR(50) NOT NULL,
                Timestamp DATETIME NOT NULL
            );
        `);

        return newdb;
    }

    #OpenDatabase(path) {
        const db = new sqlite3.Database(path, sqlite3.OPEN_READWRITE, (err) => {
            let a =5;
        });

        const sql = `SELECT DataKey, DataValue, Timestamp FROM Telemetry WHERE TimeStamp > $DateCutoff`;
        //const params = { $DateCutoff: Date.now() - (DataManager.dataLifetimeHours * 60 * 60) }
        const params = { $DateCutoff: 0 }
        db.all(sql, params, (err, rows) => {
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

       return db;
    }

}

module.exports = DataManager;