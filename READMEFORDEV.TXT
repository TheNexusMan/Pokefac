///////////////////////////INFOS PROJET\\\\\\\\\\\\\\\\\\\\\\\\\\\
Identifiant sur la forge : 9004

Etudiants :
Arnaud DEBRABANT P1707147
Damien PETITJEAN P1408987
Kelly DE OLIVEIRA P1409927
Elisa SEBELLIN P1709454 


///////////////////////////LANCER LE JEU\\\\\\\\\\\\\\\\\\\\\\\\\\\
Se placer à la racine du dossier pokefac : cd .../pokefac
Compiler le jeu : make
Lancer le jeu : bin/pokefacSdl


///////////////////////////CONTROLES\\\\\\\\\\\\\\\\\\\\\\\\\\\
Flèche haut = haut
Flèche bas = bas
Flèche gauche = gauche
Flèche droite = droite
M = ouvrir/fermer menu
X = quitter le jeu

Dans les menus :
1, 2, 3, 4, 5, 6 = navigation dans les menus
M = revenir au menu précédent

Dans le menu des pokémons du joueur :
O = lancer le mode organisation

En mode organisation du menu pokémons :
Flèche haut = monter la sélection du pokémon (symbolisé par une *)
P = prendre/déposer un pokémon (vous pouvez changer l'ordre du pokémon prit en le déplaçant avec les flèches haut et bas)

Lors d'un combat :
1, 2, 3, 4 = choisir les attaques
5 = fuir le combat


///////////////////////////COMMENT JOUER\\\\\\\\\\\\\\\\\\\\\\\\\\\
Pokémon sauvages / attraper des pokémons :
    En vous plaçant sur une case de haute herbe, vous avez une 1 sur 5 de lancer un combat contre un pokémon tiré aléatoirement.
    Si vous gagnez, le pokémon est ajouter à votre collection seulement si les conditions suivantes son validées :
        - si vous avez assez de place sur vous
        - si vous ne possédez pas déjà ce pokémon
        - si vous avez au moins une pokeball

    ATTENTION les pokémons vaincus et récupérés gardent leur vie à 0, il faudra passer dans un centre de réanimation pokémon
    pour les soignés (croix rouge dans la maison du terrain1)

NPC :
    Si vous vous placez sur une des trois cases en face d'un NPC, un combat sera lancé. En cas de victoire, une somme de
    pokedollar sera ajouté dans votre porte-monnaie.
    Un seul pokémon à combattre par NPC.
    Une fois vaincu, le NPC ne vous embettera plus.

Changer de terrain / entrer dans un bâtiment :
    Vous pouvez changer de terrain ou entrer dans un bâtiment en passant par les portes symbolisées par des flèches.

Menu :
    pokémons
        Vous pouvez voir les pokémons que vous transportez en allant dans la section "Pokémons" du menu. Vous pourrez y
        trouver toutes les informations les concernant.
        Vous pouvez également les organiser différement seulement vos choix pour le lancement des combats.
    
    Sauvegarde
        Sauvegarde toutes les données de votre partie :
            - vos pokémons et leurs état
            - votre nombre de pokéball
            - votre position
            - votre argent
            - les NPC battus

    Charger
        Charge toutes les données sauvegardées

    Quitter le jeu
        Vous pouvez quitter le jeu en sélectionnant cette option.


///////////////////////////ORGANISATION DES FICHIERS TXT\\\\\\\\\\\\\\\\\\\\\\\\\\\
* = un nombre entier utilisé comme id

terrain*.txt :
    Terrain de 20 x 20 caractères
    # = arbres
    H = hautes herbes
    N = NPC
    O = porte
    R = chemin

Maison*.txt
    Maison de 5 x 7 caractères
    * = mur
    N = NPC
    O = porte
    V = vie, regènère la vie des pokémons

pokemons.txt
    Id
    Nom
    Type
    Trouvé 1/0
    Niveau
    Vie
    Vie maximum
    Stat d'attaque
    Stat de défence
    Image
    nom attaque 1 | points de dommage
    nom attaque 2 | points de dommage
    nom attaque 3 | points de dommage
    nom attaque 4 | points de dommage

NPCs.txt
    Id
    Nom
    Position X
    Position Y
    Orientation (n = Nord, s = Sud, e = Est, o = Ouest)
    Terrain
    Image
    Id du pokémon
    Nombre de dialogue
    Dialogue 1
    Dialogue 2
    .
    .
    .
    Dialogue nbDialog

doors.txt
    Position X
    Position Y
    Position de destination X
    Position de destination Y
    Orientation
    Nom du terrain de départ
    Nom du terrain d'arrivé


///////////////////////////ORGANISATION DES DOSSIERS\\\\\\\\\\\\\\\\\\\\\\\\\\\
bin = Exécutables généré par la compilation
data = fichiers txt et dossiers des polices, musiques, images, ...
    font = police de caractères
    logs = logs
    music = musiques et sons
    NPC = textures NPC
    pokemon = texture pokémons
    saveGames = dossier de sauvegarde (existe seulement après une sauvegarde)
    textures = texture du terrain
doc = Documentation (Doxygen)
obj = Fichiers objets .o générés par la compilation
src = Fichiers sources .cpp et .h


///////////////////////////MAKEFILE\\\\\\\\\\\\\\\\\\\\\\\\\\\
Commande du makefile :
    make : Compiler
    make clean : Effacer les fichiers objets .o et les exécutables


///////////////////////////GIT\\\\\\\\\\\\\\\\\\\\\\\\\\\
Pour arreter d'entrer son identifiant et mot de passe à chaque connection au serveur (git pull et git push) :
    Redemande les identifiants et mot de passe toutes les heures = git config credential.helper 'cache --timeout=3600'
    Ne plus jamais demander les identifiants et mot de passe = git config credential.helper store

Fichier .gitignore :
    Y sont écrit les nom des fichiers / dossiers que git doit ignorer (par exemple .vscode)

Branches principales :
    master = branche de livraison / démonstration (code TOUJOURS fonctionnel)
    develop = branche de developpement principale (c'est ici qu'on crée les branches sur les lesquelles on travaille)

COMMANDES GIT :
1-Récupérer le code depuis le serveur (pull) :
    Se placer sur la branche où on veut récupérer le code (exemple avec develop) = git checkout develop
    Télécharger le code depuis le serveur = git pull

2-Créer une branche :
    Se placer sur la branche develop = git checkout develop
    Créer la branche = git branch nom-de-branche
    Se placer sur la nouvelle branche = git checkout nom-de-branche
    Pousser la branche sur le serveur = git push --set-upstream origin nom-de-branche

3-Commiter et pousser des modifications (sauvegarder) :
    Ajouter les fichiers modifiés = git add *
    Commiter = git commit -m "Message d'explication des modifications"
    git push

4-Fusion / merge d'une branche avec une autre :
    AVANT DE MERGER : comparer les deux branches à merger sur l'outil de comparaison de gitlab (Dépôt/Comparer) pour
    réparer d'éventuels conflits
    Se placer sur la branche reçevant la fusion (exemple ici avec develop) = git checkout develop
    git merge nom-de-branche

4bis-EN CAS DE CONFLIT LORS D'UNE FUSION / MERGE :
    Les fichiers comportant des conflits ont été modifiés aux endroits avec les erreurs, il suffit de supprimer ce que l'on ne veut
    pas garder et de sauvegarder. Une fois toutes les erreurs corriger, commiter et pousser les changements.

5-Supprimer une branche devenue inutile (les deux commandes sont nécessaires) :
    Supprimer en local = git branch -d nom-de-branche
    Supprimer sur le serveur = git push --delete origin nom-de-branche