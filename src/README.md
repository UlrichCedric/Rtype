# NETWORK R-TYPE [DOCUMENTATION]

<a href="https://img.shields.io/badge/MADE%20WITH-BOOST::ASIO-brightgreen" alt="BOOST::ASIO">
    <img src="https://img.shields.io/badge/MADE%20WITH-BOOST::ASIO-brightgreen" /></a>

## Serveur

① Le serveur est créé et envoie des données sur l'endpoint initialisée

```
handleTimer

• Fonction qui fait office de boucle principale du serveur.
• Elle est appelée en boucle rythmée par une clock.
• handleTimer appelle handleTimer toutes les X millisecondes
```

```
Inside handleTimer

La fonction sendSprites est appelée
```

```
sendSprites

Envoie la liste des SpriteData au client
```

```c
typedef struct SpriteData {
    std::pair<float, float> coords;
    std::size_t id;
} SpriteData;
```

## Client

➁ Un client est créé et envoie des données sur le serveur

```
    Lorsqu'un client est créé, il crée avec lui un uuid.
```

```
    Lorsque le joueur intéragit avec le jeu, l'input est envoyé au serveur avec son uuid
    (il envoie une Action)
```

```c
typedef struct Action {
    enum Input input;
    boost::uuids::uuid uuid;
} Action;
```

```c
enum Input {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    NONE
};
```

```
    Côté serveur, la fonction startReceive permet de recevoir de la data en continu
    en asynchrone grâce à la fonction async_receive_from.
    Cette fonction rappelle startReceive lorsqu'elle reçoit une donnée.
    Ce qui permet donc au serveur d'être prêt à recevoir de la donnée en continu.
```

```
    startRecieve()
    {
        async_receive_from(data, handleReceive);
    }

    handleReceive()
    {
        /* gère la data reçue */
        startReceive();
    }
```

❸ Mise à jour coordonnées sprite du player OU nouveau client

```
    Si l'uuid reçu est inconnu du serveur, des coordonnées pour son sprite ainsi qu'un id lui
    sont attribués, son endpoint et son uuid sont stockées.
```

```c
typedef struct Player {
    boost::asio::ip::udp::endpoint endpoint;
    boost::uuids::uuid uuid;
    std::size_t idSprite;
} Player;
```

```
    Si l'uuid est déjà connu, les coordonnées du sprite du player sont mis à jour.
    Ils seront envoyés automatiquement dans la fonction sendSprites de la boucle handleTimer.
```

```c
    std::vector<SpriteData> _sprites;
```

```c
RAPPEL:

typedef struct SpriteData {
    std::pair<float, float> coords;
    std::size_t id;
} SpriteData;
```
