# YololTranslator

## Le programme
C'est un simple programme pour traduire du texte normal en un texte écrit par un kikoulol avec plein d'abréviations et de fautes.

Pour compiler utilisez cmake ou bien un simple "g++ src/main.cpp -std=c++14" suffit.

Pour utiliser le programme lancer l'executable suivit de la phrase entre guillements que vous voulez traduire.

## L'API Rest
Une API Rest existe, le code est dans le dossier __api__ et une instance tourne sur mon Raspberry pi. Pour l'utilisez envoyer une requête POST sur: https://yololtranslate-api.baduit.eu/translate avec le texte que vous voulez traduire dans une variable nommée __test__.


## Le bot discord
Un bot discord existe et tourne actuellement sur mon Raspberry pi. Le code est dans le dossier __discord-bot__. Pour ajouter le bot à votre serveur, voici le lien https://discordapp.com/api/oauth2/authorize?client_id=536250577051451402&permissions=2048&redirect_uri=https%3A%2F%2Fdiscordapp.com%2Fapi%2Foauth2%2Fauthorize%3Fclient_id%3D536250577051451402%26redirect_uri%3Dhttps%253A%252F%252Fdiscordapp.com%252Foauth2%252Fauthorize%253F%2526client_id%253D53625057705145140&scope=bot.