///////////////////////////LANCER LE JEU\\\\\\\\\\\\\\\\\\\\\\\\\\\
Se placer à la racine du dossier pokefac : cd .../pokefac
Compiler le jeu : make
Lancer le jeu : bin/pokefac


///////////////////////////CONTROLES\\\\\\\\\\\\\\\\\\\\\\\\\\\
Z = haut
S = bas
Q = gauche
D = droite
M = ouvrir/fermer menu
X = quitter le jeu


///////////////////////////COMMENT JOUER\\\\\\\\\\\\\\\\\\\\\\\\\\\
Pokémon sauvages / attraper des pokémons :
    En vous plaçant sur une case de haute herbe, vous avez une 1 sur 5 de lancer un combat contre un pokémon tiré aléatoirement.
    Si vous gagnez, le pokémon est ajouter à votre collection : sur vous si vous avez assez de place, /En cours de développement/ sinon il sera rangé sur
    le PC.
    ATTENTION les pokémons vaincus et récupérés gardent leur vie à 0, il faudra passer dans un centre de réanimation pokémon
    pour les soignés.

NPC :
    /En cours de développement/ Si vous vous placez sur une des trois cases en face d'un NPC, un combat sera lancé. En cas de victoire, une somme de
    pokedollar sera ajouté dans votre porte-monnaie.
    Un seul pokémon à combattre par NPC.

Changer de terrain / entrer dans un bâtiment :
    Vous pouvez changer de terrain ou entrer dans un bâtiment en passant par les portes.

Menu :
    pokémons
        Vous pouvez voir les pokémons que vous transporté en allant dans la section "Pokémons" du menus. Vous pourrez y
        trouver toutes les informations les concernant.
        Vous pouvez également les organiser différement seulement vos choix pour le lancement des combats.
    
    Sauvegarde
        /En cours de développement/

    Quitter le jeu
        Vous pouvez quitter le jeu en sélectionnant cette option.


///////////////////////////ORGANISATION DES FICHIERS TXT\\\\\\\\\\\\\\\\\\\\\\\\\\\
* = un nombre entier utilisé comme id

terrain*.txt :
    Terrain de 20 x 20 caractères
    # = mur
    H = hautes herbes
    N = NPC
    O = porte

Maison*.txt
    Maison de 20 x 20 caractères
    # = mur
    N = NPC
    O = porte

pokemons.txt
    Id
    Nom
    Type
    Trouvé 1/0
    Niveau
    Vie
    Vie maximum
    Stat d'attaque
    Stat de deffence
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
    Nombre de dialogue
    Id du pokémon
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
    Nom du terrain de départ
    Nom du terrain d'arrivé


///////////////////////////ORGANISATION DES DOSSIERS\\\\\\\\\\\\\\\\\\\\\\\\\\\
bin = Exécutable généra par la compilation
data = Données diverses (fichiers txt, images, ...)
doc = Documentation (Doxygen)
extern = Librairie externe (SDL2)
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
