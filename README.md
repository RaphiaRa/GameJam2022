# Hasi GameJam2022

Theme: Maskerade

<img width="341" alt="grafik" src="https://user-images.githubusercontent.com/20173981/198884660-6ef6d4f0-9052-4ff0-9881-ebd116040835.png">

# Build instruction
## Prerequisites:
``` sh
sdl2
sdl2_image
````

``` sh
git clone git@github.com:RaphiaRa/GameJam2022.git
git submodule update --init
mkdir build
cd build
cmake ../ -DDISABLE_TESTS=YES
```
# Run the game
``` sh
./Game --assets ../assets/
```

# Controls
``` sh
Movement: w,a,s,d
Attack: q
```
