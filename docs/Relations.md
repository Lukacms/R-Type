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
    click ThreadPool href "../RType-Utils/include/rtype/utils/ThreadPool.hh"
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

## Client
```mermaid
classDiagram
    class ArgsParser {
        +parse_args(argv) : Infos
    }
    class Client {
        +static int launch(const Arguments &infos);
        +static void send_message(const ntw::Communication &commn, const asio::ip::udp::endpoint &endpoint, asio::ip::udp::socket &socket);
        +void loop();
        -dl::DlLoader<rtype::IGraphicModule> graphics; Graphic part of the GameEngine
        -dl::DlLoader<rtype::IAudioModule> audio; Audio part of the GameEngine
        -scenes::State state; Current state of the client
        -scenes::Menu menu; Scene used in order to display the menu
        -scenes::Lounge lounge; Scene used in order to display the lounge
        -scenes::PauseMenu pause; Scene used in order to display the pause
        -scenes::Game game; Scene used in order to display the game
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
    class Game {
        +void display(rtype::IGraphicModule &graphics);
        +void handle_events(rtype::IGraphicModule &graphics, rtype::IAudioModule &audio, State &state);
        +void handle_network(ntw::Communication &commn, rtype::IAudioModule &audio, State &state);

        +void create_entity(ntw::Communication &commn, State &state);
        +void move_entity(ntw::Communication &commn, State &state);
        +void end_game(ntw::Communication &commn, State &state);
        +void delete_entity(ntw::Communication &commn, State &state);
        +void manage_entity(ntw::Communication &commn, State &state);
        +void change_music(ntw::Communication &commn, rtype::IAudioModule &audio);
        +void change_background(ntw::Communication commn);
        
        -dl::DlLoader<rtype::ECSManager> ecs;
        -rclient::BackgroundManager background_manager;
    }
    click Client href "../Client/include/rtype/Client.hh"
    click ThreadPool href "../RType-Utils/include/rtype/utils/ThreadPool.hh"
    click Game href "../Client/include/rtype/scenes/Game.hh"
    main <-- ArgsParser : get the Arguments and handle errors
    main --> Client
    Client ..> ThreadPool
    Client ..> Game
```

## ECS (Entity Component System)
```mermaid
classDiagram
    class ECSManager {
        +Entity create_entity()
        +Entity create_entity(std::size_t entity)
        +void delete_entity(size_t entity)
        +template <class TComponent> void remove_component(size_t entity)
        +template <class TComponent> SparseArray<TComponent> &get_components()
        +template <class TComponent> TComponent &get_component(size_t entity)
        +std::function<void(ComponentManager &, float)> &add_system(std::function<void(ComponentManager &, float)> &function)
        +void apply_system(float delta_time)
        +bool is_entity_used(std::size_t entity)
        +std::vector<std::size_t> get_used_entity()
        
        -ComponentManager m_component_manager
        -EntityManager m_entity_manager
        -SystemManager m_system_manager
    }
    class EntityManager {
        +size_t create_entity()
        +size_t create_entity(size_t entity)
        +bool is_entity_used(std::size_t entity)
        +void delete_entity(size_t entity)
        +std::vector<std::size_t> get_used_entity()

        -std::vector<std::size_t> m_queue
        -std::vector<std::size_t> m_used
        -std::vector<std::unordered_map<std::string, std::any>> m_entities
    }
    class ComponentManager {

        +template <class TComponent> SparseArray<TComponent>& register_component(SparseArray<TComponent> &array)
        +template <class TComponent> SparseArray<TComponent> &get_components()
        +template <class TComponent> SparseArray<TComponent> const &get_components() const
        +template <class TComponent> void remove_component(size_t entity)
        +void remove_all_component(size_t entity)
        +template <class TComponent> std::type_index get_index() const
        
        -std::unordered_map<std::type_index, std::unique_ptr<ISparseArray>> m_arrays;
    }
    class SystemManager {
        +std::function<void(ComponentManager &, float)> &add_system(std::function<void(ComponentManager &, float)> &function)
        +void update(ComponentManager &registry, float delta_time)

        -std::vector m_systems
    }
    click ECSManager href "../GameEngine/ECS/include/rtype/ECSManager.hh"
    click SystemManager href "../GameEngine/ECS/include/rtype/SystemManager.hh"
    click ComponentManager href "../GameEngine/ECS/include/rtype/ComponentManager.hh"
    click EntityManager href "../GameEngine/ECS/include/rtype/EntityManager.hh"
    ECSManager --> SystemManager
    ECSManager --> ComponentManager
    ECSManager --> EntityManager
```
