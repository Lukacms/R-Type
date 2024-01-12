# R-Type - Architecture
Diagrams to show each one of the projects' architecture, whith their classes, ... 

## Server
```mermaid
classDiagram
    class ArgsParser {
        +parse_args(argv) : Infos
    }
    class Manager {
        +launch(port)
        +start_receive() : to handle commands received asynchronously
        +send_message(communication, player, socket)
        +send_to_all(communication, players, socket)
    }
    class ThreadPool {
        -mutex mutex : protect access to data
        -condition_variable condition : condition for threads to wait until there's a job
        -vector~thread~ threads
        -queue~function~void~~ queue
        -bool should_terminate : the threads will run as long as this is true
        -thread_loop() void
        +add_job(job)
        +stop()
    }
    class GameLogic {
        -vector~size_t~ entities : id of the entities from the ECS
        +game_loop(ecs_manager, players)
        +collision_response(ecs_manager, players)
    }
    class PlayersManager {
        +add_player(endpoint, socket) Player&
        +delete_Player(endpoint)
        -vector~Player~ players
    }
    click Manager href "../Server/include/rtype/Manager.hh"
    click ThreadPool href "../Server/include/rtype/clients/ThreadPool.hh"
    click PlayersManager href "../Server/include/rtype/GameLogic/GameLogic.hh"
    main <-- ArgsParser : get the Arguments and handle errors
    main --> Manager
    Manager ..> GameLogic
    Manager ..> ThreadPool
    Manager ..> PlayersManager
```

## RType-Utils

### DlLoader
```mermaid
classDiagram
    class DlLoader {
        <<Template TLoad>>
        -void *handle : handle that is returned when loading whith dlopen
        -unique_ptr~TLoad~ element : templated class that will be loaded from shared library
        +init_class~TSignature *~(path, loader_func, ...values) init the element variable from path library and entrypoint function
        +get_class() TLoad&
    }
    note for DlLoader "This class is used to load classes from shared libraries, and do actions with them. It manages by itself the destruction of the shared library handler that is created when using `dlopen`, and should be `dlclose` at the end of the class' lifetime"
```

### Network
```mermaid
classDiagram
    class NetworkType {
        <<Enum>>
        +None,
        +Start,
        +Connection,  : client trying to join a server's game
        +Refusal,     : a client cannot join a server's game
        +Ok,          : everything is good
        +End,         : End the game for one player
        +Creation,    : Create a new entity
        +Destruction, : Destruct one entity
        +Input,       : Input recieved from client to move
        +...
    }
    class Communication {
        <<Struct>>
        +NetworkType type : type of command
        +array~char~ args : has a MAX_SIZE
        +add_param(TType type) : templated class to add argument, separated with spaces
        +deserialize() vector~string~ : split args by the DELIMITOR and return a vector
    }
    Communication <.. NetworkType
    note for Communication "Used for the binary protocol. The structure is sent using asio library, and its adress is given. It's read the same way, and we use a `pragma pack` to avoid buffer overflows"
```
