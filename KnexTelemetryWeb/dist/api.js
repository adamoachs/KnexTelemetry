"use strict";
const express = require('express');
const router = express.Router();
router.post('/', function (req, res, next) {
    res.send(JSON.stringify({ test: "hello" }));
});
module.exports = router;
