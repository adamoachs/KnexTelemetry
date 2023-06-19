const express = require('express');
const router = express.Router();
const DataManager = (require('../public/javascripts/DataManager.js')).GetInstance();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { 
    title: 'Express', 
    DataManager: DataManager
  });
});

module.exports = router;
