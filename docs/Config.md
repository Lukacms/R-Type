# R-Type - Configurations

This project uses several configuration files in order to work, those files are [JSON](https://en.wikipedia.org/wiki/JSON).

## Background

If you want to change the backgrounds that are displayed. You can add those new images in the Background.json file.
Moreover, the new background must be added to the backgrounds.png.
The standard background file looks like this :
```json
{
  "BlueNebula": {
    "textureRect": {
      "x": 0,
      "y": 0,
      "width": 1024,
      "height": 1024
    }
  },
  "GreenNebula": {
    "textureRect": {
      "x": 1024,
      "y": 0,
      "width": 1024,
      "height": 1024
    }
  },
  "Starfield": {
    "textureRect": {
      "x": 0,
      "y": 1024,
      "width": 1024,
      "height": 1024
    }
  },
  "PurpleNebula": {
    "textureRect": {
      "x": 1024,
      "y": 1024,
      "width": 1024,
      "height": 1024
    }
  },
  "DeepPurpleNebula": {
    "textureRect": {
      "x": 0,
      "y": 2048,
      "width": 1024,
      "height": 1024
    }
  }
}
```

## Texture

If you want to add new textures in the game, you must add them in the Texture.json.
The standard one looks like this :
```json
{
  "BasicEnemy" : "./assets/entities/BasicEnemy.png",
  "EnemyBullet" : "./assets/entities/EnemyBullet.png",
  "Explosion" : "./assets/entities/Explosion.png",
  "Kamikaze" : "./assets/entities/KamikazeEnemy.png",
  "PlayerBullet" : "./assets/entities/PlayerShoot.png",
  "Player" : "./assets/entities/Spaceship.png",
  "UFO" : "./assets/entities/UFOEnemy.png",
  "Upgrade" : "./assets/entities/Upgrade.png",
  "Background": "./assets/backgrounds/backgrounds.png",
  "Bomba": "./assets/entities/Bomba.png",
  "BackgroundScreen": "./assets/SpaceBG.png",
  "Logo": "./assets/Rtype-logo2.png",
  "Button": "./assets/button.png",
  "Asteroid": "./assets/entities/Asteroids.png"
}
```

## SFX & BGM

You can also add more SFX or BGM if you want. Such as Texture, there are a similar Json file for SFX and BGM.
For performances and compatibility issues, be sure tu use .ogg files.
### SFX
```json
{
  "Explosion": "./assets/SFX/Explosion.ogg",
  "Shoot": "./assets/SFX/Shoot.ogg"
}
```
### BGM
```json
{
"Voyage1970": "./assets/BGM/Voyage1970.ogg",
"TitleScreen": "./assets/BGM/TitleScreen.ogg",
"BorderOfLife": "./assets/BGM/BorderOfLife.ogg",
"TheLongAwaitedOmagatoki": "./assets/BGM/TheLongAwaitedOmagatoki.ogg"
}
```

## Entities

You can customize all the entities present in the game. If you want to change them or to add more entities.
You have to open the entities.json file. One entity looks like this :
```json
{
  "entities": [
    {
      "tag": "Player",
      "sprite": {
        "texturePath": "Player",
        "textureRect": {
          "x": 0,
          "y": 0,
          "width": 33,
          "height": 15
        },
        "origin": {
          "x": 0,
          "y": 0
        }
      },
      "clock": false,
      "health": {
        "health": 100,
        "maxHealth": 100
      },
      "collider": {
        "width": 33,
        "height": 15
      },
      "transform": {
        "position": {
          "x": 300,
          "y": 400
        },
        "velocity": {
          "x": 0,
          "y": 0
        },
        "scale": {
          "x": 2,
          "y": 2
        },
        "rotation": 0
      }
    }
  ]
}
```

There are several components that an entity can have:

| Component              | Description                                                                                    |
|------------------------|------------------------------------------------------------------------------------------------|
| `TransformComponent`   | Component that describes the position of the entity, its scale, its velocity and its rotation. |
| `TagComponent`         | Component that identify what kind of entity is it.                                             |
| `HeatlhComponent`      | Component that represents the live of an entity.                                               |
| `BoxColliderComponent` | Component that represents the collider of an entity.                                           |
| `ClockComponent`       | Component that contains a clock in order to make actions that requires a timer.                |
| `SpriteComponent`      | Component that represents a sprite with generic values.                                        |
| `AnimationComponent`   | Component that represents a animation with generic values. (Represents frames of an animation) |

Do not hesitate to check how entities are created in the entities.json default file.

## Levels

You can create your own level if you want. As the other configuration files, it must be a Json file, and it must be in the following folder : "./assets/configs/level'.

A level is represented as the following exemple :
```json
{
  "Title": "AsteroidBelt",
  "Music": "TheLongAwaitedOmagatoki",
  "Background": "GreenNebula",
  "Timer": 90000,
  "Waves": [
  ]
}
```

| Key                  | Description                                                                                         |
|----------------------|-----------------------------------------------------------------------------------------------------|
| `Title`              | The name of the level.                                                                              |
| `Music`              | The BGM that plays during the level. (Uses the one declared in the BGM.json file)                   |
| `Background`         | The background that displays during the level. (Uses the one declared in the Backgrounds.json file) |
| `Timer`              | The duration of the level in milliseconds.                                                          |
| `Waves`              | All the waves of enemies that appears in the level.                                                 |

The waves of enemies are presented like this :

```json
{
"Waves" : [
    {
      "Timer": 1000,
      "Enemies": [
        {
          "tag": "BasicEnemy",
          "nb": 3
        },
        {
          "tag": "Asteroid",
          "nb": 1
        }
      ]
    }
  ]
}
```

| Key       | Description                                                               |
|-----------|---------------------------------------------------------------------------|
| `Timer`   | The time after which this wave is create in milliseconds.                 |
| `Enemies` | The list of all enemies that should appear during this wave.              |
| `tag`     | The entity which must appear, the name must be in the entities.json file. |
| `nb`      | The number of enemy which must appear.                                    |
