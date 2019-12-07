import 'package:flutter/material.dart';

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

  void _onTextChanged(String updatedText) {
    setState(() {
      _translatedText = updatedText; // TODO: make a request to translate
    });
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
            Text(
              '$_translatedText',
              style: Theme.of(context).textTheme.display1, // TODO: change the style
            ),
          ],
        ),
      ),
    );
  }
}
