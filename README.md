# YololTranslator
## Présentation du projet
Le but YololTranslator est de faire des fautes d'orthographes ridicules. Créé à partir d'une blague entre ami, au début ce projet était juste composé d'une petit programme en C++, maintenant c'est un projet bien plus étendu avec plusieurs technologies qui s'interfacent.

Voici donc les différentes parties:
- __Core__: C'est la partie qui va transformées un texte correcte en un texte digne des pires kikoulols.
- __Web__: C'est ce qui va permettre d'utiliser YololTranslator via internet, pour cela il y a une API REST ainsi qu'un site internet (https://yololtranslate-api.baduit.eu/).
- __Discord__: Un bot discord a été créé, il permet d'utiliser simplement et rapidiment YololTranslator sur un serveur discord.
- __GUI__: Ce sont des interfaces utilisateurs permettant d'utiliser YololTranslator de manière plus agréable qu'une simple application console sans pour autant devoir passer par le site internet. (Même si l'API REST peut être utilisée.)

## List des technologies utilisées
- __C++__: Core
- __Cmake__: pour build les parties en C++
- __Nodejs__: API REST et bot discord
- __Vue.js__: site web
- __html__: site web
- __Css__: site web
- __Python3__: GUI
- __Shell__: quelques petits scripts utilitaires pour déployer sur mon raspberry pi la partie web et le bot discord.
- __dart__: l'application mobile
- __flutter__: l'application mobile

## Core
### V1
Pour compiler utilisez cmake ou bien un simple "g++ src/main.cpp -std=c++14" suffit.

Pour utiliser le programme lancer l'executable suivit de la phrase entre guillements que vous voulez traduire.

La V1 

### V2
C'est la version par défaut utilisées par tout les clients (python, web, discord, app mobile).

Pour build, utilisez cmake, nécessite un compilateur supportant C++17.

Il y a un exécutable qui est une simple application console ainsi qu'une bibliothèque partagées (.so/.dll).

### V3
WIP
Nécessite cmake pour build.
Les techniques de traductions sont les mêmes que pour la V2 mais au lieu de passer par des fichiers assets au runtime, les dictionnaires seront inclus au binaire, de plus le code sera pensé pour être optimisé pendant la traduction et avoir un lancement rapide (c'est pour ça que les dicos sont dans le binaire, pour éviter de devoir parser au lancement ou pendant la traduction). 
Le but va être double:
	- avec le gain de vitesse on pourra espérer de pouvoir le compiler wasm et que le site web puisse l'utiliser sans passer par l'API
	- plus facile de partager le binaire ou les bibliothèques partagées car il n'y a plus le besoin de partager avec les dicos.

## Web
Une API Rest existe, le code est dans le dossier __api__ et une instance tourne sur mon Raspberry pi. Pour l'utilisez envoyer une requête POST sur: https://yololtranslate-api.baduit.eu/translate avec le texte que vous voulez traduire dans une variable nommée __text__.

Il y a aussi un site internet: https://yololtranslate-api.baduit.eu/

## Le bot discord
Un bot discord existe et tourne actuellement sur mon Raspberry pi. Le code est dans le dossier __discord-bot__. Pour ajouter le bot à votre serveur, voici le lien https://discordapp.com/api/oauth2/authorize?client_id=536250577051451402&permissions=2048&redirect_uri=https%3A%2F%2Fdiscordapp.com%2Fapi%2Foauth2%2Fauthorize%3Fclient_id%3D536250577051451402%26redirect_uri%3Dhttps%253A%252F%252Fdiscordapp.com%252Foauth2%252Fauthorize%253F%2526client_id%253D53625057705145140&scope=bot.

Pour l'utilisez:
`!yolol ici mon texte que je veux traduire`

Le bot répondra avec le traduit.

Il est possible de choisir la version du core utilisées:
- V1: `!yolol-v1 ici mon texte que je veux traduire`
- V2: `!yolol-v2 ici mon texte que je veux traduire`

## GUI
### Python
Une simple GUI en python3 composées d'un seul fichier utilisant l'API web pour faire les traduction.

### FlutterApp
Une app mobile très simple en dart avec le framework flutter, ça utilise l'API web pour faire les traductions.
