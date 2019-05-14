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
