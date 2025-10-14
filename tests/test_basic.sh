#!/bin/bash

# Basic IRC server test script
# This script tests basic functionality of the IRC server

echo "🧪 Starting IRC Server Tests..."

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test configuration
PORT=6667
PASSWORD="testpass"
SERVER_LOG="server_test.log"

# Function to print colored output
print_test() {
    echo -e "${BLUE}[TEST]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[PASS]${NC} $1"
}

print_fail() {
    echo -e "${RED}[FAIL]${NC} $1"
}

print_info() {
    echo -e "${YELLOW}[INFO]${NC} $1"
}

# Check if server binary exists
if [ ! -f "./ircserv" ]; then
    print_fail "Server binary './ircserv' not found. Please run 'make' first."
    exit 1
fi

print_info "Starting IRC server on port $PORT with password '$PASSWORD'"

# Start the server in background
./ircserv $PORT $PASSWORD > $SERVER_LOG 2>&1 &
SERVER_PID=$!

# Give server time to start
sleep 2

# Check if server is running
if ! kill -0 $SERVER_PID 2>/dev/null; then
    print_fail "Server failed to start"
    cat $SERVER_LOG
    exit 1
fi

print_success "Server started successfully (PID: $SERVER_PID)"

# Test 1: Basic connection
print_test "Testing basic connection..."
{
    echo "PASS $PASSWORD"
    echo "NICK testuser"
    echo "USER testuser 0 * :Test User"
    echo "QUIT :Testing"
    sleep 1
} | nc localhost $PORT > /dev/null 2>&1

if [ $? -eq 0 ]; then
    print_success "Basic connection test passed"
else
    print_fail "Basic connection test failed"
fi

# Test 2: Invalid password
print_test "Testing invalid password..."
{
    echo "PASS wrongpass"
    echo "NICK testuser"
    echo "USER testuser 0 * :Test User"
    echo "QUIT :Testing"
    sleep 1
} | nc localhost $PORT > /dev/null 2>&1

# Test 3: Channel operations
print_test "Testing channel operations..."
{
    echo "PASS $PASSWORD"
    echo "NICK channeltest"
    echo "USER channeltest 0 * :Channel Test User"
    echo "JOIN #testchannel"
    echo "PRIVMSG #testchannel :Hello channel!"
    echo "PART #testchannel :Leaving"
    echo "QUIT :Testing complete"
    sleep 2
} | nc localhost $PORT > /dev/null 2>&1

if [ $? -eq 0 ]; then
    print_success "Channel operations test passed"
else
    print_fail "Channel operations test failed"
fi

# Test 4: Multiple clients simulation
print_test "Testing multiple clients..."

# Start client 1
{
    echo "PASS $PASSWORD"
    echo "NICK user1"
    echo "USER user1 0 * :User One"
    echo "JOIN #multiclient"
    sleep 3
    echo "PRIVMSG #multiclient :Hello from user1"
    sleep 2
    echo "QUIT :User1 leaving"
} | nc localhost $PORT > /dev/null 2>&1 &
CLIENT1_PID=$!

# Start client 2
{
    sleep 1
    echo "PASS $PASSWORD"
    echo "NICK user2"
    echo "USER user2 0 * :User Two"
    echo "JOIN #multiclient"
    sleep 2
    echo "PRIVMSG #multiclient :Hello from user2"
    sleep 2
    echo "QUIT :User2 leaving"
} | nc localhost $PORT > /dev/null 2>&1 &
CLIENT2_PID=$!

# Wait for clients to finish
wait $CLIENT1_PID
wait $CLIENT2_PID

print_success "Multiple clients test completed"

# Test 5: Ping/Pong
print_test "Testing PING/PONG..."
{
    echo "PASS $PASSWORD"
    echo "NICK pingtest"
    echo "USER pingtest 0 * :Ping Test User"
    echo "PING :test"
    sleep 1
    echo "QUIT :Ping test done"
} | nc localhost $PORT > /dev/null 2>&1

if [ $? -eq 0 ]; then
    print_success "PING/PONG test passed"
else
    print_fail "PING/PONG test failed"
fi

# Clean up
print_info "Stopping server..."
kill $SERVER_PID 2>/dev/null
wait $SERVER_PID 2>/dev/null

print_info "Cleaning up..."
rm -f $SERVER_LOG

echo ""
print_success "All tests completed!"
print_info "You can also test manually using:"
print_info "  ./ircserv 6667 password"
print_info "  Then connect with: nc localhost 6667"
print_info "  Or use an IRC client like irssi, HexChat, etc."
