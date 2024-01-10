# R-Type - Tests

The project is tested using [googletests](https://github.com/google/googletest).

## Build
To build the test, you can use the command `just tests`, the binaries will be in the folder `tests`:
```
tests/
├── tests-r-type_client
├── tests-r-type_server
└── tests-r-type-utils
```
Each part has its own test binary.

## Contribute to the tests
If you cant to contribute to the tests, one can look like that:
```cpp
TEST(ServerEntityFactory, constructor_without_register)
{
    dl::DlLoader<rtype::ECSManager> ecs{};

    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("./libs/r-type-ecs.so");
    EXPECT_THROW(rserver::ServerEntityFactory::create("Enemy", ecs.get_class()), std::out_of_range);
    EXPECT_THROW(rserver::ServerEntityFactory::create("Player", ecs.get_class()),
                 std::out_of_range);
    EXPECT_THROW(rserver::ServerEntityFactory::create("OtherPlayer", ecs.get_class()),
                 std::out_of_range);
    EXPECT_THROW(rserver::ServerEntityFactory::create("PlayerBullet", ecs.get_class()),
                 std::out_of_range);
}
```
You create a `TEST` with a category and a test name.

There are multiple assertions, such as:
* EXPECT_EQ(1, 2): expressions 1 and 2 are equal
* EXPECT_THROW(1, 2): expect 1 to throw exception 2
* EXPECT_NO_THROW(1): 1 won't throw an exception
* EXPECT_STREQ(1, 2): expect two strings to be equal
* EXPECT_GE(1, 2): expression 1 must be greater or equal than 2
* EXPECT_LE(1, 2): expression 1 must be lower or equal than 2
* ...
The complete list is on [googletests](https://github.com/google/googletest) github's documentation.
