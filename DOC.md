# Fluffy-willa-42-team cube3d doc

## cube3d argument

Cube3d need only one argument, the map file path.
The argument must contain only the path, if the string contains white space before or after cube3d will return an error

------

## cub format

The cub format have two part, first the texture definition and then the map.

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
   11111111
   10000001
11110000N011111
100000000000001
111111111111111
```

**The texture format:**

- `[token]` `./[relative_path_to_texture_file]`
- `[token]` `[R,G,B]`

For the `cub` format only these token is allowed:

`{"NO", "SO", "WE", "EA"}` is the texture image for each face of a wall (North, South, East, West).

`{"F", "C"}` is the texture color for the ceiling and the floor.

> They must be defined once each and only once !

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
```

The texture path can only be a relative path that start with `./` without space inside !

The texture color use the `RGB` format `R,G,B`, three positive integer `(x>0 && x<256)` separate by comma.

> The parser try to find all the mandatory texture. If there is duplicate texture token it will retrun an error.
> Once he find all texture it will considered the next line as the map.

**The map format:**

The map can only be compose with these character `{'1', '0', 'N', 'S', 'E', 'W'}`

`{'1', '0'}` `'1'` represent the wall and `'0'` the empty space.
> The map must be closed by walls.

`{'N', 'S', 'E', 'W'}` is use to place the player position on the map and his view direction (North, South, East, West).
> It must have only one player, no more, no less.

------

## cube format

The cube format have two part, first the texture definition and then the map.

**The texture format**

- `[token]` `./[relative_path_to_texture_file]`
- `[token]` `./[relative_path_to/enemy_folder]`
- `[token]` `[R,G,B]`

**Cube sequence string**

There is two sequence:
- `~`   Is use to create a comment line in the texture definition part.
- `~~~` Is use to separate the texture definition and map part.

> The sequence must be used only at the beginning of a new line.
> If there is another character before the sequence in the line it is an undefined behavior.

**Reserved texture token**

There is some reserved `token` :
- `'.'` to set empty texture {`NORTH`, `SOUTH`, `WEST`, `EAST`, `TOP`, `BOTTOM`} or empty texture and settings for entity's and collectible {`ENITY`, `TEX`, `OPT`}. **This token can not be use to define a texture !**
-  `'*'` is for the sky box texture or color. **It can only be use for face texture.**

```
~ North face texture
N ./path_to_the_north_texture

~ South face texture
S ./path_to_the_south_texture

~ West face texture
W ./path_to_the_west_texture

~ East face texture
E ./path_to_the_east_texture

~ Ceiling face texture
C 220,100,0

~ Floor face texture
F 225,30,0

~ Skybox face texture
* ./path_to_the_skybox_texture

~ The end of the texture definition part
~~~
```

> A texture token must be defined only once !

**The chunk format**

A chunk store the texture of each face, player or entity data. So, one chunk is a 3x3 character set.

`TOP`, `BOTTOM` is the ceiling and floor color or texture use for the top and bottom face of our chunk.

`NORTH`, `WEST`, `EAST`, `SOUTH` will be the texture of each chunk face.

`ENTITY`, `TEX`, `OPT` will store player info or other entity.

```
   TOP    | NORTH | ENTITY
   -------0-------0-------
   WEST   | EAST  | TEX
   -------0-------0-------
   BOTTOM | SOUTH | OPT
```



```
~ North face texture
N ./path_to_the_north_texture

~ South face texture
S ./path_to_the_south_texture

~ West face texture
W ./path_to_the_west_texture

~ East face texture
E ./path_to_the_east_texture

~ Ceiling face texture
C 220,100,0

~ Floor face texture
F 225,30,0

~ Skybox face texture
* ./path_to_the_skybox_texture

~ The end of the texture definition part
~~~
         FN.FN.FN.FN.FN.FN.FN.FN.
         WE.WE.WE.WE.WE.WE.WE.WE.
         CS.CS.CS.CS.CS.CS.CS.CS.
         FN.F..F..F..F..F..F..FN.
         WE...................WE.
         CS.C..C..C..C..C..C..CS.
FN.FN.FN.FN.F..F..F..F..F.PF..FN.FN.FN.FN.FN.
WE.WE.WE.WE...................WE.WE.WE.WE.WE.
CS.CS.CS.CS.C..C..C..C..C.NC..CS.CS.CS.CS.CS.
FN.*..*..*..*..*..*..*..*..*..*..*..*..*..FN.
WE........................................WE.
CS.*..*..*..*..*..*..*..*..*..*..*..*..*..CS.
FN.FN.FN.FN.FN.FN.FN.FN.FN.FN.FN.FN.FN.FN.FN.
WE.WE.WE.WE.WE.WE.WE.WE.WE.WE.WE.WE.WE.WE.WE.
CS.CS.CS.CS.CS.CS.CS.CS.CS.CS.CS.CS.CS.CS.CS.
```

## mob file structure
//TODO WIP
```
.
└── mob
    ├── mob1
    │   ├── death.xml
    │   ├── hit.xml
    │   ├── walk1.xml
    │   ├── walk2.xml
    │   ├── walk3.xml
    │   └── walk4.xml
    └── mob2
        ├── death.xml
        ├── hit.xml
        ├── walk1.xml
        ├── walk2.xml
        ├── walk3.xml
        └── walk4.xml
```