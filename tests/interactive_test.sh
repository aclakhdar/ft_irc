#!/bin/bash

# Interactive IRC client simulator for testing
# Usage: ./interactive_test.sh [port] [password]

PORT=${1:-6667}
PASSWORD=${2:-password}

echo "🔌 IRC Interactive Test Client"
echo "Connecting to localhost:$PORT with password: $PASSWORD"
echo ""
echo "Commands you can test:"
echo "  PASS $PASSWORD"
echo "  NICK yournickname"
echo "  USER username 0 * :Your Real Name"
echo "  JOIN #channelname"
echo "  PRIVMSG #channelname :Your message"
echo "  PRIVMSG nickname :Private message"
echo "  PART #channelname :Reason"
echo "  QUIT :Goodbye message"
echo ""
echo "Press Ctrl+C to disconnect"
echo "----------------------------------------"

# Check if server is running
if ! nc -z localhost $PORT 2>/dev/null; then
    echo "❌ Cannot connect to server on localhost:$PORT"
    echo "Make sure the server is running: ./ircserv $PORT $PASSWORD"
    exit 1
fi

# Start interactive session
nc localhost $PORT
