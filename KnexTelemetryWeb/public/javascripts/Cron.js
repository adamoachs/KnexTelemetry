//Uses node-cron to run cron jobs

const nodeCron = require('node-cron');
const DataManager = (require('./DataManager.js')).GetInstance();

const dotenv = require('dotenv');
dotenv.config({path: 'app.env'});

//Every hour, delete old data 
nodeCron.schedule("0 * * * *", () => {
    DataManager.PruneOldData();
});