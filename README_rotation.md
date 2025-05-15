MLX42 Library Usage -> I added all the functions I learned and used inside the README, take a look if you're interested :)

Data flow

mlx_init() -> mlx_new_image() -> mlx_image_to_window() -> mlx_loop()

Some critical features explained here :

Player Rotation System

I have an element inside the t_game struct, game->player_rot which reprensents the angle in radians (facing direction) :

0 radians: Facing right (positive X-axis).
π/2 radians: Facing up (negative Y-axis).
π radians: Facing left (negative X-axis).
3π/2 radians: Facing down (positive Y-axis).
So based on which key is pressed (left arrow/right arrow), game->player_rot will update on every frame :

-The left arrow subtracts from player_rot, rotating the player counter-clockwise. (eg from 0 to π/2->π etc)
-The right arrow adds to player_rot, rotating the player clockwise. (eg from 0 to 3π/2 to π).

Directional Line

So the direction will be visual on the map by a green line I draw pixel by pixel, which starts from the player's current position to the endpoint of the line.
How it's calculated :

endpoint = player_pos + (directional current angle * fixed co-rods where we want the line to stop) -> in our case it's PLAYER_RADIUS x 2 just for visibility.

That translates more like this :

end_x = px + (int)(cos(game->player_rot) * (PLAYER_RADIUS * 2));
end_y = py - (int)(sin(game->player_rot) * (PLAYER_RADIUS * 2));
Why the usage of cos/sin ?

cos(player_rot) determines the horizontal (X-axis) direction. ( eg cos(0) = 1 (right), cos(π) = -1 (left))
-sin(player_rot) determines the vertical (Y-axis) direction (the negative sign is because Y-axis is different in computers than in algebra : the window starts from (0.0) so the values in Y axis will start from negative and will increase as we move down through the window. (eg in aglebra sin(π/2) = 1 -> for the screen it needs to be -sin(π/2) = -1, that's facing UP)
Later, inside a loop, whenever the current position is not at the endpoint, the line is drawn pixel-by-pixel, incrementing/decrementing dx/dy (current position) until reaching end_x/end_y.

Timing refinment

I used a parameter I called "delta_time" because when using valgrind the player moves extremely slowly, but unfortunatly it didn't help there. What this ensures is making the movement/rotation independent from the FPS rate each machine can have, else they would be 100 % dependand of the FPS but this way it depends on the current_time the MLX has since it was initialized. "delta-time" is used to help scale the rotation speed/movement speed inside the relevant functions. I saw this somwhere as a good practice.

current_time = mlx_get_time();  
delta_time = current_time - game->last_frame;  // game->last_frame is inside t_game struct and is initialized when mlx is initialzed : game->last_frame = mlx_get_time();
game->last_frame = current_time;
All this is happening inside the rendering function which will affect the movement/rotation of the player in timings, thus making it smooth.

this is not important at all, but it was very easy and fast to implement!!
I added a config.h file like your idea was, having all the values we want to keep changing so we don't have to look inside the code every time. I hope you like it, and feel free to change/add any values for your tests !

I added a suppression file for valgrind called valgrind.supp, and it's already inside the rule in Makefile. A lot of the erros are duplicated inside the file (it has around 48k lines.....), because that's how they appeared in the valgrind error log, but I don't think that's important to fix.

Ongoing issues :

-Valgrind doesn't allow the player to move at all. It allows the circle to rotate with a lot of lag and the outcome isn't smooth. I am not sure if we care about this, because I don't think it's a requirement for the game to run smoothly on valgrind.
-Some weird file descriptors seem to be open when you close the game while using valgrind, but they seem to be VScode related.
