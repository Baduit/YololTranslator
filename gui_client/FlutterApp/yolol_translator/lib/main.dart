import 'package:flutter/material.dart';
import 'package:http/http.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Yolol Translator',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'Yolol Translator Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  var _translatedText = "";

  void _onTextChanged(String updatedText) async {
    if (updatedText.isEmpty) {
      setState(() {
        _translatedText = "";
      });
    } else {
      String newTranslatedText = await _makePostRequest(updatedText);
      setState(() {
        _translatedText = newTranslatedText;
      });
    }
  }

  Future<String> _makePostRequest(String textToTranslate) async {
    String url = 'https://yololtranslate-api.baduit.eu/translate';
    Map<String, String> headers = {"Content-type": "application/json"};
    String json = '{"text": "$textToTranslate"}';

    Response response = await post(url, headers: headers, body: json);

    int statusCode = response.statusCode;
    if (statusCode != 200) {
      return "Problème de connexion avec le serveur.";
    }
    String body = response.body;
    return body;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            TextField(
              decoration: InputDecoration(
                border: OutlineInputBorder(),
                hintText: 'Écrit ton texte à traduire ici.',
              ),
              onChanged: _onTextChanged,
              keyboardType: TextInputType.multiline,
              minLines: 3,
              maxLines: null,
            ),
            Container(
                width: MediaQuery.of(context).size.width,
                height: 60,
                //margin: const EdgeInsets.all(10.0),
                //padding: const EdgeInsets.all(10.0),
                decoration:
                    BoxDecoration(border: Border.all(color: Colors.blueAccent)),
                child: FittedBox(
                  alignment: Alignment.centerLeft,
                  child: Text(
                    '$_translatedText',
                    style: TextStyle(
                        //fontWeight: FontWeight.bold,
                        ),
                  ),
                )),
          ],
        ),
      ),
    );
  }
}
