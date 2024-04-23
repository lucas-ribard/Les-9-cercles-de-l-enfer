# Les 9 cercles de l’enfer
Ce projet est composé de neuf étapes ( définit comme un cercle de l'enfers )
### L’ante-enfer
>*“Dante franchit la porte de l'Enfer, qui porte une inscription se terminant par
la phrase « Lasciate ogne speranza, voi ch'intrate », traduite le plus souvent
par « Abandonnez tout espoir, vous qui entrez ici."*

__Le projet devra respecter les regles suivantes:__
- Toutes les classes doivent respecter la forme [canonique de Coplien](https://cpp.developpez.com/cours/cppavance/)
- Ne pas utiliser un pointeur quand une référence peut faire l’affaire
- Les variables doivent être __const__, sauf si il est justifié qu’elles ne le soient pas
- Les fonctions et méthodes doivent être codées en __25 lignes ou moins__
- Les lignes de code ne doivent pas dépasser 80 colonnes
- L’utilisation de variables globales est à proscrire
- Les attributs doivent être __private__. Des getter/setter doivent être mis en place
- Utiliser les smart pointers

---
### Premier cercle : Les limbes
>*“Là où sont renfermées, sans autre
tourment qu'une sourde langueur, qu'un
désir de bonheur sans espérance, les âmes
de tous ceux qui n'ont pas connu la
bénédiction du C++”*

Après avoir franchi la porte des enfers, prêt à débuter le voyage, la première tâche consiste à forger et appréhender des outils de communication.  
Pour cela, il s’agira de développer deux programmes console capables de communiquer ensemble via le réseau: un client et un serveur.

Ces programmes devront être construits en s’appuyant sur une __class
LPTF_Socket__, encapsulant les différents __Syscall__ [[ W ]](https://learn.microsoft.com/fr-fr/windows/win32/api/winsock2/) [[ L ]](https://manpages.ubuntu.com/manpages/xenial/fr/man2/syscalls.2.html)
nécessaires aux échanges en réseau tels que connect, accept, bind, listen, select, read / recv, write / send ...

__Aucun syscall réseau ne doit être présent en dehors de la class LPTF_Socket.__
Les programmes ne doivent utiliser ni Thread, ni Fork (car Fork crée des threads ...).

Le cercle est considéré comme franchi lorsque le serveur est capable
d'échanger simultanément avec plusieurs clients.  

---
### Deuxième cercle : Luxure
>*“Le sort des âmes damnées dans ce cercle est d'être balayées par des vents sans relâche. Alors que les développeurs dérivaient vers l'autosatisfaction et se laissaient emporter par leurs passions, maintenant ils dérivent pour toujours.”*

Le deuxième cercle est un cercle de conception mutuelle. Avec un autre
groupe (ou plus), concevez un protocole de communication binaire. Ce
protocole doit être évolutif et prendre en compte les besoins de l’ensemble
du voyage à travers les 9 cercles.

En tant que protocole binaire, votre protocole doit être composé d’une ou
plusieurs __class/struct__ combinée. Une class LPTF_Packet doit permettre de stocker et extraire des informations en suite ou en vue d'un transfert réseau.

Ce protocole doit être nommé et rédigé à la façon d’une [RFC](https://fr.wikipedia.org/wiki/Request_for_comments) (voir RFC 959 ou
1149)

---
### Troisième cercle : Gourmandise
>*“Arrivée au troisième cercle, où sont punis les gourmands. Le
monstre Cerbère est commis à leur garde: il les assourdit de
ses aboiements, les harcèle et les mord. En même temps sur
les ombres pécheresses tombe une pluie éternelle mêlée de grêle et de neige.”*

Les choses sérieuses commencent. Les programmes clients et serveurs
évoluent en logiciels curieux et avides. Le programme client doit désormais être capable, à la demande du serveur de:
- Retourner des informations sur l’ordinateur hôte, telles que son __nom__, le __nom du user__ et son __OS__ (Windows, Linux, Autres)
- Démarrer ou stopper la captation de toutes les touches tapées par
l’utilisateur, y compris lorsque le programme n’est pas en focus (voir KeyLogger) et de les lui renvoyer
- Retourner la liste des processus en cours d'exécution
- D’exécuter une commande système sur l’ordinateur hôte (ls, dir, kill ...) et d’en retourner le résultat

Les prototypages de ces différents types de demandes et leurs réponses doivent être décrits par le protocole du cercle de la luxure.

---
### Quatrième cercle : Avarice
>*“L'enceinte est occupée, moitié par les avares, moitié par les prodigues. Ils poussent devant eux d'énormes poids de tout l'effort de leur poitrine, courant à la rencontre des uns des autres, s'entre heurtant et se reprochant le vice contraire qui les sépare.”*

Par vanité, plus que par réelle nécessité fonctionnelle, le programme serveur doit faire peau neuve et se voir développer une GUI avec [Qt](https://doc.qt.io/),  [(que l’on prononce cute et non pas cuty ...)](https://forum.qt.io/topic/132893/qt-pronunciation)

La GUI doit afficher une liste des clients connectés. Pour chacun, il doit être possible d'exécuter les requêtes prévues lors de la traversée du __troisième cercle__, d’en recevoir et d’en afficher les réponses. Il doit en plus être possible de voir l’adresse IP de chaque client ainsi que de le déconnecter du serveur.

---
### Cinquième cercle : Colère
>*“Cercle du Styx, dans les eaux boueuses duquel sont punis les colériques et les paresseux. Les colériques, tout nus dans le
marais fétide, luttent ensemble et s'entre-déchirent. Les paresseux, plongés dans la vase, soupirent une plainte étouffée.”*

Réagir à chaud, sous l’impulsion de la colère, est rarement sage. Il en va de même pour le traitement de l’information.

Le programme serveur doit offrir la possibilité d’afficher directement les réponses arrivant des clients (retours de commandes, flux de keylogging) dans la GUI et / ou de les enregistrer dans une base de données SQL. 

Plusieurs options sont possibles pour votre base de données telles que Lamp, Wamp ainsi que pour la partie C++ avec QtSQL ou MySQL Connector.
Les calls à la base de données, ainsi que la construction des requêtes doivent être fait depuis une class LPTF_Database. Lors du lancement, la GUI du serveur charge les informations de la base de données et les rend accessibles à l'utilisateur avec une
distinction graphique entre les clients online et offline.

---
### Sixième cercle : Hérésie
>*“C'est le séjour où sont punis les incrédules, plongés dans des tombeaux
brûlants. Ces pêcheurs conscients de leur péché sont enterrés et brûlés dans
un brasier sans fin.”*


Une fois passée la jubilation cynique de pouvoir accéder à des informations “interdites”, pourquoi ne pas continuer en joignant l’utile à l'agréable ...

Créer un widget dans la GUI du serveur qui permet de lancer une analyse dans les données provenant des différents clients afin d’en extraire:
- Numéros de téléphone
- Adresses email
- Potentiels Mots de passe
- Numéros de cartes bancaires

Les différentes méthodes d’analyse doivent être implémentées dans une class __LPTF_Analysis__, encapsulant les call aux différents outils à votre
disposition.

---
### Septième cercle : Violence
>*“Ce cercle est divisé en trois girons.
Le premier punis les utilisateurs de
Windows, ils sont ébouillantés dans
un fleuve de sang en ébullition.
Dans le second se tiennent les
utilisateurs de Linux transformés en
arbustes secs, éternellement
déchirés par les Harpies. Enfin le
troisième et dernier giron, est une
lande brûlante où une pluie de
flamme tombe sur les utilisateurs
de Mac ....”*

Qu’est-ce que la douleur physique face au bonheur de l’esprit ?
Votre programme client fonctionne uniquement sur l’OS de votre hôte. Afin de le rendre puissant et divin, il est maintenant temps de le rendre universel.
 
Pour cela, il doit être exécutable sur Windows et Linux.
Chacune de vos classes qui encapsule des fonctions système doit hériter d’une interface. Il sera nécessaire de créer une classe par OS. Lors de la compilation de votre programme, les instructions données au préprocesseur devront lui permettre de transformer le code source en un langage compréhensible par la machine qui le lit.

---
### Huitième cercle : Ruse et tromperie
>*“Appelé Malebolge où sont punis les fourbes, il est divisé
en dix bolges, chacune est un fossé circulaire. Les
cercles sont concentriques, creusés dans la roche et descendant en terrasses vers le bas. Dans les bolges sont punis les ruffians et séducteurs, adulateurs et flatteurs, fraudeurs et simoniaques, devins et ensorceleurs, concussionnaires, hypocrites, voleurs,
conseillers fourbes...”*

Afin que votre programme client reste le plus discret possible :
- Cacher la console du programme client
- Intégrer son code compilé dans un programme wrapper
- Installer votre client dans un endroit discret du file system de l'hôte
- Bonus: Faites que le wrapper ajoute votre client à la startup list de l'hôte
- Faites également en sorte qu’en cas de coupure avec le serveur, le
client essaie de s’y connecter régulièrement.

---
### Neuvième cercle : Trahison
>*“Ici sont punis les fourbes qui divisent les hommes :
hérésiarques, faux prophètes, fauteurs de scandales et de discordes.
Leur châtiment est analogue à leur crime. Leurs membres, coupés et
divisés à coups de glaive, pendent plus ou moins mutilés, plus ou moins séparés de leur corps, selon qu'ils ont excité de plus ou moins graves divisions sur la Terre.“*

Une fois que le mal est fait, il ne reste plus qu’à le répandre dans les abîmes, et tout recommencer.

Tout en respectant les livres sacrés et la confidentialité, propager votre programme auprès des êtres les plus distraits et négligents ... mais juste pour
tester *;)*