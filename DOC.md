# Fluffy-willa-42-team cube3d doc

## cube3d argument

Cube3d need only one argument, the map file path.
The argument must contain only the path, if the string contains white space before or after cube3d will return an error

## cub format

cub format have two part, first the texture definition and then the map.

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

`[token] ./[relative_path_to_texture_file]`

or

`[token] [R,G,B]`

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

## cube format

//TODO
text  
esc char: sep & comm  
map: chunk

```
0 ./path_to_the_north_texture
1 ./path_to_the_south_texture
2 ./path_to_the_west_texture
3 ./path_to_the_east_texture
4 220,100,0
5 225,30,0
~~~
         50.50.50.50.50.50.50.50.
         23.23.23.23.23.23.23.23.
         41.41.41.41.41.41.41.41.
         50.5..5..5..5..5..5..50.
         23...................23.
         41.4..4..4..4..4..4..41.
50.50.50.50.5..5..5..5..5.P5..50.50.50.50.50.
23.23.23.23...................23.23.23.23.23.
41.41.41.41.4..4..4..4..4.N4..41.41.41.41.41.
50.5..5..5..5..5..5..5..5..5..5..5..5..5..50.
23........................................23.
41.4..4..4..4..4..4..4..4..4..4..4..4..4..41.
50.50.50.50.50.50.50.50.50.50.50.50.50.50.50.
23.23.23.23.23.23.23.23.23.23.23.23.23.23.23.
41.41.41.41.41.41.41.41.41.41.41.41.41.41.41.
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