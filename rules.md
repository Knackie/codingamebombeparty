Survivez plus longtemps que votre adversaire.
  Règles
Le jeu se joue sur une grille large de 13 cases et haute de 11 cases. Les coordonnées X=0, Y=0 représentent la case supérieure gauche.

Une partie peut comporter jusqu'à 4 joueurs. Chaque joueur débute dans un coin de la carte.
Toutes les actions réalisées par les joueurs sont calculées simultanément.

Des caisses sont réparties sur la carte, et peuvent être détruites par des bombes.
Une caisse peut contenir un objet. En détruisant une caisse, vous faites apparaître l'objet qui est à l'intérieur .

La carte fonctionne comme suit :

    Chaque case de la grille peut être du sol, une caisse ou un mur. Le sol est indiqué par un point ( .), les caisses par un entier et les murs par une croix ( X).
    Plusieurs joueurs peuvent occuper la même case.
    Un nombre aléatoire de caisses entre 30 et 65 inclus seront placées symétriquement de part et d'autre de la grille.

Les joueurs fonctionnent comme suit :

    à chaque tour, un joueur peut se déplacer verticalement ou horizontalement vers une case adjacente. Si une bombe ou un obstacle est déjà présent sur cette case, le joueur ne pourra pas se déplacer.
    Un joueur peut occuper la même case qu'un bombe seulement si la bombe apparaît durant le même tour que celui où le joueur arrive sur la case.
    En utilisant la commande MOVE suivie de coordonnées dans la grille, le joueur tentera de se déplacer en se rapprochant de la case ciblée. Le joueur calculera automatiquement la trajectoire la plus courte pour se rendre à la case ciblée. Si la destination n'est pas une cellule disponible, le joueur choisira la case la plus proche des coordonnées entrées.
    En utilisant la commande BOMB, suivie de coordonnées, le joueur tentera de placer une bombe sur la case qu'il occupe actuellement, puis de se déplacer vers les coordonnées entrées.
    Les joueurs peuvent rester sur une case sur laquelle ils placent une bombe.
    Au début de la partie, un joueur ne peut avoir qu' 1 bombe en jeu à la fois.
    Au début de la partie, un joueur place des bombes ayant une portée de 3.

Les bombes fonctionnent comme suit :

    Les bombes ont un compte à rebours de 8 tours de jeu. À chaque tour de jeu, le compte à rebours est décrémenté de 1. Au tour où le compte à rebours arrive à 0, la bombe explose.
    Les explosions ont une portée, elles explosent donc horizontalement et verticalement jusqu'à portée cases dans chaque direction, sauf si elles rencontrent un mur, une caisse ou une autre bombe.
    Une explosion touchant une caisse la détruit.
    Une explosion touchant un objet le détruit.
    Une explosion touchant un joueur l'élimine.
    Une explosion touchant une bombe la fait exploser, créant une réaction en chaîne.

Les objets fonctionnent comme suit :

    Les objets apparaissent une fois que toutes les explosions ont eu lieu.
    Un joueur entrant dans une case qui contient un objet ramasse cet objet. Plusieurs joueurs peuvent ramasser le même objet s'ils arrivent sur la case au même tour.
    Il y a 2 objets différents, chacun représenté par un entier :
        1 Extra Portée : les bombes du joueur explosent avec une portée accrue de une unité. Cela ne s'applique pas aux bombes déjà en jeu.
        2 Extra Bombe : le joueur peut avoir une bombe de plus en jeu à la fois.

Le jeu se termine quand il ne reste qu'un survivant. Ce dernier gagne la partie.
Après 200 tours de jeu, ou si l'état du jeu n'a pas changé en 20 tours,ou 20 tours après la destruction de la dernière caisse, la partie s'arrête et tous les joueurs restants sont éliminés.
Deux joueurs éliminés au même tour sont classés par le nombre de caisses qu'ils ont détruites pendant le jeu.

L'état du jeu à chaque tour vous est donné sous la forme d'une liste d'entités, chacune avec un type, propriétaire, position, param1 et param2.

Le type peut être :

    Pour un joueur : 0.
    Pour une bombe : 1.
    Pour un objet: 2.

Le propriétaire peut être :

    Pour un joueur : l'id de ce joueur ( 0 ou 1 ou 2 ou 3).
    Pour une bombe : l'id du joueur qui l'a posé.
    Pour un objet : zéro ( 0).

Le param1 peut être:

    Pour un joueur : le nombre de bombes qu'il peut encore placer.
    Pour une bombe : le nombre de tours de jeu restants avant que la bombe explose.
    Pour un objet : le nombre représentatif de l'objet.

Le param2 peut être :

    Pour un joueur : la valeur de portée des bombes du joueur.
    Pour une bombe : la valeur de portée de cette bombe.
    Pour un objet : zéro ( 0).

 
Conditions de victoire

    Vous êtes le dernier joueur en vie.
    Vous et vos adversaires sont éliminés en même temps et vous êtes celui ayant explosé le plus de caisses.

 
Conditions de défaite

    Vous êtes touché par une bombe.
    Vous fournissez une sortie incorrecte.

  Règles pour les experts
Détails sur les calculs lors d'un tour :

    Au début d'un tour, toutes les bombes en jeu voient leur compte à rebours décrémenté de 1.
    Tout compte à rebours arrivant à 0 provoquera l'explosion immédiate de la bombe, avant que les joueurs ne bougent.
    Toute bombe prise dans une explosion est traitée comme si elle avait explosé au même moment.
    Les explosions ne se propagent pas après un obstacle (objet, caisse, bombe, mur), mais sont effectives sur la case de l'obstacle.
    Un obstacle peut arrêter plusieurs explosions au même tour.
    Une fois que toutes les explosions sont terminées, les caisses affectées sont comptabilisées. Cela implique que plusieurs joueurs peuvent recevoir des points pour la même caisse.
    Puis, les joueurs réalisent leurs actions, simultanément.
    Les nouveaux objets apparaissent, les caisses et objets détruits dissparaissent.
    Une bombe placée par un joueur apparaît à la fin du tour.

  Note
Votre programme doit d'abord lire les données d'initialisation depuis l'entrée standard, puis, dans une boucle infinie, lire les données contextuelles de la partie et écrire sur la sortie standard les actions.
  Entrées du jeu
Entrées d'initialisation
Ligne 1: 3 entiers, width, height et myId. width et height representant la taille de la grille et seront toujours 13 et 11 respectivement, et sont données par pur commodité. myId est l'id de votre joueur.
Entrées pour un tour de jeu
Les premières height lignes: une chaîne row représentant chaque ligne de la carte. Chaque caractère peut être :

    . une case sol.
    0 une caisse vide.
    Un entier positif : une caisse contenant l'objet représenté par cet entier.
    X un mur.

Ligne suivante: un entier entities pour le nombre d'entités sur la grille.
Les entities lignes suivantes : 6 entiers séparés par des espaces entityType , owner , x , y , param1 & param2 . Représente un objet, un joueur ou une bombe.
Sorties pour un tour de jeu
Une des commandes suivantes:

    MOVE suivi par deux entiers x et y.
    BOMB suivi par deux entiers x et y.


Vous pouvez rajouter du texte à votre sortie, il sera affiché dans le lecteur. e.g. MOVE 1 1 hypersonic.
Contraintes

Temps de réponse par tour ≤ 100 ms
Temps de réponse pour le premier tour ≤ 1000 ms
