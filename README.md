# C++-Template-Discord-Spotify-Tracker

This code is very complex and requires extensive set up before running. The code I've created is merely the template. The purpose is so that when you run it, the user you want to track their spotify activity for 1 hour, the tracks they've listened to will be saved in a list on a spreadsheet file on your desktop. The code will do this by tracking their sptofy activity that shows up on discord. For security purposes you will need to set up the bot individually for the user you want to track every time before running

Step 1: Set Up a Discord Bot and Get Token
Go to the Discord Developer Portal and create a new application.

Create a bot for your application and copy the bot token.
Step 2: Set Up OAuth2 for Your Bot
In the Discord Developer Portal, go to the "OAuth2" tab.
Under "OAuth2 URL Generator," select the bot and applications.commands scopes.

Add the following permissions: user-read-currently-playing and user-read-playback-state.
Copy the generated OAuth2 URL and visit it in your browser to invite the bot to your server.

Step 3: C++ Code for OAuth2 Authentication and Fetching Spotify Activity
Using cpprestsdk for OAuth2:
Install cpprestsdk using your system's package manager or download it.

# After the above steps make sure to then change the place holders in the code to fit the user you want to track and saving the files to your personal computer's user details. The bot should be set up for the user you want to track.
