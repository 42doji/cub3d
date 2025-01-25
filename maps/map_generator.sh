#!/bin/bash

MAP_FILES=("basic_map.cub" "large_open_map.cub" "maze_map.cub" "complex_map.cub" "enclosed_space_map.cub" "invalid_no_texture.cub" "invalid_open_map.cub" "invalid_color_format.cub")

TEXTURE_DIR="./textures"
mkdir -p "$TEXTURE_DIR"
touch "$TEXTURE_DIR/north_texture.xpm"
touch "$TEXTURE_DIR/south_texture.xpm"
touch "$TEXTURE_DIR/west_texture.xpm"
touch "$TEXTURE_DIR/east_texture.xpm"

cat << EOF > basic_map.cub
NO $TEXTURE_DIR/north_texture.xpm
SO $TEXTURE_DIR/south_texture.xpm
WE $TEXTURE_DIR/west_texture.xpm
EA $TEXTURE_DIR/east_texture.xpm

F 220,100,0
C 135,206,250

111111
100001
1010N1
100001
111111
EOF

echo "basic_map.cub 생성 완료"

cat << EOF > large_open_map.cub
NO $TEXTURE_DIR/north_texture.xpm
SO $TEXTURE_DIR/south_texture.xpm
WE $TEXTURE_DIR/west_texture.xpm
EA $TEXTURE_DIR/east_texture.xpm

F 150,150,150
C 200,200,200

111111111111
100000000001
100000000001
10000N000001
100000000001
100000000001
111111111111
EOF

echo "large_open_map.cub 생성 완료"

cat << EOF > maze_map.cub
NO $TEXTURE_DIR/north_texture.xpm
SO $TEXTURE_DIR/south_texture.xpm
WE $TEXTURE_DIR/west_texture.xpm
EA $TEXTURE_DIR/east_texture.xpm

F 100,50,50
C 50,100,150

111111111
100000001
101111101
101000101
101011101
1000000N1
111111111
EOF

echo "maze_map.cub 생성 완료"

cat << EOF > complex_map.cub
NO $TEXTURE_DIR/north_texture.xpm
SO $TEXTURE_DIR/south_texture.xpm
WE $TEXTURE_DIR/west_texture.xpm
EA $TEXTURE_DIR/east_texture.xpm

F 50,150,50
C 150,50,150

111111111111
100000000001
101110111101
101010001101
101011101101
101000001101
101111101101
1000000N0001
111111111111
EOF

echo "complex_map.cub 생성 완료"

cat << EOF > enclosed_space_map.cub
NO $TEXTURE_DIR/north_texture.xpm
SO $TEXTURE_DIR/south_texture.xpm
WE $TEXTURE_DIR/west_texture.xpm
EA $TEXTURE_DIR/east_texture.xpm

F 80,80,80
C 160,160,160

111111
1N0001
101011
101001
111111
EOF

cat << EOF > invalid_no_texture.cub
SO $TEXTURE_DIR/south_texture.xpm
WE $TEXTURE_DIR/west_texture.xpm
EA $TEXTURE_DIR/east_texture.xpm

F 220,100,0
C 135,206,250

111111
100001
1010N1
100001
111111
EOF

echo "invalid_no_texture.cub 생성 완료"

cat << EOF > invalid_open_map.cub
NO $TEXTURE_DIR/north_texture.xpm
SO $TEXTURE_DIR/south_texture.xpm
WE $TEXTURE_DIR/west_texture.xpm
EA $TEXTURE_DIR/east_texture.xpm

F 150,150,150
C 200,200,200

111111111111
100000000001
100000000001
10000N000001
100000000001
100000000001
111111111110
EOF

echo "invalid_open_map.cub 생성 완료"

cat << EOF > invalid_color_format.cub
NO $TEXTURE_DIR/north_texture.xpm
SO $TEXTURE_DIR/south_texture.xpm
WE $TEXTURE_DIR/west_texture.xpm
EA $TEXTURE_DIR/east_texture.xpm

F 220,100
C 135,206,250

111111
100001
1010N1
100001
111111
EOF

echo "invalid_color_format.cub 생성 완료"

echo "모든 맵 파일 생성 완료."
for MAP_FILE in "${MAP_FILES[@]}"
do
  echo "./cub3D $MAP_FILE"
done
