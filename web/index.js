const port = 4910;

var exec = require("child_process").exec;

var express = require("express");
var app = express();

const bodyParser = require("body-parser");

app.use(express.static("public"));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.route("/").get(function(req, res) {
  res.sendFile(__dirname + "/public/index.html");
});

app.route("/translate").post(function(req, res) {
  if (!req.body.text)
    return res.status(400).send('You need to specify the "text" parameter.');
  exec(
    '../YololTranslator.exe "' + req.body.text + '" ../dico/',
    (error, stdout, stderr) => {
      res.status(200).send(stdout);
    }
  );
});

app.route("/test").post(function(req, res) {
  res.status(200).send(req.body.text);
});

app.listen(port);

console.log("Server is running on port: " + port);
