const nodeCron = require('node-cron');
const DataManager = (require('./DataManager.js')).GetInstance();

const dotenv = require('dotenv');
dotenv.config({path: 'app.env'});

nodeCron.schedule("0 * * * *", () => {
    DataManager.PruneOldData();
});