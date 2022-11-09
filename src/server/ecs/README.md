
# ECS - Game engine

The game engine is the core of the game. It aims to apply the logic of the game,
update the sprites, apply the damages... run the game !

## General architecture

Our ECS is composed of three main parts :
- Entity management
- Component management
- System management

We're going to explain them in the upcoming chapters.

## I - Entity management

### The Entity
An `Entity` is an object, composed of a `std::size_t _id` and
a list of components (`std::list<std::shared_ptr<IComponent>>`). An Entity is
a game object (example: the player sprite). Every game object is an Entity : a
player, an enemy, the background, a music...

Here is the prototype for an Entity :
```c
class Entity {
    public:

    // constructor with id (0 by default)
    Entity(std::size_t id = 0);

    // returns the Entity's id
    std::size_t getId(void);

    // set Entity's ID
    void setId(std::size_t id);

    // Used to check whether Entity has a specific component
    // (see constants for an exhaustive list of comp names)
    bool has(std::string name);

    // Add component to entity
    void addComponent(int cmp);
    void addComponent(std::string name);

    // Remove Component from Entity
    void removeComponent(int cmp);
    void removeComponent(std::string name);

    // Returns the first component that refers to the given name
    // (nullptr if none)
    std::shared_ptr<IComponent> getComponent(std::string name);
    std::shared_ptr<IComponent> getComponent(const int c);

    // destructor
    ~Entity(void);

    private:

    // Entity's id
    std::size_t _id;

    // Entity's list of components
    std::list<std::shared_ptr<IComponent>> _comps;
}

// Components list for string identification
const std::unordered_map<std::string, std::function<std::shared_ptr<IComponent>(void)>> strToCmps = {
    { "drawable", [&](void) { return std::make_shared<Drawable>(); } },
    { "health", [&](void) { return std::make_shared<Health>(); } },
    { "velocity", [&](void) { return std::make_shared<Velocity>(); } },
    { "position", [&](void) { return std::make_shared<Position>(); } },
    { "repeatable", [&](void) { return std::make_shared<Repeatable>(); } },
    { "movable", [&](void) { return std::make_shared<Movable>(); } },
    { "sound", [&](void){ return std::make_shared<Sound>(); } }
};

// Components list for int identification
const std::unordered_map<int, std::function<std::shared_ptr<IComponent>(void)>> intToCmps = {
    { DRAWABLE, [&](void) { return std::make_shared<Drawable>(); } },
    { HEALTH, [&](void) { return std::make_shared<Health>(); } },
    { VELOCITY, [&](void) { return std::make_shared<Velocity>(); } },
    { POSITION, [&](void) { return std::make_shared<Position>(); } },
    { REPEATABLE, [&](void) { return std::make_shared<Repeatable>(); } },
    { MOVABLE, [&](void) { return std::make_shared<Movable>(); } },
    { SOUND, [&](void) { return std::make_shared<Sound>(); } }
};

// Comparison operators
bool operator==(Entity &ent1, Entity &ent2);
bool operator!=(Entity &ent1, Entity &ent2);
bool operator< (Entity &ent1, Entity &ent2);
bool operator> (Entity &ent1, Entity &ent2);
bool operator<=(Entity &ent1, Entity &ent2);
bool operator>=(Entity &ent1, Entity &ent2);
```

### The Factory

Entities are managed thanks to a `Factory`, which contains a list of
entities (`std::list<std::shared_ptr<Entity>>`) with all the entities
of the game. The Factory has methods that allow us to create or delete
Entities from this list, so
we can do it programmatically.

Here is a prototype of the Factory class :
```c
class Factory {
    public:

    // Constructor
    Factory(void);

    // Entity creation
    std::shared_ptr<Entity> createEntity(std::string name)

    // Destructor
    ~Factory(void);

    protected:

    // List of entities that are currently loaded in the game
    std::list<std::shared_ptr<Entity>> _entities; // a deplacer dans une classe plus générale
}
```

A template is a premade Entity you can configure creating a
file named `NAMEOFYOURENTITY.ent` in the directory `./Entities`.

## II - Components

### The Interface

In the code you will find the `IComponent` interface. Here is
its prototype :

```c
class IComponent {
    public:
    virtual ~IComponent() = default;
    virtual std::string getName(void) = 0;
    virtual int getEnum(void) = 0;
}
```

It is used as an interface the component abstract class will inherit from.

### Abstract class

But components do not inherit directly from the `IComponent` interface.
They inherit from an abstract class called `AComponent` which defines
the constructor :

```c
class AComponent: public IComponent {
    public:
    AComponent() = default;
    ~AComponent() = default;
}
```

### Components

Components inherit from `AComponent`, which inherits from `IComponent`.
They must define at least those three methods :

```c
class MyComponent: public AComponent {
    public:

    // the constructor
    MyComponent() {  }

    // returns as a string the name of the component
    std::string getName(void) { return "mycomponent"; }

    // the destructor
    ~MyComponent() {  }

    private:
    // stock here whatever you need to run your program
}
```

The naming convention for the getName method is only the
component name lowercase.

### Adding custom components

To add a new component in the game engine, just create another file
in the `src/server/ecs/Components` directory.

Create a `.hpp` file, with a class that inherits from `AComponent`.
Fill the required method (constructor, `getName` and destructor. See
the previous part for precisions) and add your own.
Then, use it as a standard component : bind it to an entity and create
an associated system !

## III - Systems

Systems are the core of your logic : they will be called at frame in
order to refresh your game. Systems aim to update a specific element of
the game (example: particles, drawing sprites, applying gravity...).
You can create your own systems to apply some components you added.

First, we did not include a gravity system, for example. If you need one,
feel free to add it on your own.

### The interface

The System interface aims to define the global methods of a system class.
Here is its prototype:
```c
class ISystem {
    public:

    // destructor
    virtual ~ISystem() = default;

    // add your logic in this method
    virtual void run(std::list<std::shared_ptr<Entity>> &) = 0;
}
```

### The asbtract class

The abstract class store a list of entities that run in your game.
Actually, they are a reference to the one in `Factory`.

```c
class Asystem: public ISystem {
    public:

    // in its constructor, ASystem takes your list of entities as a parameter
    Asystem(void);

    // will be defined in your system file
    void run(std::list<std::shared_ptr<Entity>> &ent) = 0;

    private:

    // a reference to the list of entities you sent in the constructor
    std::list<std::shared_ptr<Entity>> &_entities;
}
```

### Your systems

In order to add your custom systems, just create a `.hpp` file to the
`src/server/ecs/Systems` directory and make a class that inherits from
ASystem :

```c
class MySystem: public ASystem {
    public:

    // constructor
    MySystem(std::list<std::shared_ptr<Entity>> &ent): _entities(ent) {  };

    // your logic comes here
    void run(void) {
        updateWhateverYouWant();
    }

    // destructor
    ~MySystem() {  };
}
```

Then, add your system in the system list in `src/server/main.cpp`, where
you can find the main game loop :

```c
int main(int ac, char **av) {
    std::cout << "____ Server started ____" << std::endl;

    try {
        boost::asio::io_context io_context;
        Server server(io_context);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
```

# Special thanks

Thank you for reading ! Do not hesitate to get inspiration from this
ECS if you struggle with this notion !
