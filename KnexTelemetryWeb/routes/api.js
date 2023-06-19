const express = require('express');
const router = express.Router();
const DataManager = (require('../public/javascripts/DataManager.js')).GetInstance();

/* POST endpoints. Auth required, called by Arduino */

/*
  POST /api/data
  {
    "DataKey": "balls-in-last-hour",
    "DataValue": "240",
    "Timestamp": 1687110112
  }
*/
router.post('/data', function(req, res, next) {
  if(!Authorized(req, res))
    return;

  DataManager.LogData(req.body);
  res.send({ status: 200 });
});

/*
  POST /api/status
  {
    "StatusName": "lift-1",
    "DataValue": "online",
    "Timestamp": 1687110112
  }
*/
router.post('/status', function(req, res, next) {
  if(!Authorized(req, res))
    return;

  DataManager.SetStatus(req.body);
  res.send({ status: 200 });
});


/* GET endpoints. No auth required, called by UI */

/*
  GET /api/data
*/
router.get('/data', function(req, res, next) {
  res.send(DataManager.Data);
});

/*
  GET /api/status
*/
router.get('/status', function(req, res, next) {
  res.send(DataManager.Status);
});

function Authorized(req, res){
  if(req.headers.authorization === `Bearer ${process.env.ACCESS_TOKEN}`)
    return true
  else
  {
    res.status(401);
    res.send({error: "Invalid token"});
    return false;
  }
}

module.exports = router;
