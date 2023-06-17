const express = require('express');
const router = express.Router();
const DataManager = new (require('../public/javascripts/DataManager.js'));


router.post('/data', function(req, res, next) {
  if(!Authorized(req, res))
    return;

  DataManager.LogData(req.body)
  res.send(DataManager.Data);
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
