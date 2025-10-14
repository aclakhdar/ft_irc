#!/bin/bash

# Load testing script for IRC server
# Tests the server with multiple simultaneous connections

PORT=${1:-6667}
PASSWORD=${2:-password}
NUM_CLIENTS=${3:-10}
DURATION=${4:-30}

echo "🚀 IRC Server Load Test"
echo "Port: $PORT"
echo "Password: $PASSWORD"
echo "Clients: $NUM_CLIENTS"
echo "Duration: ${DURATION}s"
echo ""

# Check if server is running
if ! nc -z localhost $PORT 2>/dev/null; then
    echo "❌ Cannot connect to server on localhost:$PORT"
    echo "Make sure the server is running: ./ircserv $PORT $PASSWORD"
    exit 1
fi

echo "Starting load test..."

# Function to simulate a client
simulate_client() {
    local client_id=$1
    local nick="client$client_id"

    {
        echo "PASS $PASSWORD"
        echo "NICK $nick"
        echo "USER $nick 0 * :Load Test Client $client_id"
        echo "JOIN #loadtest"

        # Send messages periodically
        for i in $(seq 1 $((DURATION / 5))); do
            echo "PRIVMSG #loadtest :Message $i from $nick"
            sleep 5
        done

        echo "PART #loadtest :Load test complete"
        echo "QUIT :Load test finished"
    } | nc localhost $PORT > /dev/null 2>&1 &
}

# Start all clients
for i in $(seq 1 $NUM_CLIENTS); do
    simulate_client $i
    echo "Started client $i"
    sleep 0.1  # Small delay between client starts
done

echo "All clients started. Running for ${DURATION} seconds..."

# Wait for test duration
sleep $DURATION

echo "Load test completed!"
echo "Check server logs for any errors or issues."
