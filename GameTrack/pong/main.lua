--[[
    This is CS50 2020.
    Games Track
    Pong
]]

-- push is a library that will allow us to draw our games at a virtual
-- resolution, instead of however large our window is; used to provide
-- a more retro aesthetic
--
-- https://github.com/Ulydev/push
Class = require 'class'
push = require 'push'

require 'Ball'
require 'Paddle'

WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

PADDLE_SPEED = 100

--[[
    Runs when the game first starts up, only once; used to initialize the game
]]
function love.load()

    math.randomseed(os.time())

    -- use nearest-neighbor filtering on upscaling and downscaling to prevent blurring of text
    -- and grphics; try removing this function to see the difference!
    love.graphics.setDefaultFilter('nearest', 'nearest')

    love.window.setTitle('Pong')

    -- initialize our virtual recolution, which will be rendered withtin our
    -- actual window no matter its dimensions; replaces our love.window.setMode call
    -- from pong0
    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        vync = true,
        resizable = true
    })
    
    -- more "retro- looking font"
    smallFont = love.graphics.newFont('font.ttf', 8)
    scoreFont = love.graphics.newFont('font.ttf', 32)
    victoryFont = love.graphics.newFont('font.ttf', 24)

    sounds = {
        ['paddle_hit'] = love.audio.newSource('sounds/paddle_hit.wav', 'static'),
        ['score'] = love.audio.newSource('sounds/score.wav', 'static'),
        ['wall_hit'] = love.audio.newSource('sounds/wall_hit.wav', 'static')
    }

    -- initialize score variables, used for rendering on the screen and keeping
    -- track of the winner
    player1Score = 0
    player2Score = 0

    servingPlayer = math.random(2) == 1 and 1 or 2
    winningPlayer = 0

    --instatiate objects
    player1 = Paddle(5, 20, 5, 20)
    player2 = Paddle(VIRTUAL_WIDTH - 10, VIRTUAL_HEIGHT - 30, 5, 20)
    ball = Ball(VIRTUAL_WIDTH / 2 - 2, VIRTUAL_HEIGHT / 2 - 2, 4, 4)

    if servingPlayer == 1 then
        ball.dx = 100
    else
        ball.dx = -100
    end

    -- paddle positions on the Y axis ( they canonly move up or down)
    player1Y = 30
    player2Y = VIRTUAL_HEIGHT - 50

    gameState = 'start'
end

function love.resize(w, h)
    push:resize(w, h)
end

function love.update(dt)

    if gameState == 'play' then

        ball:update(dt)
        if ball.x <= 0 then
            player2Score = player2Score + 1
            sounds['score']:play()
            servingPlayer = 1
            ball:reset()
            ball.dx = 100
            gameState = 'serve'
            if player2Score >= 3 then
                gameState = 'victory'
                winningPlayer = 2
            else
                gameState = 'serve'
            end
        end

        if ball.x >= VIRTUAL_WIDTH - 4 then
            player1Score = player1Score + 1
            sounds['score']:play()
            servingPlayer = 2
            ball:reset()
            ball.dx = -100
            if player1Score >= 3 then
                gameState = 'victory'
                winningPlayer = 1
            else
                gameState = 'serve'
            end
        end

        if ball:collides(player1) then
            -- deflect ball to the right
            ball.dx = -ball.dx * 1.3
            ball.x = player1.x + 5

            sounds['paddle_hit']:play()

            if ball.dy < 0 then
                ball.dy = -math.random(10, 150)
            else
                ball.dy = math.random(10, 150)
            end
        end

        if ball:collides(player2) then
            -- deflect ball to the left
            ball.dx = -ball.dx * 1.3
            ball.x = player2.x - 5

            sounds['paddle_hit']:play()

            if ball.dy < 0 then
                ball.dy = -math.random(10, 150)
            else
                ball.dy = math.random(10, 150)
            end
        end

        -- ball hits the top of the screen
        if ball.y <= 0 then
            --defelct the ball down
            ball.dy = -ball.dy
            ball.y = 0

            sounds['wall_hit']:play()
        end

        -- ball hits the bottom of the screen
        if ball.y >= VIRTUAL_HEIGHT - 4 then
            -- deflect the ball up
            ball.dy = -ball.dy
            ball.y = VIRTUAL_HEIGHT - 4

            sounds['wall_hit']:play()
        end
    end
    
    -- player 1 paddle movement
    if love.keyboard.isDown('w') then

        player1.dy = -PADDLE_SPEED
    elseif love.keyboard.isDown('s') then

        player1.dy = PADDLE_SPEED
    else
        player1.dy = 0
    end

    --[[] player 2 paddle movement
    if love.keyboard.isDown('up') then

        player2.dy = -PADDLE_SPEED
    elseif love.keyboard.isDown('down') then

        player2.dy = PADDLE_SPEED
    else
        player2.dy = 0
    end
    ]]

    -- player 2 AI movement, GameTrack assignment
    if player2.y < ball.y + 2 and player2.y + 20 > ball.y + 2 then
        -- stay in spot
        player2.dy = 0
    elseif player2.y + 10 < ball.y + 2 then
        player2.dy = PADDLE_SPEED
    else
        player2.dy = -PADDLE_SPEED
    end

    player1:update(dt)
    player2:update(dt)
end

--[[
    Keyboard handling, called by Love each fram;
    passes in the key we pressed so we can access.
]]
function love.keypressed(key)
     
    -- keys can be accessed by string name
    if key == 'escape' then
        
        -- function Love gives us to terminate application
        love.event.quit()
    elseif key == 'enter' or key == 'return' then
        if gameState == 'start' then
            gameState = 'serve'
        elseif gameState == 'serve' then
            gameState = 'play'
        elseif gameState == 'victory' then
            gameState = 'start'
            player1Score = 0
            player2Score = 0
        end
    end
end
--[[
    Called after update by LOVE, used to draw anything to the screen,
     updated or otherwise.
]]
function love.draw()

    -- begin rednering at virtual resolution
    push:apply('start')

    -- set background colours
    love.graphics.clear(40/255, 45/255, 52/255, 255/255)

    ball:render()

    -- render the paddles
    player1:render()
    player2:render()

    displayFPS()
    displayScore()

    if gameState == 'start' then
        love.graphics.setFont(smallFont)
        love.graphics.printf("Welcome to Pong!", 0, 20, VIRTUAL_WIDTH, 'center')
        love.graphics.printf("Press Enter to Play!", 0, 32, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'serve' then
        love.graphics.setFont(smallFont)
        love.graphics.printf("Player " .. tostring(servingPlayer).. "'s turn!", 0, 20, VIRTUAL_WIDTH, 'center')
        love.graphics.printf("Press Enter to Serve", 0, 32, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'victory' then
        -- draw a victory message
        love.graphics.setFont(victoryFont)
        love.graphics.printf("Player " .. tostring(servingPlayer).. " wins!", 0, 10, VIRTUAL_WIDTH, 'center')
        love.graphics.setFont(smallFont)
        love.graphics.printf("Press Enter to Serve", 0, 42, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'play' then
        -- no UI messages to display in play
    end
    
    -- end rendering at virtual resolution
    push:apply('end')
end

function displayFPS()
    love.graphics.setColor(0, 1, 0, 1)
    love.graphics.setFont(smallFont)
    love.graphics.print('FPS: ' .. tostring(love.timer.getFPS()), 40, 20)
    love.graphics.setColor(1, 1, 1, 1)
end

function displayScore()

    love.graphics.setFont(scoreFont)
    love.graphics.print(player1Score, VIRTUAL_WIDTH / 2 - 50, VIRTUAL_HEIGHT / 3)
    love.graphics.print(player2Score, VIRTUAL_WIDTH / 2 + 30, VIRTUAL_HEIGHT / 3)
end
