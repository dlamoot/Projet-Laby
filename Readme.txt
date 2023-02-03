Doc Projet

Je livre ici mon interprétation du sujet avec mes idées afin de réaliser au mieux celui-ci.

Afin de réaliser le jeu labyrinthe, il a fallu passer par plusieurs phases, réfléchir puis écrire différentes fonctions.

Tout d'abord, il a fallu établir la connexion avec le serveur puis dans un second temps réfléchir comment allait s'établir et se dérouler une partie. Grâce à la fonction printLabyrinth, nous pouvons afficher le labyrinthe à partir des données récupérées depuis le serveur. Mais pour jouer,  ici n'st pas suffisant, il a fallu créer plusieurs structure :
- t_tile : représente une tuile 
- t_joueur : reprends les données correspondant à un joueur
- t_local : contient les données locale nécessaire à la mise à jour du labyrinthe.

Par la suite, nous avons écrit plusieurs fonctions permettant le bon fonctionnement du programme comme une fonction init_tile qui permet d'initialiser une tuile, une fonction récupLaby qui nous permettra d'enregistrer le labyrinthe localement afin de pouvoir le modifier et réaliser la mise à jour de celui-ci. Concernant les tuiles, nous avons une fonction insertionTuile et rotationTuile qui permettent, comme l'indique les règle du jeu, d'insérer une tuile ou de tourner une tuile.
Nous avons également une fonction jouer qui nous permet de jouer individuellement. 

Afin de programmer un bot pouvant gagner une partie, nous avons réaliser une fonction expansion qui permettra d'explorer le labyrinthe afin de trouver un trésor. Par la suite, il nous faudra une fonction qui mettra à jour le labyrinthe et réaliser la fonction bot qui utilisera toutes les fonctions précédentes (hormis jouer) afin de pouvoir réaliser les différents coups à jouer et de remporter la partie. 