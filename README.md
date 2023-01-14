# YololTranslator
Travail en cours sur le readme suite à un gros rework

## Présentation du projet
Le but YololTranslator est de faire des fautes d'orthographes ridicules. Créé à partir d'une blague entre ami, au début ce projet était juste composé d'une petit programme en C++, maintenant c'est un projet bien plus étendu avec plusieurs technologies qui s'interfacent.

Voici donc les différentes parties:
- __Core__: C'est la partie qui va transformées un texte correcte en un texte digne des pires kikoulols.
- __Web__: C'est ce qui va permettre d'utiliser YololTranslator via internet, pour cela il y a une API REST ainsi qu'un site internet (https://yololtranslate-api.baduit.eu/).
- __Discord__: Un bot discord a été créé, il permet d'utiliser simplement et rapidiment YololTranslator sur un serveur discord.

## Core
Pour build, utilisez cmake, ce la nécessite un compilateur supportant C++20.

Il y a un exécutable qui est une simple application console ainsi qu'une bibliothèque.

## Web
Une API Rest existe. Pour l'utiliser envoyez une requête POST sur: https://yololtranslate-api.baduit.eu/translate avec le texte que vous voulez traduire dans une variable nommée __text__.

Il y a aussi un site internet: https://yololtranslate-api.baduit.eu/

## Le bot discord
Un bot discord existe et tourne actuellement sur mon Raspberry pi. Le code est dans le dossier __discord-bot__. Pour ajouter le bot à votre serveur, voici le lien https://discordapp.com/api/oauth2/authorize?client_id=536250577051451402&permissions=2048&redirect_uri=https%3A%2F%2Fdiscordapp.com%2Fapi%2Foauth2%2Fauthorize%3Fclient_id%3D536250577051451402%26redirect_uri%3Dhttps%253A%252F%252Fdiscordapp.com%252Foauth2%252Fauthorize%253F%2526client_id%253D53625057705145140&scope=bot.

Pour l'utiliser:
`!yolol ici mon texte que je veux traduire`

Le bot répondra avec le texte traduit.

