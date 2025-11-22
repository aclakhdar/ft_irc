# 🚀 Complete IRC Server Commands Practice Guide

Welcome to your comprehensive practice guide for the MaverickIRC server! This guide will walk you through all available commands step-by-step.

## 📋 Table of Contents
1. [Server Setup](#server-setup)
2. [Authentication Commands](#authentication-commands)
3. [Channel Commands](#channel-commands)
4. [Communication Commands](#communication-commands)
5. [Channel Management Commands](#channel-management-commands)
6. [MaverickBot Guide](#maverickbot-guide)
7. [Complete Practice Scenarios](#complete-practice-scenarios)

---

## 🔧 Server Setup

### Start the Server
```bash
# Compile the server
make

# Start server on port 6667 with password "mypass"
./ircserv 6667 mypass
```

### Connect with Multiple Clients
Open multiple terminal windows and connect:
```bash
# Terminal 1 (Client A)
nc localhost 6667

# Terminal 2 (Client B) 
nc localhost 6667

# Terminal 3 (Client C)
nc localhost 6667
```

---

## 🔐 Authentication Commands

**⚠️ IMPORTANT: You must complete these steps in order before using any other commands!**

### 1. PASS - Server Password
```bash
PASS mypass
```
**Expected Response:** `✅ Password correct!`

### 2. NICK - Set Nickname
```bash
NICK Alice
```
**Expected Response:** `:!@localhost NICK Alice`

**Practice Variations:**
```bash
# Try invalid nicknames to see errors:
NICK Alice Bob          # Error: contains space
NICK VeryLongNickname   # Error: too long (>9 chars)
NICK Al!ce             # Error: invalid characters
NICK Alice             # Error: nickname already taken (if used)
```

### 3. USER - Set User Information
```bash
USER alice localhost localhost :Alice Smith
```
**Expected Response:** Welcome messages from server + bot welcome

**Format:** `USER <username> <hostname> <servername> :<realname>`

---

## 🏠 Channel Commands

### JOIN - Create/Join Channels

**Create New Channel (becomes operator):**
```bash
JOIN #general
```
**Expected:** `👑 Alice is now operator of #general`

**Try to Join Existing Channel:**
```bash
JOIN #general
```
**Expected:** `Cannot join channel (+i)` (invite-only by default)

**Practice Scenarios:**
```bash
JOIN #help
JOIN #random
JOIN #dev
JOIN invelalidchann    # Error: must start with #
```

### PART - Leave Channels

**Leave with message:**
```bash
PART #general :Goodbye everyone!
```

**Leave without message:**
```bash
PART #general
```

---

## 💬 Communication Commands

### PRIVMSG - Send Messages

**Send to Channel:**
```bash
PRIVMSG #general :Hello everyone in the channel!
```

**Send to User (Direct Message):**
```bash
PRIVMSG Alice :Hi Alice, this is a private message
```

**Practice Messages:**
```bash
PRIVMSG #general :This is a test message
PRIVMSG #general :How is everyone doing?
PRIVMSG MaverickBot :Hello bot!
```

### 🤖 Bot Interaction

The server has a built-in bot `MaverickBot` that provides interactive features and entertainment!

**Basic Bot Commands:**
```bash
PRIVMSG MaverickBot :help      # Show all available commands
PRIVMSG MaverickBot :hello     # Greet the bot
PRIVMSG MaverickBot :joke      # Get a random programming joke
PRIVMSG MaverickBot :tip       # Get a helpful IRC tip
PRIVMSG MaverickBot :time      # Get current server time
PRIVMSG MaverickBot :stats     # Get server statistics
PRIVMSG MaverickBot :weather   # Ask about weather (fun response!)
PRIVMSG MaverickBot :thanks    # Thank the bot
```

**Channel Interaction:**
The bot also responds when mentioned in channels:
```bash
# In a channel, mention the bot's name
PRIVMSG #test :MaverickBot hello
PRIVMSG #general :MaverickBot tell me a joke
PRIVMSG #general :MaverickBot what time is it?
```

**Bot Features:**
- 🎭 **Random Jokes:** Programming-themed humor to lighten the mood
- 💡 **IRC Tips:** Helpful suggestions for using IRC commands
- ⏰ **Time Service:** Current server timestamp
- 📊 **Server Stats:** Information about server status
- 🎯 **Smart Detection:** Only responds when mentioned by name
- 🌈 **Colorful Responses:** Bot messages appear in yellow
- 👋 **Auto-Welcome:** Greets new users automatically

**Sample Bot Conversation:**
```bash
# You
PRIVMSG MaverickBot :hello

# MaverickBot responds
:MaverickBot!bot@localhost PRIVMSG YourNick :Hello there! 👋 How can I help you today?

# You  
PRIVMSG MaverickBot :joke

# MaverickBot responds
:MaverickBot!bot@localhost PRIVMSG YourNick :Why do programmers prefer dark mode? Because light attracts bugs! 🐛
```

---

## 👑 Channel Management Commands

**⚠️ Note: Most of these require operator privileges!**

### TOPIC - Channel Topics

**View Current Topic:**
```bash
TOPIC #general
```

**Set New Topic (operators only):**
```bash
TOPIC #general :Welcome to our general discussion channel!
```

### INVITE - Invite Users to Channels

**Invite Someone:**
```bash
INVITE Bob #general
```
**Note:** Bob can now join the invite-only channel.

### KICK - Remove Users from Channels

**Kick with Reason:**
```bash
KICK #general Bob :Spamming the channel
```

**Kick without Reason:**
```bash
KICK #general Bob
```

### MODE - Change Channel Settings

**Make Channel Public (remove invite-only):**
```bash
MODE #general -i
```

**Make Channel Invite-Only:**
```bash
MODE #general +i
```

**Set User Limit:**
```bash
MODE #general +l 10
```

**Remove User Limit:**
```bash
MODE #general -l
```

**Give/Remove Operator Status:**
```bash
MODE #general +o Bob    # Make Bob an operator
MODE #general -o Bob    # Remove Bob's operator status
```

**Set Channel Password:**
```bash
MODE #general +k secretkey
```

**Remove Channel Password:**
```bash
MODE #general -k
```

**Restrict Topic Changes to Operators:**
```bash
MODE #general +t
```

**Allow Anyone to Change Topic:**
```bash
MODE #general -t
```

---

## 🤖 MaverickBot Guide

Your IRC server comes with an intelligent built-in bot called **MaverickBot**! It's automatically active and ready to interact with users.

### 🚀 Getting Started with MaverickBot

**Automatic Features:**
- ✅ **Auto-Welcome:** New users receive a friendly welcome message
- ✅ **Always Online:** Available 24/7 while the server runs  
- ✅ **No Setup Required:** Ready to use immediately
- ✅ **Multi-Channel:** Works in all channels and private messages

### 📝 Complete Command Reference

| Command | Response | Example |
|---------|----------|---------|
| `hello` / `hi` | Friendly greeting | "Hello there! 👋 How can I help you today?" |
| `help` | Shows all commands | Complete command list |
| `joke` | Random programming joke | "Why do programmers prefer dark mode? Because light attracts bugs! 🐛" |
| `tip` | IRC usage tip | "💡 Tip: Use /join #channel to join a channel!" |
| `time` | Current server time | "Current server time: [timestamp] ⏰" |
| `stats` | Server statistics | "📊 Server Stats: Uptime: Running smoothly!" |
| `weather` | Fun weather response | "I wish I could check the weather, but I'm just a simple IRC bot! ☀️" |
| `thanks` / `thank you` | Appreciation response | "You're welcome! Happy to help! 😄" |
| `bye` / `quit` | Farewell message | "Goodbye! See you later! 👋" |

### 🎯 How to Use MaverickBot

#### Method 1: Private Messages
```bash
# Direct private message to the bot
PRIVMSG MaverickBot :help
PRIVMSG MaverickBot :tell me a joke
PRIVMSG MaverickBot :what time is it?
```

#### Method 2: Channel Mentions
```bash
# In any channel, mention the bot's name
PRIVMSG #general :MaverickBot hello everyone!
PRIVMSG #help :MaverickBot can you help me?
PRIVMSG #random :MaverickBot joke
```

### 🎪 Interactive Bot Scenarios

**Scenario 1: Getting Help**
```bash
# You join a channel and need assistance
JOIN #general
PRIVMSG #general :MaverickBot help

# MaverickBot responds with full command list
# Try specific commands:
PRIVMSG #general :MaverickBot tip
```

**Scenario 2: Entertainment Break**
```bash
# Need some humor during development
PRIVMSG MaverickBot :joke
# Bot tells a programming joke

PRIVMSG MaverickBot :another joke please
# Bot provides another random joke
```

**Scenario 3: Server Information**
```bash
# Check server status and time
PRIVMSG MaverickBot :stats
PRIVMSG MaverickBot :time

# Bot provides current information
```

### 🎨 Bot Response Examples

**Welcome Message (automatic for new users):**
```
:MaverickBot!bot@localhost PRIVMSG Alice :Welcome to the server, Alice! 🎉 I'm MaverickBot, your friendly IRC bot! Type 'help' to see what I can do, or just say 'hello'! 😊
```

**Help Command Response:**
```
:MaverickBot!bot@localhost PRIVMSG Alice :🤖 MaverickBot Commands:
• 'hello/hi' - Greet the bot
• 'help' - Show this help message  
• 'time' - Get current server time
• 'joke' - Get a random programming joke
• 'tip' - Get a random IRC tip
• 'weather' - Ask about weather (just for fun!)
• 'thanks' - Thank the bot
• 'stats' - Get server statistics
Just mention my name or send me a private message!
```

**Sample Jokes (random selection):**
- "Why do Java developers wear glasses? Because they can't C#! 👓"
- "How many programmers does it take to change a lightbulb? None, that's a hardware problem! 💡"
- "What's a programmer's favorite hangout place? The Foo Bar! 🍺"

**Sample Tips (random selection):**
- "💡 Tip: Use /join #channel to join a channel!"
- "💡 Tip: Use /nick newname to change your nickname!"  
- "💡 Tip: Use /privmsg username message to send a private message!"

### 🔍 Bot Behavior Details

**Smart Recognition:**
- Bot only responds when its name "MaverickBot" is mentioned
- Case-insensitive detection (works with "maverickbot", "MAVERICKBOT", etc.)
- Ignores messages that don't mention it (won't spam channels)

**Response Format:**
- All bot responses are prefixed with the user's nickname
- Bot messages appear in yellow color for easy identification  
- Uses emojis and friendly language for better user experience

**Default Responses:**
If the bot doesn't recognize a command, it provides helpful fallback responses:
- "I didn't quite understand that. Try 'help' for commands! 🤔"
- "Hmm, that's interesting! Tell me more! 🤨"
- "I'm not sure about that. Type 'help' to see what I can do! 🤖"

### 🎲 Fun Bot Challenges

1. **Bot Conversation:** Try having a full conversation with MaverickBot
2. **Joke Collection:** Get 5 different jokes from the bot  
3. **Channel Entertainment:** Use the bot to entertain users in different channels
4. **Help Guide:** Use bot tips to learn new IRC commands
5. **Time Keeper:** Use the bot as a server time reference

### 💡 Pro Tips for Bot Usage

- **Be Natural:** Talk to the bot like a friend - it understands casual language
- **Mix Commands:** Combine bot interaction with regular IRC usage
- **Share Jokes:** Use bot jokes to lighten the mood in channels
- **Learn IRC:** Bot tips are great for learning IRC commands
- **Welcome Tool:** Bot automatically welcomes new users - great for community building

---

## 🎯 Complete Practice Scenarios

### Scenario 1: Basic Server Usage
```bash
# Terminal 1 (Alice)
PASS mypass
NICK Alice
USER alice localhost localhost :Alice Smith
JOIN #welcome
TOPIC #welcome :Welcome to our IRC server!
PRIVMSG #welcome :Hello everyone!

# Terminal 2 (Bob) 
PASS mypass
NICK Bob  
USER bob localhost localhost :Bob Jones
JOIN #welcome           # This will fail (invite-only)

# Back to Terminal 1 (Alice)
INVITE Bob #welcome     # Alice invites Bob

# Back to Terminal 2 (Bob)
JOIN #welcome           # Now succeeds
PRIVMSG #welcome :Thanks for the invite Alice!
```

### Scenario 2: Channel Management Practice
```bash
# Alice (operator) creates and manages channel
JOIN #gameroom
TOPIC #gameroom :Gaming discussions and tournaments
MODE #gameroom +l 5     # Set user limit to 5
MODE #gameroom -i       # Make it public temporarily
INVITE Bob #gameroom
INVITE Charlie #gameroom

# When Bob joins
# Alice can practice operator commands
MODE #gameroom +o Bob   # Make Bob co-operator
KICK #gameroom Charlie :Breaking rules
MODE #gameroom +i       # Make invite-only again
```

### Scenario 3: Multi-Channel Usage
```bash
# Create multiple channels for different purposes
JOIN #general
JOIN #help
JOIN #random

# Set different topics
TOPIC #general :General discussions
TOPIC #help :Ask questions here  
TOPIC #random :Random chat and fun

# Practice switching between channels
PRIVMSG #general :Hello general channel
PRIVMSG #help :Anyone know how to use MODE?
PRIVMSG #random :What's everyone up to?

# Leave some channels
PART #random :Too busy for random chat
```

### Scenario 4: Advanced Channel Modes
```bash
# Create a private channel with password
JOIN #secret
MODE #secret +k password123
MODE #secret +i
MODE #secret +t
TOPIC #secret :Top secret discussions only!

# Invite specific users
INVITE TrustedUser #secret

# Test all mode combinations
MODE #secret +l 3       # Max 3 users
MODE #secret            # View current modes
MODE #secret -k         # Remove password
MODE #secret -i -t -l   # Remove all restrictions
```

### Scenario 5: MaverickBot Interaction Practice
```bash
# Complete bot interaction workflow
PASS mypass
NICK TestUser
USER testuser localhost localhost :Test User

# Bot automatically welcomes you!
# Try private bot conversation
PRIVMSG MaverickBot :hello
PRIVMSG MaverickBot :help
PRIVMSG MaverickBot :joke
PRIVMSG MaverickBot :tip
PRIVMSG MaverickBot :time
PRIVMSG MaverickBot :stats
PRIVMSG MaverickBot :thanks

# Join channel and use bot publicly
JOIN #bottest
PRIVMSG #bottest :MaverickBot hello everyone!
PRIVMSG #bottest :MaverickBot tell us a joke
PRIVMSG #bottest :MaverickBot what time is it?

# Test bot's smart detection
PRIVMSG #bottest :This message doesn't mention the bot
# (Bot won't respond - good!)

PRIVMSG #bottest :Hey MaverickBot, how are you?
# (Bot will respond - smart detection!)
```

---

## 🐛 Error Testing Practice

Try these commands to understand error handling:

```bash
# Before authentication
JOIN #test              # Should fail - not registered

# After partial authentication  
PASS mypass
JOIN #test              # Should fail - need NICK and USER

# Invalid commands
BLAH #test              # Unknown command
JOIN                    # Missing parameters
PRIVMSG                 # Missing parameters
KICK #test              # Need target user
MODE                    # Missing parameters

# Permission errors (as non-operator)
KICK #someones_channel SomeUser    # Not operator
TOPIC #someones_channel :New topic  # Topic restricted
MODE #someones_channel +i          # Not operator
```

---

## 📝 Quick Reference Card

| Command | Syntax | Purpose |
|---------|--------|---------|
| `PASS` | `PASS <password>` | Authenticate to server |
| `NICK` | `NICK <nickname>` | Set your nickname |  
| `USER` | `USER <user> <host> <server> :<real>` | Set user info |
| `JOIN` | `JOIN #channel` | Join/create channel |
| `PART` | `PART #channel [:reason]` | Leave channel |
| `PRIVMSG` | `PRIVMSG <target> :<message>` | Send message |
| `TOPIC` | `TOPIC #channel [:new_topic]` | View/set topic |
| `INVITE` | `INVITE <nick> #channel` | Invite user |
| `KICK` | `KICK #channel <nick> [:reason]` | Remove user |
| `MODE` | `MODE #channel [+/-flags] [params]` | Change channel settings |

### Mode Flags Reference
- `+i/-i` : Invite-only mode
- `+t/-t` : Topic restriction  
- `+k/-k <key>` : Channel password
- `+l/-l <limit>` : User limit
- `+o/-o <nick>` : Operator status

---

## 🎮 Fun Practice Challenges

1. **Channel Creator Challenge:** Create 5 different channels with unique topics
2. **Mode Master:** Practice every MODE flag combination
3. **Communication Test:** Send messages to channels, users, and the bot
4. **Management Simulation:** Invite users, kick troublemakers, manage topics
5. **Multi-Client Coordination:** Use 3+ terminals to simulate real IRC usage

---

## 🚨 Common Mistakes to Avoid

1. ❌ Trying to use commands before completing PASS → NICK → USER sequence
2. ❌ Forgetting the `#` prefix for channel names
3. ❌ Forgetting the `:` prefix for message text in PRIVMSG and TOPIC
4. ❌ Trying to use operator commands without operator privileges
5. ❌ Using spaces in nicknames (use underscores instead)

---

## ✅ Success Indicators

You'll know you're using the commands correctly when you see:
- ✅ Welcome messages after USER command
- 👑 Operator status when creating channels
- 📝 Topic change notifications
- 🤖 Bot responses and welcome messages
- Proper error messages for invalid operations

Happy practicing! 🎉
