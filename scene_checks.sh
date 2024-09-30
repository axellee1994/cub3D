#! /bin/bash

export v_flags="valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes"

clear

echo -e "\033[0;31mTesting no input file\033[0m"
$v_flags ./cub3D
echo ""
echo ""

echo -e "\033[0;31mTesting multiple input files\033[0m"
$v_flags ./cub3D scenes/basic.cub scenes/basic.cub
echo ""
echo ""

echo -e "\033[0;31mTesting no file extension\033[0m"
$v_flags ./cub3D scenes/basic
echo ""
echo ""

echo -e "\033[0;31mTesting invalid file extension\033[0m"
$v_flags ./cub3D scenes/basic.ber
echo ""
echo ""

//echo -e "\033[0;31mTesting no file permissions\033[0m"
//$v_flags ./cub3D scenes/no_perm.cub
//echo ""
//echo ""

echo -e "\033[0;31mTesting no texture\033[0m"
$v_flags ./cub3D scenes/no_north.cub
echo ""
echo ""
$v_flags ./cub3D scenes/no_south.cub
echo ""
echo ""
$v_flags ./cub3D scenes/no_east.cub
echo ""
echo ""
$v_flags ./cub3D scenes/no_west.cub
echo ""
echo ""

echo -e "\033[0;31mTesting no texture file\033[0m"
$v_flags ./cub3D scenes/no_north_tex.cub
echo ""
echo ""
$v_flags ./cub3D scenes/no_south_tex.cub
echo ""
echo ""
$v_flags ./cub3D scenes/no_east_tex.cub
echo ""
echo ""
$v_flags ./cub3D scenes/no_west_tex.cub
echo ""
echo ""

echo -e "\033[0;31mTesting duplicate texture\033[0m"
$v_flags ./cub3D scenes/duplicate_north.cub
echo ""
echo ""
$v_flags ./cub3D scenes/duplicate_south.cub
echo ""
echo ""
$v_flags ./cub3D scenes/duplicate_east.cub
echo ""
echo ""
$v_flags ./cub3D scenes/duplicate_west.cub
echo ""
echo ""

echo -e "\033[0;31mTesting extra texture files\033[0m"
$v_flags ./cub3D scenes/extra_north.cub
echo ""
echo ""
$v_flags ./cub3D scenes/extra_south.cub
echo ""
echo ""
$v_flags ./cub3D scenes/extra_east.cub
echo ""
echo ""
$v_flags ./cub3D scenes/extra_west.cub
echo ""
echo ""

echo -e "\033[0;31mTesting invalid texture files\033[0m"
$v_flags ./cub3D scenes/invalid_north_tex.cub
echo ""
echo ""
$v_flags ./cub3D scenes/invalid_south_tex.cub
echo ""
echo ""
$v_flags ./cub3D scenes/invalid_east_tex.cub
echo ""
echo ""
$v_flags ./cub3D scenes/invalid_west_tex.cub
echo ""
echo ""

echo -e "\033[0;31mTesting invalid floor/ceiling\033[0m"
$v_flags ./cub3D scenes/invalid_floor.cub
echo ""
echo ""
$v_flags ./cub3D scenes/invalid_ceiling.cub
echo ""
echo ""

echo -e "\033[0;31mTesting empty line\033[0m"
$v_flags ./cub3D scenes/empty_line_middle.cub
echo ""
echo ""
$v_flags ./cub3D scenes/empty_line_end.cub
echo ""
echo ""

echo -e "\033[0;31mTesting multiple player start\033[0m"
$v_flags ./cub3D scenes/multi_player_different_direction.cub
echo ""
echo ""
$v_flags ./cub3D scenes/multi_player_same_direction.cub
echo ""
echo ""

echo -e "\033[0;31mTesting read-only .cub file\033[0m"
chmod 444 scenes/read_only.cub
$v_flags ./cub3D scenes/read_only.cub
chmod 644 scenes/read_only.cub
echo ""
echo ""

echo -e "\033[0;31mTesting very large .cub file\033[0m"
$v_flags ./cub3D scenes/large_map.cub
echo ""
echo ""

echo -e "\033[0;31mTesting invalid characters in map\033[0m"
$v_flags ./cub3D scenes/invalid_characters.cub
echo ""
echo ""

echo -e "\033[0;31mTesting unclosed map\033[0m"
$v_flags ./cub3D scenes/unclosed_map.cub
echo ""
echo ""

echo -e "\033[0;31mTesting edge cases for color values\033[0m"
$v_flags ./cub3D scenes/color_edge_cases.cub
echo ""
echo ""

echo -e "\033[0;31mTesting invalid map sizes\033[0m"
$v_flags ./cub3D scenes/one_line_map.cub
echo ""
echo ""

unset v_flags