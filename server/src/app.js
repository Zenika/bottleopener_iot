"use strict";

let express = require('express');
let app = express();
let http = require('http').Server(app);
let ws = require("nodejs-websocket");

let shiftr = require("./connectors/shiftr.module");
//now init connectors
shiftr.init();

let bodyParser = require('body-parser');
app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({extended: true})); // support encoded bodies

app.use(express.static('./public/'));
app.use(express.static('./node_modules/'));
app.get('/', function(req, res) {
    res.sendfile("public/index.html");
});

/**
 * Server itself
 * @type {http.Server}
 */
let server = app.listen(8090, function () {
    //print few information about the server
    let host = server.address().address;
    let port = server.address().port;
    console.log("Server running and listening @ " + host + ":" + port);
});

let serverws = ws.createServer(function (conn) {
    console.log("New connection");

    conn.on("text", function (str) {
        console.log("Received " + str);
    });

    conn.on("close", function (code, reason) {
        console.log("Connection closed");
    })
}).listen(8081);

/** list of current connected drinkers */
let drinkers = [
    {
        "name": "Gwen",
        "quantity": 0
    },
    {
        "name": "Adrien",
        "quantity": 0
    }
];

function _getDrinkerByName(name) {
    let drinker = null;
    for (drinker of drinkers) {
        if (name === drinker.name)
            return drinker;
    }

    //no drinker ? create a new one
    let newDrinker = {"name": name, "quantity": 0};
    drinkers.push(newDrinker);

    return newDrinker;
}

/**
 * GET instead of POST because it'll be called by Arduino YUN HttpClient that does only accept GET :(
 */
app.get("/drink", function (req, res) {
    let name = req.query.name;
    let qty = req.query.quantity;

    let drinker = _getDrinkerByName(name);
    let oldQty = parseFloat(drinker.quantity);
    drinker.quantity = oldQty + (parseFloat(qty) / 1000);


    console.log(drinker.name + " drink " + parseFloat(qty) + ". A total of " + drinker.quantity);

    res.send(drinkers);

    serverws.connections.forEach(function (conn) {
        conn.sendText(JSON.stringify(drinker));
    })
});

/**
 * Get a list of JSON for all registered drinkers
 * @path /drinkers
 * @HTTPMethod GET
 * @returns {string}
 */
app.get("/drinkers", function (req, res) {
    //encode result to Base64 to ensure there is no special character in the string
    //res.send(crypto.encode(cipher));

    res.send(drinkers);
});



